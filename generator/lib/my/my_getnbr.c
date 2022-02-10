/*
** EPITECH PROJECT, 2020
** my_getnbr
** File description:
** getnbr
*/

#include <stddef.h>

int my_getnbr(char const *str)
{
    int nb = 0;
    int neg = 1;
    int i = 0;


    while (str[i] == '+' || str[i] == '-')
    {
        if (str[i] == '-')
            neg = neg * -1;
        i++;
    }
    while (str[i] != '\0')
    {
        if (str[i] >= '0' && str[i] <= '9') {
            nb = nb * 10;
            nb = nb + str[i] - '0';
            i++;
        } else
            return (nb * neg);
    }
    return (nb * neg);
}
