##
## EPITECH PROJECT, 2020
## Makefile
## File description:
## Makefile
##

SRC	=	*.c

OBJ	=	*.o

NAME=	solver

all:	build clean

build:
		gcc -c lib/my/$(SRC)
		ar rc libmy.a $(OBJ)
		gcc -O src/$(SRC) libmy.a -lm -o $(NAME)

clean:
		rm $(OBJ)

re: clean build
