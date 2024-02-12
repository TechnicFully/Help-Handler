#!/usr/bin/env bash


cd "$(dirname "$0")"

echo "Compiling C example 1..."
gcc example1.cpp -Wall -Wextra -pedantic -std=c11 -o example1

echo "Compiling C example 2..."
gcc example2.cpp -Wall -Wextra -pedantic -std=c11 -o example2

echo "Compiling C example 3..."
gcc example3.cpp -Wall -Wextra -pedantic -std=c11 -o example3

echo "Compiling C example 4..."
gcc example4.cpp -Wall -Wextra -pedantic -std=c11 -o example4

echo "Compiling C example 5..."
gcc example5.cpp -Wall -Wextra -pedantic -std=c11 -o example5

echo "Compiling C example 6..."
gcc example6.cpp -Wall -Wextra -pedantic -std=c11 -o example6

echo "Compiling C example 7..."
gc example7.cpp -Wall -Wextra -pedantic -std=c11 -o example7

echo "Compiling C example 8..."
gcc example8.cpp -Wall -Wextra -pedantic -std=c11 -o example8
