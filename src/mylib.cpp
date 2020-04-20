//
// Created by Linxi Yeung on 2019/12/25.
//

#include "mylib.h"
#include "PI64.h"

//<-----variable definition----->
int currentCount = 0;
char _rb[] = "rb";
char _wb[] = "wb";

#ifndef _WIN32
#include <unistd.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>
timeval tv = {0, 0};
long long L1 = 0, L2 = 0;

#else

#include <io.h>
#include <direct.h>
#include <Windows.h>
LARGE_INTEGER nFreq, nBeginTime, nEndTime;
bool nStart = true, nEnd = false;
#endif

// get BUFF_LENGTH's char from fp
size_t getChars(char *buff, int BUFF_LENGTH, FILE *fp) {
    size_t a = fread(buff, sizeof(char), BUFF_LENGTH, fp);
    buff[BYTO_LENGTH] = 0;
    return a;
}

// get a FILE *fp of filePath in mode mode
FILE *getFile(FILE *fp, char *filePath, char *mode) {
#ifndef _WIN32
    fp = fopen(filePath, mode);
#else
    fopen_s(&fp, filePath, mode);
#endif
    if (fp == nullptr) {
        char errorMsg[256];
#ifndef _WIN32
        sprintf(errorMsg, "On opening {%s} ", filePath);
#else
        sprintf_s(errorMsg, 256, "On opening {%s} ", filePath);
#endif
        perror(errorMsg);
        printf("Abort. \n");
        exit(-1);
    }

    return fp;
}

// write a Pi obj to fp in binary mode
size_t putPi(Pi *aPi, FILE *fp) {
    return fwrite(aPi, sizeof(Pi), one, fp);
}

size_t putPiWithLength(Pi *aPi, int length, FILE *fp) {
    size_t a = 0;
    for (int i = 0; i < length; i++) {
        a += fwrite(&aPi->_byto[i], sizeof(char), one, fp);
    }

    return a;
}

Pi *calPiWithCharAndSha256(Pi *aPi, const char *buff, char *sha256) {
    for (int i = 0; i < BYTO_LENGTH; i++) {
        aPi->_byto[i] = aPi->_byto[i] ^ buff[i] ^ sha256[i];
    }
    return aPi;
}


Pi *getPiWithPosFromPI64(int pos, Pi *aPi) {
    currentCount += pos;
    if (currentCount > 7906) {
        currentCount = 0;
    }
    for (int i = 0; i < BYTO_LENGTH; i++) {
        aPi->_byto[i] = PI64[currentCount][i];
    }
    return aPi;
}
// f58f576eff38d9353ecc3475f7b0253d735f04968a75ef5ea03ba45c25619069
char *sha256(char *str, char *output) {
    char buf[3];
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str, strlen(str));
    SHA256_Final(hash, &sha256);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
#ifndef _WIN32
        sprintf(buf, "%02x", hash[i]);
#else
        sprintf_s(buf, 3, "%02x", hash[i]);
#endif
        for (int j = 0; j < 2; j++) {
            output[i * 2 + j] = buf[j];
        }
    }
    output[64] = 0;
    return output;
}

bool isBeginWithDashAnd(char *buff, int x) {
    if (strlen(buff) != 2) {
        return false;
    }
    if (buff[0] != 45) {
        return false;
    }
    return buff[1] == x;
}

