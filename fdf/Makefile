NAME			:= fdf
SRCS			:= fdf.c parsing.c fdf_drawing.c transformations.c bresenham.c free_data.c map_checker.c \
					hooks.c br_utils.c init.c get_dimensions.c rotations.c colour.c

OBJS			:= $(SRCS:.c=.o)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

DIR_LIBFT		:= libft/
DIR_SRCS		:= srcs/
DIR_OBJS		:= objs/
DIR_INC			:= includes/

SRCS_PFX		:= $(addprefix $(DIR_SRCS), $(SRCS))
OBJS_PFX		:= $(addprefix $(DIR_OBJS), $(OBJS))

OS := $(shell uname)
ifeq ($(OS),Linux)
LIBS			:= -L$(DIR_LIBFT) -L$(DIR_MLX) -lmlx -lX11 -lXext -lm -lz
DIR_MLX			:= minilibx_linux/
else
DIR_MLX			:= minilibx_macos/
LIBS			:= -L$(DIR_LIBFT) -L$(DIR_MLX) -lmlx -framework OpenGL -framework Appkit
endif

LIBFT_MLX		:= $(DIR_LIBFT)libft.a $(DIR_MLX)libmlx.a
INC				:= -I$(DIR_INC) -I$(DIR_LIBFT) -I$(DIR_MLX)

all: $(LIBFT_MLX) $(NAME)

$(NAME): $(OBJS_PFX) $(LIBFT_MLX)
	$(CC) $(CFLAGS) $(LIBS) $(LIBFT_MLX) $(OBJS_PFX) -o $@ $(INC)

$(DIR_OBJS):
	mkdir -p $@

${DIR_OBJS}%.o: $(DIR_SRCS)%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(LIBFT_MLX):
	make -C $(DIR_LIBFT)
	make -C $(DIR_MLX)

clean:
	make clean -C $(DIR_LIBFT)
	make clean -C $(DIR_MLX)
	rm -rf $(DIR_OBJS)

fclean: clean
	make fclean -C $(DIR_LIBFT)
	make clean -C $(DIR_MLX)
	rm -f $(NAME)

re: fclean all
