#!/usr/bin/env bash

gcc -Wall -Werror -I../header/ -o linked_list_test ../src/linked_list.c ../test/linked_list_test.c
./linked_list_test
rm linked_list_test
