Path=$(PWD)


IncludeDir="$(Path)"
IncludeHPP = $(shell find SAD/ -type f -name '*.hpp')



CC=g++
OPT=-O3
# STD=-std=c++14 #you need c++14 and above
STD=-std=c++17

FLG=-I$(IncludeDir) $(OPT) $(STD) -Wall

all: example_sad.run

example_sad.run: example_sad.cpp makefile $(IncludeHPP)
	
	$(CC) -o $@ $< $(FLG) 

clean:
	rm example_sad.run || true