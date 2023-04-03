#include "snake_body.h"

#include <stdlib.h>

void snake_body_init(int x, int y, int dx, int dy, char ch, 
                     struct snake_body *body)
{
    body->x = x;
    body->y = y;
    body->dx = dx;
    body->dy = dy;
    body->ch = ch;
    body->next = NULL;
}

void snake_body_free(struct snake_body *body)
{
    struct snake_body *tmp;
    while (body) {
        tmp = body;
        body = body->next;
        free(tmp);
    }
}

void snake_body_move(struct snake_body *body)
{
    body->x += body->dx;
    body->y += body->dy;
}

void snake_body_grow(struct snake_body **body)
{
    struct snake_body *new_body;
    new_body = malloc(sizeof(struct snake_body));
    snake_body_init((*body)->x + (*body)->dx, (*body)->y + (*body)->dy,
                    (*body)->dx, (*body)->dy,
                    (*body)->ch,
                    new_body);
    new_body->next = *body;
    *body = new_body;
}
