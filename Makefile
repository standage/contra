CFLAGS=-Wall -Iinc/ --std=c++11

TESTBINS=bin/test bin/bst_rand_test

all: $(TESTBINS)

test: bin/bst_rand_test
	bin/bst_rand_test 1000000 | aux/check-order.py

clean:
	rm -f obj/*.o $(TESTBINS)

obj/bstree.o: src/bstree.cpp inc/bstree.hpp
	g++ $(CFLAGS) -c -o $@ $<

bin/test: test/test.cpp obj/bstree.o
	g++ $(CFLAGS) -o $@ $^

bin/bst_rand_test: test/bst_rand.cpp obj/bstree.o
	g++ $(CFLAGS) -o $@ $^
