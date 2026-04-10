#ifndef __UniversalReflection__
#define __UniversalReflection__

namespace universe {
    template<typename derived>
    class refl {
    public:

        using typeTag = Refl;
        using type    = refl;

        refl() {}
        ~refl() {}
        void show() {
            static_cast<derived*>(this)->derived::log("Calling Refl!\n");
        }

    };
}

#endif