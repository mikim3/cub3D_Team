# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mikim3 <mikim3@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/10 20:01:35 by mikim3            #+#    #+#              #
#    Updated: 2023/03/31 15:28:56 by mikim3           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

INC			= include
SRCS_DIR	= srcs
SRCS		=			\
		main.c			\
		check_map.c		\
		key.c			\
		map.c			\
		parsing.c		\
		player.c		\
		ray.c			\
		read.c			\
		render_master.c	\
		render_wall.c	\
		parsing_utils.c	\
		utils.c			\
		cal_ray.c		\
		ray_util.c		\
		draw_background.c


OBJS_DIR	= objs
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

MLX_DIR		= mlx
MLX			= libmlx.a
LIBFT_DIR	= libft
LIBFT		= libft.a
LIBS		= -L $(MLX_DIR) -l mlx -L $(LIBFT_DIR) -l ft

CFLAGS		= -Wall -Wextra -Werror -g3
IFLAGS		= -I $(INC) -I $(MLX_DIR) -I $(LIBFT_DIR)/$(INC)
APIFLAGE	= -framework OpenGL -framework Appkit

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(OBJS_DIR) $(OBJS) $(MLX_DIR)/$(MLX) $(LIBFT_DIR)/$(LIBFT)
		$(CC) $(LIBS) $(APIFLAGE) -o $(NAME) $(OBJS)

$(OBJS_DIR)	:
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(MLX_DIR)/$(MLX):
	make -C $(MLX_DIR)

$(LIBFT_DIR)/$(LIBFT):
	make -C $(LIBFT_DIR)

clean		:
		rm -rf $(OBJS_DIR)
		make clean -C $(MLX_DIR)
		make clean -C $(LIBFT_DIR)

fclean		:	clean
		rm -f $(NAME)
		make fclean -C $(LIBFT_DIR)

re			:	fclean all
