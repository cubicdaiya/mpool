
CC = gcc
AR = ar
CFLAGS = -Wall -g -std=c99 -fPIC
ARFLAGS = r
STATIC_LFILE = libmpool.a
DYNAMIC_LFILE = libmpool.so
OBJS = mpool.o

.c.o:
	$(CC) $(CFLAGS) -c $<

$(STATIC_LFILE): $(OBJS)
	$(AR) $(ARFLAGS) $(STATIC_LFILE) $(OBJS)
	$(CC) -shared $(CFLAGS) $(OBJS) -o $(DYNAMIC_LFILE)

clean:
	rm $(OBJS) $(STATIC_LFILE) $(DYNAMIC_LFILE)


mpool.o: mpool.c mpool.h

