CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 

Nbody: nbody.o main.o 
	${CXX} ${CXXFLAGS} -o Nbody nbody.o main.o

nbody.o: nbody.hpp
main.o: nbody.hpp
