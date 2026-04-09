#ifndef __UniversalFile__
#define __UniversalFile__

namespace universe {
    template<typename derived>
    class file {
    public:
        file() {}
        ~file() {}
        void save() {
            static_cast<derived*>(this)->derived::log("Saving Data!\n");
        }

    };
}

#endif