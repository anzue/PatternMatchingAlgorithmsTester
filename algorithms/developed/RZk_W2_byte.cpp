#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))

int search_RZk_w2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char z[mask + 1];

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

    int pos1 = ndiv2;
    int pos2 = n - m;

    while (pos1 >= 0) {
        while (z[word(T + pos1) & mask] != 0 &&
               z[word(T + pos2) & mask] != 0) {
            pos1 -= m;
            pos2 -= m;
        }
        if (z[word(T + pos1 + 1) & mask] == 0) {
            for (i = 0; i < m && P[i] == T[pos1 + i]; ++i) {
            };
            if (i == m) {
                count++;
            }
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= m - 1;

        if (z[word(T + pos2 + 1) & mask] == 0 && pos2 > ndiv2) {
            for (i = 0; i < m && P[i] == T[pos2 + i]; ++i) {
            };
            if (i == m) {
                count++;
            }
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= m - 1;
    }

    while (pos2 > ndiv2) {
        while (z[word(T + pos2) & mask] != 0) {
            pos2 -= m;
        }
        if (z[word(T + pos2 + 1) & mask] == 0 && pos2 > ndiv2) {
            for (i = 0; i < m && P[i] == T[pos2 + i]; ++i) {
            };
            if (i == m) {
                count++;
            }
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= m - 1;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
    return count;
}
