#ifndef __UniversalIpc__
#define __UniversalIpc__

namespace universe {
    template<typename derived>
    class trivialIpc {
    public:

        using typeTag = Ipc;
        using type    = trivialIpc;

        trivialIpc() {}
        ~trivialIpc() {}
        void send() {
            static_cast<derived*>(this)->derived::log("Calling IPC!\n");
        }

    };
}

#endif