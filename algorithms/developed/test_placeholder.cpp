#include <bitset>
#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"
#include "algorithms/simd_defines_i128.h"

#define word(a) *((unsigned short*)(T + a))

int test_algo(unsigned char* P, int m, unsigned char* T, int n, int k, float* time){
    // this array size must be >= 1 + MAX_PAT_LEN // 16
    __m128i packed_pattern[30];
    __m128i packed_text;
    bool eq;

    int i, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char z[mask + 1];
    int mm1 = m - 1;

    START_TIMER

    pack_pattern_i128();
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


    __m128i fill_m = _mm_set1_epi32(m - 1);
    __m128i packed_positions = _mm_setr_epi32(ndiv3, twondiv3, n - m, 0);

    int &pos0 = *((int*)(&packed_positions));
    int &pos1 = *((int*)(&packed_positions) + 1);
    int &pos2 = *((int*)(&packed_positions) + 2);

    while (pos0 + m >= 0) {
        while (z[word(pos0) & mask] != 0
            && z[word(pos1) & mask] != 0
            && z[word(pos2) & mask] != 0) {
            packed_positions = _mm_sub_epi32(packed_positions, fill_m);
        }

        if (z[word(pos0 + 1) & mask] == 0 && pos0 >= 0) {
            check_i128(pos0);
            pos0 -= RQS[T[pos0 - 1]];
        } else
            pos0 -= mm1;

        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv3) {
            check_i128(pos1);
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= mm1;

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv3) {
            check_i128(pos2);
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= mm1;
    }

    while (pos1 >= ndiv3) {
        while (z[word(pos1) & mask] != 0 && z[word(pos2) & mask] != 0) {
            packed_positions = _mm_sub_epi32(packed_positions, fill_m);
        }

        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv3) {
            check_i128(pos1);
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= mm1;

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv3) {
            check_i128(pos2);
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= mm1;
    }

    while (pos2 >= twondiv3) {
        while (z[word(pos2) & mask] != 0) {
            pos2 -= m;
        }
        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv3) {
            check_i128(pos2);
            pos2 -= RQS[T[pos2 - 1]];
        } else
            pos2 -= mm1;
    }

    FINISH_TIMER

    return count;
}
