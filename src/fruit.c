#include "fruit.h"

enum { fruit_color = fc_red };

void fruit_init(int x, int y, struct fruit *fruit)
{
    fruit->x = x;
    fruit->y = y;
}

void fruit_show(const struct fruit *fruit, const struct field *field)
{
    field_addch(fruit->x, fruit->y, fruit_char, fruit_color, field); 
}

void fruit_hide(const struct fruit *fruit, const struct field *field)
{
    field_addch(fruit->x, fruit->y, ' ', fruit_color, field); 
}
