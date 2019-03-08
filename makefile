CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -Wstatic-float-init

Nbody: 
	${CXX} ${CXXFLAGS} -o Nbody nbody.cpp

