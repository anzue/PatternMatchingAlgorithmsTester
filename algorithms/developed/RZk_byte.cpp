#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))

int RZk_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    START_TIMER
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

    int pos = n;
    do {
        do {
            pos -= m;
            while (z[word(T + pos) & mask] != 0) {
                pos -= m;
            }
            pos += 1;
        } while (z[word(T + pos) & mask] != 0);
        pos -= 1;
        for (i = 0; i < m && P[i] == T[pos + i]; ++i) {
        };
        if (i == m) {
            MATCH(pos);
        }
        pos += m - RQS[T[pos - 1]];

    } while (pos >= 0);

    FINISH_TIMER
    delete[] z;

    return count - 1;
}
