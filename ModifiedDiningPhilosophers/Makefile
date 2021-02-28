CC=gcc
CFLAGS=-I.
DEPS = 
OBJ =  a4_2019028.o  A4_2019028.o

%.o: %.c $(DEPS)
	$(CC) -pthread -o  $@ $< $(CFLAGS)

all: $(OBJ)

clean:
	rm -f $(OBJ)
