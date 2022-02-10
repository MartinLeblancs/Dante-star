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
#include <time.h>
#include "../include/generator.h"

int wall_to_stdout(int wall) {
    if (wall == 1) {
        my_putchar('X');
    } else if (wall == 0) {
        my_putchar('*');
    } else {
        write(2, "Error: wall type %d doesn't exist\n", 35);
        return(84);
    }
}

int buffer_to_stdout(int *buffer, int size) {
    for (int k = 0; k < size; k++) {
        if (wall_to_stdout(buffer[k]) == 84)
            return (84);
    }
    my_putchar('\n');
}

int main(int ac, char **av) {
    if (ac != 3 && ac != 4)
        return (84);
    time_t t;
    srand((unsigned) time(&t));
    if (ac == 4 && my_strcmp("perfect", av[3]) != 0
    && my_strcmp("imperfect", av[3]))
        return (84);
    struct utils *util = malloc(sizeof(struct utils));
    util->x = my_getnbr(av[1]);
    util->y = my_getnbr(av[2]);
    if (util->x <= 2 || util->y <= 2)
        return (84);
    util->maze_width = (util->x - 1) / 2;
    util->maze_heigth = (util->y - 1) / 2;
    util->n_cell = util->maze_heigth * util->maze_width;
    struct maze_cell *cells = malloc(sizeof(struct maze_cell) * util->n_cell);
    cell_grid(util, cells);
    cells[0].up_wall = 0;
    cells[util->n_cell - 1].down_wall = 0;
    if (perfect_maze(util, cells) == 84)
        return (84);
    if (write_maze(util, cells) == 84)
        return (84);

    free(util->first_line_buffer);
    free(util->second_line_buffer);
    free(util->third_line_buffer);
    free(cells);

    return 0;
}
