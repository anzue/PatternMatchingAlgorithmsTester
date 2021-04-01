#include "algorithms/consts.h"
#include <bitset>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(T + a))


int search_RZk_w3_byte2(unsigned char* P, int m, unsigned char* T, int n, int k, float* time)
{
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char* z = new char[mask + 1];

    QueryPerformanceCounter(&start);
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

    int pos1 = ndiv3;
    int pos2 = twondiv3;
    int pos3 = n - m;

    while (pos1 + m >= 0) {
        while (z[word(pos1) & mask] != 0 && z[word(pos2) & mask] != 0 && z[word(pos3) & mask] != 0) {
            pos1 -= m;
            pos2 -= m;
            pos3 -= m;
        }

        if (z[word(pos1 + 1) & mask] == 0 && pos1 >= 0) {
            for (i = 0; i < m && P[i] == T[pos1 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1);
            }
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= m - 1;

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv3) {
            for (i = 0; i < m && P[i] == T[pos2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos2);
            }
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= m - 1;

        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
            for (i = 0; i < m && P[i] == T[pos3 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos3);
            }
            pos3 -= RQS[T[pos3 - 1]];
        } else
            pos3 -= m - 1;
    }

    while (pos2 >= ndiv3) {
        while (z[word(pos2) & mask] != 0 && z[word(pos3) & mask] != 0) {
            pos2 -= m;
            pos3 -= m;
        }

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv3) {
            for (i = 0; i < m && P[i] == T[pos2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos2);
            }
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= m - 1;

        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
            for (i = 0; i < m && P[i] == T[pos3 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos3);
            }
            pos3 -= RQS[T[pos3 - 1]];
        } else
            pos3 -= m - 1;
    }

    while (pos3 >= twondiv3) {
        while (z[word(pos3) & mask] != 0) {
            pos3 -= m;
        }
        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
            for (i = 0; i < m && P[i] == T[pos3 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos3);
            }
            pos3 -= RQS[T[pos3 - 1]];
        } else
            pos3 -= m - 1;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;

    delete[] z;

    return count;
}
