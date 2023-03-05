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

SRCS		=			\
		main.c			\
		map.c			\
		player.c		\
		key.c			\
		render_master.c	\
		ray.c

OBJS_DIR	= objs
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

MLX			= mlx
CFLAGS		= -Wall -Wextra -Werror
LFLAGE 		= -L ./$(MLX) -l $(MLX)
APIFLAGE	= -framework OpenGL -framework Appkit

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(OBJS_DIR) $(OBJS)
		$(CC) $(LFLAGE) $(APIFLAGE) -o $(NAME) $(OBJS)

$(OBJS_DIR)	:
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(MLX):
	make -c $(MLX)

clean		:
		rm -rf $(OBJS_DIR)
		make clean -C $(MLX)

fclean		:	clean
		rm -f $(NAME)

re			:	fclean all
