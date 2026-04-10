#ifndef __UniversalImplmentation__
#define __UniversalImplmentation__

namespace universe {
template<typename dType>
class trivialImpl {
public:

    using typeTag = Impl;
    using type    = trivialImpl;

    trivialImpl() {}
    ~trivialImpl() {}
    void call() {
        as<dType*>(this)->log("Calling Implmentation!\n");
    }

};
}

#endif