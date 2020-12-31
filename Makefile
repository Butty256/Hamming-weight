test1: test1.o popcount.o
	gcc -o test1.out test1.o popcount.o

test2: test2.o popcount.o
	gcc -o test2.out test2.o popcount.o

test1.o: test1.c popcount.h
	gcc -O0 -march=native -c test1.c

test2.o: test2.c popcount.h
	gcc -O0 -march=native -c test2.c

popcount.o: popcount.c popcount.h
	gcc -O3 -c popcount.c

clean:
	rm *.o *.out
