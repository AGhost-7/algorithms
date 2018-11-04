#!/usr/bin/env bash

set -ex

mkdir -p target

compile() { gcc -Wall -x c -c $@; }

compile murmur3/murmur3.c -o target/murmur3.o
compile -Imurmur3 -I. hashmap.c -o target/hashmap.o
compile -Imurmur3 -I. hashmap_test.c -o target/hashmap_test.o
gcc target/hashmap_test.o target/hashmap.o target/murmur3.o -o target/hashmap_test

./target/hashmap_test
