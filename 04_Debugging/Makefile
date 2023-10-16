
all: range

range: 
	cc -o0 -g range.c -o range

test: 
	gdb -x test1.txt --args ./range | grep '@@@' | cut -c 4- > out1.txt
	gdb -x test2.txt --args ./range | grep '@@@' | cut -c 4- > out2.txt 
	cmp out1.txt etalon1.txt
	cmp out2.txt etalon2.txt
	
clean:
	rm -f range out*

