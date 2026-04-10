#ifndef __UniversalTrivialFileIO__
#define __UniversalTrivialFileIO__

namespace universe {
    template<typename derived>
    class trivialFileIO {
    public:
        using typeTag = FileIO;
        using type    = trivialFileIO;

        trivialFileIO() {}
        ~trivialFileIO() {}
        void save() {
            static_cast<derived*>(this)->derived::log("Saving Data!\n");
        }

    };
}

#endif