#ifndef __BaseClassDrake__
#define __BaseClassDrake__

namespace universal {

    template<
    typename ImplmentationClass_t,
    typename IPCClass_t,
    typename GuiClass_t,
    typename TerminalClass_t,
    typename FileClass_t,
    typename NetworkClass_t,
    typename ReflectionClass_t
    >
    class baseClass {
        baseClass() {}

        virtual void save() {
            FileClass_t::save();
        }

        virtual void gui() {
            ImplmentationClass_t::gui();
        }

        virtual void impl() {
            ImplmentationClass_t::impl();
        }

        virtual void ipc() {
            ImplmentationClass_t::ipc();
        }

        virtual void list() {
            NetworkClass_t::list();
        }

        virtual void refl() {
            ReflectionClass_t::refl();
        }

        virtual void term() {
            TerminalClass_t::term();
        }

    };
}

#endif