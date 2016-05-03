/*     Copyright (C) 2016  N. Perna, N. Nedialkov, T. Gwosdz
  
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <openacc.h>
#include <omp.h>
#include <math.h>
#include "a3.h"

//#pragma acc routine seq
inline double pixelDistance (const RGB *a, const RGB *b)
{
  
  double rd = a->r-b->r,
    gd = a->g-b->g,
    bd = a->b-b->b;
  
  return rd*rd+gd*gd+bd*bd;

}

//#pragma acc routine seq
void compFitness (const RGB *A, Individual *B, int width, int height) 
{
  int i, j;
  double f = 0;
  #define num threads
  j = width*height;
  RGB * ptr = B->image;
  #pragma acc data copyin(A[0:j], ptr[0:j]) 
  #pragma acc loop reduction(+:f) vector 
  #pragma omp parallel for reduction(+:f) firstprivate(A, B, j) private(i) 
  for (i = 0; i < j; i++) 
    f += pixelDistance(&A[i], &(ptr[i]));
  
  
  B->fitness = f;
}




