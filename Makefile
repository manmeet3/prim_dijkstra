# Manmeet Singh - msingh11@ucsc.edu

# Definitions 
CC	= gcc
CFLAGS	= -g -Wall -O0

# Creating the executable
graph04: graph04.o edgeList.o minPQ.o primDJK.o
	${CC} -o graph04 ${CFLAGS} graph04.o  edgeList.o minPQ.o primDJK.o

graph04.o: graph04.c edgeList.h minPQ.h
	${CC} -c ${CFLAGS} graph04.c

edgeList.o: edgeList.c
	${CC} -c ${CFLAGS} edgeList.c
	
minPQ.o: minPQ.c
	${CC} -c ${CFLAGS} minPQ.c	

primDJK.o: primDJK.c
	${CC} -c ${CFLAGS} primDJK.c	

# Remove object files
clean:
	rm *.o
spotless:
	rm *.o graph04
