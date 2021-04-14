#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

int Z8_w2_byte(unsigned char* P, int m, unsigned char* T, int n, float* time) {

    assert(m >= 4);

    int i, s, count = 0, QS[MAX_SIGMA];
    int b = 8;
    char z[256];

    QueryPerformanceCounter(&start);
    memset(z, 1, 256);

    for (i = 0; i < m; ++i) {
        z[P[i]] = 0;
    }

    for (i = 0; i < SIGMA; ++i)
        QS[i] = m + 1;
    for (i = 0; i < m; ++i)
        QS[P[i]] = m - i;

    int pos0 = m - 2;
    int pos1 = n / 2;

    while (pos0 < n / 2) {

        while (z[T[pos0]] != 0 &&
               z[T[pos1]] != 0) {
            pos0 += m - 1;
            pos1 += m - 1;
        }

        if (z[T[pos0 - 1]] == 0 && pos0 < n / 2) {
            for (i = 0; i < m && P[i] == T[pos0 - m + 1 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos0 - m + 1);
            }
            pos0 += QS[T[pos0 + 2]];
        } else
            pos0 += m - 2;

        if (z[T[pos1 - 1]] == 0 && pos1 < n) {

            for (i = 0; i < m && P[i] == T[pos1 - m + 2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1 - m + 2);
            }
            pos1 += QS[T[pos1 + 2]];
        } else
            pos1 += m - 2;
    }

    while (pos0 < n / 2) {

        while (z[T[pos0]] != 0) {
            pos0 += m - 1;
        }
        if (z[T[pos0 - 1]] == 0 && pos0 - m + 1 < n / 2) {
            for (i = 0; i < m && P[i] == T[pos0 - m + 1 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos0 - m + 1);
            }
            pos0 += QS[T[pos0 + 1]];
        } else
            pos0 += m - 2;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;

    return count - 1;
}
