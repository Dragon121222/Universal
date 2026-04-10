#ifndef __UniversalImplmentation__
#define __UniversalImplmentation__

namespace universe {
    template<typename derived>
    class trivialImpl {
    public:

        using typeTag = Impl;
        using type    = trivialImpl;

        trivialImpl() {}
        ~trivialImpl() {}
        void call() {
            static_cast<derived*>(this)->derived::log("Calling Implmentation!\n");
        }

    };
}

#endif