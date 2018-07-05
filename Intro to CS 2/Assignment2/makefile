CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = List.o Item.o CS162.o shoppingList.o

SRCS = List.cpp Item.cpp CS162.cpp shoppingList.cpp

HEADERS = List.hpp Item.hpp CS162.hpp

TARGET = shopList

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean: 
	${RM} ${TARGET} *.o *~
