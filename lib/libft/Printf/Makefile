# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwallage <mwallage@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/25 13:18:50 by mwallage          #+#    #+#              #
#    Updated: 2023/05/30 18:49:48 by mwallage         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			:= cc
AR			:= ar
CFLAGS		:= -Wall -Wextra -Werror
SRCDIR		:= src
OBJDIR		:= obj
INCDIR		:= inc
SRCS		:= $(SRCDIR)/conversions.c $(SRCDIR)/conversions_hex.c \
				$(SRCDIR)/conversion_utils.c $(SRCDIR)/ft_printf.c \
				$(SRCDIR)/put_conversions.c $(SRCDIR)/read_modifiers.c \
				$(SRCDIR)/utils.c
OBJS		:= $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
NAME 		:= libftprintf.a

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJS)
	$(AR) rcs $@ $(OBJS)

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: all
	
clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all bonus clean fclean re
