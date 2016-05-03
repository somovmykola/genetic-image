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

#include <time.h>
#include <omp.h>
#include <stdlib.h>
#include <assert.h>
#include "a3.h"

int main(int argc, char** argv)
{
  //float start, end;
  //start = omp_get_wtime();
  struct timeval start, stop;
  gettimeofday(&start, 0);
  const char *input_file  = argv[2];
  const char *output_file = argv[3];
  
  int num_generations = atoi(argv[4]);
  int population_size = atoi(argv[5]);
  int threads = atoi(argv[1]);  

  omp_set_dynamic(0);
  omp_set_num_threads(threads);
  // population size, must be multiple of 4 right now
  assert(population_size % 4 == 0);
  
  // Load the desired image
  RGB *desired_image;  
  int width, height, max;
  desired_image = readPPM(input_file, &width, &height, &max);
  
  // Compute an image
  RGB *found_image = (RGB*)malloc(width*height*sizeof(RGB));
  compImage(desired_image, width, height, max, 
	    num_generations, population_size, found_image, output_file);
  
  // Write it back into an output file
  writePPM(output_file, width, height, max, found_image);
  
  free(found_image);
  free(desired_image);


  gettimeofday(&stop, 0);
  //end = omp_get_wtime();
  //printf("\n %lu \n", (stop.tv_sec-start.tv_sec)*10000+(stop.tv_usec-start.tv_usec));
  printf("\n %lu \n", stop.tv_sec-start.tv_sec);

  return(0);
}
