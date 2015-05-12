#############################################
# 
# Simple makefile for hex2asc and asc2hex utilities
#
#IDIR =../include
CC=gcc
#CFLAGS=-I$(IDIR)
CFLAGS=-I.
LDFLAGS=-lm
DEPS = 
OBJASC = hex2asc.o binaschex.o
OBJHEX = asc2hex.o binaschex.o
OBJINT = hex2int.o binaschex.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: asc2hex hex2asc hex2int

asc2hex: $(OBJHEX)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

hex2asc: $(OBJASC)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

hex2int: $(OBJINT)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core  

cleanall:
	rm -f *.o *~ core hex2asc asc2hex hex2int

install:
	install -s hex2asc asc2hex hex2int /usr/local/sbin

