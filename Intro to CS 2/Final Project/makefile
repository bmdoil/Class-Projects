CXX = g++
CXXFLAGS = -std=c++0x
CXXFLAGS += -Wall
CXXFLAGS += -pedantic-errors
CXXFLAGS += -g

OBJS = Wilderness.o Trainer.o Surf.o Store.o Squirtle.o Space.o Roster.o Pokemon.o Player.o Pikachu.o Map.o Item.o Hospital.o Hills.o Forest.o finalMain.o CS162.o Charmander.o Cave.o Bulbasaur.o Backpack.o Attack.o

SRCS = Wilderness.cpp Trainer.cpp Surf.cpp Store.cpp Squirtle.cpp Space.cpp Roster.cpp Pokemon.cpp Player.cpp Pikachu.cpp Map.cpp Item.cpp Hospital.cpp Hills.cpp Forest.cpp finalMain.cpp CS162.cpp Charmander.cpp Cave.cpp Bulbasaur.cpp Backpack.cpp Attack.cpp

HEADERS = Wilderness.hpp Trainer.hpp Surf.hpp Store.hpp Squirtle.hpp Space.hpp Roster.hpp Pokemon.hpp Player.hpp Pikachu.hpp Map.hpp Item.hpp Hospital.hpp Hills.hpp Forest.hpp CS162.hpp Charmander.hpp Cave.hpp Bulbasaur.hpp Backpack.hpp Attack.hpp

TARGET = pokemonFinal

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean: 
	${RM} ${TARGET} *.o *~
