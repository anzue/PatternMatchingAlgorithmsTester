#ifndef EXECUTABLEALGO_H
#define EXECUTABLEALGO_H

#include <string>

#include "algos.h"

typedef int (*PatternMatchAlgo)(unsigned char*, int, unsigned char*, int, float*);

class ExecutableAlgo {
public:
    std::string name = "no name";
    bool isSelected = true;
    PatternMatchAlgo function;

    ExecutableAlgo(std::string name, PatternMatchAlgo function, bool isSelected = true)
    {
        this->name = name;
        this->isSelected = isSelected;
        this->function = function;
    }

    virtual int search(unsigned char* P, int M, unsigned char* T, int N, float* time)
    {
        (*function)(P, M, T, N, time);
    }

    ExecutableAlgo* withSelection(bool active)
    {
        isSelected = active;
        return this;
    }
};

template <int k>
class RZk_byte_v1 : public ExecutableAlgo {
public:
    RZk_byte_v1()
        : ExecutableAlgo("RZ_" + to_string(k), NULL, true)
    {
    }

    int search(unsigned char* P, int M, unsigned char* T, int N, float* time = NULL)
    {
        return search_RZk_byte(P, M, T, N, k, time);
    }
};

#endif // EXECUTABLEALGO_H
