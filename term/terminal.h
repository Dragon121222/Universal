#ifndef __UniversalTerminal__
#define __UniversalTerminal__

namespace universe {
    template<typename derived>
    class term { 
    public:

        using typeTag = Term;
        using type    = term;

        term() {}
        ~term() {}
        void log(universe::str_t msg, universe::str_t prefix = "", universe::str_t postfix = "") {
            std::cout << prefix << msg << postfix;
        }

    };
}

#endif