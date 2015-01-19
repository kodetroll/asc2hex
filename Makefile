#############################################
# 
# Simple makefile for hex2bin and asc2hex utilities
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
	gcc -o $@ $^ $(CFLAGS)

hex2asc: $(OBJASC)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean

cleanall:
	rm -f hex2asc asc2hex *.o *~ core  
clean:
	rm -f *.o *~ core  
