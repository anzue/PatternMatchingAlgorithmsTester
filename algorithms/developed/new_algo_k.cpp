#include "algorithms/consts.h"

#define LONG64 long long

//#define K 2


#define PARENS ()

#define EXPAND(...) EXPAND4(EXPAND4(EXPAND4(EXPAND4(__VA_ARGS__))))
#define EXPAND4(...) EXPAND3(EXPAND3(EXPAND3(EXPAND3(__VA_ARGS__))))
#define EXPAND3(...) EXPAND2(EXPAND2(EXPAND2(EXPAND2(__VA_ARGS__))))
#define EXPAND2(...) EXPAND1(EXPAND1(EXPAND1(EXPAND1(__VA_ARGS__))))
#define EXPAND1(...) __VA_ARGS__

#define FOR_EACH(macro, ...)                                    \
__VA_OPT__(EXPAND(FOR_EACH_HELPER(macro, __VA_ARGS__)))
#define FOR_EACH_HELPER(macro, a1, ...)                         \
macro(a1)                                                     \
    __VA_OPT__(FOR_EACH_AGAIN PARENS (macro, __VA_ARGS__))
#define FOR_EACH_AGAIN() FOR_EACH_HELPER


#define K 2

#define check_shift(shift) !(shift_table&((LONG64)1<<(*(s-shift)&0x3f)))


int new_algo_k(unsigned char* P, int m, unsigned char* T, int n, float* time) {
    int count = 0;
    LONG64 shift_table = 0;
    int real_shift [300];

    for(int i=0;i<m;i++)
        shift_table|=(LONG64)1<<(P[i]&0x3f);  // Preprocessing

    for(int i=0;i< 300; ++i){
        real_shift[i] = m;
    }

    for(int i=0;i<m-K;i++){
        real_shift[P[i]] = std::min(real_shift[P[i]], m - i - K);
    }

    unsigned char* s = T + m - 1;
    unsigned char* text_end = T + n;
    int shift = 0;

    START_COUNTER

    while( s < text_end){
        while(!(shift_table&((LONG64)1<<(*s&0x3f)))
               && FOR_EACH(check_shift, 1)
               )  // Search skip loop
            s+=m;
        if( s < text_end) {
            for(shift = m-K; shift >= 0 && P[shift] ==  *(s - (m-1) + shift); --shift);
            if(shift == -1) MATCH( s - (m-1) - T);
            s+= real_shift[*s];
        }
    }
    FINISH_COUNTER
    return count;
}
