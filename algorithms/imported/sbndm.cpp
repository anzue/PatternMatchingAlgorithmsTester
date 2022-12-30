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
 * This is an implementation of the Simplified BNDM algorithm
 * in H. Peltola and J. Tarhio. Alternative Algorithms for Bit-Parallel String Matching. 
 * Proceedings of the 10th International Symposium on String Processing and Information Retrieval SPIRE'03, 
 * Lecture Notes in Computer Science, vol.2857, pp.80--94, Springer-Verlag, Berlin, (2003).
 */

#include "algorithms/consts.h"
#include "include/main.h"

int large_sbndm(unsigned char *x, int m, unsigned char *y, int n);

int sbndm(unsigned char *x, int m, unsigned char *y, int n) {
   int j,i, last, first;
   unsigned int D, B[MAX_SIGMA], s;
   int mM1 = m-1;
   int mM2 = m-2;
   int count = 0, restore[MAX_PAT_LEN+1], shift;

   if(m>32) return large_sbndm(x,m,y,n);   

   /* Preprocessing */
   for (i=0; i<SIGMA; i++)  B[i] = 0;
   for (i=0; i<m; i++) B[x[m-i-1]] |= (unsigned int)1 << (i+WORD_-m);

   last = m;
   s = (unsigned int)(~0) << (WORD_-m);
   s = (unsigned int)(~0);
   for (i=m-1; i>=0; i--) {
      s &= B[x[i]]; 
      if (s & ((unsigned int)1<<(WORD_-1))) {
         if(i > 0)  last = i; 
      }
      restore[i] = last;
      s <<= 1;
   }
        shift = restore[0];

   for(i=0; i<m; i++) y[n+i]=x[i];

   /* Searching */
   if(!memcmp(x,y,m)) OUTPUT(0);
   i = m;
   while (1) {
      D = B[y[i]];
      j = i-1; first = i-m+1;
      while (1) {
         D = (D << 1) & B[y[j]];
         if (!((j-first) && D)) break;
         j--;
      }
      if (D != 0) {
         if (i >= n) return count;
         OUTPUT(first);
         i += shift;
      } 
      else {
         i = j+m;
      }
   }
}

/*
 * Simplified Backward Nondeterministic DAWG Matching algorithm designed for large patterns
 * The present implementation searches for prefixes of the pattern of length 32.
 * When an occurrence is found the algorithm tests for the whole occurrence of the pattern
 */

int large_sbndm(unsigned char *x, int m, unsigned char *y, int n) {
   int j,i, last, first, p_len, k;
   unsigned int D, B[MAX_SIGMA], s;
   int mM1 = m-1;
   int mM2 = m-2;
   int count = 0, restore[MAX_PAT_LEN+1], shift;

   p_len = m;
   m = 32;
   int diff = p_len-m;

   /* Preprocessing */
   for (i=0; i<SIGMA; i++)  B[i] = 0;
   for (i=0; i<m; i++) B[x[m-i-1]] |= (unsigned int)1 << (i+WORD_-m);

   last = m;
   s = (unsigned int)(~0) << (WORD_-m);
   s = (unsigned int)(~0);
   for (i=m-1; i>=0; i--) {
      s &= B[x[i]]; 
      if (s & ((unsigned int)1<<(WORD_-1))) {
         if(i > 0)  last = i; 
      }
      restore[i] = last;
      s <<= 1;
   }
   shift = restore[0];

   for(i=0; i<m; i++) y[n+i]=x[i];

   /* Searching */
   if(!memcmp(x,y,m)) OUTPUT(0);
   i = m;
   while (1) {
      while ((D = B[y[i]]) == 0) i += m;
      j = i-1; first = i-m+1;
      while (1) {
         D = (D << 1) & B[y[j]];
         if (!((j-first) && D)) break;
         j--;
      }
      if (D != 0) {
         if (i+diff >= n) return count;
         k=m;
         while(k<m && x[k]==y[first+k]) k++;
         if(k==m) OUTPUT(first);
         i += shift;
      } 
      else {
         i = j+m;
      }
   }
}
