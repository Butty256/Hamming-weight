#include <stdio.h>
#include <time.h>
#include <x86intrin.h>

#define M1  0x5555555555555555ULL
#define M2  0x3333333333333333ULL
#define M4  0x0f0f0f0f0f0f0f0fULL
#define M8  0x00ff00ff00ff00ffULL
#define M16 0x0000ffff0000ffffULL
#define M32 0x00000000ffffffffULL
#define H01 0x0101010101010101ULL
#define NUM 100000000

int popcount64a(register unsigned long long x)
{
	x = (x & M1 ) + ((x >>  1) & M1 );
	x = (x & M2 ) + ((x >>  2) & M2 );
	x = (x & M4 ) + ((x >>  4) & M4 );
	x = (x & M8 ) + ((x >>  8) & M8 );
	x = (x & M16) + ((x >> 16) & M16);
	x = (x & M32) + ((x >> 32) & M32);
	return x;
}

int popcount64b(register unsigned long long x)
{
	x -= (x >> 1) & M1;
	x = (x & M2) + ((x >> 2) & M2);
	x = (x + (x >> 4)) & M4;
	x += x >>  8;
	x += x >> 16;
	x += x >> 32;
	return x & 0x7f;
}

int popcount64c(register unsigned long long x)
{
	x -= (x >> 1) & M1;
	x = (x & M2) + ((x >> 2) & M2);
	x = (x + (x >> 4)) & M4;
	return (x * H01) >> 56;
}

int popcount64d(register unsigned long long x)
{
	int count;
	for (count=0; x; count++) x &= x - 1;
	return count;
}

static unsigned char wordbits[65535];
int popcount64e(register unsigned long long x)
{
	return wordbits[x & 0xFFFF] + wordbits[(x >> 16) & 0xFFFF] + wordbits[(x >> 32) & 0xFFFF] + wordbits[x >> 48];
}

void popcount64e_init(void)
{
	register unsigned long i, x;
	register unsigned char cnt;
	for (i = 0; i < 0xFFFF; i++)
	{
		x = i;
		for (cnt = 0; x; cnt++) x &= x - 1;
		wordbits[i] = cnt;
	}
}

unsigned long long r[NUM];

int main(void)
{
	clock_t s, e;
	int i;
	unsigned long long tmp;
	for (i = 0; i < NUM; i++) r[i] = rand();
	popcount64e_init();

	s = clock();
	for (i = 0; i < NUM; i++) popcount64a(r[i]);
	e = clock();
	printf("a        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) popcount64b(r[i]);
	e = clock();
	printf("b        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) popcount64c(r[i]);
	e = clock();
	printf("c        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) popcount64d(r[i]);
	e = clock();
	printf("d        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) popcount64e(r[i]);
	e = clock();
	printf("e        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) _popcnt64(r[i]);
	e = clock();
	printf("_popcnt64: %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) __asm__("popcntq %1, %0" : "=r"(tmp) : "r"(r[i]));
	e = clock();
	printf("__asm__  : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	return 0;
}
