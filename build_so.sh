#!/usr/bin/env bash

gcc -c -Wall -Werror -fpic -I./header/ -o linked_list.o src/linked_list.c
gcc -c -Wall -Werror -fpic -I./header/ -o hash_map.o src/hash_map.c

gcc -shared -o libstruct.so linked_list.o hash_map.o

rm linked_list.o
rm hash_map.o
