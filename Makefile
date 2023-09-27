# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 15:31:16 by mwallage          #+#    #+#              #
#    Updated: 2023/09/27 13:26:33 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
MLX_DIR		:= ./lib/MLX42
MLX		:= $(MLX_DIR)/build/libmlx42.a
LIBFT_DIR	:= ./lib/libft
LIBFT 	:= $(LIBFT_DIR)/libft.a
HEADERS	:= -I ./inc -I $(LIBMLX)/include -I $(LIBFT_DIR)/inc
UNAME_S	:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS	:= -L$(LIBFT_DIR) -lft $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBS	:= -L$(LIBFT_DIR) -lft $(MLX_DIR)/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -pthread -lm
endif
SRCDIR	:= src
SRC		:= fdf_main.c \
			fdf_draw.c \
			fdf_error.c \
			fdf_parse.c \
			fdf_utils.c \
			fdf_hooks.c \
			fdf_color.c \
			fdf_rotate.c
SRCS	:= $(addprefix $(SRCDIR)/, $(SRC))
OBJ		:= ${SRCS:.c=.o}
NAME	:= fdf

all: $(NAME)

$(MLX): $(MLX_DIR)
	cmake $(MLX_DIR) -B $(MLX_DIR)/build;
	make -C$(MLX_DIR)/build -j4;

$(LIBFT): $(LIBFT_DIR)
	make -C$(LIBFT_DIR);

$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $@;

$(LIBFT_DIR):
	git clone https://github.com/MartijnWallage/42_libft.git $@;

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) -g $(OBJ) $(LIBS) $(HEADERS) -o $@

%.o: %.c inc/fdf.h
	$(CC) -g $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -rf $(OBJ)
	make clean -C$(LIBFT_DIR)

fclean: clean
	rm $(NAME)
	rm -rf $(LIBFT_DIR)
	rm -rf $(MLX_DIR)

re: clean all

.PHONY: all, clean, fclean, re
