# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim3 <mikim3@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 20:01:35 by mikim3            #+#    #+#              #
#    Updated: 2023/03/03 10:13:08 by mikim3           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

SRCS		= main.c \
			map.c \
			player.c \
			key.c \
			render_master.c \
			ray.c

OBJS		= $(SRCS:%.c=%.o)
LIBC		= ar rcs
FLAGS		= -Wall -Wextra -Werror

all			:	$(NAME)

$(NAME)		:	$(OBJS)
		cc -o $(NAME) $(OBJS) -L./mlx -lmlx -framework OpenGL -framework AppKit

%.o			:	%.c
		cc $(FLAGS) -c $^ -I./ -o $@

clean		:
		rm -f $(OBJS)

fclean		:	clean
		rm -f $(NAME)

re			:	fclean all

.PHONY		:	all clean fclean re bonus
