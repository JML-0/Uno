CC = gcc
SRC = rules.c pile.c controls.c uno.c
OBJ = $(SRC:.c=.o)
HEADERS = rules.h pile.h controls.h
CFLAGS = -Wall
PROG = UNO

$(PROG): $(OBJ) $(HEADERS)
	$(CC) -o $@ $(OBJ)
%.o: %.c
	$(CC) -c $< $(CFLAGS)