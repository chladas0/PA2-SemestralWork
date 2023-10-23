#!/bin/bash

# adding !() syntax
shopt -s extglob

g++ src/!(main).cpp tests/testAll.cpp -o test

#execute the test
valgrind ./test

#clean all
rm test 2>/dev/null