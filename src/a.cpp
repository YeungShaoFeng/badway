//
// Created by Linxi Yeung on 2019/12/26.
//

#include <stdio.h>
#include <string.h>
#include <limits>
#include <iostream>
//#include "../include/main.h"

using namespace std;

char *dirMaker(char *path) {
    // get the length of the path
//    int pathLengthCnt = strlen(path);
//    while(true) {
//        if(path[++pathLengthCnt]==0) break;
//    }
    { cout << "Length: " << strlen(path) << endl; }

//    // path contains at least half the length of the path
//    char separateDirs[pathLengthCnt/2] = {0};
//
//    int i = 0;
//    while(true) {
//#ifndef _WIN32
//        if(path[++i]==47) {
//            while(path[++i] != 47) {
//
//            }
//        }
//#else
//
//#endif
//    }

    return path;
}

int main() {
    char myPath[] = "./a/b/cdjk";

    dirMaker(myPath);

    return 0;
}


// SHIFT TERM METHOD
/*
 * a | b                                    b | d
 * --|--                                    --|--
 * c | d                                    a | c
 *    0  1    2  3    4  5    6  7
 * a a0 a1 | a2 a3 | a4 a5 | a6 a7          a7 b7
 * b b0 b1 | b2 b3 | b4 b5 | b6 b7
 *   ------|-------|-------|------          ------|---------------------
 * c c0 c1 | c2 c3 | c4 c5 | c6 c7          h2 g2 |
 * d d0 d1 | d2 d3 | d4 d5 | d6 d7    -->   h3 g3 |
 *   --------------|--------------
 * e e0 e1 | e2 e3 | e4 e5 | e6 e7    -->
 * f f0 f1 | f2 f3 | f4 f5 | f6 f7
 *   ------|-------|-------|------
 * g g0 g1 | g2 g3 | g4 g5 | g6 g7
 * h h0 h1 | h2 h3 | h4 h5 | h6 h7
//     * i i0 i1 i2 i3 i4 i5 i6 i7
 */