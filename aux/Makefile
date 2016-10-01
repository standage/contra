INC=$(shell pkg-config contra --cflags-only-I --libs-only-L)

example: example.cpp
	g++ -Wall --std=c++11 $(INC) -o example example.cpp -lcontra
