#ifndef __UniversalTrivialGui__
#define __UniversalTrivialGui__

namespace universe {
template<typename dType>
class trivialGui {
public:
    using typeTag = Gui;
    using type    = trivialGui;

    trivialGui() {}
    ~trivialGui() {}
    void draw() {
        as<dType*>(this)->log("Drawing Data!\n");
    }

};
}

#endif