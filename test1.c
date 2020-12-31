#include "popcount.h"
#include <stdio.h>
#include <time.h>
#include <x86intrin.h>

#define NUM 100000000

unsigned long long r[NUM];

int main(void)
{
	clock_t s, e;
	int i;
	volatile unsigned long long tmp;
	for (i = 0; i < NUM; i++) r[i] = (((unsigned long long)rand() & 0xFFFF) << 48) | (((unsigned long long)rand() & 0xFFFF) << 32) | (((unsigned long long)rand() & 0xFFFF) << 16) | ((unsigned long long)rand() & 0xFFFF);
	popcount64e_init();

	tmp = 0;
	for (i = 0; i < NUM; i++) tmp += popcount64a(r[i]);
	printf("bit      : %.1f\n", (double)tmp / NUM);

	s = clock();
	for (i = 0; i < NUM; i++) tmp = popcount64n(r[i]);
	e = clock();
	printf("n        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) tmp = popcount64a(r[i]);
	e = clock();
	printf("a        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) tmp = popcount64b(r[i]);
	e = clock();
	printf("b        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) tmp = popcount64c(r[i]);
	e = clock();
	printf("c        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) tmp = popcount64d(r[i]);
	e = clock();
	printf("d        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) tmp = popcount64e(r[i]);
	e = clock();
	printf("e        : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) tmp = _popcnt64(r[i]);
	e = clock();
	printf("_popcnt64: %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	s = clock();
	for (i = 0; i < NUM; i++) __asm__("popcntq %1, %0" : "=r"(tmp) : "r"(r[i]));
	e = clock();
	printf("__asm__  : %.3f\n", (double)(e - s) / CLOCKS_PER_SEC);

	return 0;
}
