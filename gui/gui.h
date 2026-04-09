#ifndef __UniversalGui__
#define __UniversalGui__

namespace universe {
    template<typename derived>
    class gui {
    public:
        gui() {}
        ~gui() {}
        void draw() {
            static_cast<derived*>(this)->derived::log("Drawing Data!\n");
        }

    };
}

#endif