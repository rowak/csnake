#include "list_adt.h"
#include "snake.h"

#define GRID_WIDTH 80
#define GRID_HEIGHT 24
#define BAD_DIR 8

#define EXIT_KEY 'q'

#define CLOCK_SPEED_H 50000
#define CLOCK_SPEED_V 70000

int update(Snake *, Direction, Point **);
void draw_snake(Snake *);
void draw_food(Point);
void draw_gameover(int);
Direction get_dir(int);
int num_digits(int);
void sleep_timer(Direction);
Point *get_random_food();
void reset_food(Snake *, Point **);
int check_collision(Snake *, Point **);
int check_snake_food_collision(Snake *, Point);
int check_snake_wall_collision(Snake *);
int check_snake_snake_collision(Snake *);
