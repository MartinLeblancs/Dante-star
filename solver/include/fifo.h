/*
** EPITECH PROJECT, 2021
** fifo.h
** File description:
** fifo.h
*/

#ifndef FIFO_H
#define FIFO_H

struct path {
    struct path *previous;
    int from_cell;
    int x;
    int y;
};

struct fifo_cell {
    struct path *current;
    struct fifo_cell *next;
};

struct path *pop_fifo(struct fifo_cell **start, struct fifo_cell **end);
void append_fifo(struct fifo_cell **start,
        struct fifo_cell **end, struct path *new_cell_path);
void my_putchar(char c);

#endif