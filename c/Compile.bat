@ECHO OFF
ECHO Compiling C example...
gcc examples/example1.c -Wall -Wextra -pedantic -Wconversion -fstack-protector-all -fstack-protector-strong -D_FORTIFY_SOURCE=2 -Wformat=2 -Wshadow -fwrapv -Werror=implicit-function-declaration -Wunreachable-code -g3 -std=c11 -o example1
PAUSE
