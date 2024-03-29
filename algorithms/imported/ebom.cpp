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
 * This is an implementation of the Extended Backward Oracle Matching algorithm
 * in S. Faro and T. Lecroq. 
 * Efficient Variants of the Backward-Oracle-Matching Algorithm. 
 * Proceedings of the Prague Stringology Conference 2008, pp.146--160, Czech Technical University in Prague, Czech Republic, (2008).
 */

#include "algorithms/consts.h"
#include "include/main.h"

int ebom(unsigned char *x, int m, unsigned char *y, int n, float* time) {
   int S[MAX_PAT_LEN], FT[MAX_SIGMA][MAX_SIGMA];
   int *trans[MAX_PAT_LEN];
   int i, j, p, q;
   int iMinus1, mMinus1, count;
   unsigned char c;
   count = 0;

   // Preprocessing
   for(i=0; i<=m+1; i++) trans[i] = (int *)malloc (sizeof(int)*(SIGMA));
   for(i=0; i<=m+1; i++) for(j=0; j<SIGMA; j++) trans[i][j]=UNDEFINED;
   S[m] = m + 1;
   for (i = m; i > 0; --i) {
      iMinus1 = i - 1;
      c = x[iMinus1];
      trans[i][c] = iMinus1;
      p = S[i];
      while (p <= m && (q = trans[p][c]) ==  UNDEFINED) {
         trans[p][c] = iMinus1;
         p = S[p];
      }
      S[iMinus1] = (p == m + 1 ? m : q);
   }

   /* Construct the FirstTransition table */
   for(i=0; i<SIGMA; i++) {
      q = trans[m][i];
      for(j=0; j<SIGMA; j++)
         if(q>=0) FT[i][j] = trans[q][j];
         else FT[i][j] = UNDEFINED;
   }

   START_COUNTER

   /* Searching */
   for(i=0; i<m; i++) y[n+i]=x[i];
   if( !memcmp(x,y,m) ) count++;
   j=m;
   mMinus1 = m-1;
   while (j<n) {
      while ( (FT[y[j]][y[j-1]]) == UNDEFINED ) j+=mMinus1;
      i = j-2;
      p = FT[y[j]][y[j-1]];
      while ( (p = trans[p][y[i]]) != UNDEFINED ) i--;
      if (i < j-mMinus1 && j<n) {
         MATCH(i);
         i++;
      }
      j = i + m;
   }

   FINISH_COUNTER
   for(i=0; i<=m+1; i++) free(trans[i]);
   return count;
}



