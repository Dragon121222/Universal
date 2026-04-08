#include "baseClassDrake.h"
#include "file/file.h"
#include "gui/gui.h"
#include "impl/impl.h"
#include "ipc/ipc.h"
#include "network/network.h"
#include "reflection/reflection.h"
#include "terminal/terminal.h"

int main() {

    using Camera_t = universal::baseClass<
        CameraImpl,
        CameraIpc,
        CameraGui,
        CameraTerm,
        CameraFile,
        CameraNet,
        CameraReflect
    >;

}