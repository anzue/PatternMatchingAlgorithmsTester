#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))


int RZk_w2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    QueryPerformanceCounter(&start);
    memset(z, 1, mask);

    for (i = 0; i < m - 1; ++i) {
        z[word(P + i) & mask] = 0;
    }
    for (i = 0; i < (1 << (k - b)); ++i) {
        z[(i << b) | P[m - 1]] = 0;
    }

    for (i = 0; i < SIGMA; ++i)
        RQS[i] = m + 1;
    for (i = m - 1; i >= 0; --i)
        RQS[P[i]] = i + 1;

    int ndiv2 = n / 2;

    int pos0 = ndiv2;
    int pos1 = n - m;

    while (pos0 + m >= 0) {
        while (z[word(T + pos0) & mask] != 0 &&
               z[word(T + pos1) & mask] != 0) {
            pos0 -= m;
            pos1 -= m;
        }

        if (z[word(T + pos0 + 1) & mask] == 0) {
            for (i = 0; i < m && P[i] == T[pos0 + i]; ++i);
            if (i == m) {
                MATCH(pos0);
            }
            pos0 -= RQS[T[pos0 - 1]];

        } else {
            pos0 -= m - 1;

        }

        if (z[word(T + pos1 + 1) & mask] == 0 && pos1 > ndiv2) {
            for (i = 0; i < m && P[i] == T[pos1 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1);
            }
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= m - 1;
    }

    while (pos1 > ndiv2) {
        while (z[word(T + pos1) & mask] != 0) {
            pos1 -= m;
        }
        if (z[word(T + pos1 + 1) & mask] == 0 && pos1 > ndiv2) {
            for (i = 0; i < m && P[i] == T[pos1 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1);
            }
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= m - 1;
    }


  //  cout << pos0 << " " << pos1 << " "<< m << " "<< n << std::endl;

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
    delete[] z;

    return count - 1;
}
