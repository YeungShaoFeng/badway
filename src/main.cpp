#include "main.h"

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
        makeDir("./tmp");

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