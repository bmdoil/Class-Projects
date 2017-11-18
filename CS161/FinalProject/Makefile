CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors

OBJS = Book.o Library.o Patron.o mainLib.o
SRCS = Book.cpp Library.cpp Patron.cpp 
HEADERS = Book.hpp Library.hpp Patron.hpp
TARGET1 = mainLib
TARGET2 = lib

all: ${TARGET1} ${TARGET2} 

${TARGET1}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${TARGET1}.cpp -o ${TARGET1}

${TARGET2}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} ${TARGET2}.cpp -o ${TARGET2}


clean: 
	${RM} ${TARGET1} ${TARGET2} *.o *~
