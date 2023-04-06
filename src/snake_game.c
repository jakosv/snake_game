#include "snake_game.h"
#include "field.h"
#include "snake.h"
#include "fruit.h"

#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

enum { delay_duration = 100 };
enum { field_width = 50, field_height = 15 };
enum { key_escape = 27 };

static int rand_int(int low, int hight)
{
    return low + (int)(1.0*hight*rand()/(RAND_MAX+1.0));
}

static void add_snake(struct snake_game *game)
{
    int x, y, dx, dy;
    x = rand_int(2, game->field->width-3);
    y = rand_int(2, game->field->height-3);
    dx = rand_int(-1, 1);
    if (dx == 0)
        dy = rand_int(0, 1) == 0 ? 1 : -1;
    else
        dy = 0;
    game->snake = malloc(sizeof(struct snake));
    snake_init(x, y, dx, dy, game->snake);
}

static void add_fruit(struct snake_game *game)
{
    int x, y;
    do {
        x = rand_int(0, game->field->width-1);
        y = rand_int(0, game->field->height-1);
    } while (game->snake && is_snake_tail(x, y, game->snake));

    game->fruit = malloc(sizeof(struct fruit));
    game->fruit->x = x;
    game->fruit->y = y;
}

void snake_game_init(struct snake_game *game)
{
    int row, col;

    initscr();
    cbreak();
    keypad(stdscr, 1);
    noecho();
    curs_set(0);
    timeout(delay_duration);
    getmaxyx(stdscr, row, col);

    game->score = 0;

    game->field = malloc(sizeof(struct field));
    field_init(col, row, field_width, field_height, game->field);

    add_snake(game);
    add_fruit(game);
    
    game->game_over = !is_correct_window_size(row, col, game->field);
}

static void game_show(const struct snake_game *game)
{
    field_show_score(game->score, game->field);
    field_show_border(game->field);
    snake_show(game->snake, game->field);
    fruit_show(game->fruit, game->field); 
    refresh();
}

void snake_game_free(struct snake_game *game)
{
    snake_free(game->snake);
    free(game->snake);
    free(game->fruit);
    free(game->field);
    game->snake = NULL;
    game->fruit = NULL;
    game->field = NULL;
}

static void handle_resize(struct snake_game *game)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    if (!is_correct_window_size(row, col, game->field)) {
        game->game_over = 1;
        return;
    }
    field_update_coords(col, row, game->field);
    clear();
    game_show(game);
    refresh();
}

static int check_snake_fruit_collision(const struct fruit *fruit, 
                                       const struct snake *snake)
{
    int snake_x, snake_y;
    snake_x = snake->head->x + snake->head->dx;
    snake_y = snake->head->y + snake->head->dy;
    return snake_x == fruit->x && snake_y == fruit->y;
}

static void handle_snake_fruit_collision(struct snake_game *game)
{
    free(game->fruit);
    snake_eat_fruit(game->snake, game->field);
    add_fruit(game);
    fruit_show(game->fruit, game->field);
    game->score++;
    field_show_score(game->score, game->field);
}

void snake_game_start(struct snake_game *game)
{
    int key;
    game_show(game);
    while ((key = getch()) != key_escape && !game->game_over) {
        switch (key) {
        case KEY_UP:
            snake_set_direction(0, -1, game->snake);
            break;
        case KEY_DOWN:
            snake_set_direction(0, 1, game->snake);
            break;
        case KEY_LEFT:
            snake_set_direction(-1, 0, game->snake);
            break;
        case KEY_RIGHT:
            snake_set_direction(1, 0, game->snake);
            break;
        case KEY_RESIZE:
            handle_resize(game);
            break;
        } 
        
        if (check_snake_fruit_collision(game->fruit, game->snake))
            handle_snake_fruit_collision(game);
        else if (check_snake_tail_collision(game->snake))
            game->game_over = 1;
        else
            snake_move(game->snake, game->field); 
        refresh();
    }
    endwin();
}
