# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rmei <rmei@student.42berlin.de>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/23 12:10:35 by rmei              #+#    #+#              #
#    Updated: 2024/07/01 15:07:37 by rmei             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#### -- VARIABLES -- ####
SRC = atoi bzero calloc get_next_line haschar isalnum isalpha isascii isdigit \
	isprint itoa lstnew lstadd_back lstadd_front lstclear lstdelone lstiter lstlast \
	lstmap lstsize memchr memcmp memcpy memmove memset printf putchar_fd putendl_fd \
	putnbr_fd putnbr_base_fd putstr_fd realloc split substr strchr strdup striteri \
	strjoin strlcat strlcpy strlen strmapi strncmp strnstr strrchr strtrim tolower \
	toupper
SRC := $(addsuffix .c, $(addprefix ft_, ${SRC}))

OBJS = ${SRC:%.c=%.o}

NAME = libft.a

CPPFLAGS = -I.
CFLAGS = -Wall -Wextra -Werror

#### -- RULES -- ####
all: ${NAME}

${NAME}: ${OBJS}
	@ar -rcs $@ $^

%.o: %.c
	@cc ${CPPFLAGS} ${CFLAGS} -c -o $@ $<

clean:
	@rm -f ${OBJS}

fclean: clean
	@rm -f ${NAME}

re: fclean all
