# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmei <rmei@student.42berlin.de>             +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/25 20:57:11 by rmei              #+#    #+#              #
#    Updated: 2024/08/09 20:29:38 by rmei             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### -- VARIABLES -- ####
SRC = main.c \
		draw.c mlx_events.c transform.c utils.c vectors.c
SRC := $(addprefix src/, $(SRC))
OBJS = $(SRC:%.c=%.o)
LIBFT = lib/libft
MINILIBX = lib/minilibx
NAME = fdf

CPPFLAGS = -I./include
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
