#include "field.h"

#include <curses.h>
#include <stdlib.h>

enum { field_border = '#' };

static const char score_message[] = "Score:";
static const int fcolors[fc_count] = { 
    fc_default, COLOR_GREEN | A_BOLD, COLOR_RED | A_BOLD
};

void field_update_coords(int col, int row, struct field *field)
{
    field->x = (col - field->width) / 2;
    field->y = (row - field->height + 1) / 2;
    field->score_msg_x = (col - sizeof(score_message)) / 2;
    field->score_msg_y = field->y - 2;
    field->work_bw = !has_colors();
    if (!field->work_bw) {
        int i;
        start_color();
        use_default_colors();
        for (i = 1; i < fc_count; i++)
            init_pair(i, fcolors[i], COLOR_BLACK); 
    }
}

void field_init(int col, int row, int fwidth, int fheight, 
                struct field *field)
{
    field->width = fwidth;
    field->height = fheight;
    field_update_coords(col, row, field);
}

void field_addch(int x, int y, char ch, enum field_color color,
                 const struct field* field)
{
    if (!field->work_bw && color != fc_default)
        attrset(COLOR_PAIR(color));
    move(field->y + y, field->x + x);
    addch(ch);
    if (!field->work_bw && color != fc_default)
        attrset(COLOR_PAIR(fc_default));
}

static void show_border_line(int y, const struct field *field)
{
    int x;
    for (x = -1; x <= field->width; x++)
        field_addch(x, y, field_border, fc_default, field);
}

static void show_border_line_corners(int y, const struct field *field)
{
    field_addch(-1, y, field_border, fc_default, field);
    field_addch(field->width, y, field_border, fc_default, field);
}

void field_show_score(int score, const struct field *field)
{
    mvprintw(field->score_msg_y, field->score_msg_x, "%s %d    ", 
             score_message, score);
}

void field_show_border(const struct field *field)
{
    int i;
    show_border_line(-1, field); 
    for (i = 0; i < field->height; i++)
        show_border_line_corners(i, field);
    show_border_line(field->height, field); 
}

int is_correct_window_size(int row, int col, const struct field *field)
{
    return (row >= field->height + 3) && (col >= field->width + 2);
}