int *setTargetOptions(Target *target, int argc, char *argv[], int *xorOptions) {
    int arguments[] = {
            100, // d
            101, // e
            105, // i
            108, // l
            111, // o
            112, // p
            116, // t
    };

    for (int i = 1; i < argc; i++) {
        for (int argument : arguments) {
            if (isBeginWithDashAnd(argv[i], argument)) {
                switch (int(argv[i][1])) {
                    case 100: // option d
                    {
                        *xorOptions ^= 100;
                        setTarget_willDecryp(true, target);
                        break;
                    }
                    case 101: // option e
                    {
                        *xorOptions ^= 101;
                        setTarget_willEncryp(true, target);
                        break;
                    }
                    case 105: // option i
                    {
                        *xorOptions ^= 105;
                        setTarget_inputFileName(argv[++i], target);
                        setTargetBytosCntAndLackOfBytes(target);
                        break;
                    }
                    case 108: // option l
                    {
                        *xorOptions ^= 108;
                        setTarget_logLevel(int(*argv[++i]) - 48, target);
                        break;
                    }
                    case 111: // option o
                    {
                        *xorOptions ^= 111;
                        setTarget_outputFileName(argv[++i], target);
                        break;
                    }
                    case 112: // option p
                    {
                        *xorOptions ^= 112;
                        setTarget_Password(argv[++i], target);
                        char *buff = new char[BYTO_LENGTH + 1];
                        sha256(target->Password, buff);
                        setTarget_sha256_Password(buff, target);
                        break;
                    }
                    case 116: // option t
                    {
                        *xorOptions ^= 116;
                        setTarget_willTest(true, target);
                        break;
                    }
                    default: {
                        printf("None matched option. Please see the documentation. \n");
                        break;
                    }
                }
                break;
            }
        }
    }

    return xorOptions;
}

Target *setTarget_willEncryp(bool willEncryp, Target *target) {
    target->willEncryp = willEncryp;
    return target;
}

Target *setTarget_willDecryp(bool willDecryp, Target *target) {
    target->willDecryp = willDecryp;
    return target;
}

Target *setTarget_willTest(bool willTest, Target *target) {
    target->willTest = willTest;
    return target;
}

Target *setTarget_logLevel(int logLevel, Target *target) {
    target->logLevel = logLevel;
    return target;
}

Target *setTarget_inputFileName(char *inputFilename, Target *target) {
    target->inputFileName = inputFilename;
    return target;
}

Target *setTarget_outputFileName(char *outputFilename, Target *target) {
    target->outputFileName = outputFilename;
    return target;
}

Target *setTarget_Password(char *Password, Target *target) {
    target->Password = Password;
    return target;
}

Target *setTarget_sha256_Password(char *sha256_Password, Target *target) {
    target->sha256_Password = sha256_Password;
    return target;
}

Target *setTargetBytosCntAndLackOfBytes(Target *target) {
    FILE *fp = nullptr;

    fp = getFile(fp, target->inputFileName, _rb);
    if (fp) {
        fseek(fp, 0L, SEEK_END);
        unsigned long size = ftell(fp);
        target->TargetFileBytosCnt = size / (sizeof(char) * 64);
        target->lackOfBytes = char(size % (sizeof(char) * 64));
        fclose(fp);
    } else {
        printf("fp is nullptr\n");
    }

    return target;
}

Target *printTarget(Target *target) {
    printf("\nTarget info: \n");
    if (target->logLevel < 3) {
        printf("   willEncryp: {%d}. \n", target->willEncryp);
        printf("   willDecryp: {%d}. \n", target->willDecryp);
        printf("   willTest: {%d}. \n", target->willTest);
        printf("   lackOfBytes: {%d}. \n", int(target->lackOfBytes));
        printf("   logLevel: {%d}. \n", target->logLevel);
    }
    step_printTarget("inputFileName", target->inputFileName);
    step_printTarget("outputFileName", target->outputFileName);
    step_printTarget("Password", target->Password);

    if (target->logLevel < 3) {
        printf("   TargetFileBytosCnt: {%lu}. \n", target->TargetFileBytosCnt);
        if (target->sha256_Password == nullptr) {
            printf("   sha256_Password: {nullptr}. \n");
        } else {
            printf("   sha256_Password: {%s}. \n", target->sha256_Password);
        }
    }
    return target;
}

void step_printTarget(const char *targetPropertyName, char *targetProperty) {
    if (targetProperty != nullptr) {
        printf("   %s: {%s}. \n", targetPropertyName, targetProperty);
    } else {
        printf("   %s: {nullptr}. \n", targetPropertyName);
    }
}

