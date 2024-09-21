NAME			:= miniRT
SRCS			:= main.c vect_creation.c vect_ops.c vect_ops_ext.c utils.c \
					draw.c colours.c mlx_init.c

OBJS			:= $(SRCS:.c=.o)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

DIR_LIBFT		:= libft/
DIR_SRCS		:= srcs/
DIR_OBJS		:= objs/
DIR_INC			:= inc/

SRCS_PFX		:= $(addprefix $(DIR_SRCS), $(SRCS))
OBJS_PFX		:= $(addprefix $(DIR_OBJS), $(OBJS))

OS := $(shell uname)
ifeq ($(OS),Linux)
DIR_MLX			:= minilibx_linux/
LIBS			:= -L$(DIR_LIBFT) -lft -L$(DIR_MLX) -lmlx -lX11 -lXext -lm -lz
else
DIR_MLX			:= minilibx_macos/
LIBS			:= -L$(DIR_LIBFT) -lft -L$(DIR_MLX) -lmlx -framework OpenGL -framework Appkit
endif

LIBFT_MLX		:= $(DIR_LIBFT)libft.a $(DIR_MLX)libmlx.a
INC				:= -I$(DIR_INC) -I$(DIR_LIBFT) -I$(DIR_MLX)

all: $(DIR_OBJS) $(LIBFT_MLX) $(NAME)

$(NAME): $(OBJS_PFX) $(LIBFT_MLX)
	$(CC) $(CFLAGS) $(OBJS_PFX) $(LIBS) -o $@

$(DIR_OBJS):
	mkdir -p $@

${DIR_OBJS}%.o: $(DIR_SRCS)%.c
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
	rm -f $(NAME)

re: fclean all
