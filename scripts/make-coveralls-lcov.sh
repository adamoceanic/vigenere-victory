#!/usr/bin/env bash

set -e -x

# cmake build, make coveralls, generate the lcov report
echo "Building project for Coveralls and lcov"

build_test_dir=/home/sapho/portfolio-work/vigenere-victory/build-test
build_dir=/home/sapho/portfolio-work/vigenere-victory/build

if [ -d "$build_test_dir" ]; then
    echo "Deleting build-test directory"
    rm -rfv "$build_test_dir"
fi

if [ -d "$build_dir" ]; then
    echo "Deleting build directory contents"
    rm -rfv "$build_dir"
    mkdir ../build
fi

mkdir -p ../build-test

cd ../build-test

cmake --enable-gcov -DCOVERALLS=ON -DCMAKE_BUILD_TYPE=Debug .. && make

make coveralls

./../build/VigenereVictory

lcov --capture --directory . --output-file ../lcov-output/coverage.info

cd ../lcov-output

genhtml coverage.info --output-directory .






