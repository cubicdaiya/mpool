
CC = gcc
CFLAGS = -Wall -g -std=c99
IFLAGS = -I../src
STATIC_LFILE = ../src/libmpool.a
ALL_OBJS = mpool_test
OBJS = mpool_test.o
MPOOL_OBJS = ../src/mpool.o

.c.o:
	cd ../src && $(MAKE)
	$(CC) $(CFLAGS) $(IFLAGS) -c $<

all : $(ALL_OBJS)


mpool_test : $(OBJS) $(STATIC_LFILE)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(STATIC_LFILE)

clean :
	rm $(ALL_OBJS) $(OBJS) 

mpool_test.o : mpool_test.c ../src/mpool.c ../src/mpool.h
