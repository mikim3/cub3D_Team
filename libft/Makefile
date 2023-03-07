# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: soylee <soylee@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 17:50:51 by soylee            #+#    #+#              #
#    Updated: 2022/11/01 17:42:00 by soylee           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
IFLAGS = -I include

SRC1 = ft_isalpha.c	\
	   ft_isdigit.c	\
	   ft_isalnum.c	\
	   ft_isascii.c	\
	   ft_isprint.c	\
	   ft_strlen.c	\
	   ft_memset.c	\
	   ft_bzero.c	\
	   ft_memcpy.c	\
	   ft_memmove.c	\
	   ft_strlcpy.c	\
	   ft_strlcat.c	\
	   ft_toupper.c	\
	   ft_tolower.c	\
	   ft_strchr.c	\
	   ft_strrchr.c	\
	   ft_strncmp.c	\
	   ft_memchr.c	\
	   ft_memcmp.c	\
	   ft_strnstr.c	\
	   ft_atoi.c	\
	   ft_calloc.c	\
	   ft_strdup.c	

SRC2 = ft_substr.c	\
	   ft_strjoin.c	\
	   ft_strtrim.c	\
	   ft_split.c	\
	   ft_itoa.c	\
	   ft_strmapi.c	\
	   ft_striteri.c	\
	   ft_putchar_fd.c	\
	   ft_putstr_fd.c	\
	   ft_putendl_fd.c	\
	   ft_putnbr_fd.c

GNL = get_next_line.c

BONUS = ft_lstnew.c	\
		ft_lstadd_front.c	\
		ft_lstsize.c	\
		ft_lstlast.c	\
		ft_lstadd_back.c	\
		ft_lstdelone.c	\
		ft_lstclear.c	\
		ft_lstiter.c	\
		ft_lstmap.c		

SRC_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR), $(SRC1) $(SRC2))
BONUS_S = $(addprefix $(SRC_DIR), $(BONUS))

OBJ_DIR = ./objs/
GNL_O = $(addprefix $(OBJ_DIR), $(GNL:.c=.o))
OBJS = $(addprefix $(OBJ_DIR), $(SRC1:.c=.o) $(SRC2:.c=.o))
BONUS_O = $(addprefix $(OBJ_DIR), $(BONUS:.c=.o))

.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(GNL_O)
	ar rsu $(NAME) $(OBJS) $(GNL_O)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(IFLAGS) $(CFLAGS) -c $< -o $@

$(GNL_O): $(SRC_DIR)$(GNL)
	$(CC) $(IFLAGS) $(CLFAGES) -c $< -o $@ -D BUFFER_SIZE=42

bonus: $(NAME) $(BONUS_O)
	ar rsuv $(NAME) $(BONUS_O)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
