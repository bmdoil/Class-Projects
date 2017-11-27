CXX = gcc
CXXFLAGS = -g
CXXFLAGS += -Wall

OBJS = ftserv.o 
SRCS = ftserv.c 
TARGET = ftserv

${TARGET}: ${SRCS} ${HEADERS}
	${CXX} ${CXXFLAGS} ${SRCS} -o ${TARGET}

clean:
	${RM} ${TARGET} *.o *~