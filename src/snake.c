#include "snake.h"
#include "snake_body.h"
#include "utils.h"

#include <stdlib.h>

MAKE_SWAP_FUNCTION(int)
MAKE_SWAP_FUNCTION(char)

enum { 
    snake_head_char = '@', 
    snake_body_char = 'o', 
    snake_tail_char = '+',
    snake_full_body_char = 'O' 
};

void snake_init(int x, int y, int dx, int dy, struct snake *snake)
{
    snake->head = malloc(sizeof(struct snake_body));
    snake_body_init(x, y, dx, dy, snake_body_char, snake->head);
    snake_body_grow(&snake->head);
    snake->head->ch = snake_head_char;
    snake->head->next->ch = snake_tail_char;
}

void snake_free(struct snake *snake)
{
    snake_body_free(snake->head);
    snake->head = NULL;
}

static void snake_body_show(const struct snake_body *body,
                     const struct field *field)
{
    field_addch(field->x + body->x, field->y + body->y, body->ch);
}

static void snake_body_hide(const struct snake_body *body,
                     const struct field *field)
{
    field_addch(field->x + body->x, field->y + body->y, ' ');
}

void snake_hide(const struct snake *snake, const struct field *field)
{
    struct snake_body *tmp;
    for (tmp = snake->head; tmp; tmp = tmp->next)
        snake_body_hide(tmp, field);
}

void snake_show(const struct snake *snake, const struct field *field)
{
    struct snake_body *tmp;
    for (tmp = snake->head; tmp; tmp = tmp->next)
        snake_body_show(tmp, field);
}

static void check_coord(int *coord, int max_coord)
{
    if (*coord > max_coord)
       *coord = 0;
    else if (*coord < 0)
       *coord = max_coord;
}

static void update_body_direction(int *dx, int *dy, struct snake_body *body)
{
    if (body->dx != *dx || body->dy != *dy) {
        swap_int(&body->dx, dx);
        swap_int(&body->dy, dy);
    }
}

void snake_move(struct snake *snake, const struct field *field)
{
    struct snake_body *tmp;
    int body_dx, body_dy;
    char body_char;
    body_dx = snake->head->dx;
    body_dy = snake->head->dy;
    body_char = snake_body_char;
    for (tmp = snake->head; tmp; tmp = tmp->next) {
        snake_body_hide(tmp, field);
        snake_body_move(tmp);
        check_coord(&tmp->x, field->width - 1);
        check_coord(&tmp->y, field->height - 1);
        if (tmp != snake->head)
            update_body_direction(&body_dx, &body_dy, tmp);
        if (tmp->ch != body_char && tmp != snake->head && tmp->next)
            swap_char(&body_char, &tmp->ch);
        snake_body_show(tmp, field);
    }
}

static int is_correct_direction(int dx, int dy, const struct snake *snake)
{
    return (snake->head->dx * dx + snake->head->dy * dy) == 0;
}

void snake_set_direction(int dx, int dy, struct snake *snake)
{
    if (!is_correct_direction(dx, dy, snake))
        return;
    snake->head->dx = dx;
    snake->head->dy = dy;
}

void snake_eat_fruit(struct snake *snake, const struct field *field)
{
    snake_body_grow(&snake->head);
    snake->head->next->ch = snake_full_body_char;
    snake_body_show(snake->head, field);
    snake_body_show(snake->head->next, field);
}

int is_snake_tail(int x, int y, const struct snake *snake)
{
    struct snake_body *tmp;
    for (tmp = snake->head; tmp; tmp = tmp->next)
        if (tmp->x == x && tmp->y == y)
            return 1;
    return 0;
}

int check_snake_tail_collision(const struct snake *snake)
{
    int snake_x, snake_y;
    snake_x = snake->head->x + snake->head->dx;
    snake_y = snake->head->y + snake->head->dy;
    return is_snake_tail(snake_x, snake_y, snake);
}

