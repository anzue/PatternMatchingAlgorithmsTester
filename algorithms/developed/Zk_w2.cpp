#include <stdio.h>
#include <string.h>
#include <cassert>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))

int Zk_w2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, QS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    assert(m >= 4);

    START_TIMER
    memset(z, 1, mask);

    for (i = 0; i < m - 1; ++i) {
        z[word(P + i) & mask] = 0;
    }
    for (i = 0; i < (1 << b); ++i) {
        z[((P[m - 1] << b) | i) & mask] = 0;
    }

    for (i = 0; i < SIGMA; ++i)
        QS[i] = m + 1;
    for (i = 0; i < m; ++i)
        QS[P[i]] = m - i;

    int pos0 = m - 2;
    int pos1 = n / 2;
    while (pos1 < n) {

        while (z[word(T + pos0) & mask] != 0 &&
               z[word(T + pos1) & mask] != 0) {
            pos0 += m - 1;
            pos1 += m - 1;
        }

        if (z[word(T + pos0 - 1) & mask] == 0 && pos0 < n / 2) {
            for (i = 0; i < m && P[i] == T[pos0 - m + 2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos0 - m + 2);
            }
            pos0 += QS[T[pos0 + 2]];
          //  cout << "1" << pos0 << " " << pos1 << "\n";
        } else
            pos0 += m - 2;

        if (z[word(T + pos1 - 1) & mask] == 0 && pos1 < n) {

            for (i = 0; i < m && P[i] == T[pos1 - m + 2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1 - m + 2);
            }
            pos1 += QS[T[pos1 + 2]];
         //   cout << "2 " << pos0 << " " << pos1 << "\n";
        } else
            pos1 += m - 2;
    //    cout << pos0 << " " << n / 2 << " " << pos1 << " " << n << " " << m << std::endl;
    }

    while (pos0 < n / 2) {

        while (z[word(T + pos0) & mask] != 0) {
            pos0 += m - 1;
        }
        if (z[word(T + pos0 - 1) & mask] == 0 && pos0 - m + 2 < n / 2) {
            for (i = 0; i < m && P[i] == T[pos0 - m + 2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos0 - m + 2);
            }
            pos0 += QS[T[pos0 + 2]];
        } else
            pos0 += m - 2;
    }

    FINISH_TIMER

    delete[] z;

    return count;
}
