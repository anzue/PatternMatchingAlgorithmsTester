#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))


int RZk_w2_byte_single_var(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    memset(z, 1, mask);

    for (i = 0; i < m - 1; ++i) {
        z[word(P + i) & mask] = 0;
    }
    for (i = 0; i < (1 << (k - b)); ++i) {
        z[(i << b) | P[m - 1]] = 0;
    }

    for (i = 0; i < MAX_SIGMA; ++i)
        RQS[i] = m + 1;
    for (i = m - 1; i >= 0; --i)
        RQS[P[i]] = i + 1;

    int pos0 = n - m;

    int mm1 = m-1;
    int m2m1 = m + m - 1;
    int m2 = m + m;
    START_COUNTER

    while (pos0 >= 0) {
        while (z[word(T + pos0) & mask] != 0 &&
               z[word(T + pos0 - m) & mask] != 0) {
            pos0 -= m2;
        }

        if(z[word(T + pos0) & mask] == 0){
            if (z[word(T + pos0 + 1) & mask] == 0) {
                for (i = 0; i < m && P[i] == T[pos0 + i]; ++i);
                if (i == m) {
                    MATCH(pos0);
                }
                pos0 -= RQS[T[pos0 - 1]];
            } else pos0 -= mm1;
        } else {
            pos0 -= m;
            if (z[word(T + pos0 + 1) & mask] == 0) {
                for (i = 0; i < m && P[i] == T[pos0 + i]; ++i) {
                };
                if (i == m) {
                    MATCH(pos0);
                }
                pos0 -= RQS[T[pos0 - 1]];
            } else
                pos0 -= mm1;
            }
    }

    FINISH_COUNTER
    
    delete[] z;

    return count;
}
