
all: esub

esub: 
	cc -Wall -g esub.c -o esub
	
test:	esub
	echo "Вывод команды sed:"
	echo "Пн 30 окт 2023 20:22:12 MSK"| sed -E "s/(([[:digit:]]+).*)([[:digit:]]+)/<1=\1><2=\2><3=\3>/"
	echo "Вывод программы:"
	./esub "(([[:digit:]]+).*)([[:digit:]]+)" "<1=\1><2=\2><3=\3>" "Пн 30 окт 2023 20:22:12 MSK"

clean:
	rm -f esub 
	
