CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = BabaYaga.o  Barbarian.o BlueMen.o Creature.o CS162.o FightLogic.o Harry.o main3.o Medusa.o

SRCS = BabaYaga.cpp  Barbarian.cpp BlueMen.cpp Creature.cpp CS162.cpp FightLogic.cpp Harry.cpp main3.cpp Medusa.cpp

HEADERS = BabaYaga.hpp  Barbarian.hpp BlueMen.hpp Creature.hpp CS162.hpp FightLogic.hpp Harry.hpp Medusa.hpp

TARGET = main3

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean: 
	${RM} ${TARGET} *.o *~
