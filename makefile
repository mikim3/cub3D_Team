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

INC			= include
SRCS_DIR	= srcs
SRCS		=			\
		main.c			\
		map.c			\
		player.c		\
		key.c			\
		render_master.c	\
		ray.c

OBJS_DIR	= objs
OBJS		= $(addprefix $(OBJS_DIR)/, $(SRCS:.c=.o))

MLX_DIR		= mlx
MLX			= libmlx.a
LIBFT_DIR	= libft
LIBFT		= libft.a
LIBS		= -L $(MLX_DIR) -l mlx -L $(LIBFT_DIR) -l ft

CFLAGS		= -Wall -Wextra -Werror
IFLAGS		= -I $(INC) -I $(MLX_DIR) -I $(LIBFT_DIR)/$(INC)
APIFLAGE	= -framework OpenGL -framework Appkit

.PHONY		:	all clean fclean re bonus

all			:	$(NAME)

$(NAME)		:	$(OBJS_DIR) $(OBJS) $(MLX) $(LIBFT)
		$(CC) $(LIBS) $(APIFLAGE) -o $(NAME) $(OBJS)

$(OBJS_DIR)	:
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(MLX):
	make -C $(MLX_DIR)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean		:
		rm -rf $(OBJS_DIR)
		make clean -C $(MLX_DIR)
		make clean -C $(LIBFT_DIR)

fclean		:	clean
		rm -f $(NAME)
		make fclean -C $(LIBFT_DIR)

re			:	fclean all
