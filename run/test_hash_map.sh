#!/usr/bin/env bash

gcc -Wall -Werror -I../header/ -o hash_map_test ../src/hash_map.c ../test/hash_map_test.c
./hash_map_test
rm hash_map_test
