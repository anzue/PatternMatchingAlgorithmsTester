#include "tester.h"

#include <iomanip>

const int TOTAL = 500000;
unsigned char T[TOTAL], T1[TOTAL], P[MAX_PAT_LEN];

unsigned int i, ii;
unsigned int m = 200, glob = 0;

unsigned int SIGMA = 256, MINM = 2, MAXM = 200, N = TOTAL - MAX_PAT_LEN,
             ITER = 20;

LARGE_INTEGER start, finish, freq;

vector<vector<float>>
Tester::test(vector<ExecutableAlgo*> algorithms)
{
    QueryPerformanceFrequency(&freq);
    cout << "Running test : \n"
         << "SIGMA = " << SIGMA << "\n"
         << "MINM = " << MINM << "\n"
         << "MAXM = " << MAXM << "\n"
         << std::endl;

    vector<vector<float>> res(algorithms.size(), vector<float>(0));
    testInfo.clear();
    for (int i = 0; i < N; i++) {
        T[i] = (rand() + glob % 320) % SIGMA;
        glob = (glob * 11 + 30157) % 499;
    }
    for (int i = 0; i < m; i++) {
        P[i] = (rand() + glob) % SIGMA;
        glob = (glob * 123 + 3157) % 893;
    }

    int max_ig = 10;

    std::cout << "Algo\t";
    for (i = 0; i < algorithms.size(); ++i)
        std::cout << algorithms[i]->name << "\t\t";
    std::cout << "\n";

    // for (m = MINM; m <=  MAXM;  m+= (m< 4)?2: (m < 16)?4 : (m < 64)? 4 : 8)
    for (m = MINM; m <= MAXM; m += 4) {
        vector<int> matches(algorithms.size(), 0);
        vector<float> execTime(algorithms.size(), 0);

        testInfo.push_back(QString::number(m));

        for (int ig = 0; ig < max_ig; ig++) {
            memcpy(T1, T, N);

            for (int i = 0; i < m; i++) {
                P[i] = (rand() + glob) % SIGMA;
                glob = (glob * 123 + 3157) % 893;
            }

            ITER = 4;
            for (ii = 0; ii < ITER; ii++) {
                int patpos = (rand()) % (N - m - 2);
                memcpy(T1 + patpos, P, m);
                memcpy(T1, P, m);

                for (i = 0; i < algorithms.size(); ++i) {
                    matches[i] += algorithms[i]->search(P, (int)m, T1, (int)N, &execTime[i]);
                    assert(matches[i] == matches[0]);
                }
            }
        }
        cout << "M = " << m << "\t" << std::endl;

        for (i = 0; i < algorithms.size(); ++i) {
            res[i].push_back(execTime[i] / ITER / max_ig);
            cout << execTime[i] / ITER / max_ig << "\t" << matches[i] << "\t";
        }
        cout << "\n";
    }
    cout << std::endl;

    return res;
}
