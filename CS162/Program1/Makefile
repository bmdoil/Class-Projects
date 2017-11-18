CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = A1Grid.o Ant.o CS162.o mainAnt.o

SRCS = A1Grid.cpp Ant.cpp CS162.cpp mainAnt.cpp

HEADERS = A1Grid.hpp Ant.hpp CS162.hpp

TARGET = mainAnt

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean: 
	${RM} ${TARGET} *.o *~
