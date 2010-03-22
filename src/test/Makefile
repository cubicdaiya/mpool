
CC = gcc
CFLAGS = -Wall -g -std=c99
IFLAGS = -I..
STATIC_LFILE = ../libmpool.a
ALL_OBJS = mpool_test
OBJS = mpool_test.o
MPOOL_OBJS = ../mpool.o

.c.o:
	cd .. && $(MAKE)
	$(CC) $(CFLAGS) $(IFLAGS) -c $<

all : $(ALL_OBJS)


mpool_test : $(OBJS) $(STATIC_LFILE)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(STATIC_LFILE)

clean :
	rm $(ALL_OBJS) $(OBJS) 

mpool_test.o : mpool_test.c ../mpool.c ../mpool.h
