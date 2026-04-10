#ifndef __UniversalTrivialFileIO__
#define __UniversalTrivialFileIO__

namespace universe {
template<typename dType>
class trivialFileIO {
public:
    using typeTag = FileIO;
    using type    = trivialFileIO;

    trivialFileIO() {}
    ~trivialFileIO() {}
    void save() {
        as<dType*>(this)->log("Saving Data!\n");
    }

};
}

#endif