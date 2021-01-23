#ifndef CONSTS_H
#define CONSTS_H

#include <algorithm>
#include <conio.h>
#include <cstdio>
#include <iostream>
#include <malloc.h>
#include <map>
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/timeb.h>
#include <time.h>
#include <vector>
#include <windows.h>
using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define FALSE 0
#define TRUE 1
#define WSIZE 256 //greater int value fitting in a computer word
#define AS 4
#define LOGAS 2

//#define SIGMA 8
//#define SIGMA       32				//constant alphabet size
#define SIGMAKV 1024
#define SIGMAKUB 32768
#define SIGMA4 256
#define SIGMA5 1024
#define SIGMA6 2097152
#define SIGMA7 16777216
//#define ALPHA       256				//constant alphabet size
//#define ASIZE		256				//constant alphabet size
#define UNDEFINED -1
#define HALFDEFINED -2
#define WORD 32 //computer word size (in bit)
#define OUTPUT(j) count++

#define RANK3 3

const unsigned int MAX_SIGMA = 256;
const unsigned int MAX_PAT_LEN = 520;

extern unsigned int SIGMA, MINM, MAXM;

extern float sumu2, sum_rzk[20], sum_bsdm;
extern LARGE_INTEGER start, finish, freq;

#endif // CONSTS_H
