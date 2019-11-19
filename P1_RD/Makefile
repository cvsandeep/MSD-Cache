# This is my makefile for ECE 485 
     

CC=gcc
# compile for 32-bit rather than 64-bit
CFLAGS=-m32 -O0 
DFLAGS=-g
PROGS=ECE485_P1

all: $(PROGS)

%: %.c
	$(CC) $(CFLAGS) $(DFLAGS) $< -Wall -pthread -lm -o $@

clean:
	rm -f $(PROGS) *.o ~* 


