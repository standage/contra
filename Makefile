CFLAGS=-Wall -Iinc/ --std=c++11

all: bin/test

clean:
	rm -f obj/*.o bin/test

obj/avltree.o: src/avltree.cpp inc/avltree.hpp
	g++ $(CFLAGS) -c -o $@ $<

obj/test.o: src/test.cpp
	g++ $(CFLAGS) -c -o $@ $<

bin/test: obj/test.o obj/avltree.o
	g++ $(CFLAGS) -o $@ $^
