CXX = gcc
CXXFLAGS = -g
CXXFLAGS += -Wall
CXXFLAGS += -lpthread

OBJS = ftserver.o server.o
SRCS = ftserver.c server.c
HEADERS = server.h
TARGET = ftserver

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean:
	${RM} ${TARGET} *.o *~