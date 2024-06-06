SRC = $(DIRBIGINT)/bigint.c $(DIRRSA)/rsa.c $(DIRMAIN)/main.c
TESTSRC = $(DIRBIGINT)/test_bigint.c

DIRBIGINT = ./src/bigint
DIRRSA = ./src/rsa
DIRMAIN = ./src/programa

OBJ = $(SRC:.c=.o)
BIN = rsa
TESTBIN = test_bigint

CC = gcc
CFLAGS = -I$(DIRBIGINT) -Wall -Wextra -Werror -O3
CTESTFLAGS = -I$(DIRBIGINT) -Wall -Wextra -g -O3

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TESTBIN)

a:
	gcc -Wall -Wextra -g -O3 ./src/bigint/bigint.c ./src/rsa/rsa.c ./src/rsa/test.c -o test


$(TESTBIN): $(TESTSRC) $(SRC)
	$(CC) $(CTESTFLAGS) -o $@ $^

profile: $(TESTBIN)
	./$(TESTBIN)
	gprof $(TESTBIN) gmon.out > profile.txt

clean:
	rm -f $(BIN) $(TESTBIN) gmon.out profile.txt test
