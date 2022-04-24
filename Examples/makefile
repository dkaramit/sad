rootDir="../"


IncludeDir=$(rootDir)
IncludeHPP = $(shell find $(rootDir)SAD/ -type f -name '*.hpp')

CC=g++
OPT=-O3
# STD=-std=c++14 #you need c++14 and above
STD=-std=c++17

FLG=-I$(IncludeDir) $(OPT) $(STD) -Wall

all: variables_constants_expressions.run

variables_constants_expressions.run: variables_constants_expressions.cpp makefile $(IncludeHPP)
	$(CC) -o $@ $< $(FLG) 

clean:
	rm variables_constants_expressions.run || true