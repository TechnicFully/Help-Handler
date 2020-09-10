#!/usr/bin/env sh


echo "Compiling C example"
gcc main.c -Wall -Wextra -pedantic -std=c99 -o main_c
echo "Compiling C++ example"
g++ main.cpp -Wall -Wextra -pedantic -std=c++11 -o main_cpp
echo "Compiling Java example"
javac -cp "../" -d "./" main.java #--release 7
