#ifndef ALGOS_H
#define ALGOS_H

#include "consts.h"

int searchBSDM(unsigned char* x, int m, unsigned char* y, int n);
int search_h(unsigned char* P, int m, unsigned char* T, int n, float* time);
int search_RZk_byte(unsigned char* P, int m, unsigned char* T, int n, int k, float* time);

int search_fsbndm_w1(unsigned char* x, int m, unsigned char* y, int n, float* time);
int search_fsbndm_w2(unsigned char* x, int m, unsigned char* y, int n, float* time);
int search_fsbndm_w4(unsigned char* x, int m, unsigned char* y, int n, float* time);
int search_fsbndm_w6(unsigned char* x, int m, unsigned char* y, int n, float* time);
int search_fsbndm_w8(unsigned char* x, int m, unsigned char* y, int n, float* time);

int search_fs_w1(unsigned char* P, int m, unsigned char* T, int n, float* time);
int search_fs_w2(unsigned char* P, int m, unsigned char* T, int n, float* time);
int search_fs_w4(unsigned char* P, int m, unsigned char* T, int n, float* time);
int search_fs_w6(unsigned char* P, int m, unsigned char* T, int n, float* time);
int search_fs_w8(unsigned char* P, int m, unsigned char* T, int n, float* time);

int search_fsbndmq31(unsigned char* x, int m, unsigned char* y, int n, float* time);

int search_fs_w4(unsigned char* P, int m, unsigned char* T, int n, float* time);
int search_fs_w6(unsigned char* P, int m, unsigned char* T, int n, float* time);
int search_fs_w8(unsigned char* P, int m, unsigned char* T, int n, float* time);

#endif // ALGOS_H
