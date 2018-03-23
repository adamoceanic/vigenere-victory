#!/usr/bin/env bash

CXX="clang++"

if [ "$CXX" == "clang++" ]; then
    echo $CXX
    echo "clang++ compiling"
else
    echo "g++ compiling"
fi