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
 */

#include "algorithms/consts.h"
#include "include/main.h"

void preQsBc_smith(unsigned char *P, int m, int qbc[])
{
	int i;
	for(i=0;i<SIGMA;i++)	qbc[i]=m+1;
	for(i=0;i<m;i++) qbc[P[i]]=m-i;
}

void preBmBc_smith(unsigned char *x, int m, int bmBc[]) {
   int i;
 
   for (i = 0; i < SIGMA; ++i)
      bmBc[i] = m;
   for (i = 0; i < m - 1; ++i)
      bmBc[x[i]] = m - i - 1;
}

int smith(unsigned char *x, int m, unsigned char *y, int n) {
   int j, bmBc[MAX_SIGMA], qsBc[MAX_SIGMA], count;

   /* Preprocessing */
   preBmBc_smith(x, m, bmBc);
   preQsBc_smith(x, m, qsBc);

   count = 0;
   /* Searching */
   j = 0;
   while (j<= n - m) {
      if (memcmp(x, y + j, m) == 0)
         OUTPUT(j);
      j += MAX(bmBc[y[j + m - 1]], qsBc[y[j + m]]);
   }
   return count;
}


