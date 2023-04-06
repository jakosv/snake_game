#ifndef FIELD_H_SENTRY
#define FIELD_H_SENTRY

enum field_color {
    fc_default, fc_green, fc_red, fc_count
};

struct field {
    int x, y, width, height, score_msg_x, score_msg_y;
    int work_bw;
};

void field_init(int col, int row, int fwidth, int fheight, 
                struct field *field);
void field_update_coords(int col, int row, struct field *field);
void field_addch(int x, int y, char ch, enum field_color color, 
                 const struct field *field);
void field_show_score(int score, const struct field *field);
void field_show_border(const struct field *field);
int is_correct_window_size(int row, int col, const struct field *field);

#endif
