#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

int search_Z8_byte(unsigned char* P, int m, unsigned char* T, int n, float* time) {

    assert(m >= 4);

    int i, s, count = 0, QS[MAX_SIGMA];
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

    int pos = -1;
    while (pos < n + m) {
        do {
            pos += m - 1;
            while (z[T[pos]] != 0) {
                pos += m - 1;
            }
            pos -= 1;
        } while (z[T[pos]] != 0);

        for (i = 0; i < m && P[i] == T[pos - m + 1 + i]; ++i) {
        };
        if (i == m)  {
            MATCH(pos - m + 1);
        }
        pos += QS[T[pos + 1]] - m + 1;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;

    return count - 1;
}