bool checkTargetProperties(Target *target) {
    bool a = true, b = true, c = true;
    { cout << "1" << endl; }
    if (!target->willDecryp && !target->willEncryp) {
        a = false;
        printf("You missed the -e or -d option. \n");
    }
    { cout << "2" << endl; }
    if (target->inputFileName == nullptr) {
        b = false;
        printf("Did you forget to specify a input file name? \n");
    } else {
        { cout << "3" << endl; }
        if (!checkDirOrFileOut(target->inputFileName)) {
            b = false;
            printf("The input file name you specified was invalid. \n");
        }
    }

    if (target->Password == nullptr) {
        c = false;
        printf("You missed the Password. \n");
    }

    if (a && b && c) {
        return true;
    } else {
        printf("Abort. \n");
        return false;
    }
}

void resetCurrentCount() {
    currentCount = 0;
}

void printPounch(Target *target, const char *msg) {
    if (target->logLevel < 3) {
        for (int i = 0; i < 30; i++) {
            printf("\n%c", 35);
        }
    }
    printf("%s", msg);
}

void in(Target *target) {
    printPounch(target, "\n->in...\n");

    stage_one(target);

    printPounch(target, "in<-\n");
}

void out(Target *target) {
    printPounch(target, "\n->out...\n");

    stage_one(target);

    printPounch(target, "out<-\n");

}

void stage_one(Target *target) {
    FILE *afp = nullptr, *bfp = nullptr;

    afp = getFile(afp, target->inputFileName, _rb);
    bfp = getFile(bfp, target->outputFileName, _wb);

    stage_two(target, afp, bfp);

    fclose(afp);
    fclose(bfp);
}

void stage_two(Target *target, FILE *afp, FILE *bfp) {
    resetCurrentCount();
    xorTargetWithPi(target, afp, bfp);
}

void xorTargetWithPi(Target *target, FILE *afp, FILE *bfp) {
    size_t cnt = 1;
    bool isFinished = false;
    Pi aPi = {0, 0};
    char buff[BYTO_LENGTH + 1], buff_b[BYTO_LENGTH + 1];
    char indexOfPi[BYTO_LENGTH + 1];

#ifndef _WIN32
    strcpy(indexOfPi, target->sha256_Password);
    strcpy(buff_b, target->sha256_Password);
#else
    strcpy_s(indexOfPi, BYTO_LENGTH + 1, target->sha256_Password);
    strcpy_s(buff_b, BYTO_LENGTH + 1, target->sha256_Password);
#endif

    while (true) {
        // logger
        if (target->logLevel < 3) {
            printf("calTargetWithPi cnt: {%d}. \n", int(cnt));
            printf("global currentCount: {%d}. \n", currentCount);
            if (target->logLevel < 2) {
                printf("calTargetWithPi indexOfPi: {%s}. \n", indexOfPi);
            }
        }
        // core code
        for (int i = 0; i < BYTO_LENGTH; i++) {
            cnt = getChars(buff, BYTO_LENGTH, afp);
            if (cnt == 0) {
                // end of the input file
                isFinished = true;
                break;
            }
            getPiWithPosFromPI64(indexOfPi[i], &aPi);
            calPiWithCharAndSha256(&aPi, buff, target->sha256_Password);
            if (cnt != BYTO_LENGTH) {
                putPiWithLength(&aPi, int(target->lackOfBytes), bfp);
            } else {
                putPi(&aPi, bfp);
            }
        }
        // determine if is finished
        if (!isFinished) {
            // not finished
            sha256(buff_b, indexOfPi);
#ifndef _WIN32
            strcpy(buff_b, indexOfPi);
#else
            strcpy_s(buff_b, BYTO_LENGTH + 1, indexOfPi);
#endif
        } else {
            // finished. Get out of the while loop
            break;
        }

    }
}

