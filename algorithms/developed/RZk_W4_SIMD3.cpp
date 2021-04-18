#include "algorithms/consts.h"
#include "algorithms/simd_defines_i128.h"

#include <bitset>
#include <intrin.h>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(T + a))

int RZk_w4_simd3(unsigned char* P, int m, unsigned char* T, int n, int k, float* time)
{
    // this array size must be >= 1 + MAX_PAT_LEN // 16
    __m128i packed_pattern[30];
    __m128i packed_text;
    bool eq;

    int i, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char z[mask + 1];

    QueryPerformanceCounter(&start);

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

    int ndiv4 = n / 4;
    int twondiv4 = n / 2;
    int threendiv4 = 3 * ndiv4;

    int pos0 = ndiv4;
    int pos1 = twondiv4;
    int pos2 = threendiv4;
    int pos3 = n - m;

    __m128i fill_m = _mm_set1_epi32(m - 1);
    __m128i packed_positions = _mm_setr_epi32(pos0, pos1, pos2, pos3);

    while (get0_i128(packed_positions) + m >= 0) {
        while (z[word(get0_i128(packed_positions)) & mask] != 0
            && z[word(get1_i128(packed_positions)) & mask] != 0
            && z[word(get2_i128(packed_positions)) & mask] != 0
            && z[word(get3_i128(packed_positions)) & mask] != 0) {
            packed_positions = _mm_sub_epi32(packed_positions, fill_m);
        }

        pos0 = get0_i128(packed_positions);
        pos1 = get1_i128(packed_positions);
        pos2 = get2_i128(packed_positions);
        pos3 = get3_i128(packed_positions);

        if (z[word(pos0 + 1) & mask] == 0 && pos0 >= 0) {
            check_i128(pos0);
            sub0_i128(RQS[T[pos0 - 1]]);
        } else
            sub0_i128(m - 1);

        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv4) {
            check_i128(pos1);
            sub1_i128(RQS[T[pos1 - 1]]);
        } else
            sub1_i128(m - 1);

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv4) {
            check_i128(pos2);
            sub2_i128(RQS[T[pos2 - 1]]);
        } else
            sub2_i128(m - 1);

        if (z[word(pos3 + 1) & mask] == 0 && pos3 > threendiv4) {
            check_i128(pos3);
            sub3_i128(RQS[T[pos3 - 1]]);
        } else
            sub3_i128(m - 1);
    }

    packed_positions = _mm_srli_si128(packed_positions, 4);

    while (get0_i128(packed_positions) >= ndiv4) {
        while (z[word(get0_i128(packed_positions)) & mask] != 0
            && z[word(get1_i128(packed_positions)) & mask] != 0
            && z[word(get2_i128(packed_positions)) & mask] != 0) {
            packed_positions = _mm_sub_epi32(packed_positions, fill_m);
        }

        pos1 = get0_i128(packed_positions);
        pos2 = get1_i128(packed_positions);
        pos3 = get2_i128(packed_positions);

        if (z[word(pos1 + 1) & mask] == 0 && pos1 > ndiv4) {
            check_i128(pos1);
            sub0_i128(RQS[T[pos1 - 1]]);
        } else
            sub0_i128(m - 1);

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv4) {
            check_i128(pos2);
            sub1_i128(RQS[T[pos2 - 1]]);
        } else
            sub1_i128(m - 1);

        if (z[word(pos3 + 1) & mask] == 0 && pos3 > threendiv4) {
            check_i128(pos3);
            sub2_i128(RQS[T[pos3 - 1]]);
        } else
            sub2_i128(m - 1);
    }

    packed_positions = _mm_srli_si128(packed_positions, 4);

    while (get0_i128(packed_positions) >= twondiv4) {
        while (z[word(get0_i128(packed_positions)) & mask] != 0 && z[word(get1_i128(packed_positions)) & mask] != 0) {
            packed_positions = _mm_sub_epi32(packed_positions, fill_m);
        }
        pos2 = get0_i128(packed_positions);
        pos3 = get1_i128(packed_positions);

        if (z[word(pos2 + 1) & mask] == 0 && pos2 > twondiv4) {
            check_i128(pos2);
            sub0_i128(RQS[T[pos2 - 1]]);
        } else
            sub0_i128(m - 1);

        if (z[word(pos3 + 1) & mask] == 0 && pos3 > threendiv4) {
            check_i128(pos3);
            sub1_i128(RQS[T[pos3 - 1]]);
        } else
            sub1_i128(m - 1);
    }

    pos3 = get1_i128(packed_positions);

    while (pos3 >= threendiv4) {
        while (z[word(pos3) & mask] != 0) {
            pos3 -= m;
        }
        if (z[word(pos3 + 1) & mask] == 0 && pos3 > threendiv4) {
            check_i128(pos3);
            pos3 -= RQS[T[pos3 - 1]];
        } else
            pos3 -= m - 1;
    }

    QueryPerformanceCounter(&finish);
    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;

    return count;
}
