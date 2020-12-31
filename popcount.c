#include "popcount.h"

int popcount64n(unsigned long long x)
{
	int cnt = 0;
	for (; x; x = x >> 1) cnt += x & 1;
	return cnt;
}

int popcount64a(unsigned long long x)
{
	x = (x & M1 ) + ((x >>  1) & M1 );
	x = (x & M2 ) + ((x >>  2) & M2 );
	x = (x & M4 ) + ((x >>  4) & M4 );
	x = (x & M8 ) + ((x >>  8) & M8 );
	x = (x & M16) + ((x >> 16) & M16);
	x = (x & M32) + ((x >> 32) & M32);
	return x;
}

int popcount64b(unsigned long long x)
{
	x -= (x >> 1) & M1;
	x = (x & M2) + ((x >> 2) & M2);
	x = (x + (x >> 4)) & M4;
	x += x >>  8;
	x += x >> 16;
	x += x >> 32;
	return x & 0x7f;
}

int popcount64c(unsigned long long x)
{
	x -= (x >> 1) & M1;
	x = (x & M2) + ((x >> 2) & M2);
	x = (x + (x >> 4)) & M4;
	return (x * H01) >> 56;
}

int popcount64d(unsigned long long x)
{
	int cnt;
	for (cnt = 0; x; cnt++) x &= x - 1;
	return cnt;
}

static unsigned char wordbits[65536];
int popcount64e(unsigned long long x)
{
	return wordbits[x & 0xFFFF] + wordbits[(x >> 16) & 0xFFFF] + wordbits[(x >> 32) & 0xFFFF] + wordbits[x >> 48];
}

void popcount64e_init(void)
{
	unsigned long i, x;
	unsigned char cnt;
	for (i = 0; i <= 0xFFFF; i++)
	{
		x = i;
		for (cnt = 0; x; cnt++) x &= x - 1;
		wordbits[i] = cnt;
	}
}
