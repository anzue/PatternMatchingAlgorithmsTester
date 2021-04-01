#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"

#define word(a) *((unsigned short*)(a))

int search_Zk_w2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
    int i, s, count = 0, QS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char *z = new char[mask + 1];

    assert(m >= 4);

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

    int pos1 = m - 2;
    int pos2 = n / 2;
    while (pos2 < n) {

        while (z[word(T + pos1) & mask] != 0 &&
               z[word(T + pos2) & mask] != 0) {
            pos1 += m - 1;
            pos2 += m - 1;
        }

        if (z[word(T + pos1 - 1) & mask] == 0 && pos1 < n / 2) {
            for (i = 0; i < m && P[i] == T[pos1 - m + 2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1 - m + 2);
            }
            pos1 += QS[T[pos1 + 2]];
          //  cout << "1" << pos1 << " " << pos2 << "\n";
        } else
            pos1 += m - 2;

        if (z[word(T + pos2 - 1) & mask] == 0 && pos2 < n) {

            for (i = 0; i < m && P[i] == T[pos2 - m + 2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos2 - m + 2);
            }
            pos2 += QS[T[pos2 + 2]];
         //   cout << "2 " << pos1 << " " << pos2 << "\n";
        } else
            pos2 += m - 2;
    //    cout << pos1 << " " << n / 2 << " " << pos2 << " " << n << " " << m << std::endl;
    }

    while (pos1 < n / 2) {

        while (z[word(T + pos1) & mask] != 0) {
            pos1 += m - 1;
        }
        if (z[word(T + pos1 - 1) & mask] == 0 && pos1 - m + 2 < n / 2) {
            for (i = 0; i < m && P[i] == T[pos1 - m + 2 + i]; ++i) {
            };
            if (i == m) {
                MATCH(pos1 - m + 2);
            }
            pos1 += QS[T[pos1 + 2]];
        } else
            pos1 += m - 2;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;

    delete[] z;

    return count;
}
