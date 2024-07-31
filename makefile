CXX=g++
CXXFLAGS=-std=c++17 -g -MMD
EXEC=chess
CCFILES=$(wildcard */*.cpp)
OBJECTS=${CCFILES:.cpp=.o}
DEPENDS=${CCFILES:.cpp=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS} ${EXEC}
