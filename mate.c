/* 
    Copyright (C) 2016  N. Perna, N. Nedialkov, T. Gwosdz
  
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

#include <omp.h>
#include "a3.h"

void mate (Individual *parent1, Individual *parent2, 
	   Individual *child1, Individual *child2, int width, int height) 
{
  int crossover = RANDOM(width*height-1);
  int i, j;
  j = width*height;
  
  //#pragma acc data copyin(parent1.image[0:j], parent2.image[0:j]) 
  //#pragma acc parallel 
  #pragma omp parallel for private(i)    
  for (i = 0; i < j; i++){
    
    if(i<crossover){
      child1->image[i] = parent1->image[i];
      child2->image[i] = parent2->image[i];
    }
    else
    {
      child1->image[i] = parent2->image[i];
      child2->image[i] = parent1->image[i];
    }
  }



/*      #pragma omp parallel for shared(crossover, child1, child2, parent1, parent2) private(i) num_threads(8)   
  for (i = 0; i < crossover; i++) 
    {
      child1->image[i] = parent1->image[i];
      child2->image[i] = parent2->image[i];
    }
  #pragma omp parallel for shared(child1, child2, parent2, parent1, crossover, j) private(i) num_threads(8)   
  for (i = crossover; i < j; i++) 
    {
      child1->image[i] = parent2->image[i];
      child2->image[i] = parent1->image[i];
    }*/
}

