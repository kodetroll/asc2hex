#############################################
# 
# Simple makefile for hex2asc and asc2hex utilities
#
#IDIR =../include
CC=gcc
#CFLAGS=-I$(IDIR)

CC=gcc
CFLAGS=-I.
DEPS = 
OBJASC = hex2asc.o  
OBJHEX = asc2hex.o 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: asc2hex hex2asc

asc2hex: $(OBJHEX)
	$(CC) -o $@ $^ $(CFLAGS)

hex2asc: $(OBJASC)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ core  

cleanall:
	rm -f *.o *~ core hex2asc asc2hex

install:
	install -s hex2asc asc2hex /usr/local/sbin

