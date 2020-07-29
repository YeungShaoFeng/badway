#ifndef _mylib_h
#define _mylib_h        1
#pragma once

/*
 * sizeof(int) == 4: 256GB max ~= 13.5h
 * int_4_bytos == 2 ** 32
 * sizeof(int) == 2 : 4GB max ~= 12.5m
 * int_2_bytos == 2 ** 26
*/

//<-----headers------>
#include <cstdio>
#include <cstring>
#include <iostream>
#include "sha.h"
#include "nums.h"
#include "typos.h"

using namespace std;
//<-----------------func prototypes------------------------->
/*
 * level: 3
 *      global lake
 *      global TargetFileBytosCnt
 *      Target info
 *      time benchMark
 * level: 2
 *      level 3
 *      global currentCount
 * level: 1
 *      level 2
 *      xorTargetWithPi indexOfPi
*/
// get BUFF_LENGTH's char from fp
size_t getChars(unsigned char *buff, int BUFF_LENGTH, FILE *fp);

// get a FILE *fp of filePath in mode mode
FILE *getFile(FILE *fp, char *filePath, char *mode);

// write a Pi obj to fp in binary mode
size_t putPi(Pi *aPi, FILE *fp);

size_t putPiWithLength(Pi *aPi, int length, FILE *fp);

Pi *calPiWithCharAndSha256(Pi *aPi, const unsigned char *buff, const unsigned char *sha256);

Pi *getPiWithPosFromPI64(int pos, Pi *aPi);

unsigned char *sha256(unsigned char *str, unsigned char *output);

bool isBeginWithDashAnd(char *buff, char x);

/*
 * options:
 * -e<encryption> Or -d<decryption>
 * -i<input file>
 * -o<output file>
 * -p<password>
 * -t<test>
 * -l<log level>
*/
unsigned int *setTargetOptions(Target *target, int argc, char *argv[], unsigned int *xorOptions);

// target setters
Target *setTarget_willEncryp(bool willEncryp, Target *target);

Target *setTarget_willDecryp(bool willDecryp, Target *target);

Target *setTarget_willTest(bool willTest, Target *target);

Target *setTarget_logLevel(int logLevel, Target *target);

Target *setTarget_inputFileName(char *inputFilename, Target *target);

Target *setTarget_outputFileName(char *outputFilename, Target *target);

Target *setTarget_Password(unsigned char *Password, Target *target);

Target *setTarget_sha256_Password(unsigned char *sha256_Password, Target *target);

Target *setTargetBytosCntAndLackOfBytes(Target *target);

Target *printTarget(Target *target);

void step_printTarget(const char *targetPropertyName, char *targetProperty);

void step_printTarget(const char *targetPropertyName, unsigned char *targetProperty);

bool checkDirOrFileOut(const char *fileNameOrDirPath);

bool checkTargetProperties(Target *target);

void resetCurrentCount();

void printPounch(Target *target, const char *msg);

void in(Target *target);

void out(Target *target);

void stage_one(Target *target);

void stage_two(Target *target, FILE *afp, FILE *bfp);

void xorTargetWithPi(Target *target, FILE *afp, FILE *bfp);

void releasePtr(unsigned char *ptr);

void releasePtr(char *ptr);

void myTimer();

int dirMaker(const char *path);


#endif  //mylib_h