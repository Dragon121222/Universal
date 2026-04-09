#ifndef __UniversalIpc__
#define __UniversalIpc__

namespace universe {
    template<typename derived>
    class ipc {
    public:
        ipc() {}
        ~ipc() {}
        void send() {
            static_cast<derived*>(this)->derived::log("Calling IPC!\n");
        }

    };
}

#endif