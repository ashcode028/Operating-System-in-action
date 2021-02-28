
CC=gcc
CFLAGS=-I.
DEPS = 
OBJ = q1.o q2a.o q2b.o q2c.o q3a.o q3b.o q3c.o q4.o q5.o q6.o  

%.o: %.c $(DEPS)
	$(CC) -pthread -o $@ $< $(CFLAGS)

all: $(OBJ)

clean:
	rm -f $(OBJ)
