#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))

int Zk_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {

    assert(m >= 4);

    int i, s, count = 0, QS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    START_COUNTER
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

    int pos = -1;
    while (pos < n) {
        do {
            pos += m - 1;
            while (z[word(T + pos) & mask] != 0) {
                pos += m - 1;
            }
            pos -= 1;
        } while (z[word(T + pos) & mask] != 0);

        for (i = 0; i < m && P[i] == T[pos - m + 3 + i]; ++i) {
        };
        if (i == m)  {
            MATCH(pos - m + 3);
        }
        pos += QS[T[pos + 3]] - m + 2;
    }

    FINISH_COUNTER
    

    delete[] z;
    return count - 1;
}
