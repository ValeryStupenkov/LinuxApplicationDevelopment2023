
move:
	cc -Wall -g move.c -o move

test:	move test-protect testOK test1 test2 test3 test4 test5 clean

test-protect: 
	cc -shared -o protect.so protect.c
	printf "Hello there!" > src_PROTECT
	LD_PRELOAD=./protect.so ./move src_PROTECT dst
	test -f src_PROTECT 
	rm src_PROTECT dst protect.so 
	
testOK:
	printf "Hello there!" > src
	strace ./move src dst 2>&1 >/dev/null | grep "exited with" | grep -o '[0-9]*' > output
	echo 0 > expected
	cmp output expected
	rm -f src dst output expected

test1:
	printf "Hello there!" > src
	strace -e trace=openat -e fault=openat:error=EPERM:when=3 ./move src dst 2>&1 >/dev/null | grep "exited with" | grep -o '[0-9]*' > output
	echo 2 > expected
	cmp output expected
	rm -f src dst output expected

test2:
	printf "Hello there" > src
	strace -e trace=openat -e fault=openat:error=EPERM:when=4 ./move src dst 2>&1 >/dev/null | grep "exited with" | grep -o '[0-9]*' > output
	echo 3 > expected
	cmp output expected
	rm -f src dst output expected
test3: 
	printf "Hello there" > src
	strace -e trace=close -e fault=close:error=EPERM:when=3 ./move src dst 2>&1 >/dev/null | grep "exited with" | grep -o '[0-9]*' > output
	echo 6 > expected
	cmp output expected
	rm -f src dst output expected
	
test4: 
	printf "Hello there" > src
	strace -e trace=close -e fault=close:error=EPERM:when=4 ./move src dst 2>&1 >/dev/null | grep "exited with" | grep -o '[0-9]*' > output
	echo 7 > expected
	cmp output expected
	rm -f src dst output expected
	
test5:
	printf "Hello there" > src
	strace -e trace=unlink -e fault=unlink:error=EPERM:when=1 ./move src dst 2>&1 >/dev/null | grep "exited with" | grep -o '[0-9]*' > output
	echo 8 > expected
	cmp output expected
	rm -f src dst output expected
		
clean:
	rm -f move
	
