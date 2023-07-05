rootDir="./"

IncludeDir="$(rootDir)"
IncludeHPP = $(shell find SAD/ -type f -name '*.hpp')

CC=g++
OPT=-O3
STD=-std=c++17 #in order to utilize type deduction, use c++17

FLG= -fsplit-stack  -I$(IncludeDir) $(OPT) $(STD) -Wall -pedantic
##### -fsplit-stack allows for extremely large expressions with no segfault. I need to find a better way of handling memory.

all: test.run examples

test.run: test.cpp makefile $(IncludeHPP)
	$(CC) -o $@ $< $(FLG) 

examples:
	cd Examples && $(MAKE) all


clean:
	rm test.run || true
	cd Examples && $(MAKE) clean
