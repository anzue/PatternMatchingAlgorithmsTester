#ifndef ALGOS_H
#define ALGOS_H

#include "consts.h"

int searchBSDM(unsigned char* x, int m, unsigned char* y, int n);
int h(unsigned char* P, int m, unsigned char* T, int n, float* time);

int fsbndm_w1(unsigned char* x, int m, unsigned char* y, int n, float* time);
int fsbndm_w2(unsigned char* x, int m, unsigned char* y, int n, float* time);
int fsbndm_w4(unsigned char* x, int m, unsigned char* y, int n, float* time);
int fsbndm_w6(unsigned char* x, int m, unsigned char* y, int n, float* time);
int fsbndm_w8(unsigned char* x, int m, unsigned char* y, int n, float* time);

int fs_w1(unsigned char* P, int m, unsigned char* T, int n, float* time);
int fs_w2(unsigned char* P, int m, unsigned char* T, int n, float* time);
int fs_w4(unsigned char* P, int m, unsigned char* T, int n, float* time);
int fs_w6(unsigned char* P, int m, unsigned char* T, int n, float* time);
int fs_w8(unsigned char* P, int m, unsigned char* T, int n, float* time);

int fsbndmq31(unsigned char* x, int m, unsigned char* y, int n, float* time);

int fs_w4(unsigned char* P, int m, unsigned char* T, int n, float* time);
int fs_w6(unsigned char* P, int m, unsigned char* T, int n, float* time);
int fs_w8(unsigned char* P, int m, unsigned char* T, int n, float* time);

int fjs(unsigned char* x, int m, unsigned char* y, int n, float* time);
int fs(unsigned char* x, int m, unsigned char* y, int n, float* time);

int RZk_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
int RZk_w2_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w3_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
int RZk_w3_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int Zk_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
//int Zk_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
int Zk_w2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int test_algo(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int Z8_byte(unsigned char* P, int m, unsigned char* T, int n, float* time);

int Zk_shift2_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);


int RZk_w3_byte2(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w3_simd1(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
int RZk_w3_simd2(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w2_mmx(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w4_simd2(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
int RZk_w2_simd3(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w3_simd2_range_cmp(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w4_simd3(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
int RZk_w3_simd3_range_cmp(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w3_simd3(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int RZk_w3_simd3_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);
int RZk_w4_simd3_pointer(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);



#endif // ALGOS_H
