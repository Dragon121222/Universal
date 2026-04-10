#ifndef __UniversalIpc__
#define __UniversalIpc__

namespace universe {
    template<typename dType>
    class trivialIpc {
    public:

        using typeTag = Ipc;
        using type    = trivialIpc;

        trivialIpc() {}
        ~trivialIpc() {}
        void send() {
            as<dType*>(this)->log("Calling IPC!\n");
        }

    };
}

#endif