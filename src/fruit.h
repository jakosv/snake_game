#ifndef FRUIT_H_SENTRY
#define FRUIT_H_SENTRY

#include "field.h"

enum { fruit_char = 'a' };

struct fruit {
    int x, y;
};

void fruit_init(int x, int y, struct fruit *fruit);
void fruit_show(const struct fruit *fruit, const struct field *field);
void fruit_hide(const struct fruit *fruit, const struct field *field);

#endif
