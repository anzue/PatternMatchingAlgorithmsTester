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

#include <Algorithms/algos.h>

#ifndef AUTOMATON
#define AUTOMATON

#define setTarget(p, c, q) ttrans[(p)*SIGMA+(c)] = (q)
#define getTarget(p, c) ttrans[(p)*SIGMA+(c)]
#define setLength(p, q) tlength[(p)] = (q)
#define getLength(p) tlength[(p)]
#define setSuffixLink(p, q) tsuffix[(p)] = (q)
#define getSuffixLink(p) tsuffix[(p)]
#define setShift(p,c,q) tshift[(p)*SIGMA + c] = (q)
#define getShift(p,c) tshift[(p)*SIGMA + c]
#define setPosition(p,q) tposition[(p)]=(q)
#define getPosition(p) tposition[(p)]
#define setTerminal(p) tterminal[(p)] = 1
#define isTerminal(p) tterminal[(p)]
#define newState() counter++
#define error(string) exit(1)

#define setSMA(p, c, q) ttransSMA[(p)*SIGMA+(c)] = (q)
#define getSMA(p, c) ttransSMA[(p)*SIGMA+(c)]
#define isSMATerminal(p) p==m

#define UNDEFINED -1
#define FALSE      0
#define TRUE       1

#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))

  struct _cell{
    int element;
    struct _cell *next;
  };

  typedef struct _cell *List;

char *reverse(char *x, int m) ;



void buildSimpleSuffixAutomaton(unsigned char *x, int m, 
   int *ttrans, int *tlength, int *tsuffix, unsigned char *tterminal);


void preSMA(unsigned char *x, int m, int *ttransSMA);

#endif
