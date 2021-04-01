#include <iomanip>

#include "algorithms/consts.h"
#include "mainchart.h"
#include "ui/progressbar.h"
#include "ui_mainchart.h"

LARGE_INTEGER start, finish, freq;
unsigned char T[TOTAL], T1[TOTAL], P[MAX_PAT_LEN];
#define TN (T1 + m)

unsigned int SIGMA = 256;

QStringList MainChart::getTestPatternLengths()
{
    QStringList res;
    for (QString& mstr : patternLengths) {
        int m = mstr.toInt();

        if (m >= MINM && m <= MAXM)
            res.append(mstr);
    }
    return res;
}

vector<vector<float>> MainChart::test(vector<Algo*> algorithms)
{
    QueryPerformanceFrequency(&freq);
    cout << "Running test : \n"
         << "SIGMA = " << SIGMA << "\n"
         << "MINM = " << MINM << "\n"
         << "MAXM = " << MAXM << "\n"
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

    auto patternLengths = getTestPatternLengths();

    progressBar->mProgress->setMaximum(patternLengths.size());
    progressBar->mProgress->setValue(0);

    for (QString& mstr : patternLengths) {
        m = mstr.toInt();

        progressBar->mProgress->setValue(progressBar->mProgress->value() + 1);
        progressBar->mProgress->setFormat("M progress " + QString::number(m));

        vector<int> matches(algorithms.size(), 0);
        vector<float> execTime(algorithms.size(), 0);

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

                int patpos = (rand()) % (N - m - 2);
                memcpy(TN + patpos, P, m);

                CLEAR_MATCHES

                for (i = 0; i < algorithms.size(); ++i) {
                    matches[i] = algorithms[i]->search(P, (int)m, TN, (int)N, &execTime[i]);

                    if (matches[i] != matches[0]) {
                        cout << "Result for algo " << algorithms[i]->name << " is " << matches[i]
                             << " while for algo " + algorithms[0]->name + " is " + to_string(matches[0])
                             << "\nM = " << m << ", SIGMA = " << SIGMA << std::endl;

                        FIND_DIFF_MATCHES
                    }
                    assert(matches[i] == matches[0]);
                }
            }
        }
        for (i = 0; i < algorithms.size(); ++i) {
            res[i].push_back(execTime[i] / (OUTER_ITER * INNER_ITER));
        }
    }
    return res;
}
