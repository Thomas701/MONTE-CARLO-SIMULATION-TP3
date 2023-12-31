#ifndef MT_H

#define MT_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#define PI 3.14159265358979323846

void init_genrand(unsigned long s);
void init_by_array(unsigned long init_key[], int key_length);
unsigned long genrand_int32(void);
long genrand_int31(void);
double genrand_real1(void);
double genrand_real2(void);
double genrand_real3(void);

#endif