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
 * This is an implementation of the BXS algorithm
 * in Branislav Durian1, Hannu Peltola, Leena Salmela and Jorma Tarhio2 	
 * Bit-Parallel Search Algorithms for Long Patterns
 * International Symposium on Experimental Algorithms (SEA 2010)
 * Q is the dimension of q-grams
 */

#include "algorithms/consts.h"
#include "include/main.h"
#define Q 4 

int bxs4(unsigned char *x, int m, unsigned char *y, int n, float* time) {
   unsigned int B[MAX_SIGMA], D, set;
   int i, j, first, k, mm, sh, m1, count;
   if(m<Q) return -1;
	int w = WORD, mq1 = m-Q+1, nq1 = n-Q+1;
	if (w > m) w = m;
	unsigned int mask = 1<<(w-1);
		
   /* Preprocessing */
   count = 0;
   set = 1;
	for(i=0; i<SIGMA; i++) B[i]=0;
   for (i = m-1; i >=0; i--) {
		B[x[i]] |= set;
		set<<=1;
		if(set==0) set=1;
	}
	
   START_COUNTER
   /* Searching */
	for (i=mq1-1; i<nq1; i+=mq1) {
		D = B[y[i+3]];
		D = (D<<1) & B[y[i+2]];
		D = (D<<1) & B[y[i+1]];
		D = (D<<1) & B[y[i]];
		if ( D ) {
			j = i; 
			first = i-mq1;
		   do {
			   j--;
			   if (D >= mask) {
				   if (j-first) i=j;
				   else {
					   for (k=m; y[first+k]==x[k-1] && (k); k--);
                       if ( k==0 ) MATCH(first);
				   }
				   D = ((D<<1)|1) & B[y[j]];
			   }
			   else D = (D<<1) & B[y[j]];
		   } while (D && j>first);
	   }
   }

   FINISH_COUNTER
   return count;
}
