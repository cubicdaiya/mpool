
VPATH = ../

CC = gcc
CFLAGS = -Wall -g -std=c99
LFLAGS = -lcunit
IFLAGS = -I..
TARGETS = mpool_test
OBJS = mpool_test.o mpool.o

.c.o:
	$(CC) $(CFLAGS) $(IFLAGS) -c $<

all : $(TARGETS)

mpool_test : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LFLAGS)

check : mpool_test
	@./mpool_test

clean :
	rm $(TARGETS) $(OBJS) 

mpool_test.o : mpool_test.c ../mpool.c ../mpool.h
