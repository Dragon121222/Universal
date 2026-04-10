#ifndef __UniversalTrivialReflection__
#define __UniversalTrivialReflection__

namespace universe {
    template<typename derived>
    class trivialRefl {
    public:

        using typeTag = Refl;
        using type    = trivialRefl;

        trivialRefl() {}
        ~trivialRefl() {}
        void show() {
            static_cast<derived*>(this)->derived::log("Calling Refl!\n");
        }

    };
}

#endif