reootDir="./"

IncludeDir="$(reootDir)"
IncludeHPP = $(shell find SAD/ -type f -name '*.hpp')

CC=g++
OPT=-O3
STD=-std=c++17 #in order to utilize type deduction, use c++17

FLG=-I$(IncludeDir) $(OPT) $(STD) -Wall


all: test.run examples

test.run: test.cpp makefile $(IncludeHPP)
	$(CC) -o $@ $< $(FLG) 

examples:
	cd Examples && $(MAKE) all


clean:
	rm test.run || true
	cd Examples && $(MAKE) clean