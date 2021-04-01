//#include "algorithms/consts.h"
//#include <bitset>
//#include <stdio.h>
//#include <string.h>
//#include <intrin.h>

//#define word(a) *((unsigned short*)(T + a))

//inline __attribute__((always_inline)) bool compare(unsigned char *P, unsigned char *T, int m){
//    bool eq = true;
//    for (int i = 15; eq && i < m; i += 16) {
//        auto pArr = _mm_set_epi8(
//                    P[i - 15], P[i - 14], P[i - 13], P[i -12], P[i -11], P[i -10], P[i - 9], P[i - 8],
//                    P[i - 7], P[i - 6], P[i - 5], P[i - 4], P[i - 3], P[i - 2], P[i - 1], P[i]);
//        auto tArr = _mm_set_epi8(
//                    T[i - 15], T[i - 14], T[i - 13], T[i -12], T[i -11], T[i -10], T[i - 9], T[i - 8],
//                    T[i - 7], T[i - 6], T[i - 5], T[i - 4], T[i - 3], T[i - 2], T[i - 1], T[i]);

//        eq &= (_popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi8(pArr, tArr))) == 16);
////        for(int j=i-15; j <= i;++j)
////            cout << P[j] << " " << T[j] << "\n";
//  //      cout << eq << " " << _popcnt32(_mm_movemask_epi8(_mm_cmpeq_epi16(pArr, tArr))) << std::endl;

//    }


//    for(int j = m - m%16; j < m ;++j){
//        eq &= (P[j] == T[j]);
//    }

////    int mod = m % 16;
////    int moded = m - mod;
////    if(eq && mod > 0){
////        eq &= P[moded] == T[moded];
////        if(mod > 1){
////            eq &= P[moded + 1] == T[moded + 1];
////            if(mod > 2){
////                eq &= P[moded + 2] == T[moded + 2];
////                if(mod > 3){
////                    eq &= P[moded + 3] == T[moded + 3];
////                    if(mod > 4){
////                        eq &= P[moded + 4] == T[moded + 4];
////                        if(mod > 5){
////                            eq &= P[moded + 5] == T[moded + 5];
////                            if(mod > 6){
////                                eq &= P[moded + 6] == T[moded + 6];
////                                if(mod > 7){
////                                    eq &= P[moded + 7] == T[moded + 7];
////                                    if(mod > 8){
////                                        eq &= P[moded + 8] == T[moded + 8];
////                                        if(mod > 9){
////                                            eq &= P[moded + 9] == T[moded + 9];
////                                            if(mod > 10){
////                                                eq &= P[moded + 10] == T[moded + 10];
////                                                if(mod > 11){
////                                                    eq &= P[moded + 11] == T[moded + 11];
////                                                    if(mod > 12){
////                                                        eq &= P[moded + 12] == T[moded + 12];
////                                                        if(mod > 13){
////                                                            eq &= P[moded + 13] == T[moded + 13];
////                                                            if(mod > 14){
////                                                                eq &= P[moded + 14] == T[moded + 14];
////                                                            } } } } } } } } } } } } } }}


//  //  cout << eq << " zzzz\n";
//    return eq;
//}

//int search_test_algo(unsigned char* P, int m, unsigned char* T, int n, int k, float* time) {
//    int i, s, count = 0, RQS[MAX_SIGMA];
//    int mask = (1 << k) - 1;
//    int b = 8;
//    char *z = new char[mask + 1];

//    QueryPerformanceCounter(&start);
//    memset(z, 1, mask);

//    for (i = 0; i < m - 1; ++i) {
//        z[(*(unsigned short*)(P + i)) & mask] = 0;
//    }
//    for (i = 0; i < (1 << (k - b)); ++i) {
//        z[(i << b) | P[m - 1]] = 0;
//    }

//    for (i = 0; i < SIGMA; ++i)
//        RQS[i] = m + 1;
//    for (i = m - 1; i >= 0; --i)
//        RQS[P[i]] = i + 1;

//    int ndiv3 = n / 3;
//    int twondiv3 = 2 * n / 3;

//    int pos1 = ndiv3;
//    int pos2 = twondiv3;
//    int pos3 = n - m;

//    while (pos1 + m >= 0) {
//        while (z[word(pos1) & mask] != 0 &&
//               z[word(pos2) & mask] != 0 &&
//               z[word(pos3) & mask] != 0) {
//            pos1 -= m;
//            pos2 -= m;
//            pos3 -= m;
//        }

//        if (z[word(pos1 + 1) & mask] == 0 && pos1 >= 0) {
//            for (i = 0; i < m && P[i] == T[pos1 + i]; ++i) {
//            };
//            if ( compare(P, T + pos1, m)  ) {
//                MATCH(pos1);
//            }
//            pos1 -= RQS[T[pos1 - 1]];
//        } else
//            pos1 -= m - 1;

//        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv3) {

//            if (compare(P, T + pos2, m)) {
//                 MATCH(pos2);
//            }
//            pos2 -= RQS[T[pos2 - 1]];
//        } else
//            pos2 -= m - 1;

//        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
//            if (compare(P, T + pos3, m)) {
//                MATCH(pos3);
//            }
//            pos3 -= RQS[T[pos3 - 1]];
//        } else
//            pos3 -= m - 1;
//    }

//    while (pos2 >= ndiv3) {
//        while (z[word(pos2) & mask] != 0 &&
//               z[word(pos3) & mask] != 0) {
//            pos2 -= m;
//            pos3 -= m;
//        }

//        if (z[word(pos2 + 1) & mask] == 0 && pos2 > ndiv3) {
//            if (compare(P, T + pos2, m)) {
//                 MATCH(pos2);
//            }
//            pos2 -= RQS[T[pos2 - 1]];
//        } else
//            pos2 -= m - 1;

//        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
//            if (compare(P, T + pos3, m)) {
//                 MATCH(pos3);
//            }
//            pos3 -= RQS[T[pos3 - 1]];
//        } else
//            pos3 -= m - 1;
//    }

//    while (pos3 >= twondiv3) {
//        while (z[word(pos3) & mask] != 0) {
//            pos3 -= m;
//        }
//        if (z[word(pos3 + 1) & mask] == 0 && pos3 > twondiv3) {
//            if (compare(P, T + pos3, m)) {
//                MATCH(pos3);
//            }
//            pos3 -= RQS[T[pos3 - 1]];
//        } else
//            pos3 -= m - 1;
//    }

//    QueryPerformanceCounter(&finish);
//    *time += (finish.QuadPart - start.QuadPart) * 1000000 / freq.QuadPart;

//    delete[] z;

//    return count;
//}

