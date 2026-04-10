#ifndef __UniversalTrivialReflection__
#define __UniversalTrivialReflection__

namespace universe {
    template<typename dType>
    class trivialRefl {
    public:

        using typeTag = Refl;
        using type    = trivialRefl;

        trivialRefl() {}
        ~trivialRefl() {}
        void show() {
            as<dType*>(this)->log("Calling Refl!\n");
        }

    };
}

#endif