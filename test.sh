#!/usr/bin/env bash

set -ex

mkdir -p target

compile() { gcc -g -Wall -x c -c $@; }

#compile murmur3/murmur3.c -o target/murmur3.o
#compile -Imurmur3 -I. hashmap.c -o target/hashmap.o
#compile -Imurmur3 -I. hashmap_test.c -o target/hashmap_test.o
#gcc target/hashmap_test.o target/hashmap.o target/murmur3.o -o target/hashmap_test
#
#./target/hashmap_test
#
#compile linkedlist.c -o target/linkedlist.o
#compile -I. linkedlist_test.c -o target/linkedlist_test.o
#gcc target/linkedlist_test.o target/linkedlist.o -o target/linkedlist_test
#
#./target/linkedlist_test
#
#compile -I. binarysearchtree.c -o target/binarysearchtree.o
#compile -I. binarysearchtree_test.c -o target/binarysearchtree_test.o
#gcc target/binarysearchtree_test.o target/binarysearchtree.o -o target/binarysearchtree_test
#
#./target/binarysearchtree_test
#
#compile -I. circularbuffer.c -o target/circularbuffer.o
#compile -I. circularbuffer_test.c -o target/circularbuffer_test.o
#gcc target/circularbuffer.o target/circularbuffer_test.o -o target/circularbuffer_test
#
#./target/circularbuffer_test
#
#compile -I. binaryheap.c -o target/binaryheap.o
#compile -I. binaryheap_test.c -o target/binaryheap_test.o
#gcc -g target/binaryheap_test.o target/binaryheap.o -o target/binaryheap_test
#
#./target/binaryheap_test

compile -I. skiplist.c -o target/skiplist.o
compile -I. skiplist_test.c -o target/skiplist_test.o
gcc -g target/skiplist_test.o target/skiplist.o -o target/skiplist_test

./target/skiplist_test
