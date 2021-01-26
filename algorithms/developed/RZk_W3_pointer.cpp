#include "algorithms/consts.h"
#include <bitset>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(a))

int search_RZk_w3_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char z[mask + 1];

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

    unsigned char* ndiv3 = T + n / 3;
    unsigned char* twondiv3 = T + 2 * n / 3;

    unsigned char* pos1 = ndiv3;
    unsigned char* pos2 = twondiv3;
    unsigned char* pos3 = T + n - m;

    while (pos1 >= T) {
        while (z[word(pos1) & mask] != 0 &&
               z[word(pos2) & mask] != 0 &&
               z[word(pos3) & mask] != 0) {
            pos1 -= m;
            pos2 -= m;
            pos3 -= m;
        }

        if (z[word(pos1 + 1) & mask] == 0) {
            for (i = 0; i < m && P[i] == *(pos1 + i); ++i) {
            };
            if (i == m) {
                count++;
            }
            pos1 -= RQS[*(pos1 - 1)];
        } else
            pos1 -= m - 1;

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv3) {
            for (i = 0; i < m && P[i] == *(pos2 + i); ++i) {
            };
            if (i == m) {
                count++;
            }
            pos2 -= RQS[*(pos2 - 1)];
        } else
            pos2 -= m - 1;

        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
            for (i = 0; i < m && P[i] == *(pos3 + i); ++i) {
            };
            if (i == m) {
                count++;
            }
            pos3 -= RQS[*(pos3 - 1)];
        } else
            pos3 -= m - 1;
    }

    while (pos2 >= ndiv3) {
        while (z[word(pos2) & mask] != 0 &&
               z[word(pos3) & mask] != 0) {
            pos2 -= m;
            pos3 -= m;
        }

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv3) {
            for (i = 0; i < m && P[i] == *(pos2 + i); ++i) {
            };
            if (i == m) {
                count++;
            }
            pos2 -= RQS[*(pos2 - 1)];
        } else
            pos2 -= m - 1;

        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
            for (i = 0; i < m && P[i] == *(pos3 + i); ++i) {
            };
            if (i == m) {
                count++;
            }
            pos3 -= RQS[*(pos3 - 1)];
        } else
            pos3 -= m - 1;
    }

    while (pos3 >= twondiv3) {
        while (z[word(pos3) & mask] != 0) {
            pos3 -= m;
        }
        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
            for (i = 0; i < m && P[i] == *(pos3 + i); ++i) {
            };
            if (i == m) {
                count++;
            }
            pos3 -= RQS[*(pos3 - 1)];
        } else
            pos3 -= m - 1;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;
    return count;
}
