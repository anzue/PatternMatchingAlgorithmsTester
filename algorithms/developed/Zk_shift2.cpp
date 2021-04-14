#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))

int Zk_shift2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {

    assert(m >= 4);

    int i, s, count = 0, QS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    QueryPerformanceCounter(&start);
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

    int pos = m-1;
    int twom = m + m - 2;

    while (pos < n + m) {
        while(z[word(T + pos) & mask] != 0 &&
              z[word(T + pos + m - 1) & mask] != 0
              ){
            pos += twom;
        }
        if(z[word(T + pos) & mask] != 0 ){
            pos += m-1;
        }

        for (i = 0; i < m && P[i] == T[pos - m + 2 + i]; ++i) {
        };
        if (i == m) {
            MATCH(pos - m + 2);
        }
        pos += QS[T[pos + 2]];
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;

    delete[] z;
    return count - 1;
}
