#include <algorithm>
#include <iomanip>

#include "algorithms/consts.h"
#include "mainchart.h"
#include "ui/progressbar.h"
#include "ui_mainchart.h"

LARGE_INTEGER start, finish, freq;
unsigned char T[TOTAL], T1[TOTAL], P[MAX_PAT_LEN];
#define TN (T1 + MAXM + MAXM + 1)

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

const int MAX_ALGO_COUNT = 100;

int matches[MAX_ALGO_COUNT];
float execTime[MAX_ALGO_COUNT];
int ids[MAX_ALGO_COUNT];


int get_rand_int(int max){
    return (rand() * RAND_MAX + rand()) % max;
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
    unsigned int m,  glob = 0;
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

    for (int i = 0; i < algorithms.size(); ++i) {
        ids[i] = i;
    }

    for (QString& mstr : patternLengths) {
        m = mstr.toInt();

        progressBar->mProgress->setValue(progressBar->mProgress->value() + 1);
        progressBar->mProgress->setFormat("M progress " + QString::number(m));

        memset(execTime, 0, sizeof(float) * algorithms.size());


        for (ig = 0; ig < OUTER_ITER; ig++)
               {
                   for (int i = 0; i < N; i++)
                   {
                       TN[i] = (rand() + glob % 320) % SIGMA;
                       glob = (glob * 11 + 30157) % 499;
                   }

                   //  memset(T1, 0, TOTAL);
                   //  memcpy(TN, T, N);

                   for (int i = 0; i < m; i++)
                   {
                       P[i] = (rand() + glob) % SIGMA;
                       glob = (glob * 123 + 3157) % 893;
                   }

                //   memcpy(TN, T1, N);

                   memcpy(TN - m, P, m);
                   memcpy(TN - 2*m - 1, P, m);
                   memcpy(TN + N, P, m);

                   for (ii = 0; ii < INNER_ITER; ii++)
                   {

                       int patpos = get_rand_int(N - m - 2);
                       memcpy(TN + patpos, P, m);

                       CLEAR_MATCHES;

                       std::random_shuffle(ids, ids + algorithms.size());

                       int consensus_result = -11;
                       string consensus_name;

                       for (i = 0; i < algorithms.size(); ++i)
                       {
                           int id_i = ids[i];
                           if (algorithms[id_i]->is_applicable(SIGMA, m))
                           {
                               // cout << "Running " << algorithms[id_i]->name << " for patlen = " << m << " and sigma = " << SIGMA << std::endl;
                               matches[id_i] = algorithms[id_i]->search(P, (int)m, TN, (int)N, &execTime[id_i]);
                               if (consensus_result == -11)
                               {
                                   consensus_result = matches[id_i];
                                   consensus_name = algorithms[id_i]->name;
                               }
                               if (matches[id_i] != consensus_result)
                               {
                                   cout << "Result for algo " << algorithms[id_i]->name << " is " << matches[id_i]
                                        << " while for algo " + consensus_name + " is " + to_string(consensus_result)
                                        << "\nM = " << m << ", N = " << N << ", SIGMA = " << SIGMA << std::endl;

                                   FIND_DIFF_MATCHES
                               }
                           }
                           else
                           {
                               matches[id_i] = -11;
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
