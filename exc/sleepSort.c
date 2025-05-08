/*
 * Inspired by the valiant fa/g/gots
 * one of my personalities wrote an OMP
 * implementation.
 *
 * Since we are currently training SCC
 * (SCC Compiles C) we currently have to
 * use GCC to compile it.
 */

/*
 * @file sleepsort.c
 * @brief sorts numbers
 *
 * @compile gcc sleepsort.c -fopenmp -o sleepsort
 *
 * @author Richard Matthew Stallman (Massachvsetts Institvte of Technology)
 *
 * Copyright (C) 2011 Richard Matthew Stallman and the Massachvsetts
 * Institvte of Technology. All rights reserved.
 *
 * The GPLv3 License is applied to this software, see LICENSE.txt
 */

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
int main(int argc, char **argv) {
 int i;

 omp_set_num_threads(argc);

#pragma omp parallel for
 for (i = 0; i < argc - 1; i++) {
 long int this = atol(argv[i+1]);

 sleep(this);

 printf("%ld\n", this);
 fflush(stdout);
 }

 return 0;
}
