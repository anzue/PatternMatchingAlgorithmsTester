#include "algorithms/consts.h"
#include <bitset>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(a))

int search_RZk_w2_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
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

    unsigned char* ndiv2 = T + n / 2;

    unsigned char* pos1 = T + n / 2;
    unsigned char* pos2 = T + n - m;

    while (pos1 >= T) {
        while (z[word(pos1) & mask] != 0 &&
               z[word(pos2) & mask] != 0) {
            pos1 -= m;
            pos2 -= m;
        }
        if (z[word(pos1 + 1) & mask] == 0) {
            for (i = 0; i < m && P[i] == *(pos1 + i); ++i) {
            };
            if (i == m) {
                MATCH(pos1 - T);
            }
            pos1 -= RQS[*(pos1 - 1)];
        } else
            pos1 -= m - 1;

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv2) {
            for (i = 0; i < m && P[i] == *(pos2 + i); ++i) {
            };
            if (i == m) {
                MATCH(pos2 - T);
            }
            pos2 -= RQS[*(pos2 - 1)];
        } else
            pos2 -= m - 1;
    }

    while (pos2 > ndiv2) {
        while (z[word(pos2) & mask] != 0) {
            pos2 -= m;
        }
        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv2) {
            for (i = 0; i < m && P[i] == *(pos2 + i); ++i) {
            };
            if (i == m) {
                MATCH(pos2 - T);
            }
            pos2 -= RQS[*(pos2 - 1)];
        } else
            pos2 -= m - 1;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
    return count;
}
