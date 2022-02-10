/*
** EPITECH PROJECT, 2021
** my_strcmp
** File description:
** my_strcmp
*/

int my_strcmp (const char *s1, const char *s2)
{
    int i = 0;

    while ((s1[i] == s2[i]) && (s1[i] != '\0'))
        i++;
    return (s1[i] - s2[i]);
}