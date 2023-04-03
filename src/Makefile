PROG = snake_game
CFLAGS = -Wall -g -ansi -pedantic
LDFLAGS = -lncurses
OBJMODULES = snake.o snake_game.o fruit.o field.o snake_body.o

.PHONY: clean

%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

$(PROG): main.c $(OBJMODULES)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

clean:
	rm $(PROG) *.o
