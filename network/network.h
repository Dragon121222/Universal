#ifndef __UniversalNetwork__
#define __UniversalNetwork__

namespace universe {
    template<typename derived>
    class net {
    public:
        net() {}
        ~net() {}
        void send() {
            static_cast<derived*>(this)->derived::log("Calling Net!\n");
        }

    };
}

#endif