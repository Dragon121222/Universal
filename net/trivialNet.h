#ifndef __UniversalTrivialNetwork__
#define __UniversalTrivialNetwork__

namespace universe {
template<typename dType>
class trivialNet {
public:

    using typeTag = Net;
    using type    = trivialNet;

    trivialNet() {}
    ~trivialNet() {}
    void send() {
        as<dType*>(this)->log("Calling Net!\n");
    }

};
}

#endif