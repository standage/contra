CFLAGS=-Wall -Iinc/ --std=c++11

all: bin/test

clean:
	rm -f obj/*.o bin/test

obj/bstree.o: src/bstree.cpp inc/bstree.hpp
	g++ $(CFLAGS) -c -o $@ $<

obj/test.o: src/test.cpp
	g++ $(CFLAGS) -c -o $@ $<

bin/test: obj/test.o obj/bstree.o
	g++ $(CFLAGS) -o $@ $^
