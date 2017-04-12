#############################################
# 
# Simple makefile for hex2asc and asc2hex utilities
#
INSTALL=install
WHERE=~/bin
#IDIR =../include
CC=gcc
#CFLAGS=-I$(IDIR)
CFLAGS=-I.
LDFLAGS=-lm
DEPS = 
OBJASC = hex2asc.o binaschex.o 
OBJHEX = binaschex.o asc2hex.o 
OBJINT = binaschex.o hex2int.o 

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

cleanall: clean
	rm -f hex2asc asc2hex hex2int

install:
	$(INSTALL) -s hex2asc asc2hex hex2int $(WHERE)

