#include "algorithms/consts.h"

#define LONG64 unsigned long long


int compressed_shifts_w2(unsigned char* P, int m, unsigned char* T, int n, float* time) {
    int count = 0;
    LONG64 shift_table=0;
    int real_shift [SIGMA];
    for(int i=0;i<m;i++)
        shift_table|= 1LL<<(P[i]&0x3f);  // Preprocessing

    for(int i=0;i< SIGMA; ++i){
        real_shift[i] = m;
    }

    for(int i=0;i<m;i++){
        real_shift[P[i]] = m - i;
    }

    unsigned char* Tmed = T + n/2;
    unsigned char* s1 = T + m - 1;
    unsigned char* s0 = Tmed;
    unsigned char* text_end = T + n;
    int shift = 0;
    int mm1 = m-1;
    START_COUNTER

    while( s0 < text_end){
        while(!(shift_table&(1LL<<(*s0&0x3f))) && !(shift_table&(1LL<<(*s1&0x3f)))) {
            s0+=m;
            s1+=m;
        }
        if( s0 < text_end && (shift_table&(1LL<<(*(s0-1)&0x3f)))) {
            unsigned char* st = s0 - mm1;
            for(shift = mm1; shift >=0 && P[shift] ==  *(st + shift); --shift);
            if(shift == -1) MATCH( s0 - mm1 - T);
            s0 += real_shift[*(s0+1)];
        } else {
            s0+= mm1;
        }
        if( s1 < Tmed && (shift_table&(1LL<<(*(s1-1)&0x3f)))) {
            unsigned char* st = s1 - mm1;
            for(shift = mm1; shift >=0 && P[shift] ==  *(st + shift); --shift);
            if(shift == -1) MATCH( s1 - mm1 - T);
            s1 += real_shift[*(s1+1)];
        } else {
            s1+= mm1;
        }
    }

    while( s1 < Tmed){
        while(!(shift_table&(1LL<<(*s1&0x3f)))) {
            s1+=m;
        }
        if( s1 < Tmed && shift_table&(1LL<<(*(s1-1)&0x3f))) {
            unsigned char* st = s1 - mm1;
            for(shift = mm1; shift >=0 && P[shift] ==  *(st + shift); --shift);
            if(shift == -1) MATCH( s1 - mm1 - T);
            s1 += real_shift[*(s1+1)];
        } else {
            s1 += mm1;
        }
    }

    FINISH_COUNTER
        return count;
}
