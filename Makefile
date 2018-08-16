# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abaille <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/01/25 00:22:44 by abaille           #+#    #+#              #
#    Updated: 2018/06/25 19:14:37 by abaille          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT =	./libft
MLX =	./minilibx
FRK =	-framework
OPEN =	OpenGL
APPK =	AppKit
SRCS =	fractol.c	\
		keycode.c	\
		mousecode.c \
		fractales.c	\
		lyapunov.c	\
		draw.c		\
		color.c		\
		checkerrors.c
OBJS = ${SRCS:.c=.o}

.PHONY:clean fclean

all: $(NAME)

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJS)
	make -C $(LIBFT)
	make -C $(MLX)
	$(CC) $(CFLAGS) -o $@ $(OBJS) -L$(LIBFT) -lft -L$(MLX) -lmlx $(FRK) $(OPEN) $(FRK) $(APPK)

clean:
	make -C $(LIBFT) clean
	make -C $(MLX) clean
	rm -f $(OBJS)

fclean:clean
	make -C $(LIBFT) fclean
	rm -f $(NAME)

lldb:
	$(CC) -g $(SRCS) ./libft/*.c -I ./libft/ -I ./ -L$(MLX) -lmlx $(FRK) $(OPEN) $(FRK) $(APPK) -o fdf

re:fclean all
