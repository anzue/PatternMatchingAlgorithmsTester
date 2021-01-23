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
 * This is an implementation of the Extended Backward Oracle Matching 2 algorithm
 * in C. Liu and Y. Wang and D. Liu and D. Li. 
 * Two Improved Single Pattern Matching Algorithms. ICAT Workshops, pp.419--422, IEEE Computer Society, Hangzhou, China, (2006).
 */

#include "Algorithms/consts.h"
#include "include/main.h"
#include "include/AUTOMATON.h"

#define setTarget(p, c, q) ttrans[(p)*SIGMA+(c)] = (q)
#define getTarget(p, c) ttrans[(p)*SIGMA+(c)]
#define setLength(p, q) tlength[(p)] = (q)
#define getLength(p) tlength[(p)]
#define setSuffixLink(p, q) tsuffix[(p)] = (q)
#define getSuffixLink(p) tsuffix[(p)]
#define setTerminal(p) tterminal[(p)] = 1
#define isTerminal(p) tterminal[(p)]
#define newState() counter++
#define setSMA(p, c, q) ttransSMA[(p)*SIGMA+(c)] = (q)
#define getSMA(p, c) ttransSMA[(p)*SIGMA+(c)]

int search_ildm2(unsigned char *x, int m, unsigned char *y, int n) {
   int k,i,j, R, L, r, ell, end, count, l, m2;
   int *ttrans, *tlength, *tsuffix;
   int *ttransSMA;
   unsigned char *tterminal;
   unsigned char *xR;

   xR = (unsigned char*) malloc (sizeof(char)*(m+1));
   for(i=0; i<m; i++) xR[i] = x[m-i-1];
   xR[m] = '\0';    

   /* Preprocessing */
   ttrans = (int *)malloc(3*m*SIGMA*sizeof(int));
   memset(ttrans, -1, 3*m*SIGMA*sizeof(int));
   tlength = (int *)calloc(3*m, sizeof(int));
   tsuffix = (int *)calloc(3*m, sizeof(int));
   tterminal = (unsigned char *)calloc(3*m, sizeof(char));
   buildSimpleSuffixAutomaton(xR, m, ttrans, tlength, tsuffix, tterminal);
   ttransSMA = (int *)malloc((m+1)*SIGMA*sizeof(int));
   memset(ttransSMA, -1, (m+1)*SIGMA*sizeof(int));
   preSMA(x, m, ttransSMA);

   /* Searching */
   count = 0;
   k = m-1 ;
   while ( k < n ) {
      L = 0 ; R = 0; l = 0;
      while ( k - l >= 0 && ( L = getTarget( L, y[k-l]) ) != UNDEFINED ) {
         l++;
         if ( isTerminal(L) ) R = l;
      }
      while ( R > m/2 ) {
         if ( R==m ) OUTPUT( k - m + 1 );
         k ++ ;
         if ( k >= n ) break;
         R = getSMA ( R, y[k] ) ;
      }
      k = k + m-R ;
   }

   free(ttransSMA);
   free(ttrans);
   free(tlength);
   free(tsuffix);
   free(tterminal);
   return count;
}
