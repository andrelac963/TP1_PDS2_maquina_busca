C = g++
W = -std=c++11 -g -w

B = ./build
I = ./include
S = ./src

all: mkdir main

main: ${B}/main.o ${B}/indexing.o
	${C} ${W} ${B}/*.o -o search_machine

${B}/main.o: ${S}/main.cpp
	${C} ${W} -I ${I} -c ${S}/main.cpp -o ${B}/main.o
${B}/indexing.o: ${I}/indexing.hpp ${S}${E}/indexing.cpp
	${C} ${W} -I ${I} -c ${S}/indexing.cpp -o ${B}/indexing.o

mkdir:
	mkdir -p ${B}

run:
	./search_machine

clear:
	rm ${B}/*.o
	rm ./search_machine