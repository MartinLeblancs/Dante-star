/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../include/fifo.h"

struct utils {
    int maze_heigth;
    int maze_width;
    int n_ascii;
    FILE *maze_file;
    int **maze;
};

void test_char(struct utils *util, char current_char)
{
    while ((current_char = fgetc(util->maze_file)) != EOF) {
        if (current_char == '\n') {
            util->maze[util->n_ascii / util->maze_width] = malloc(util->maze_width * sizeof(int));
            continue;
        } else if (current_char == '*') {
            util->maze[util->n_ascii / util->maze_width][util->n_ascii % util->maze_width] = 0;
        } else if (current_char == 'X') {
            util->maze[util->n_ascii / util->maze_width][util->n_ascii % util->maze_width] = 1;
        } else {
            write(2, "Incorrect char encountered\n", 27);
        }
        util->n_ascii++;
    }
}

void modify_maze(struct utils *util, struct path *current_path)
{
    while (true) {
        util->maze[current_path->y][current_path->x] = 2;
        if (current_path->previous == NULL) {
            break;
        } else {
            current_path = current_path->previous;
        }
    }
}

void print_maze(struct utils *util)
{
    for (int line = 0; line < util->maze_heigth; line++) {
        for (int column = 0; column < util->maze_width; column++) {
            if (util->maze[line][column] == 0) {
                my_putchar('*');
            } else if (util->maze[line][column] == 1) {
                my_putchar('X');
            } else if (util->maze[line][column] == 2) {
                my_putchar('o');
            } else {
                write(2, "Error: unknown ascii encountered in the maze\n",
                46);
            }
        }
        my_putchar('\n');
    }
}

int main(int argc, char **argv) {
    if (argc != 2)
        return (84);

    struct utils *util = malloc(sizeof(struct utils *));
    util->maze_file = fopen(argv[1], "r");

    if (util->maze_file == NULL) {
        write(2, "Could not open the file\n", 25);
        return (84);
    }

    char current_char;
    fpos_t maze_file_begin;
    fgetpos(util->maze_file, &maze_file_begin);
    util->maze_heigth = 0;
    util->n_ascii = 0;

    while ((current_char = fgetc(util->maze_file)) != EOF) {
        if (current_char == '\n') {
            util->maze_heigth++;
        } else {
            util->n_ascii++;
        }
    }
    util->maze_width = util->n_ascii / util->maze_heigth;

    if (util->n_ascii % util->maze_heigth != 0) {
        write(2, "Nombre d'ascii invalide\n", 25);
        exit(84);
    }

    fsetpos(util->maze_file, &maze_file_begin);

    util->maze = (int **) malloc(util->maze_heigth * sizeof(int *));
    util->maze[0] = malloc(util->maze_width * sizeof(int));

    util->n_ascii = 0;
    test_char(util, current_char);


    struct path *init_path = malloc(sizeof(struct path));
    init_path->previous = NULL;
    init_path->from_cell = 0;
    init_path->x = 0;
    init_path->y = 0;
    struct fifo_cell **fifo_begin = malloc(sizeof(struct fifo_cell *));
    struct fifo_cell **fifo_end = malloc(sizeof(struct fifo_cell *));
    append_fifo(fifo_begin, fifo_end, init_path);

    struct path *current_path;
    while (true) {
        current_path = pop_fifo(fifo_begin, fifo_end);
        int from_cell = current_path->from_cell;
        int current_x = current_path->x;
        int current_y = current_path->y;

        if (current_x == util->maze_width - 1 && current_y == util->maze_heigth - 1) {
            break;
        }

        if (from_cell != 0 && current_x != 0 &&
            util->maze[current_y][current_x - 1] == 0) {

            struct path *new_path_cell = malloc(sizeof(struct path));
            new_path_cell->previous = current_path;
            new_path_cell->from_cell = 1;
            new_path_cell->x = current_x - 1;
            new_path_cell->y = current_y;
            append_fifo(fifo_begin, fifo_end, new_path_cell);
        }
        if (from_cell != 1 && current_x != util->maze_width - 1 &&
            util->maze[current_y][current_x + 1] == 0) {
            struct path *new_path_cell = malloc(sizeof(struct path));
            new_path_cell->previous = current_path;
            new_path_cell->from_cell = 0;
            new_path_cell->x = current_x + 1;
            new_path_cell->y = current_y;
            append_fifo(fifo_begin, fifo_end, new_path_cell);
        }
        if (from_cell != 2 && current_y != 0 &&
            util->maze[current_y - 1][current_x] == 0) {
            struct path *new_path_cell = malloc(sizeof(struct path));
            new_path_cell->previous = current_path;
            new_path_cell->from_cell = 3;
            new_path_cell->x = current_x;
            new_path_cell->y = current_y - 1;
            append_fifo(fifo_begin, fifo_end, new_path_cell);
        }
        if (from_cell != 3 && current_y != util->maze_heigth - 1 &&
            util->maze[current_y + 1][current_x] == 0) {
            struct path *new_path_cell = malloc(sizeof(struct path));
            new_path_cell->previous = current_path;
            new_path_cell->from_cell = 2;
            new_path_cell->x = current_x;
            new_path_cell->y = current_y + 1;
            append_fifo(fifo_begin, fifo_end, new_path_cell);
        }

        if (fifo_begin == NULL) {
            write(2, "no solution found\n", 19);
            exit(84);
        }
    }

    modify_maze(util, current_path);
    print_maze(util);

    return 0;
}