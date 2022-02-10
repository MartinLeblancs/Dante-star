/*
** EPITECH PROJECT, 2021
** write_maze
** File description:
** write_maze
*/

#include "../include/generator.h"

int write_maze(struct utils *util, struct maze_cell *cells)
{
    util->buffer_width = util->x;
    util->first_line_buffer = malloc(util->buffer_width * sizeof(int));
    util->second_line_buffer = malloc(util->buffer_width * sizeof(int));
    util->third_line_buffer = malloc(util->buffer_width * sizeof(int));
    for (int k = 0; k < util->buffer_width; k++) {
        util->first_line_buffer[k] = 1;
        util->second_line_buffer[k] = 1;
        util->third_line_buffer[k] = 1;
    }

    for (int line = 0; line < util->maze_heigth; line++) {
        for (int column = 0; column < util->maze_width; column++) {
            int cell_id = line * util->maze_width + column;
            struct maze_cell *current_cell = cells + cell_id;

            if (line == 0) {
                util->first_line_buffer[2 * column] = 1;
                util->first_line_buffer[2 * column + 1] = current_cell->up_wall;
                if (column == (util->maze_width - 1)) {
                    util->first_line_buffer[2 * column + 2] = 1;
                }
            }

            if (column == 0) {
                util->second_line_buffer[0] = current_cell->left_wall;
                util->third_line_buffer[0] = 1;
            }

            util->second_line_buffer[2 * column + 1] = 0;
            util->second_line_buffer[2 * column + 2] = current_cell->right_wall;
            util->third_line_buffer[2 * column + 1] = current_cell->down_wall;
            util->third_line_buffer[2 * column + 2] = 1;
        }
        if (line == 0) {
            util->first_line_buffer[0] = 0;
        } else if (line == util->maze_heigth - 1) {
            util->third_line_buffer[2 * util->maze_width] = 0;
            if (util->x % 2 != 1) {
                util->third_line_buffer[util->buffer_width - 1] = 0;
            }
        }

        if (line == 0) {
            if (buffer_to_stdout(util->first_line_buffer, util->buffer_width) == 84)
                return (84);
        }
        if (buffer_to_stdout(util->second_line_buffer, util->buffer_width) == 84)
            return (84);
        if (buffer_to_stdout(util->third_line_buffer, util->buffer_width) == 84)
            return (84);
    }

    if (util->y % 2 != 1) {
        for (int k = 0; k < util->buffer_width - 1; k++) {
            util->third_line_buffer[k] = 1;
        }
        util->third_line_buffer[util->buffer_width - 1] = 0;
        if (buffer_to_stdout(util->third_line_buffer, util->buffer_width) == 84)
            return (84);
    }
}

void merge_list(struct maze_cell *adjacent_cell,
                struct maze_cell *before_adjacent_cell,
                struct maze_cell *random_cell)
{
    while (true) {
        before_adjacent_cell->path_id = random_cell->path_id;
        if (before_adjacent_cell->next_cell == adjacent_cell) {
            before_adjacent_cell->next_cell = random_cell->next_cell;
            break;
        }
        before_adjacent_cell = before_adjacent_cell->next_cell;
    }
}