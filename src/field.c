#include "field.h"

#include <curses.h>
#include <stdlib.h>

enum { field_border = '#' };

static const char score_message[] = "Score:";

void field_update_coords(int col, int row, struct field *field)
{
    field->x = (col - field->width) / 2;
    field->y = (row - field->height + 1) / 2;
    field->score_msg_x = (col - sizeof(score_message)) / 2;
    field->score_msg_y = field->y - 2;
}

void field_init(int col, int row, int fwidth, int fheight, struct field *field)
{
    field->width = fwidth;
    field->height = fheight;
    field_update_coords(col, row, field);
}

void field_addch(int x, int y, char ch)
{
    move(y, x);
    addch(ch);
}

static void show_border_line(int x, int y, int width)
{
    int i;
    move(y, x);
    for (i = 0; i < width; i++)
        addch(field_border);
}

static void show_border_line_corners(int x, int y, int width)
{
    field_addch(x, y, field_border);
    field_addch(x + width - 1, y, field_border);
}

void field_show_score(int score, const struct field *field)
{
    mvprintw(field->score_msg_y, field->score_msg_x, "%s %d    ", 
             score_message, score);
}

void field_show_border(const struct field *field)
{
    int i;
    show_border_line(field->x - 1, field->y - 1, field->width + 2); 
    for (i = 0; i < field->height; i++)
        show_border_line_corners(field->x - 1, field->y + i, 
                                 field->width + 2);
    show_border_line(field->x - 1, field->y + field->height, 
                     field->width + 2); 
}

int is_correct_window_size(int row, int col, const struct field *field)
{
    return (row >= field->height + 3) && (col >= field->width + 2);
}
