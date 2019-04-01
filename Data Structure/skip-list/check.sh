#!/bin/bash

for ((i = 1; i; i = i + 1)) do
	./make_data.py > main.in
	./linkList.cpp.out
	if [ $? -ne 0 ] ; then
		echo Wa
		exit
	else
		echo Ac$i
	fi
done
