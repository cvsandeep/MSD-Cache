CC     = gcc
CFLAGS = -I.
DEPS   = 
OBJ    = main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

cache: main.o
	$(CC) -o Release/$@ $^ $(CFLAGS)

clean: 
	rm -f *.o *~ 
