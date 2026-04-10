#ifndef __MainInclude__
#define __MainInclude__

#include <iostream>
#include <tuple>
#include <type_traits>

namespace universe {

    using str_t = std::string;

}

#include "baseClassDrake.h"
#include "fileIO/include.h"
#include "gui/include.h"
#include "impl/include.h"
#include "ipc/include.h"
#include "net/include.h"
#include "refl/include.h"
#include "term/include.h"

namespace universe {

    class demoMixin;

    using demoMixin_t = universe::mixin<
        universe::trivialImpl<demoMixin>,
        universe::trivialIpc<demoMixin>,
        universe::trivialGui<demoMixin>,
        universe::term<demoMixin>,
        universe::trivialFileIO<demoMixin>,
        universe::trivialNet<demoMixin>,
        universe::trivialRefl<demoMixin>
    >;

    class demoMixin : public demoMixin_t {
    public:
        demoMixin() {}
        ~demoMixin() {}
    };

};

#endif