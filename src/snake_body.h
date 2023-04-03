#ifndef SNAKE_BODY_H_SENTRY
#define SNAKE_BODY_H_SENTRY

struct snake_body {
    int x, y, dx, dy;
    char ch;
    struct snake_body *next;
};

void snake_body_init(int x, int y, int dx, int dy, char ch, 
                     struct snake_body *body);
void snake_body_free(struct snake_body *body);
void snake_body_move(struct snake_body *body);
void snake_body_grow(struct snake_body **body);

#endif
