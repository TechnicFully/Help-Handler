#!/usr/bin/env bash


cd "$(dirname "$0")"

echo "Compiling C++ example 1..."
g++ example1.cpp -Wall -Wextra -pedantic -std=c++11 -o example1

echo "Compiling C++ example 2..."
g++ example2.cpp -Wall -Wextra -pedantic -std=c++11 -o example2

echo "Compiling C++ example 3..."
g++ example3.cpp -Wall -Wextra -pedantic -std=c++11 -o example3

echo "Compiling C++ example 4..."
g++ example4.cpp -Wall -Wextra -pedantic -std=c++11 -o example4

echo "Compiling C++ example 5..."
g++ example5.cpp -Wall -Wextra -pedantic -std=c++11 -o example5

echo "Compiling C++ example 6..."
g++ example6.cpp -Wall -Wextra -pedantic -std=c++11 -o example6

echo "Compiling C++ example 7..."
g++ example7.cpp -Wall -Wextra -pedantic -std=c++11 -o example7

echo "Compiling C++ example 8..."
g++ example8.cpp -Wall -Wextra -pedantic -std=c++11 -o example8