void releasePtr(char *ptr) {
    delete[] ptr;
}

// timeBenchMark for main()
void myTimer() {
#ifndef _WIN32
    if (L1 == 0) {
        gettimeofday(&tv, nullptr);
        L1 = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
        return;
    }
    if (L2 == 0) {
        gettimeofday(&tv, nullptr);
        L2 = tv.tv_sec * 1000 * 1000 + tv.tv_usec;
        return;
    }
    if (L2 && L1) {
        printf("Finished in {%lld}u_secs. \n", L2 - L1);
    }
#else
    if (nStart)
    {
        QueryPerformanceFrequency(&nFreq);
        QueryPerformanceCounter(&nBeginTime);
        nStart = false;
        nEnd = true;
        return;
    }
    if (nEnd)
    {
        QueryPerformanceCounter(&nEndTime);
        double totalTime = (double)(nEndTime.QuadPart - nBeginTime.QuadPart) / 1000 / nFreq.QuadPart;
        printf("Finished in {%lf}s. \n", totalTime);
        nStart = nEnd = false;
        return;
    }
#endif
}

bool checkDirOrFileOut(const char *fileNameOrDirPath) {
    bool status = false;
#ifndef _WIN32
    int accessed = access(fileNameOrDirPath, 0); //有指定访问权限则返回0，否则函数返回-1
#else
    int accessed = _access(fileNameOrDirPath, 0);
#endif
    if (accessed == -1) {
        status = false;
    } else if (accessed == 0) {
        status = true;
    }
    return status;
}

int makeDir(const char *dirPath) {
    if (!checkDirOrFileOut(dirPath)) {
        printf("missing {%s}, now making... \n", dirPath);
#ifndef _WIN32
        int status = mkdir("./tmp", 0777);
#else
        int status = _mkdir("./tmp");
#endif
        if (status == 0) {
            printf("Successfully made directory: {%s}. \n", dirPath);
            return status;
        } else {
            printf("Failed to make directory: {%s}. \n", dirPath);
            printf("Maybe you should check it out. \n");
            printf("Now exiting...\n");
            exit(-1);
        }
    } else {
        printf("Directory {%s} already exits. \n", dirPath);
    }
}

int dirMaker(const char *path) {
    // get the length of the path
    int pathLengthCnt = strlen(path);
    { cout << path << endl; }

    // path contains at least half the length of the path
    char *dirsNeededToBeMade = new char[pathLengthCnt + 9];
    memset_s(dirsNeededToBeMade, pathLengthCnt, 0, pathLengthCnt);

    char tmp = 0;
    int last_slash = 0;

    // Find the last slash which followed by the encrypt file name.
    for (int i = 0; i < pathLengthCnt; i++) {
        if(path[i] == 47) {
            last_slash = i;
        }
    }
    last_slash += 1;

    // dirsNeededToBeMade[0-5] = "mkdir "
    dirsNeededToBeMade[0] = 109; // "m"
    dirsNeededToBeMade[1] = 107; // "k"
    dirsNeededToBeMade[2] = 100; // "d"
    dirsNeededToBeMade[3] = 105; // "i"
    dirsNeededToBeMade[4] = 114; // "r"
    dirsNeededToBeMade[5] = 32;  // " "

#ifndef _WIN32
    // "mkdir -p " + path
    dirsNeededToBeMade[6] = 45;  // "-"
    dirsNeededToBeMade[7] = 112; // "p"
    dirsNeededToBeMade[8] = 32;  // " "
    for (int i = 0; i < last_slash; i++) {
        dirsNeededToBeMade[i+9] = path[i];
    }
#else
    // "mkdir " + path
    for (int i = 0; i < last_slash; i++) {
        dirsNeededToBeMade[i+6] = path[i];
    }
#endif
    // execute the mkdir command.
    { cout << dirsNeededToBeMade << endl; }
    int status = system(dirsNeededToBeMade);

    releasePtr(dirsNeededToBeMade);
    return status;
}