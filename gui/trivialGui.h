#ifndef __UniversalTrivialGui__
#define __UniversalTrivialGui__

namespace universe {
    template<typename derived>
    class trivialGui {
    public:
        using typeTag = Gui;
        using type    = trivialGui;

        trivialGui() {}
        ~trivialGui() {}
        void draw() {
            static_cast<derived*>(this)->derived::log("Drawing Data!\n");
        }

    };
}

#endif