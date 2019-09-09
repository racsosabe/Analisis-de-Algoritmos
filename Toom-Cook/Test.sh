#!/bin/bash

g++ Gen.cpp -o Gen
g++ "$1.cpp" -o Bad
g++ Checker.cpp -o Checker
ver="Accepted"
for((i = 0; i < 300; i++)); do
	./Gen > int
	echo "Running on test $i"
	python3 solution.py < int > out1
	timeout 20 ./Bad < int > out2
	./Checker int out2 out1 ver
	ver=$(cat ver)
	if [ "$ver" != "Accepted" ]; then
		break
	fi
done

if [ "$ver" == "Accepted" ]; then
	echo $ver
else
	echo "$ver on test $tc"
	cat int
fi
