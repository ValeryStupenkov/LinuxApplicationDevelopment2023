#!/bin/bash

tput clear

delay=0
if [ $# != 0 ]; then
	delay=$1
fi

text=()
x=()
y=()
xi=0
yi=0
pos=0

while read L; do
	while (( xi < ${#L} )); do
		sym=${L:$xi:1}
		if [ "$sym" != " " ]; then
			text[$pos]=$sym
			x[$pos]=$xi
			y[$pos]=$yi
			((pos++))
		fi
		((xi++))
	done	
	xi=0
	((yi++))
done

perm=$(shuf -i 0-$((pos-1)))

i=1
while (( i <= pos)); do
  	idx=$(echo ${perm[0]} | cut -d ' ' -f $i)
  	tput cup ${y[idx]} ${x[idx]}
  	echo ${text[idx]}
  	((i++))
  	sleep $delay
done

tput cup $yi 0
