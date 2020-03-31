CC=gcc
CFLAGS=-I.
DEPS = bank.h
DEPS += customer.h
OBJ = main.o
OBJ += customer.o
OBJ += bank.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bankers: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f *.o bankers
