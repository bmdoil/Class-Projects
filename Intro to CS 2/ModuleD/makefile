CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = Grid.o Critter.o CS162.o modD.o Ant.o Doodlebug.o

SRCS = Grid.cpp Critter.cpp CS162.cpp modD.cpp Ant.cpp Doodlebug.cpp

HEADERS = Grid.hpp Critter.hpp CS162.hpp Ant.hpp Doodlebug.hpp

TARGET = modD

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean: 
	${RM} ${TARGET} *.o *~
