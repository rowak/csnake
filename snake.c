#include "snake.h"

Snake *create_snake(Point origin)
{
    Snake *snake = malloc(sizeof(Snake));
    snake->body = create_list();
    push(snake->body, &origin);
    snake->head = get_nth(snake->body, 0);
    return snake;
}

int snake_size(Snake *snake)
{
    return snake->body->size;
}

Point *get_head(Snake *snake)
{
    return snake->head;
}

Point *get_part(Snake *snake, int n)
{
    return get_nth(snake->body, n);
}

int snake_at_point(Snake *snake, Point point)
{
    for (int i = 0; i < snake_size(snake); i++)
    {
        Point *part = get_part(snake, i);
        if (part->x == point.x && part->y == point.y)
        {
            return 1;
        }
    }
    return 0;
}

void add_part(Snake *snake, Point *part)
{
    append(snake->body, part);
}

void update_snake(Snake *snake, Direction dir, Point food)
{
    if (snake_size(snake) > 1)
    {
        for (int i = snake_size(snake)-1; i > 0; i--)
        {
            Point *part = get_part(snake, i);
            Point *prev_part = get_part(snake, i-1);
            part->x = prev_part->x;
            part->y = prev_part->y;
        }
    }
    Point *head = get_head(snake);
    head->x += dir.point.x;
    head->y += dir.point.y;
}

void destroy_snake(Snake *snake)
{
    destroy_list(snake->body);
    free(snake);
}
