# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 15:31:16 by mwallage          #+#    #+#              #
#    Updated: 2023/08/22 15:12:24 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler targets and libraries
CC		:= CC
UNAME	:= $(shell uname)
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
NAME	:= fdf
LIBFT	:= libft.a
MLX42	:= libmlx42.a

# Directories
SRC_DIR		:= ./src
MLX_DIR		:= ./lib/MLX42
LIBFT_TDIR	:= ./lib/libft
LIBS		:= -L$(LIBFT_DIR) -lft $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

SRC		:= fdf_main.c
SRCS	:= $(addprefix $(SRCDIR), $(SRC))
OBJ		:= ${SRCS:.c=.o}
HEADERS	:= -I ./inc -I $(MLX_DIR)/include -I $(LIBFT_DIR)/inc

all: libmlx libft $(NAME)

libmlx:
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

libft:
	make -C$(LIBFT_DIR)

%.o: %.c
	$(CC) -g $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJ)
	$(CC) -g $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)

clean:
	rm -rf $(OBJ)
	rm -rf $(MLX_DIR)/build
	make clean -C$(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	make fclean -C$(LIBFT_DIR)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
