#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include "csnake.h"

#define DIR_UP KEY_UP
#define DIR_DOWN KEY_DOWN
#define DIR_LEFT KEY_LEFT
#define DIR_RIGHT KEY_RIGHT

int main(int argc, char *argv[])
{
    Point HEAD_ORIGIN = {GRID_WIDTH/2, GRID_HEIGHT/2};
    Snake *snake = create_snake(HEAD_ORIGIN);
    Point *food = get_random_food();
    Direction dir = get_dir(DIR_RIGHT);
    int playing = TRUE;
    initscr();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    noecho();
    nodelay(stdscr, TRUE);

    int c;
    while ((c = getch()) != 'q')
    {
        if (playing)
        {
            Direction dir_temp = get_dir(c);
            if (dir_temp.name != BAD_DIR &&
                dir_temp.name != BAD_DIR)
            {
                dir = dir_temp;
            }
            if (!update(snake, dir, &food))
            {
                playing = FALSE;
            }
        }
        else
        {
            clear();
            mvprintw(GRID_HEIGHT/2-2, GRID_WIDTH/2-4, "GAME OVER");
            refresh();
        }
        sleep_timer(dir);
    }

    endwin();
    destroy_snake(snake);
    return 0;
}

int update(Snake *snake, Direction dir, Point **food)
{
    clear();
    update_snake(snake, dir, *(*food));
    if (check_collision(snake, food))
    {
        mvprintw(0, 0, "GAME OVER");
        return 0;
    }
    draw_food(*(*food));
    draw_snake(snake);
    refresh();
    return 1;
}

void draw_snake(Snake *snake)
{
    for (int i = 0; i < snake_size(snake); i++)
    {
        Point *p = get_part(snake, i);
        mvprintw(p->y, p->x, "#");
    }
}

void draw_food(Point food)
{
    mvprintw(food.y, food.x, "@");
}

Direction get_dir(int dir)
{
    switch (dir)
    {
        case DIR_UP:
            return (Direction){{0, -1}, DIR_UP};
        case DIR_DOWN:
            return (Direction){{0, 1}, DIR_DOWN};
        case DIR_LEFT:
            return (Direction){{-1, 0}, DIR_LEFT};
        case DIR_RIGHT:
            return (Direction){{1, 0}, DIR_RIGHT};
        default:
            return (Direction){{0, 0}, BAD_DIR};
    }
}

void sleep_timer(Direction dir)
{
    if (dir.name == DIR_UP || dir.name == DIR_DOWN)
    {
        usleep(CLOCK_SPEED_V);
    }
    else if (dir.name == DIR_LEFT || dir.name == DIR_RIGHT)
    {
        usleep(CLOCK_SPEED_H);
    }
}

Point *get_random_food()
{
    srandom(clock());
    Point *food = malloc(sizeof(Point));
    food->x = (random()/(float)RAND_MAX)*GRID_WIDTH;
    food->y = (random()/(float)RAND_MAX)*GRID_HEIGHT;
    return food;
}

int check_collision(Snake *snake, Point **food)
{
    Point *head = get_head(snake);
    // Snake-food collision
    if (head->x == (*food)->x && head->y == (*food)->y)
    {
        Point *part = malloc(sizeof(Point));
        part->x = head->x;
        part->y = head->y;
        add_part(snake, part);
        *food = get_random_food();
    }
    // Snake-wall collision
    else if (head->x < 0 || head->x > GRID_WIDTH-1 ||
        head->y < 0 || head->y > GRID_HEIGHT-1)
    {
        return TRUE;
    }
    // Snake-snake collision
    else
    {
        for (int i = 1; i < snake_size(snake); i++)
        {
            Point *part = get_part(snake, i);
            if (head->x == part->x && head->y == part->y)
            {
                return TRUE;
            }
        }
    }
    return FALSE;
}
