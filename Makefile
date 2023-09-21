# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/10 15:31:16 by mwallage          #+#    #+#              #
#    Updated: 2023/09/21 15:54:50 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		:= cc
CFLAGS	:= -Wall -Wextra -Werror -Wunreachable-code -Ofast
MLX_DIR	:= ./lib/MLX42
LIBFT	:= ./lib/libft
HEADERS	:= -I ./inc -I $(LIBMLX)/include -I $(LIBFT)/inc
UNAME_S	:= $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	LIBS	:= -L$(LIBFT) -lft $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm
endif
ifeq ($(UNAME_S),Darwin)
	LIBS	:= -L$(LIBFT) -lft $(MLX_DIR)/build/libmlx42.a -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/" -pthread -lm
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

${MLX_DIR}:
		git clone https://github.com/codam-coding-college/MLX42.git ${MLX_DIR};
		cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C$(MLX_DIR)/build -j4;

${LIBFT}:
		git clone https://github.com/MartijnWallage/42_libft.git ${LIBFT};
		make -C$(LIBFT);

$(NAME): $(MLX_DIR) $(LIBFT) $(OBJ)
	$(CC) -g $(OBJ) $(LIBS) $(HEADERS) -o $@

%.o: %.c inc/fdf.h
	$(CC) -g $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -rf $(OBJ)
	make clean -C$(LIBFT)

fclean: clean
	rm -rf $(NAME)
	make fclean -C$(LIBFT)
	rm -rf $(LIBFT) $(MLX_DIR)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, libft
