SRC = $(DIRBIGINT)/bigint.c
TESTSRC = $(DIRBIGINT)/test_bigint.c

DIRBIGINT = ./src/bigint

OBJ = $(SRC:.c=.o)
BIN = bigint
TESTBIN = test_bigint

CC = gcc
CFLAGS = -I$(DIRBIGINT) -Wall -Wextra -Werror -O3
CTESTFLAGS = -I$(DIRBIGINT) -Wall -Wextra -pg -O3

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(TESTBIN)


$(TESTBIN): $(TESTSRC) $(SRC)
	$(CC) $(CTESTFLAGS) -o $@ $^

profile: $(TESTBIN)
	./$(TESTBIN)
	gprof $(TESTBIN) gmon.out > profile.txt

clean:
	rm -f $(BIN) $(TESTBIN) gmon.out profile.txt
