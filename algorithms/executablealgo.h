#ifndef EXECUTABLEALGO_H
#define EXECUTABLEALGO_H

#include <string>

#include "algos.h"

typedef int (*PatternMatchAlgo)(unsigned char *, int, unsigned char *, int, float *);

typedef int (*KPatternMatchAlgo)(unsigned char *, int, unsigned char *, int, int, float *);

class Algo {
public:
    pair<int, int> alphabet_constraint = {2, 10000};
    pair<int, int> pattern_constraint = {1, 10000};

    std::string name;
    bool is_selected = true;

    bool is_applicable(int alphabet, int pattern) {
        return alphabet >= alphabet_constraint.first &&
               alphabet <= alphabet_constraint.second &&
               pattern >= pattern_constraint.first &&
               pattern <= pattern_constraint.second;
    }

    virtual int search(unsigned char *P, int M, unsigned char *T, int N, float *time) = 0;
};

class ExecutableAlgo : public Algo {
public:
    PatternMatchAlgo function;

    ExecutableAlgo();

    ExecutableAlgo(std::string name_value,
                   PatternMatchAlgo function_value,
                   bool is_selected = true,
                   pair<int, int> alphabet = {2, 1000},
                   pair<int, int> pattern = {1, 1000}
    ) {
        this->name = name_value;
        this->is_selected = is_selected;
        this->function = function_value;
        this->alphabet_constraint = alphabet;
        this->pattern_constraint = pattern;
    }

    int search(unsigned char *P, int M, unsigned char *T, int N, float *time) { return (*function)(P, M, T, N, time); }
};

class KExecutableAlgo : public Algo {
public:
    KPatternMatchAlgo function;
    int k;

    KExecutableAlgo(
            std::string name_pattern,
            KPatternMatchAlgo function = NULL,
            int k = 13,
            bool isSelected = true,
            pair<int, int> alphabet = {2, 1000},
            pair<int, int> pattern = {1, 1000}
    ) {
        auto pos = name_pattern.find("{}");
        if (pos < name_pattern.size())
            name_pattern.replace(pos, 2, to_string(k));

        this->name = name_pattern;
        this->is_selected = isSelected;
        this->function = function;
        this->k = k;
        this->pattern_constraint = pattern;
        this->alphabet_constraint = alphabet;
    }

    int search(unsigned char *P, int M, unsigned char *T, int N, float *time) {
        return (*function)(P, M, T, N, k, time);
    }
};


#endif // EXECUTABLEALGO_H
