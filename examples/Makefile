
CC = gcc
CFLAGS = -Wall -g -std=c99
IFLAGS = -I../src
STATIC_LFILE = ../src/libmpool.a
ALL_OBJS = example
OBJS = example.o
MPOOL_OBJS = ../src/mpool.o

.c.o:
	cd ../src && $(MAKE)
	$(CC) $(CFLAGS) $(IFLAGS) -c $<

all : $(ALL_OBJS)


example : $(OBJS) $(STATIC_LFILE)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(STATIC_LFILE)

clean :
	rm $(ALL_OBJS) $(OBJS) $(STATIC_LFILE) $(MPOOL_OBJS)

example.o : example.c ../src/mpool.c ../src/mpool.h
