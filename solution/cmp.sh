#!/bin/bash

if [[ -z $1 || -z $2 ]]; then
	echo "ERROR: missing operand"
	exit 1
elif [[ -z $3 ]]; then
	echo "ERROR: missing testcase directory"
	exit 1
fi

if [[ -z $4 ]]; then
	form="*.in"
else
	form=$4
fi

gcc $1 -o a.out 2>/dev/null
gcc $2 -o b.out 2>/dev/null

for input in $3/$form; do
	echo $(readlink -m $input)
	./a.out <$input >output_a
	./b.out <$input >output_b
	diff output_a output_b
done
