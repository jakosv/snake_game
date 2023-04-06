#ifndef SNAKE_GAME_H_SENTRY
#define SNAKE_GAME_H_SENTRY

#include <sys/time.h>

struct snake_game {
    struct field *field;
    struct snake *snake;
    struct fruit *fruit;
    int score, score_msg_x, score_msg_y;
    int game_over;
};

void snake_game_init(struct snake_game *game);
void snake_game_free(struct snake_game *game);
void snake_game_start(struct snake_game *game);

#endif
