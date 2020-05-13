#include <stdlib.h>
#include "list_adt.h"

typedef struct point
{
    int x, y;
} Point;

typedef struct direction
{
    Point point;
    int name;
} Direction;

typedef struct snake
{
    Point *head;
    List *body;
} Snake;

Snake *create_snake(Point origin);
int snake_size(Snake *);
Point *get_head(Snake *);
Point *get_part(Snake *, int);
int snake_at_point(Snake *, Point);
void add_part(Snake *, Point *);
void update_snake(Snake *, Direction, Point);
void destroy_snake(Snake *);
