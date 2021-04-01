#include "algorithms/consts.h"
#include <bitset>
#include <intrin.h>
#include <stdio.h>
#include <string.h>

#define word(a) *((unsigned short*)(T + a))
#define word_xor(pos)

#define get0(i128) _mm_cvtsi128_si32(i128)
#define get1(i128) _mm_cvtsi128_si32()
#define get2(i128) _mm_cvtsi128_si32(_mm_movehl_ps(i128))

#define _mm_extract_epi32(x, imm) \
    _mm_cvtsi128_si32(_mm_srli_si128((x), 4 * (imm)))

#define get(i128, position) _mm_extract_epi32(i128, position)



#define pack_last(P, mod)         \
    _mm_set_epi8(                 \
        mod > 0 ? *(P) : 0,       \
        mod > 1 ? *(P + 1) : 0,   \
        mod > 2 ? *(P + 2) : 0,   \
        mod > 3 ? *(P + 3) : 0,   \
        mod > 4 ? *(P + 4) : 0,   \
        mod > 5 ? *(P + 5) : 0,   \
        mod > 6 ? *(P + 6) : 0,   \
        mod > 7 ? *(P + 7) : 0,   \
        mod > 8 ? *(P + 8) : 0,   \
        mod > 9 ? *(P + 9) : 0,   \
        mod > 10 ? *(P + 10) : 0, \
        mod > 11 ? *(P + 11) : 0, \
        mod > 12 ? *(P + 12) : 0, \
        mod > 13 ? *(P + 13) : 0, \
        mod > 14 ? *(P + 14) : 0, \
        mod > 14 ? *(P + 14) : 0);

#define check(pos)                                                                                                                                        \
    __m128i packed_text;                                                                                                                                  \
    bool eq = true;                                                                                                                                       \
    for (i = pos + 15; eq && i < pos + m; i += 16) {                                                                                                      \
        packed_text = _mm_set_epi8(                                                                                                                       \
            T[i - 15], T[i - 14], T[i - 13], T[i - 12], T[i - 11], T[i - 10], T[i - 9], T[i - 8],                                                         \
            T[i - 7], T[i - 6], T[i - 5], T[i - 4], T[i - 3], T[i - 2], T[i - 1], T[i]);                                                                  \
        eq &= (_popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi8(packed_text, packed_pattern[(i - pos) / 16]))) == 16);                                          \
    }                                                                                                                                                     \
    if (eq) {                                                                                                                                             \
        packed_text = pack_last(T + pos + m - m % 16, m % 16);                                                                                                   \
        eq &= (_popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi8(packed_text, packed_pattern[(m) / 16]))) == 16);\
        if (eq) {                                                                                                                                         \
            MATCH(pos);                                                                                                                                   \
        }                                                                                                                                                 \
    }

int RZk_w3_simd1(unsigned char* P, int m, unsigned char* T, int n, int k, float* time)
{

    // this array size must be >= 1 + MAX_PAT_LEN // 16
    __m128i packed_pattern[30];

    int i, s, count = 0, RQS[MAX_SIGMA];
    int mask = (1 << k) - 1;
    int b = 8;
    char* z = new char[mask + 1];

    QueryPerformanceCounter(&start);

    for (i = 15; i < m; i += 16) {
        packed_pattern[i / 16] = _mm_set_epi8(
            P[i - 15], P[i - 14], P[i - 13], P[i - 12], P[i - 11], P[i - 10], P[i - 9], P[i - 8],
            P[i - 7], P[i - 6], P[i - 5], P[i - 4], P[i - 3], P[i - 2], P[i - 1], P[i]);
    }

    packed_pattern[m / 16] = pack_last(P + m - m % 16, m % 16);

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

    __m128i fill_m = _mm_set1_epi32(m - 1);
    __m128i packed_positions = _mm_setr_epi32(pos1, pos2, pos3, 0);

    while (get(packed_positions, 0) + m >= 0) {
        packed_positions = _mm_setr_epi32(pos1, pos2, pos3, 0);
        while (z[word(get(packed_positions, 0)) & mask] != 0 && z[word(get(packed_positions, 1)) & mask] != 0 && z[word(get(packed_positions, 2)) & mask] != 0) {
            packed_positions = _mm_sub_epi32(packed_positions, fill_m);
        }

        pos1 = get(packed_positions, 0);
        pos2 = get(packed_positions, 1);
        pos3 = get(packed_positions, 2);

        if (z[word(pos1 + 1) & mask] == 0 && pos1 >= 0) {
            check(pos1);
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
