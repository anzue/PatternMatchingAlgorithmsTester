#include "algorithms/consts.h"

#define LONG64 unsigned long long


int new_algo(unsigned char* P, int m, unsigned char* T, int n, float* time) {
    int count = 0;
    LONG64 shift_table=0;
    int real_shift [SIGMA];
    for(int i=0;i<m;i++)
        shift_table|= 1LL<<(P[i]&0x3f);  // Preprocessing

    for(int i=0;i< SIGMA; ++i){
        real_shift[i] = m;
    }

    for(int i=0;i<m-1;i++){
        real_shift[P[i]] = std::min(real_shift[P[i]], m - i - 1);
    }

    unsigned char* s = T + m - 1;
    unsigned char* text_end = T + n;
    int shift = 0;
    int mm1 = m-1;
    START_COUNTER

    while( s < text_end){
        while(!(shift_table&(1LL<<(*s&0x3f))))
            s+=m;
        if( s < text_end) {
            unsigned char* st = s - mm1;
            for(shift = mm1; shift >=0 && P[shift] ==  *(st + shift); --shift);
            if(shift == -1) MATCH( s - mm1 - T);
            s += real_shift[*s];
        }
    }

    FINISH_COUNTER
    return count;
}
