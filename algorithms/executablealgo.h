#ifndef EXECUTABLEALGO_H
#define EXECUTABLEALGO_H

#include <string>

#include "algos.h"

typedef int (*PatternMatchAlgo)(unsigned char*, int, unsigned char*, int, float*);
typedef int (*KPatternMatchAlgo)(unsigned char*, int, unsigned char*, int, int, float*);

class Algo {
  public:
    std::string name;
    bool isSelected = true;

    virtual int search(unsigned char* P, int M, unsigned char* T, int N, float* time) = 0;
};

class ExecutableAlgo : public Algo {
  public:
    PatternMatchAlgo function;

    ExecutableAlgo(std::string name, PatternMatchAlgo function, bool isSelected = true) {
        this->name = name;
        this->isSelected = isSelected;
        this->function = function;
    }

    int search(unsigned char* P, int M, unsigned char* T, int N, float* time) { (*function)(P, M, T, N, time); }
};

class KExecutableAlgo : public Algo {
  public:
    KPatternMatchAlgo function;
    int k;

    KExecutableAlgo(std::string pattern, KPatternMatchAlgo function = NULL, int k = 13, bool isSelected = true) {
        auto pos = pattern.find("{}");
        if (pos < pattern.size())
            pattern.replace(pos, 2, to_string(k));

        this->name = pattern;
        this->isSelected = isSelected;
        this->function = function;
        this->k = k;
    }

    int search(unsigned char* P, int M, unsigned char* T, int N, float* time) { (*function)(P, M, T, N, k, time); }
};

#endif // EXECUTABLEALGO_H
