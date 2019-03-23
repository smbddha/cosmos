CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 

Nbody: nbody.o main.o 
	${CXX} ${CXXFLAGS} -o Nbody nbody.o main.o

nbody.o: nbody.hpp
main.o: nbody.hpp

test:
	./Nbody 2> /dev/null | ../vis/visual.py

clean:
	rm -f Nbody *.o
