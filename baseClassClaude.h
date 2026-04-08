#ifndef __BaseClass__
#define __BaseClass__


#pragma once
#include "policies.hpp"
#include "constraints.hpp"
#include "fn_traits.hpp"
#include "handles.hpp"

namespace refl {

template<typename Derived, Policy... Policies>
class baseClass : private PolicyConstraints<Policies...> {

    using PS = PolicySet<Policies...>;

    // ── Feature flags ─────────────────────────────────────────────────────────
    static constexpr bool has_signals       = PS::template has<ipc_signals>;
    static constexpr bool has_unix_socket   = PS::template has<ipc_unix_socket>;
    static constexpr bool has_shm           = PS::template has<ipc_shared_memory>;
    static constexpr bool has_dbus          = PS::template has<ipc_dbus>;

    static constexpr bool has_properties    = PS::template has<data_properties>;
    static constexpr bool has_change_notify = PS::template has<data_change_notify>;
    static constexpr bool has_undo          = PS::template has<data_undo_stack>;
    static constexpr bool has_serial        = PS::template has<data_serializable>;

    static constexpr bool has_meta          = PS::template has<refl_meta>;
    static constexpr bool has_scriptable    = PS::template has<refl_scriptable>;
    static constexpr bool has_inspectable   = PS::template has<refl_inspectable>;
    static constexpr bool has_versioned     = PS::template has<refl_versioned>;

    static constexpr bool has_timer         = PS::template has<sys_timer>;
    static constexpr bool has_evloop        = PS::template has<sys_event_loop>;
    static constexpr bool has_gpu           = PS::template has<sys_gpu_resource>;
    static constexpr bool has_power         = PS::template has<sys_power>;

    static constexpr bool has_render_gui    = PS::template has<render_gui>;
    static constexpr bool has_render_term   = PS::template has<render_terminal>;

    static constexpr bool has_file          = PS::template has<file_config>
                                           || PS::template has<file_asset>
                                           || PS::template has<file_directory>
                                           || PS::template has<file_log>
                                           || PS::template has<file_socket>;

    static constexpr bool has_net           = PS::template has<net_http>
                                           || PS::template has<net_mqtt>
                                           || PS::template has<net_peer>
                                           || PS::template has<net_mdns>;

    static constexpr bool has_lifecycle     = PS::template has<lifecycle_singleton>
                                           || PS::template has<lifecycle_pooled>
                                           || PS::template has<lifecycle_managed>
                                           || PS::template has<lifecycle_persistent>;

    static constexpr bool thread_safe       = PS::template has<impl_thread_safe>;

    // ── CRTP downcast ─────────────────────────────────────────────────────────
    Derived&       self()       { return static_cast<Derived&>(*this); }
    const Derived& self() const { return static_cast<const Derived&>(*this); }

public:
    // ── No copy — Qt semantics ────────────────────────────────────────────────
    ReflObject(const ReflObject&)            = delete;
    ReflObject& operator=(const ReflObject&) = delete;
    ReflObject(ReflObject&&)                 = default;
    ReflObject& operator=(ReflObject&&)      = default;
    virtual ~ReflObject()                    = default;

    // ── Construction ──────────────────────────────────────────────────────────
    explicit ReflObject() {
        if constexpr (has_signals)
            m_signals.resize(Derived::N_SIGNALS);
        if constexpr (has_meta)
            m_meta = MetaTable(Derived::__class_name);
        if constexpr (has_file)
            m_file = FileHandle(Derived::__file_path);
    }

    // =========================================================================
    // IPC — Signals
    // =========================================================================

    template<auto SignalPtr, typename... Args>
    requires has_signals
    void emit_signal(Args&&... args) {
        constexpr size_t idx = Derived::template signal_index<SignalPtr>();
        static_assert(idx < Derived::N_SIGNALS, "signal index out of range");

        auto packed = FnTraits<decltype(SignalPtr)>::pack(std::forward<Args>(args)...);
        m_signals.emit(idx, packed.data(), packed.size());
    }

    // Connect to a member slot on another ReflObject-derived receiver
    template<auto SignalPtr, typename ReceiverDerived, auto SlotPtr>
    requires has_signals && CompatibleSignature<SignalPtr, SlotPtr>
    void connect(ReceiverDerived& receiver) {
        constexpr size_t idx = Derived::template signal_index<SignalPtr>();
        using Traits = FnTraits<decltype(SlotPtr)>;

        m_signals.connect(idx, {
            idx,
            [&receiver](const std::any* args, size_t) {
                Traits::template invoke<SlotPtr>(receiver, args);
            }
        });
    }

    // Connect to a callable (lambda, free function)
    template<auto SignalPtr, typename Callable>
    requires has_signals
    void connect(Callable&& fn) {
        constexpr size_t idx = Derived::template signal_index<SignalPtr>();
        m_signals.connect(idx, {
            idx,
            [f = std::forward<Callable>(fn)](const std::any*, size_t) { f(); }
        });
    }

    void disconnect(size_t signal_idx)
    requires has_signals {
        m_signals.disconnect(signal_idx);
    }

    // =========================================================================
    // Data Model — Properties
    // =========================================================================

    // Compile-time index access — zero overhead, no map lookup
    template<size_t Idx>
    requires has_properties
    auto get() const {
        return Derived::template property_get<Idx>(self());
    }

