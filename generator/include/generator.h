/*
** EPITECH PROJECT, 2020
** generator.h
** File description:
** generator.h
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct maze_cell {
    int left_wall;
    int right_wall;
    int up_wall;
    int down_wall;
    int path_id;
    struct maze_cell *next_cell;
};

struct utils {
    int x;
    int y;
    int n_cell;
    int maze_width;
    int maze_heigth;
    int buffer_width;
    int *first_line_buffer;
    int *second_line_buffer;
    int *third_line_buffer;
};

int wall_to_stdout(int wall);
int buffer_to_stdout(int *buffer, int size);
int write_maze(struct utils *util, struct maze_cell *cells);
void cell_grid(struct utils *util, struct maze_cell *cells);
int perfect_maze(struct utils *util, struct maze_cell *cells);
void merge_list(struct maze_cell *adjacent_cell,
        struct maze_cell *before_adjacent_cell, struct maze_cell *random_cell);
int my_getnbr(char const *str);
int my_strcmp (const char *s1, const char *s2);
int my_putchar(char c);
char my_putstr(char *str);