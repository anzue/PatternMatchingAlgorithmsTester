

#include "algorithms/consts.h"
int Z_w5(unsigned char *x, const int m, unsigned char *y, int n,int k, float* time) {

    int mp1=m+1, mm1=m-1, mm2=m-2, mm3=m-3, m2=m*2, r, count = 0;
    unsigned char *ptr1, *ptr2, *third = y+n/3, *_1 = y+n/5, *_2=y+2*n/5, *_3=y+3*n/5, *_4=y+4*n/5, *pos1, *pos2, *pos3,*pos4,*pos5,*fin=y+n;
    const unsigned int b=8; // b bits in byte; k significant bits in 2-byte read
    const unsigned int sigma=1<<b, _2_power_k=(1<<k);
    const unsigned int mask=_2_power_k-1, _2_power_k_2=_2_power_k*2;
    unsigned char *Z=(unsigned char *)calloc(_2_power_k,sizeof(unsigned char));
    int QS[sigma];

//	QueryPerformanceCounter(&start);
// Preprocessing
    for (int i = 0; i < _2_power_k; i++)
        Z[i] = 1;
    for (int i = 0; i < mm1; i++)
        Z[(*(ushort*)(x+i))&mask] = 0;

    for(int i=0;i<sigma;i++)				        // QS shift table
        QS[i]=mp1;
    for(int i=0;i<m;i++)
        QS[x[i]]=m-i;

//Search
    memcpy(y+n,x,m);
    pos1=y+mm2;
    pos2=_1;
    pos3=_2;
    pos4=_3;
    pos5=_4;

    START_COUNTER

    if(m>2) {
    while (pos1<_1) {
        while(Z[((*(unsigned short*)(pos1)))&mask] & Z[((*(unsigned short*)(pos2)))&mask] & Z[((*(unsigned short*)(pos3)))&mask] & Z[((*(unsigned short*)(pos4)))&mask] & Z[((*(unsigned short*)(pos5)))&mask]) {
            pos1+=mm1;
            pos2+=mm1;
            pos3+=mm1;
            pos4+=mm1;
            pos5+=mm1;
        }
            if(!Z[(*(unsigned short*)(--pos1))&mask]) {         // Alg. 3, line 6 combined with Alg. 5, line 7
                for (r = 0; r < m && pos1[r-mm3] == x[r]; r++);	// occurrence check, Alg. 3, line 7
                if (r == m)
                    if(pos1<_1)
                        count++;
                pos1+=QS[*(pos1+3)]+1;  // Alg. 3, line 8
            } else
                pos1+=mm1;              // Alg. 3, line 10
            if(!Z[(*(unsigned short*)(--pos2))&mask]) {         // Alg. 3, line 6 combined with Alg. 5, line 12
                for (r = 0; r < m && pos2[r-mm3] == x[r]; r++);	// occurrence check, Alg. 3, line 7
                if (r == m)
                    if(pos2<_2)
                        count++;
                pos2+=QS[*(pos2+3)]+1;  // Alg. 3, line 8
            } else
                pos2+=mm1;              // Alg. 3, line 10
            if(!Z[(*(unsigned short*)(--pos3))&mask]) {
                for (r = 0; r < m && pos3[r-mm3] == x[r]; r++);
                if (r == m)
                    if(pos3<_3)
                        count++;
                pos3+=QS[*(pos3+3)]+1;
            } else
                pos3+=mm1;
            if(!Z[(*(unsigned short*)(--pos4))&mask]) {
                for (r = 0; r < m && pos4[r-mm3] == x[r]; r++);
                if (r == m)
                    if(pos4<_4)
                        count++;
                pos4+=QS[*(pos4+3)]+1;
            } else
                pos4+=mm1;
            if(!Z[(*(unsigned short*)(--pos5))&mask]) {
                for (r = 0; r < m && pos4[r-mm3] == x[r]; r++);
                if (r == m)
                    if(pos5<fin)
                        count++;
                pos5+=QS[*(pos5+3)]+1;
            } else
                pos5+=mm1;
        }
        while(pos2<_2) {          // If pos1 has reached 1/3 of the text, but pos2 has not reached 2/3 of the text
            while(Z[((*(unsigned short*)(pos2)))&mask])
                pos2+=mm1;
            for (r = 0; r < m && pos2[r-mm2] == x[r]; r++);
            if (r == m)
                if(pos2<_2)
                    count++;
            pos2+=QS[*(pos2+2)];
        }
        while(pos3<_3) {               // If pos1 has reached 1/3 of the text, but pos3 has not reached the end of the text
            while(Z[((*(unsigned short*)(pos3)))&mask])
                pos3+=mm1;
            for (r = 0; r < m && pos3[r-mm2] == x[r]; r++);
            if (r == m)
                if(pos3<_3)
                    count++;
            pos3+=QS[*(pos3+2)];
         }
         while(pos4<_4) {               // If pos1 has reached 1/3 of the text, but pos3 has not reached the end of the text
            while(Z[((*(unsigned short*)(pos4)))&mask])
                pos4+=mm1;
            for (r = 0; r < m && pos4[r-mm2] == x[r]; r++);
            if (r == m)
                if(pos4<_4)
                    count++;
            pos4+=QS[*(pos4+2)];
         }
         while(pos5<fin) {               // If pos1 has reached 1/3 of the text, but pos3 has not reached the end of the text
            while(Z[((*(unsigned short*)(pos5)))&mask])
                pos5+=mm1;
            for (r = 0; r < m && pos5[r-mm2] == x[r]; r++);
            if (r == m)
                if(pos5<fin)
                    count++;
            pos5+=QS[*(pos5+2)];
         }
    } else {        // special case m==2
            while (pos1<_1) {
                while(Z[((*(unsigned short*)(pos1)))&mask] & Z[((*(unsigned short*)(pos2)))&mask] & Z[((*(unsigned short*)(pos3)))&mask] & Z[((*(unsigned short*)(pos4)))&mask] & Z[((*(unsigned short*)(pos5)))&mask]) {
                    pos1++; pos2++; pos3++; pos4++; pos5++;
                }
                if(!Z[(*(unsigned short*)(pos1))&mask]) // occurrence check
                    if(pos1<_1)
                        count++;
                pos1+=QS[*(pos1+2)];
                if(!Z[(*(unsigned short*)(pos2))&mask]) // occurrence check
                    if(pos2<_2)
                        count++;
                pos2+=QS[*(pos2+2)];
                if(!Z[(*(unsigned short*)(pos3))&mask]) // occurrence check
                    if(pos3<fin)
                        count++;
                pos3+=QS[*(pos3+2)];
                if(!Z[(*(unsigned short*)(pos4))&mask]) // occurrence check
                    if(pos4<fin)
                        count++;
                pos4+=QS[*(pos4+2)];
                if(!Z[(*(unsigned short*)(pos5))&mask]) // occurrence check
                    if(pos5<fin)
                        count++;
                pos5+=QS[*(pos5+2)];
            }
            while(pos2<_2) {
                while(Z[((*(unsigned short*)(pos2)))&mask])
                    pos2++;
                if(pos2<_2)
                    count++;
                pos2++;
            }
            while(pos3<_3) {
                while(Z[((*(unsigned short*)(pos3)))&mask])
                    pos3++;
                if(pos3<_3)
                    count++;
                pos3++;
            }
            while(pos4<_4) {
                while(Z[((*(unsigned short*)(pos4)))&mask])
                    pos4++;
                if(pos4<_4)
                    count++;
                pos4++;
            }
            while(pos5<fin) {
                while(Z[((*(unsigned short*)(pos5)))&mask])
                    pos5++;
                if(pos5<fin)
                    count++;
                pos5++;
            }
    }

    FINISH_COUNTER

    return count;
}
