CC = g++ # otherwise linking will automatically will gcc instead of g++ and result in error

CXXFLAGS = -std=c++17
LDFLAGS = 
LDLIBS =

main: main.o simplify.o contract.o operator.o term.o elem.o sym.o utils.o toLatex.o

main.o: main.cc defs.h

simplify.o: simplify.cc defs.h

contract.o: contract.cc defs.h

operator.o: operator.cc defs.h

term.o: term.cc defs.h

elem.o: elem.cc defs.h

sym.o: sym.cc defs.h

utils.o: utils.cc defs.h

toLatex.o: toLatex.cc defs.h

clean:
	rm *.o
