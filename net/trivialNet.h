#ifndef __UniversalTrivialNetwork__
#define __UniversalTrivialNetwork__

namespace universe {
    template<typename derived>
    class trivialNet {
    public:

        using typeTag = Net;
        using type    = trivialNet;

        trivialNet() {}
        ~trivialNet() {}
        void send() {
            static_cast<derived*>(this)->derived::log("Calling Net!\n");
        }

    };
}

#endif