#ifndef __UniversalReflection__
#define __UniversalReflection__

namespace universe {
    template<typename dType>
    class refl {
    public:

        using typeTag = Refl;
        using type    = refl;

        refl() {}
        ~refl() {}
        void show() {
            as<dType*>(this)->log("Calling Refl!\n");
        }

    };
}

#endif