#!/bin/bash

ls -al;
g++ main.cpp -g -o output;
if [ -d "./debug" ]; then
	echo "Debug Directory Already Exist";
else
	echo "Creating Debug Directory";
	mkdir debug;
fi
echo "Building Project..."
mv ./output ./debug
echo "===========================================================================";
./debug/output;
echo "===========================================================================";
