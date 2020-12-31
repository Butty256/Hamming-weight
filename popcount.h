#ifndef _POPCOUNT_H_
#define _POPCOUNT_H_

#define M1  0x5555555555555555ULL
#define M2  0x3333333333333333ULL
#define M4  0x0f0f0f0f0f0f0f0fULL
#define M8  0x00ff00ff00ff00ffULL
#define M16 0x0000ffff0000ffffULL
#define M32 0x00000000ffffffffULL
#define H01 0x0101010101010101ULL

int popcount64n(unsigned long long x);
int popcount64a(unsigned long long x);
int popcount64b(unsigned long long x);
int popcount64c(unsigned long long x);
int popcount64d(unsigned long long x);
int popcount64e(unsigned long long x);
void popcount64e_init(void);

#endif /* _POPCOUNT_H_ */
