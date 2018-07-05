CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = Team.o Defeated.o  BabaYaga.o  Barbarian.o BlueMen.o Creature.o CS162.o FightLogic.o Harry.o assign4.o Medusa.o

SRCS = Team.cpp Defeated.cpp BabaYaga.cpp  Barbarian.cpp BlueMen.cpp Creature.cpp CS162.cpp FightLogic.cpp Harry.cpp assign4.cpp Medusa.cpp

HEADERS = Team.hpp Defeated.hpp BabaYaga.hpp  Barbarian.hpp BlueMen.hpp Creature.hpp CS162.hpp FightLogic.hpp Harry.hpp Medusa.hpp 

TARGET = assign4

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean: 
	${RM} ${TARGET} *.o *~
