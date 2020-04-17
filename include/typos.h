//
// Created by Linxi Yeung on 2019/12/25.
//
#pragma once
#ifndef BADWAY_TYPOS_H
#define BADWAY_TYPOS_H      1

#include "nums.h"

typedef struct Pi {
    char _byto[BYTO_LENGTH];
} Pi;

typedef struct Target {
    bool willEncryp;
    bool willDecryp;
    bool willTest;
    char lackOfBytes;
    int logLevel;
    char *inputFileName;
    char *outputFileName;
    char *Password;
    char *sha256_Password;
    unsigned long TargetFileBytosCnt;
} Target;

#endif //BADWAY_TYPOS_H
