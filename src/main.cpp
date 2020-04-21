#include "main.h"
//#include <sys/_types/_errno_t.h>
//
//int main() {
//    char myPath[] = "./zero/one/two/three/four/five/six/seven/eight/nine/ten";
//    dirMaker(myPath);
//
//    return 0;
//}



//<-----------------------func implementations-------------->
int main(int argc, char *argv[]) {
    Target myTarget = {false, false,
                       false, 4,
                       3, nullptr,
                       nullptr, nullptr,
                       nullptr, 0
    };

    myTimer();
    // target properties
    int xorOptions = 0;
    setTargetOptions(&myTarget, argc, argv, &xorOptions);

    if (checkTargetProperties(&myTarget)) {
        dirMaker(myTarget.outputFileName);

        if (myTarget.logLevel < 4) {
            printTarget(&myTarget);
        }

        if (myTarget.willEncryp) {
            in(&myTarget);
            myTimer();
        } else if (myTarget.willDecryp) {
            out(&myTarget);
            myTimer();
        }

        myTimer();
    }
    releasePtr(myTarget.sha256_Password);

    return 0;
}