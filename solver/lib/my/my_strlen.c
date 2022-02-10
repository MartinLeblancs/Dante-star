/*
** EPITECH PROJECT, 2020
** my_strlen.c
** File description:
** my_strlen
*/

int  my_strlen(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;

    while (str[i] != '\0')
    {
        count++;
        i++;
    }

    return (count);
}



