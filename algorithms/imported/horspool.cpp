#include "algorithms/consts.h"

int h(unsigned char *P, int m, unsigned char *T, int n, float* time) {
    int i, s, count, hbc[MAX_SIGMA];
    START_COUNTER
    for (i=0;i<SIGMA;i++)   hbc[i]=m;
    for (i=0;i<m-1;i++) hbc[P[i]]=m-i-1;
    /* Searching */
    s = 0;
    count = 0;
    int nm2=n-m,mm1=m-1;
    while(s<=nm2) {
        i=0;
        while(i<m && P[i]==T[s+i]) i++;
        if (i==m)
            count++;

        s+=hbc[T[s+mm1]];
    }
    FINISH_COUNTER
    auto  u=(finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart ;
    *time+=u;
    return count;
}
