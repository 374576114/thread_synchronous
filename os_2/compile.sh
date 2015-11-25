#!/bin/bash
echo "编译所有程序"
gcc -omain main.c
gcc -oget get.c
gcc -oput put.c
gcc -ocopy copy.c
rm *.o
