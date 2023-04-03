#ifndef FIELD_H_SENTRY
#define FIELD_H_SENTRY

struct field {
    int x, y, width, height, score_msg_x, score_msg_y;
};

void field_init(int col, int row, int fwidth, int fheight, struct field *field);
void field_update_coords(int col, int row, struct field *field);
void field_addch(int x, int y, char ch);
void field_show_score(int score, const struct field *field);
void field_show_border(const struct field *field);
int is_correct_window_size(int row, int col, const struct field *field);

#endif
