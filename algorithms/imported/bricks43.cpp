


#include "algorithms/consts.h"
int Bricks43(unsigned char *P, int m, unsigned char *T, int n, float* time) {
    int mp1=m+1, mm1=m-1, mm2=m-2, mm3=m-3, mm4=m-4, m2=m*2, r, count = 0;
    const unsigned int k=16, _2_power_k=(1<<k);
    unsigned char *Z=(unsigned char *)calloc(_2_power_k,sizeof(unsigned char));
    unsigned char *s, *stop;
    int QS[256];
    if(m<=2)
        return -1;

  //Preprocessing
    for(int i=0;i<256;i++)				        // QS shift table
        QS[i]=mp1;
    for(int i=0;i<m;i++)
        QS[P[i]]=m-i;
    uint32_t p=*(uint32_t*)P;
    for (int i = 0; i < _2_power_k; i++)
        Z[i] = 1;
    for(int i=0;i<mm2;i++)
        Z[P[i]+(P[i+1]<<4)+(P[i+2]<<8)]=0;

    START_COUNTER

   // Search
   s = T+m-3;       //current position
   stop = T+n-2;
   count = 0;
   memcpy(T+n,P,m);
   while(s<stop) {
        while(Z[*s+(*(s+1)<<4)+(*(s+2)<<8)])
            s+=mm2;
        if(*(uint32_t*)(s-mm3)==p) {   // occurrence check;
            for (r = 4; r < m && s[r-mm3] == P[r]; r++);
            if (r == m && s<stop)
                MATCH(s - T -mm3);
        }
        s+=QS[*(s+3)];
    }

    FINISH_COUNTER
    free(Z);
    return count;
}
