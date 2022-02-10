/*
** EPITECH PROJECT, 2021
** fifo
** File description:
** fifo
*/

#include "../include/fifo.h"
#include <stdlib.h>

struct path *pop_fifo(struct fifo_cell **start, struct fifo_cell **end)
{
    struct fifo_cell *current_start = *start;
    struct path *result = current_start->current;
    if (current_start->next == NULL)
        *end = NULL;
    *start = current_start->next;
    free(current_start);

    return (result);
}

void append_fifo(struct fifo_cell **start,
        struct fifo_cell **end, struct path *new_cell_path)
{
    struct fifo_cell *new_cell = malloc(sizeof(struct fifo_cell));

    new_cell->current = new_cell_path;
    if (*end != NULL)
        (*end)->next = new_cell;
    *end = new_cell;
    if (*start == NULL)
        *start = new_cell;

    return;
}