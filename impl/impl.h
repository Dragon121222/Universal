#ifndef __UniversalImplmentation__
#define __UniversalImplmentation__

namespace universe {
    template<typename derived>
    class impl {
    public:
        impl() {}
        ~impl() {}
        void call() {
            static_cast<derived*>(this)->derived::log("Calling Implmentation!\n");
        }

    };
}

#endif