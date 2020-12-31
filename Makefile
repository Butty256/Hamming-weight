CC     = gcc
CFLAGS = -O2 -march=native -flto
LD     = gcc
LFLAGS = -flto

.SUFFIXES:
.SUFFIXES: .out .o .c

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

.o.out:
	$(LD) $(LFLAGS) $^ -o $@

targets: test1.out test2.out

clean:
	rm -f *.o *.out

all: clean targets

test1.out: test1.o popcount.o
test2.out: test2.o popcount.o
test1.o: test1.c popcount.h
test2.o: test2.c popcount.h
popcount.o: popcount.c popcount.h
