#!/usr/bin/env bash

set -ex

mkdir -p target

compile() { gcc -Wall -x c -c $@; }

compile murmur3/murmur3.c -o target/murmur3.o
compile -Imurmur3 -I. hashmap.c -o target/hashmap.o
compile -Imurmur3 -I. hashmap_test.c -o target/hashmap_test.o
gcc target/hashmap_test.o target/hashmap.o target/murmur3.o -o target/hashmap_test

./target/hashmap_test

compile linkedlist.c -o target/linkedlist.o
compile -I. linkedlist_test.c -o target/linkedlist_test.o
gcc target/linkedlist_test.o target/linkedlist.o -o target/linkedlist_test

./target/linkedlist_test

compile -I. binarysearchtree.c -o target/binarysearchtree.o
compile -I. binarysearchtree_test.c -o target/binarysearchtree_test.o
gcc target/binarysearchtree_test.o target/binarysearchtree.o -o target/binarysearchtree_test

./target/binarysearchtree_test