    template<size_t Idx, typename V>
    requires has_properties
    void set(V&& val) {
        if constexpr (has_change_notify) {
            auto old = get<Idx>();
            Derived::template property_set<Idx, V>(self(), std::forward<V>(val));
            m_changelog.record(
                std::string(Derived::template property_name<Idx>()),
                std::any(old),
                std::any(get<Idx>()));
        } else {
            Derived::template property_set<Idx, V>(self(), std::forward<V>(val));
        }
    }

    // Runtime string access — scripting/QML bridge
    std::any get_dynamic(std::string_view name) const
    requires has_properties {
        return m_properties.get(&self(), name);
    }

    void set_dynamic(std::string_view name, std::any val)
    requires has_properties {
        m_properties.set(&self(), name, std::move(val));
    }

    const ChangeLog& changelog() const requires has_change_notify { return m_changelog; }
    void             clear_changelog()  requires has_change_notify { m_changelog.clear(); }

    void undo() requires has_undo { m_undo.undo(); }
    void redo() requires has_undo { m_undo.redo(); }

    // =========================================================================
    // Reflection — Meta
    // =========================================================================

    static constexpr std::string_view class_name()
    requires has_meta {
        return Derived::__class_name;
    }

    std::any invoke(std::string_view method, std::span<std::any> args)
    requires has_meta {
        return m_meta.invoke(&self(), method, args);
    }

    void register_method(std::string name, MetaTable::Invoker inv)
    requires has_meta {
        m_meta.register_method(std::move(name), std::move(inv));
    }

    const ScriptBridge& script_bridge() const requires has_scriptable { return m_script; }

    uint32_t schema_version() const requires has_versioned { return m_file.schema_version; }

    // =========================================================================
    // System
    // =========================================================================

    void start_timer(uint64_t interval_ns)
    requires has_timer { m_timer.start(interval_ns); }

    void stop_timer()
    requires has_timer { m_timer.stop(); }

    bool timer_running() const
    requires has_timer { return m_timer.running; }

    EventLoopHandle& event_loop()
    requires has_evloop { return m_evloop; }

    // =========================================================================
    // Render — GUI
    // =========================================================================

    void set_geometry(int x, int y, int w, int h)
    requires has_render_gui {
        m_gui.geometry = {x, y, w, h};
        m_gui.mark_dirty();
        self().on_geometry_changed(m_gui.geometry);
    }

    const Rect& geometry() const requires has_render_gui { return m_gui.geometry; }

    void set_visible(bool v)
    requires has_render_gui { m_gui.visible = v; m_gui.mark_dirty(); }

    void set_opacity(float o)
    requires has_render_gui { m_gui.opacity = o; m_gui.mark_dirty(); }

    bool is_dirty() const requires has_render_gui { return m_gui.dirty; }

    void paint()
    requires has_render_gui {
        if (!m_gui.visible) return;
        self().render_gui_impl(m_gui);
        m_gui.dirty = false;
    }

    // =========================================================================
    // Render — Terminal
    // =========================================================================

    void set_term_position(int row, int col)
    requires has_render_term {
        m_term.row = row; m_term.col = col;
        m_term.mark_dirty();
    }

    void set_term_size(int w, int h)
    requires has_render_term {
        m_term.width = w; m_term.height = h;
        m_term.mark_dirty();
    }

    void draw()
    requires has_render_term {
        if (!m_term.visible) return;
        self().render_terminal_impl(m_term);
        m_term.needs_redraw = false;
    }

    // =========================================================================
    // File
    // =========================================================================

    const std::filesystem::path& file_path() const
    requires has_file { return m_file.path; }

    bool file_exists() const
    requires has_file { return m_file.exists(); }

    // =========================================================================
    // Network
    // =========================================================================

    void set_endpoint(std::string ep, uint16_t port)
    requires has_net { m_net.set_endpoint(std::move(ep), port); }

    bool net_connected() const
    requires has_net { return m_net.connected; }

    // =========================================================================
    // Lifecycle
    // =========================================================================

    void set_parent(void* parent)
    requires has_lifecycle { m_lifecycle.set_parent(parent); }

    bool is_alive() const
    requires has_lifecycle { return m_lifecycle.alive; }

    // =========================================================================
    // Members — value semantics, zero cost when policy absent
    // =========================================================================

private:
    // The compiler eliminates default-constructed empty structs under
    // [[no_unique_address]] when they carry no active state. Each handle
    // is inert (no-op methods, zero-size or default state) unless the
    // corresponding policy is present and the constructor activates it.

    [[no_unique_address]]
    std::conditional_t<thread_safe, SignalTableThreaded, SignalTable> m_signals;

    [[no_unique_address]] PropertyStore    m_properties;
    [[no_unique_address]] ChangeLog        m_changelog;
    [[no_unique_address]] UndoStack        m_undo;

    [[no_unique_address]] MetaTable        m_meta;
    [[no_unique_address]] ScriptBridge     m_script;

    [[no_unique_address]] SocketHandle     m_socket;
    [[no_unique_address]] ShmChannel       m_shm;

    [[no_unique_address]] TimerHandle      m_timer;
    [[no_unique_address]] EventLoopHandle  m_evloop;

    [[no_unique_address]] GUIRenderState   m_gui;
    [[no_unique_address]] TermRenderState  m_term;

    [[no_unique_address]] FileHandle       m_file;
    [[no_unique_address]] NetHandle        m_net;
    [[no_unique_address]] LifecycleHandle  m_lifecycle;
};

} // namespace refl

#endif