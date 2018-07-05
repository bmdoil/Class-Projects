CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = modF.o CS162.o Queue.o Traffic.o

SRCS = CS162.cpp modF.cpp Queue.cpp Traffic.cpp

HEADERS = Queue.hpp CS162.hpp Traffic.hpp

TARGET = modF

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean: 
	${RM} ${TARGET} *.o *~
