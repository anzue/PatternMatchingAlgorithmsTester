#include "algoexecutor.h"


#include <vector>
#include "../algorithms/executablealgo.h"


vector<vector <float> >  test(
    vector<Algo *> algorithms, 
    vector<int> patternLength, 
    int SIGMA, 
    int N, 
    int OUTER_ITER = 5, 
    int INNER_ITER = 5);
