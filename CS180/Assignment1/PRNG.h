#ifndef PRNG_H
#define PRNG_H

unsigned ut_rand(void);            /* returns a random 32-bit integer */
void ut_srand(unsigned, unsigned); /* seed the generator              */
int RandomInt(int low, int high);  /* range                           */

#endif
