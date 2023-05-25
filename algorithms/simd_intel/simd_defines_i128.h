#ifndef SIMD_DEFINES_I128_H
#define SIMD_DEFINES_I128_H

#define get_i128(i128, position) _mm_cvtsi128_si32(_mm_srli_si128((i128), 4 * (position)))

// todo better extraction
#define get0_i128(i128) _mm_cvtsi128_si32(i128)
#define get1_i128(i128) _mm_cvtsi128_si32(_mm_srli_si128((i128), 4))
#define get2_i128(i128) _mm_cvtsi128_si32(_mm_srli_si128((i128), 8))
#define get3_i128(i128) _mm_cvtsi128_si32(_mm_srli_si128((i128), 12))
//_mm_cvtsi128_si32(_mm_movehl_ps(i128)) todo

#define pack_last_i128(P, mod)    \
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

#define sub0_i128(val)                \
    packed_positions = _mm_sub_epi32( \
        packed_positions,             \
        _mm_setr_epi32(val, 0, 0, 0));

#define sub1_i128(val)                \
    packed_positions = _mm_sub_epi32( \
        packed_positions,             \
        _mm_setr_epi32(0, val, 0, 0));

#define sub2_i128(val)                \
    packed_positions = _mm_sub_epi32( \
        packed_positions,             \
        _mm_setr_epi32(0, 0, val, 0));

#define sub3_i128(val)                \
    packed_positions = _mm_sub_epi32( \
        packed_positions,             \
        _mm_setr_epi32(0, 0, 0, val));

#define pack_pattern_i128()                                               \
    for (i = 15; i < m; i += 16) {                                        \
        packed_pattern[i / 16] = _mm_loadu_si128((__m128i*)(P + i - 15)); \
    }                                                                     \
    packed_pattern[m / 16] = pack_last_i128(P + m - m % 16, m % 16);

// todo maybe use _mm_sad_epu8
#define check_i128(pos)                                                                                          \
    eq = true;                                                                                                   \
    for (i = pos + 15; eq && i < pos + m; i += 16) {                                                             \
        packed_text = _mm_loadu_si128((__m128i*)&T[i - 15]);                                                     \
        eq &= (_popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi8(packed_text, packed_pattern[(i - pos) / 16]))) == 16); \
    }                                                                                                            \
    if (eq) {                                                                                                    \
        packed_text = pack_last_i128(T + pos + m - m % 16, m % 16);                                              \
        eq &= (_popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi8(packed_text, packed_pattern[(m) / 16]))) == 16);       \
        if (eq) {                                                                                                \
            MATCH(pos);                                                                                          \
        }                                                                                                        \
    }

#define check_i128_ptr(T_ptr)                                                                                            \
    eq = true;                                                                                                           \
    cout << "Check " << T_ptr - T << "\n";                                                                               \
    for (i = 15; eq && i < m; i += 16) {                                                                                 \
        packed_text = _mm_loadu_si128((__m128i*)(T_ptr + i - 15));                                                       \
        eq &= (_popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi8(packed_text, packed_pattern[i / 16]))) == 16);                 \
        cout << i << " " << _mm_movemask_epi8(_mm_cmpeq_epi8(packed_text, packed_pattern[i / 16])) << " " << eq << "\n"; \
        for (int j = i - 15; j <= i; ++j)                                                                                \
            cout << (int)T_ptr[j] << " " << (int)P[j] << "\n";                                                           \
    }                                                                                                                    \
    if (eq) {                                                                                                            \
        packed_text = pack_last_i128(T_ptr + m - m % 16, m % 16);                                                        \
        eq &= (_popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi8(packed_text, packed_pattern[m / 16]))) == 16);                 \
        if (eq) {                                                                                                        \
            MATCH(T_ptr - T);                                                                                            \
        }                                                                                                                \
    }                                                                                                                    \
    cout << eq << "\n";

#define alpha_i128 16

#define SIMDcompare_i128(x, y) \
    _mm_movemask_epi8(_mm_cmpeq_epi8(_mm_loadu_si128(x), _mm_set1_epi8(y)))

#define check_cmp_i128(pos, lim)                                                \
    found = UINT_MAX;                                                           \
    for (_j = 0; _j < m; ++_j) {                                                \
        found = found & SIMDcompare_i128((__m128i*)(T + pos + _j - 15), P[_j]); \
        if (found == 0)                                                         \
            break;                                                              \
    }                                                                           \
    MULTIMATCH(pos - 15, found, lim);

#endif // SIMD_DEFINES_I128_H
