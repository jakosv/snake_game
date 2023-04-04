#include "snake_game.h"

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int main()
{
    struct snake_game game;

    srand(time(NULL));
    snake_game_init(&game);
    snake_game_start(&game);
    printf("Score: %d\n", game.score);
    snake_game_free(&game);

    return 0;
}
