#include "main.h"


int main(int argc, char *argv[]) {
    Target myTarget = {
            false, false, false,
            4, nullptr, nullptr,
            0u, nullptr, nullptr,
            0uL
    };

    myTimer();
    // target properties
    unsigned int xorOptions = 0;
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