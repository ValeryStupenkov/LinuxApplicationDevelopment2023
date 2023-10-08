
all:    prog prog-a prog-so

prog:   const.o fun.o prog.o
	cc $^ -o $@

prog-a:
	ar -rcs liboutput_static.a const.o fun.o
	cc -L. prog.o -loutput_static -o prog-a

prog-so:
	rm -f *.o
	make CFLAGS=-fPIC prog
	cc -shared fun.o const.o -o liboutput.so
	cc -L. prog.o -loutput -o prog-so 

fun.o:  outlib.h

test: test_1 test_2 test_3

test_1:
	@echo "\nTest 1:\n"
	./prog > out_1_1 2&>1
	./prog-a > out_1_2 2&>1
	LD_LIBRARY_PATH='./' ./prog-so > out_1_3 2&>1
	cmp out_1_1 out_1_2
	cmp out_1_1 out_1_3

test_2:
	@echo "\nTest 2:\n"
	./prog one > out_2_1
	./prog-a one > out_2_2
	LD_LIBRARY_PATH='./' ./prog-so one > out_2_3
	cmp out_2_1 out_2_2
	cmp out_2_1 out_2_3

test_3:
	@echo "\nTest 3:\n"
	./prog one two three > out_3_1
	./prog-a one two three > out_3_2
	LD_LIBRARY_PATH='./' ./prog-so one two three > out_3_3
	cmp out_3_1 out_3_2
	cmp out_3_1 out_3_3

clean:
	rm -f prog prog-a prog-so *.a *.o *.so out_* 1

