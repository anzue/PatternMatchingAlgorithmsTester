#include "algos.h"
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(a))

int search_RZk_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* sum)
{
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
        for (i = 0; i < m && P[i] == T[pos + i]; ++i)
            ;
        if (i == m) {
            count++;
        }
        pos += m - RQS[T[pos - 1]];

    } while (pos >= m);

    QueryPerformanceCounter(&finish);
    *sum += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
    return count;
}
