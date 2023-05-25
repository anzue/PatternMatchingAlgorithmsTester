#ifndef SIMD_DEFINES_I64_H
#define SIMD_DEFINES_I64_H

#define get_i64(i64, position) _mm_cvtsi64_si32(_mm_srli_si64((i64), 32 * (position)))

#define get0_i64(i64) _mm_cvtsi64_si32((i64))
#define get1_i64(i64) _mm_cvtsi64_si32(_mm_srli_si64((i64), 32))

#define sub0_i64(val)                \
    packed_positions = _mm_sub_pi32( \
        packed_positions,            \
        _mm_setr_pi32(val, 0));

#define sub1_i64(val)                \
    packed_positions = _mm_sub_pi32( \
        packed_positions,            \
        _mm_setr_pi32(0, val));

#define unpack_i64(val, x, y)           \
    {                                   \
        int tmp[2];                     \
        memcpy(tmp, &val, sizeof(val)); \
        x = tmp[0];                     \
        y = tmp[1];                     \
    }

#define print_i64(i64)                                \
    {                                                 \
        int tmp[2];                                   \
        memcpy(tmp, &i64, sizeof(i64));               \
        cout << tmp[0] << " " << tmp[1] << std::endl; \
    }

#endif // SIMD_DEFINES_I64_H
