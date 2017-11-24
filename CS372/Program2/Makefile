CXX = gcc
CXXFLAGS = -g
CXXFLAGS += -Wall
CXXFLAGS += -lpthread

OBJS = ftserver.o
SRCS = ftserver.c
HEADERS = ftserver.h
TARGET = ftserver

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean:
	${RM} ${TARGET} *.o *~