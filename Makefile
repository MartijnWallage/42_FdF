# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 15:31:16 by mwallage          #+#    #+#              #
#    Updated: 2023/08/24 15:57:56 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
LIBMLX	:= ./lib/MLX42
LIBFT	:= ./lib/libft
HEADERS	:= -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc
LIBS	:= -L$(LIBFT) -lft $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= src
SRC		:= fdf_main.c \
			fdf_draw.c \
			fdf_error.c \
			fdf_parse.c \
			fdf_utils.c \
			fdf_rotate.c \
			fdf_hooks.c
SRCS	:= $(addprefix $(SRCDIR)/, $(SRC))
OBJ		:= ${SRCS:.c=.o}

all: libmlx libft $(NAME)

libmlx:
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

libft:
	make -C$(LIBFT)

$(NAME): $(OBJ)
	$(CC) -g $(OBJ) $(LIBS) $(HEADERS) -o $@

%.o: %.c
	$(CC) -g $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -rf $(OBJ)
	rm -rf $(LIBMLX)/build
	make clean -C$(LIBFT)

fclean: clean
	rm -rf $(NAME)
	make fclean -C$(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
