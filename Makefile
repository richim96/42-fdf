# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmei <rmei@student.42berlin.de>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 20:57:11 by rmei              #+#    #+#              #
#    Updated: 2024/07/10 14:32:15 by rmei             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### -- VARIABLES -- ####
SRC = draw.c hooks.c main.c matrix.c utils.c
OBJS = $(SRC:%.c=%.o)
NAME = fdf

CPPFLAGS = -I./libft -I./minilibx/
CFLAGS = -Wall -Werror -Wextra 
LDFLAGS = -lm -L./libft -lft -L./minilibx/ -lmlx -framework OpenGL -framework AppKit

#### -- RULES -- ####
all: $(NAME)

$(NAME): $(OBJS)
	make -sC libft
	make -sC minilibx
	cc $^ $(LDFLAGS) -o $@

%.o: %.c
	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	make clean -sC libft
	make clean -sC minilibx
	rm -f $(OBJS)

fclean: 
	make fclean -sC libft
	make fclean -sC minilibx
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
