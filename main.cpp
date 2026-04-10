#include "main.h"

int main() {

    using namespace universe;

    demoMixin x; 

    x.log("Test Log\n");
    x.call();
    x.draw();
    x.save();
    x.show();
    x.as<Ipc>::send();
    x.as<Net>::send();

}