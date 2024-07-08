#### -- VARIABLES -- ####
SRC = mlx_shaders.c mlx_new_window.m mlx_init_loop.m mlx_new_image.m mlx_xpm.c mlx_int_str_to_wordtab.c
OBJS = $(SRC:.c=.o)
OBJS := $(OBJS:.m=.o)
NAME = libmlx.a
CFLAGS+=-O2

#### -- RULES -- ####
all: $(NAME)

$(NAME): $(OBJS)
	@ar -r $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJS)
	@rm -f mlx_app
fclean: clean
	@rm -r $(NAME)

re: fclean all
