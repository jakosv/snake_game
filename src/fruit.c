#include "fruit.h"

void fruit_show(const struct fruit *fruit, const struct field *field)
{
    field_addch(field->x + fruit->x, field->y + fruit->y, fruit_char); 
}

void fruit_hide(const struct fruit *fruit, const struct field *field)
{
    field_addch(field->x + fruit->x, field->y + fruit->y, ' '); 
}
