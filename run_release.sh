#!/bin/bash

ls -al;
g++ main.cpp -o output;
if [ -d "./release" ]; then
        echo "Release Directory Already Exist";
else
        echo "Creating Release Directory";
        mkdir release;
fi
echo "Building Project...";
mv ./output ./release;
echo "===========================================================================";
./release/output;
echo "===========================================================================";
