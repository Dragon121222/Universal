#ifndef __MainInclude__
#define __MainInclude__

#include <iostream>

namespace universe {

    using str_t = std::string;

}

#include "baseClassDrake.h"
#include "file/file.h"
#include "gui/gui.h"
#include "impl/impl.h"
#include "ipc/ipc.h"
#include "network/network.h"
#include "reflection/reflection.h"
#include "terminal/terminal.h"

namespace universe {

    class demoUnion;

    using demoUnion_t = universe::unionClass<
        universe::impl<demoUnion>,
        universe::ipc<demoUnion>,
        universe::gui<demoUnion>,
        universe::term<demoUnion>,
        universe::file<demoUnion>,
        universe::net<demoUnion>,
        universe::refl<demoUnion>
    >;

    class demoUnion : public demoUnion_t {
    public:
        demoUnion() {}
        ~demoUnion() {}
    };

};

#endif