GCC = gcc -g -Wall -Wshadow
OBJS = mymatrix.o matrix.o
HEADS = mymatrix.h
VAL = valgrind --tool=memcheck --leak-check=full


matrix: $(OBJS) $(HEADS)
	$(GCC) $(OBJS) -o $@

.c.o:
	$(GCC) $(CFLAGS) -c $*.c

clean:
	rm -f matrix $(OBJS) log* output*

testall: test0 test1 test2 test3

test0: matrix
	$(VAL) ./matrix < input0 > output0
	diff -q output0 expected0

test1: matrix
	$(VAL) ./matrix < input1 > output1
	diff -q output1 expected1

test2: matrix
	$(VAL) ./matrix < input2 > output2
	diff -q output2 expected2

test3: matrix
	$(VAL) ./matrix < input3 > output3
	diff -q output3 expected3
