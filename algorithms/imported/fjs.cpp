/*
 * SMART: string matching algorithms research tool.
 * Copyright (C) 2012  Simone Faro and Thierry Lecroq
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 *
 * contact the authors at: faro@dmi.unict.it, thierry.lecroq@univ-rouen.fr
 * download the tool at: http://www.dmi.unict.it/~faro/smart/
 *
 * This is an implementation of the FJS algorithm
 * in F. Franek and C. G. Jennings and W. F. Smyth.
 * A simple fast hybrid pattern-matching algorithm. J. Discret. Algorithms, vol.5, pp.682--695, (2007).
 */

#include "algorithms/consts.h"
#include "include/main.h"

void preQsBc_fjs(unsigned char* x, int m, int qbc[]) {
    int i;
    for (i = 0; i < SIGMA; i++)
        qbc[i] = m + 1;
    for (i = 0; i < m; i++)
        qbc[x[i]] = m - i;
}

void preKmp_fjs(unsigned char* x, int m, int kmpNexy[]) {
    int i, j;
    i = 0;
    j = kmpNexy[0] = -1;
    while (i < m) {
        while (j > -1 && x[i] != x[j])
            j = kmpNexy[j];
        i++;
        j++;
        if (i < m && x[i] == x[j])
            kmpNexy[i] = kmpNexy[j];
        else
            kmpNexy[i] = j;
    }
}

int fjs(unsigned char* x, int m, unsigned char* y, int n, float* time) {
    int i, s, count, qsbc[MAX_SIGMA], kmp[MAX_PAT_LEN];

    START_COUNTER

    /* Preprocessing */
    preQsBc_fjs(x, m, qsbc);
    preKmp_fjs(x, m, kmp);

    /* Searching */
    s = 0;
    count = 0;
    while (s <= n - m) {
        while (s <= n - m && x[m - 1] != y[s + m - 1])
            s += qsbc[y[s + m]];
        if (s > n - m)
            break;
        i = 0;
        while (i < m && x[i] == y[s + i])
            i++;
        if (i >= m)
            count++;
        s += (i - kmp[i]);
    }

    FINISH_COUNTER
    
    return count;
}
