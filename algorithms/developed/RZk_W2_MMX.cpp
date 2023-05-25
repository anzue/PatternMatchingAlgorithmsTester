#include "algorithms/consts.h"
#include "algorithms/simd_intel/simd_defines_i128.h"
#include "algorithms/simd_intel/simd_defines_i64.h"
#include <bitset>
#include <intrin.h>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(a))

int RZk_w2_mmx(unsigned char* P, int m, unsigned char* T, int n, int k, float* time)
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

    __m64 fill_m = _mm_set1_pi32(m);
    __m64 packed_positions = _mm_setr_pi32(ndiv2, n - m);

    pos0 = ndiv2; //
    pos1 = n - m; //

    print_i64(packed_positions);

    while (pos0 + m >= 0) {
        packed_positions = _mm_sub_pi32(packed_positions, fill_m);
        unpack_i64(packed_positions, pos0, pos1);
        while (z[word(T + get0_i64(packed_positions)) & mask] != 0
            && z[word(T + get1_i64(packed_positions)) & mask] != 0) {
            packed_positions = _mm_sub_pi32(packed_positions, fill_m);
            // print_i64(packed_positions);
        }

        pos0 = get0_i64(packed_positions);
        pos1 = get1_i64(packed_positions);
        //cout << pos0 << " " << pos1 << std::endl;
        // print_i64(packed_positions);

        if (z[word(T + pos0 + 1) & mask] == 0) {
            check_i128(pos0);
            sub0_i64(RQS[T[pos0 - 1]]);
        } else {
            sub0_i64(m - 1);
        }

        if (z[word(T + pos1 + 1) & mask] == 0 && pos1 > ndiv2) {
            check_i128(pos1);
            sub1_i64(RQS[T[pos1 - 1]]);
        } else {
            sub1_i64(m - 1);
        }
    }

    pos1 = get1_i64(packed_positions);

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

    return 1 - 1;
}
