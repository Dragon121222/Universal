#include "main.h"

int main() {

    universe::demoUnion x; 

    x.log("Test Log\n");
    x.call();
    x.draw();
    x.save();
    x.show();
    x.ipc_t::send();
    x.net_t::send();

}