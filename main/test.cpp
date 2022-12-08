//
// Created by anton on 12/4/2022.
//


#pragma once

#include <vector>
#include "algorithms/algos.h"
#include "algorithms/executablealgo.h"
#include <algorithm>

#define MAX_ALGO_COUNT 100

// #define MAX_SIGMA 256
// #define MAX_PAT_LEN 520
// #define TOTAL 50000

unsigned char T[TOTAL], T1[TOTAL], P[MAX_PAT_LEN];

#define TN (T1 + m)

int matches[MAX_ALGO_COUNT];
float execTime[MAX_ALGO_COUNT];
int ids[MAX_ALGO_COUNT];

using std::vector;

int get_rand_int(int max) {
    return (rand() * RAND_MAX + rand()) % max;
}


vector<vector <float> >  test(vector<Algo *> algorithms, int SIGMA, int N, int MINM, int MAXM, int OUTER_ITER , int INNER_ITER ){
    // QueryPerformanceFrequency(&freq);
    cout << "Running test : "
         << "SIGMA = " << SIGMA << " "
         << "MINM = " << MINM << " "
         << "MAXM = " << MAXM << " "
         << std::endl;

    vector<vector<float>> res(algorithms.size(), vector<float>(0));
    unsigned int m, glob = 0;
    for (int i = 0; i < N; i++) {
        TN[i] = (rand() + glob % 320) % SIGMA;
        glob = (glob * 11 + 30157) % 499;
    }
    for (int i = 0; i < MAX_PAT_LEN; i++) {
        P[i] = (rand() + glob) % SIGMA;
        glob = (glob * 123 + 3157) % 893;
    }

    unsigned int ii, ig, i;

    vector<int> patternLengths = {2,4,8, 16, 32, 64, 128, 256};

    for (int i = 0; i < algorithms.size(); ++i) {
        ids[i] = i;
    }

    for (int &m: patternLengths) {
        if( m < MINM || m > MAXM) continue;
        memset(execTime, 0, sizeof(float) * algorithms.size());

        for (ig = 0; ig < OUTER_ITER; ig++) {
            //  memset(T1, 0, TOTAL);
            //  memcpy(TN, T, N);

            for (int i = 0; i < m; i++) {
                P[i] = (rand() + glob) % SIGMA;
                glob = (glob * 123 + 3157) % 893;
            }

            memcpy(TN - m, P, m);
            memcpy(TN + N, P, m);

            for (ii = 0; ii < INNER_ITER; ii++) {

                int patpos = get_rand_int(N - m - 2);
                memcpy(TN + patpos, P, m);

                CLEAR_MATCHES;

                std::random_shuffle(ids, ids + algorithms.size());

                int consensus_result = -11;
                string consensus_name;

                for (i = 0; i < algorithms.size(); ++i) {
                    int id_i = ids[i];
                    try  {
                        if (algorithms[id_i]->is_applicable(SIGMA, m)) {
                            cout << "Running " << algorithms[id_i]->name << " for patlen = " << m << " and sigma = " << SIGMA << std::endl;
                            matches[id_i] = algorithms[id_i]->search(P, (int) m, TN, (int) N, &execTime[id_i]);
                            if (consensus_result == -11) {
                                consensus_result = matches[id_i];
                                consensus_name = algorithms[id_i]->name;
                            }
                            if (matches[id_i] != consensus_result) {
                                cout << "Result for algo " << algorithms[id_i]->name << " is " << matches[id_i]
                                     << " while for algo " + consensus_name + " is " + to_string(consensus_result)
                                     << "\nM = " << m << ", N = " << N << ", SIGMA = " << SIGMA << std::endl;

                                FIND_DIFF_MATCHES
                            }
                        } else {
                            matches[id_i] = -11;
                        } } catch(...) {
                        cout << "Error (((";
                    }
                    //  assert(matches[id_i] == matches[id_0]);
                }
            }
        }
        for (i = 0; i < algorithms.size(); ++i) {
            // cout << i << " " << algorithms[i]->name << " " << execTime[i] << std::endl;
            res[i].push_back(execTime[i] / (OUTER_ITER * INNER_ITER));
        }
    }
    return res;
}


