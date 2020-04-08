CC=gcc
CFLAGS=-I.
DEPS = bank.h
DEPS += customer.h
OBJ = main.o
OBJ += customer.o
OBJ += bank.o

LDLIBS = -lpthread

%.o: %.c $(DEPS)
	$(CC) -g -c -o $@ $< $(CFLAGS)

bankers: $(OBJ)
	$(CC)  -o $@ $^ $(CFLAGS) $(LDLIBS)

clean:
	rm -f *.o bankers
