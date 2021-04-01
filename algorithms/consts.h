#ifndef CONSTS_H
#define CONSTS_H

#include <QStringList>
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
#define WSIZE 256 // greater int value fitting in a computer word
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
#define WORD 32 // computer word size (in bit)
#define OUTPUT(j) count++

#define RANK3 3

#define MAX_SIGMA 256
#define MAX_PAT_LEN 520
#define TOTAL 500000

extern LARGE_INTEGER start, finish, freq;
extern unsigned int SIGMA;
extern unsigned char T[TOTAL], T1[TOTAL], P[MAX_PAT_LEN];

//#define MATCH_DEBUGGING

#ifdef MATCH_DEBUGGING
extern std::map<string, vector<int>> matches_pos;
#define MATCH(pos)                                               \
    {                                                            \
        if (matches_pos.find(__FUNCTION__) == matches_pos.end()) \
            matches_pos[__FUNCTION__] = vector<int>();           \
        matches_pos[__FUNCTION__].push_back(pos);                \
        ++count;                                                 \
    }

#define CLEAR_MATCHES \
    { matches_pos.clear(); }

//                PRINT_DIFF(std::next(std::next(matches_pos.begin()))->first, pair.first) \

#define FIND_DIFF_MATCHES                                          \
    {                                                              \
        auto defAlgo = matches_pos.begin()->second;                \
        for (auto& pair : matches_pos) {                           \
      /*  if (pair.second.size() != defAlgo.size())    */               \
        {                 \
                PRINT_DIFF(matches_pos.begin()->first, pair.first)      \
        }                                                               \
        }                                                               \
}

#define PRINT_DIFF(ALGO1, ALGO2)                                                                                           \
    {                                                                                                                      \
        vector<int> algo1 = matches_pos[ALGO1];                                                                            \
        vector<int> algo2 = matches_pos[ALGO2];                                                                            \
        std::sort(algo1.begin(), algo1.end());                                                                             \
        std::sort(algo2.begin(), algo2.end());                                                                             \
        algo1.push_back(1000000000);                                                                                       \
        algo2.push_back(1000000000);                                                                                       \
        int algo1_iter = 0;                                                                                                \
        int algo2_iter = 0;                                                                                                \
        cout << "{ " << ALGO1 << " } , ( " << ALGO2 << " ) ";                                                              \
        while (algo1_iter < algo1.size() && algo2_iter < algo2.size()) {                                                   \
            if (algo1[algo1_iter] < algo2[algo2_iter]) {                                                                   \
                cout << "{ ";                                                                                              \
                while (algo1[algo1_iter] < algo2[algo2_iter])                                                              \
                    cout << algo1[algo1_iter++] << ", ";                                                                   \
                cout << "}, ";                                                                                             \
            }                                                                                                              \
            if (algo2[algo2_iter] < algo1[algo1_iter]) {                                                                   \
                cout << "( ";                                                                                              \
                while (algo2[algo2_iter] < algo1[algo1_iter])                                                              \
                    cout << algo2[algo2_iter++] << ", ";                                                                   \
                cout << "), ";                                                                                             \
            }                                                                                                              \
            if (algo2[algo2_iter] == algo1[algo1_iter]) {                                                                  \
                cout << "[ " << algo1[algo1_iter] << ", ";                                                                 \
                int common = 0;                                                                                            \
                while (algo1_iter < algo1.size() && algo2_iter < algo2.size() && algo1[algo1_iter] == algo2[algo2_iter]) { \
                    ++common;                                                                                              \
                    ++algo1_iter;                                                                                          \
                    ++algo2_iter;                                                                                          \
                }                                                                                                          \
                if (common > 2)                                                                                            \
                    cout << "..." << common << "... , ";                                                                   \
                if (common > 1)                                                                                            \
                    cout << algo1[algo1_iter - 1] << "], ";                                                                \
                else                                                                                                       \
                    cout << "],";                                                                                          \
            }                                                                                                              \
        }                                                                                                                  \
        algo1.pop_back();                                                                                                  \
        algo2.pop_back();                                                                                                  \
        cout << std::endl;                                                                                                 \
    }

#else
#define MATCH(pos) ++count

#define CLEAR_MATCHES
#define FIND_DIFF_MATCHES
#define PRINT_DIFF(ALGO1, ALGO2)

#endif // MATCH_DEBUGGING

#endif // CONSTS_H
