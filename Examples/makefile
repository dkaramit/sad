rootDir="../"


IncludeDir=$(rootDir)
IncludeHPP = $(shell find $(rootDir)SAD/ -type f -name '*.hpp')

CC=g++
OPT=-O3
# STD=-std=c++14 #you need c++14 and above
STD=-std=c++17

FLG= -fsplit-stack -I$(IncludeDir) $(OPT) $(STD) -Wall

EXE = $(shell find . -type f -name '*.cpp' | sed 's/\.cpp/.run/g' | sed 's/\.\///g')

all: $(EXE)


%.run: %.cpp makefile $(IncludeHPP)
	$(CC) -o $@ $< $(FLG) 


clean:
	rm *.run || true
