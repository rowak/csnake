#include "list_adt.h"
#include "snake.h"

#define GRID_WIDTH 80
#define GRID_HEIGHT 24
#define BAD_DIR 8

#define CLOCK_SPEED_H 50000
#define CLOCK_SPEED_V 70000

int update(Snake *, Direction, Point **);
void draw_snake(Snake *);
void draw_food(Point food);
Direction get_dir(int);
void sleep_timer(Direction);
Point *get_random_food();
int check_collision(Snake *, Point **);
