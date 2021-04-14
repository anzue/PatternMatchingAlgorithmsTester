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
 * This is an implementation of the Backward SNR DAWG Matching algorithm
 * in S. Faro and T. Lecroq. 
 * A Fast Suffix Automata Based Algorithm for Exact Online String Matching. 
 * 17-th International Conference on Implementation and Application of Automata - CIAA 2012, pp.146--160 (2012).
 */


#include "algorithms/consts.h"
#include "include/main.h"

int bsdm_tmp(unsigned char *x, int m, unsigned char *y, int n) {
    unsigned int B[MAX_SIGMA];
	int i, j, k, count;
    unsigned int s,d;

	/* Preprocessing */
    unsigned int occ[MAX_SIGMA] = {0};
    int start = 0, len = 0;
    for(i=0, j=0; i<m; i++) {
        if(occ[x[i]]) {
            while(x[j]!=x[i]) {
                occ[x[j]]=0;
                j++;
            } 
            occ[x[j]]=0;
            j++;
        }
        occ[x[i]]=1;
        if(len < i-j+1 ) {
            len = i-j+1;
            start = j;
        }
    }
    unsigned int pos[MAX_SIGMA];
    for(i=0; i<SIGMA; i++) pos[i]=-1;
	for(i=0; i<len; i++) pos[x[start+i]]=i;

    //printf("%d / %d\n",m,len);
    //for(i=start; i<start+len; i++) printf("%d ",x[i]);
    //if(start+len<m) printf("[%d] ",x[start+len]);
    //printf("\n\n");
	
	/* Searching */
	for(i=0; i<m; i++) y[n+i]=x[i];
	unsigned char *xstart = x+start;
	int offset = len+start-1;
	j = len-1;
	while(j<n) {
	    while ((i=pos[y[j]])<0) j+=len;
	    k=1;
	    while(k<=i && xstart[i-k]==y[j-k]) k++;
	    if(k>i) {
	    	if(k==len) {
	    		if(!memcmp(x,y+j-offset,m)) if(j-offset<=n-m) count++;
	    	}
	    	else j-=k;
	    }
	    j+=len;
	}
   	return count;
}



