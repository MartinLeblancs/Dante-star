/*
** EPITECH PROJECT, 2020
** my_put_nbr
** File description:
** my_put_nbr
*/

#include <unistd.h>

int my_putchar(char c);

int my_put_nbr(int nb) {
    int division = 1;

    if (nb == -2147483648) {
        write(1, "-2147483648", 11);
        my_putchar('\n');
        return (0);
    }
    if (nb < 0) {
        my_putchar('-');
        nb = nb * (-1);
    }
    while (nb / division >= 10) {
        division = division * 10;
    }
    while (division > 0) {
        my_putchar(((nb / division) % 10) + 48);
        division = division / 10;
    }
    return (0);
}
