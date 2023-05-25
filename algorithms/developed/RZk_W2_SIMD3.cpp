#include <bitset>
#include <intrin.h>
#include <stdio.h>
#include <string.h>

#include "algorithms/consts.h"
#include "algorithms/simd_intel/simd_defines_i128.h"

#define word(a) *((unsigned short*)(a))

int RZk_w2_simd3(unsigned char* P, int m, unsigned char* T, int n, int k, float* time)
{
    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char z[mask + 1];
    __m128i packed_pattern[30];
    __m128i packed_text;
    bool eq;

    int ndiv2 = n / 2;
    int pos0, pos1;

    START_COUNTER
    memset(z, 1, mask);

    pack_pattern_i128();

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

    __m128i fill_m = _mm_set1_epi32(m);
    __m128i packed_positions = _mm_setr_epi32(ndiv2, n - m, 0, 0);

    while (get0_i128(packed_positions) + m >= 0) {

        while (z[word(T + get0_i128(packed_positions)) & mask] != 0
            && z[word(T + get1_i128(packed_positions)) & mask] != 0) {
            packed_positions = _mm_sub_epi32(packed_positions, fill_m);
        }

        pos0 = get0_i128(packed_positions);
        pos1 = get1_i128(packed_positions);
        if (z[word(T + pos0 + 1) & mask] == 0) {
            check_i128(pos0);
            sub0_i128(RQS[T[pos0 - 1]]);
        } else {
            sub0_i128(m - 1);
        }

        if (z[word(T + pos1 + 1) & mask] == 0 && pos1 > ndiv2) {
            check_i128(pos1);
            sub1_i128(RQS[T[pos1 - 1]]);
        } else {
            sub1_i128(m - 1);
        }
    }

    pos1 = get1_i128(packed_positions);

    while (pos1 > ndiv2) {
        while (z[word(T + pos1) & mask] != 0) {
            pos1 -= m;
        }
        if (z[word(T + pos1 + 1) & mask] == 0 && pos1 > ndiv2) {
            check_i128(pos1);
            pos1 -= RQS[T[pos1 - 1]];
        } else
            pos1 -= m - 1;
    }

    FINISH_COUNTER
    
    return count - 1;
}
