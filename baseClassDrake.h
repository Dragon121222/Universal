#ifndef __UnionClass__
#define __UnionClass__

namespace universe {

template<
    typename impl,
    typename ipc,
    typename gui,
    typename term,
    typename file,
    typename net,
    typename refl
>
class unionClass : 
    public impl,
    public ipc,
    public gui,
    public term,
    public file,
    public net,
    public refl 
{
public:
    
    using impl_t = impl;
    using ipc_t = ipc;
    using gui_t = gui;
    using term_t = term;
    using file_t = file;
    using net_t = net;
    using refl_t = refl;

    unionClass() {}
    ~unionClass() {}
};

}

#endif