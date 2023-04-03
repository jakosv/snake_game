#ifndef SNAKE_H_SENTRY
#define SNAKE_H_SENTRY

#include "snake_body.h"
#include "field.h"

struct snake {
    struct snake_body *head;
};

void snake_init(int x, int y, int dx, int dy, struct snake *snake);
void snake_free(struct snake *snake);
void snake_move(struct snake *snake, const struct field *field);
void snake_set_direction(int dx, int dy, struct snake *snake);
void snake_eat_fruit(struct snake *snake, const struct field *field);
void snake_hide(const struct snake *snake, const struct field *field);
void snake_show(const struct snake *snake, const struct field *field);
int is_snake_tail(int x, int y, const struct snake *snake);
int check_snake_tail_collision(const struct snake *snake);

#endif
