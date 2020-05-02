CC = gcc
SRC = rules.c pile.c controls.c uno.c
OBJ = $(SRC:.c=.o)
SRC_B = rules.c pile.c controls.c tests_unitaire.c
OBJ_B = $(SRC_B:.c=.o)
HEADERS = rules.h pile.h controls.h uno.h
CFLAGS = -Wall
PROG = UNO

$(PROG): $(OBJ) $(HEADERS)
	$(CC) -o $@ $(OBJ)
%.o: %.c
	$(CC) -c $< $(CFLAGS)
test: $(OBJ_B) $(HEADERS)
	$(CC) -o $@ $(OBJ_B)