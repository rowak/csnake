#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include "csnake.h"

/*
 * Program Name: csnake.c
 * Author: Ethan Rowan
 * Created: 12/05/20
 * Modified: 13/05/20
 * Compilation: make csnake
 * Execution: ./csnake
 */

int main(int argc, char *argv[])
{
    Point HEAD_ORIGIN = {GRID_WIDTH/2, GRID_HEIGHT/2};
    Snake *snake = create_snake(HEAD_ORIGIN);
    Point *food = get_random_food();
    Direction dir = get_dir(DIR_RIGHT);
    int playing = TRUE;

    // Initialize curses in "game mode"
    initscr();
    keypad(stdscr, TRUE);
    curs_set(FALSE);
    noecho();
    nodelay(stdscr, TRUE);

    int c;
    while ((c = getch()) != EXIT_KEY)
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
            draw_gameover(snake_size(snake)-1);
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
    update_snake(snake, dir, **food);
    if (check_snake_wall_collision(snake) ||
        check_snake_snake_collision(snake))
    {
        return 0;
    }
    if (check_snake_food_collision(snake, **food))
    {
        reset_food(snake, food);
    }
    draw_food(**food);
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

void draw_gameover(int score)
{
    clear();
    mvprintw(GRID_HEIGHT/2-2, GRID_WIDTH/2-4, "GAME OVER");
    // x position of score, adjusted based on width of text
    int score_x = (GRID_WIDTH/2)-(num_digits(score)/2)-3;
    mvprintw(GRID_HEIGHT/2-1, score_x, "score: %d", score);
}

int num_digits(int x)
{
    if (x == 0)
    {
        return 1;
    }
    int digits = 0;
    while (x > 0)
    {
        x /= 10;
        digits++;
    }
    return digits;
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

void reset_food(Snake *snake, Point **food)
{
    Point *head = get_head(snake);
    Point *part = malloc(sizeof(Point));
    part->x = head->x;
    part->y = head->y;
    add_part(snake, part);
    free(*food);
    *food = get_random_food();
}

int check_snake_food_collision(Snake *snake, Point food)
{
    Point *head = get_head(snake);
    if (head->x == food.x && head->y == food.y)
    {
        return TRUE;
    }
    return FALSE;
}

int check_snake_wall_collision(Snake *snake)
{
    Point *head = get_head(snake);
    if (head->x < 0 || head->x > GRID_WIDTH-1 ||
        head->y < 0 || head->y > GRID_HEIGHT-1)
    {
        return TRUE;
    }
    return FALSE;
}

int check_snake_snake_collision(Snake *snake)
{
    Point *head = get_head(snake);
    for (int i = 1; i < snake_size(snake); i++)
    {
        Point *part = get_part(snake, i);
        if (head->x == part->x && head->y == part->y)
        {
            return TRUE;
        }
    }
    return FALSE;
}
