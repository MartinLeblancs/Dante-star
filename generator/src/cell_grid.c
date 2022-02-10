/*
** EPITECH PROJECT, 2021
** main
** File description:
** main
*/

#include "../include/generator.h"

void cell_grid(struct utils *util, struct maze_cell *cells)
{
    for (int line = 0; line < util->maze_heigth; line++) {
        for (int column = 0; column < util->maze_width; column++) {
            int cell_id = line * util->maze_width + column;
            struct maze_cell *current_cell = cells + cell_id;

            current_cell->path_id = cell_id;
            current_cell->next_cell = current_cell;

            current_cell->left_wall = 1;
            current_cell->right_wall = 1;
            current_cell->up_wall = 1;
            current_cell->down_wall = 1;
        }
    }
}

int perfect_maze(struct utils *util, struct maze_cell *cells)
{
    int unique_paths = util->n_cell;
    int iterations = 0;

    while (true) {
        int random_cell_id = rand() % util->n_cell;
        struct maze_cell *random_cell = cells + random_cell_id;
        int random_wall_id = (rand() % 4);

        iterations++;
        if (iterations > 1000000) {
            write(2,
            "Too much iterations of "
            "our perfect maze algorithm\n", 51);
            break;
        }

        int *wall_random_cell;
        int *wall_adjacent_cell;
        struct maze_cell *adjacent_cell;
        if (random_wall_id == 0) {
            if (random_cell_id % util->maze_width == 0) {
                continue;
            }
            wall_random_cell = &random_cell->left_wall;
            adjacent_cell = random_cell - 1;
            wall_adjacent_cell = &adjacent_cell->right_wall;
        } else if (random_wall_id == 1) {
            if (random_cell_id % util->maze_width == util->maze_width - 1) {
                continue;
            }
            wall_random_cell = &random_cell->right_wall;
            adjacent_cell = random_cell + 1;
            wall_adjacent_cell = &adjacent_cell->left_wall;
        } else if (random_wall_id == 2) {
            if (random_cell_id < util->maze_width) {
                continue;
            }
            wall_random_cell = &random_cell->up_wall;
            adjacent_cell = random_cell - util->maze_width;
            wall_adjacent_cell = &adjacent_cell->down_wall;
        } else if (random_wall_id == 3) {
            if (random_cell_id / util->maze_width == util->maze_heigth - 1) {
                continue;
            }
            wall_random_cell = &random_cell->down_wall;
            adjacent_cell = random_cell + util->maze_width;
            wall_adjacent_cell = &adjacent_cell->up_wall;
        } else {
            write(2, "The wall id "
            "should be between 0 and 3 included\n", 48);
            return (84);
        }

        if (*wall_random_cell == 0) {
            continue;
        }
        if (adjacent_cell->path_id == random_cell->path_id) {
            continue;
        }
        *wall_adjacent_cell = 0;
        *wall_random_cell = 0;

        struct maze_cell *before_adjacent_cell = adjacent_cell;
        merge_list(adjacent_cell, before_adjacent_cell, random_cell);
        random_cell->next_cell = adjacent_cell;
        unique_paths--;

        if (unique_paths == 1) {
            break;
        }
    }
}