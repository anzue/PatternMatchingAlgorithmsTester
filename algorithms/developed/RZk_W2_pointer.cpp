#include "algorithms/consts.h"
#include <bitset>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(a))

int RZk_w2_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    START_COUNTER
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

    unsigned char* pos0 = T + n / 2;
    unsigned char* pos1 = T + n - m;

    while (pos0 + m >= T) {
        while (z[word(pos0) & mask] != 0 &&
               z[word(pos1) & mask] != 0) {
            pos0 -= m;
            pos1 -= m;
        }
        if (z[word(pos0 + 1) & mask] == 0) {
            for (i = 0; i < m && P[i] == *(pos0 + i); ++i) {
            };
            if (i == m) {
                MATCH(pos0 - T);
            }
            pos0 -= RQS[*(pos0 - 1)];
        } else
            pos0 -= m - 1;

        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv2) {
            for (i = 0; i < m && P[i] == *(pos1 + i); ++i) {
            };
            if (i == m) {
                MATCH(pos1 - T);
            }
            pos1 -= RQS[*(pos1 - 1)];
        } else
            pos1 -= m - 1;
    }

    while (pos1 > ndiv2) {
        while (z[word(pos1) & mask] != 0) {
            pos1 -= m;
        }
        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv2) {
            for (i = 0; i < m && P[i] == *(pos1 + i); ++i) {
            };
            if (i == m) {
                MATCH(pos1 - T);
            }
            pos1 -= RQS[*(pos1 - 1)];
        } else
            pos1 -= m - 1;
    }

    FINISH_COUNTER
    
    delete[] z;

    return count - 1;
}
