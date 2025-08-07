#makefile since 2024-03-27
CC = gcc
#CFLAGS = -g3 -Wall -Wextra -std=c11
CFLAGS = -g
LDFLAGS = -li2c
SRC = shmenu.c led2472g.c hts221.c lps25h.c lsm9ds1.c tcs3400.c
OBJ = $(SRC:.c=.o)
DEPS = led2472g.h hts221.h lps25h.h lsm9ds1.h tcs3400.h
EXEC = shmenu
.PHONY: all clean
	all: $(EXEC)
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)
%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ) $(EXEC)
	touch *