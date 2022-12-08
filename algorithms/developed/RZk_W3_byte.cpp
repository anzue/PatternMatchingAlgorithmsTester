#include "algorithms/consts.h"
#include <bitset>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(T + a))


int RZk_w3_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time)
{
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char* z = new char[mask + 1];

    START_TIMER
    memset(z, 1, mask);

    for (i = 0; i < m - 1; ++i) {
        z[(*(unsigned short*)(P + i)) & mask] = 0;
    }
    for (i = 0; i < (1 << (k - b)); ++i) {
        z[(i << b) | P[m - 1]] = 0;
    }

    for (i = 0; i < SIGMA; ++i)
        RQS[i] = m + 1;
    for (i = m - 1; i >= 0; --i)
        RQS[P[i]] = i + 1;

    int ndiv3 = n / 3;
    int twondiv3 = 2 * n / 3;

    int pos0 = ndiv3;
    int pos1 = twondiv3;
    int pos2 = n - m;

    while (pos0 + m >= 0) {
        while (z[word(pos0) & mask] != 0 && z[word(pos1) & mask] != 0 && z[word(pos2) & mask] != 0) {
            pos0 -= m;
            pos1 -= m;
            pos2 -= m;
        }

        if (z[word(pos0 + 1) & mask] == 0 && pos0 >= 0) {
            for (i = 0; i < m && P[i] == T[pos0 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos0);
            }
            pos0 -= RQS[T[pos0 - 1]];
        } else
            pos0 -= m - 1;

        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv3) {
            for (i = 0; i < m && P[i] == T[pos1 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1);
            }
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= m - 1;

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv3) {
            for (i = 0; i < m && P[i] == T[pos2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos2);
            }
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= m - 1;
    }

    while (pos1 >= ndiv3) {
        while (z[word(pos1) & mask] != 0 && z[word(pos2) & mask] != 0) {
            pos1 -= m;
            pos2 -= m;
        }

        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv3) {
            for (i = 0; i < m && P[i] == T[pos1 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1);
            }
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= m - 1;

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv3) {
            for (i = 0; i < m && P[i] == T[pos2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos2);
            }
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= m - 1;
    }

    while (pos2 >= twondiv3) {
        while (z[word(pos2) & mask] != 0) {
            pos2 -= m;
        }
        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv3) {
            for (i = 0; i < m && P[i] == T[pos2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos2);
            }
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= m - 1;
    }

    FINISH_TIMER

    delete[] z;

    return count;
}
