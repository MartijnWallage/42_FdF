# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 15:31:16 by mwallage          #+#    #+#              #
#    Updated: 2023/08/25 13:39:49 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
UNAME	:= $(shell uname)
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
MLX_DIR	:= ./lib/MLX42
LIBFT	:= ./lib/libft
HEADERS	:= -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc
LIBS	:= -L$(LIBFT) -lft $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
SRCDIR	:= src
SRC		:= fdf_main.c \
			fdf_draw.c \
			fdf_error.c \
			fdf_parse.c \
			fdf_utils.c \
			fdf_project.c \
			fdf_hooks.c
SRCS	:= $(addprefix $(SRCDIR)/, $(SRC))
OBJ		:= ${SRCS:.c=.o}
NAME	:= fdf

all: libmlx libft $(NAME)

libmlx:
	@if [ -d ${MLX_DIR} ]; then git -C ${MLX_DIR} pull; \
    else git clone git@github.com:codam-coding-college/MLX42.git ${MLX_DIR}; fi
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

libft:
	make -C$(LIBFT)

$(NAME): $(OBJ)
	$(CC) -g $(OBJ) $(LIBS) $(HEADERS) -o $@

%.o: %.c
	$(CC) -g $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -rf $(OBJ)
	rm -rf $(MLX_DIR)/build
	make clean -C$(LIBFT)

fclean: clean
	rm -rf $(NAME)
	make fclean -C$(LIBFT)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
