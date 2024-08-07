# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmei <rmei@student.42berlin.de>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 20:57:11 by rmei              #+#    #+#              #
#    Updated: 2024/08/07 20:16:06 by rmei             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### -- VARIABLES -- ####
SRC = draw.c hooks.c main.c utils.c vectors.c
SRC := $(addprefix src/, $(SRC))
OBJS = $(SRC:%.c=%.o)
LIBFT = include/libft
MINILIBX = include/minilibx
NAME = fdf

CPPFLAGS = -I./include -I./$(LIBFT) -I./$(MINILIBX)
CFLAGS = -Wall -Werror -Wextra -g 
LDFLAGS = -lm -L./$(LIBFT) -lft -L./$(MINILIBX) -lmlx -framework OpenGL -framework AppKit

#### -- RULES -- ####
all: $(NAME)

$(NAME): $(OBJS)
	make -sC $(LIBFT)
	make -sC $(MINILIBX)
	cc $^ $(LDFLAGS) -o $@

%.o: %.c
	cc $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	make clean -sC $(LIBFT)
	make clean -sC $(MINILIBX)
	rm -f $(OBJS)

fclean: 
	make fclean -sC $(LIBFT)
	make fclean -sC $(MINILIBX)
	rm -f $(OBJS) $(NAME)

re: fclean all

.PHONY: all clean fclean re
