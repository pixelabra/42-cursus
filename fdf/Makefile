NAME			:= fdf
SRCS			:= fdf.c parsing.c fdf_drawing.c transformations.c bresenham.c free_data.c map_checker.c \
					hooks.c
OBJS			:= $(SRCS:.c=.o)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

DIR_LIBFT		:= libft/
DIR_SRCS		:= srcs/
DIR_OBJS		:= objs/
DIR_MLX			:= minilibx_PxAb/
DIR_INC			:= includes/

SRCS_PFX		:= $(addprefix $(DIR_SRCS), $(SRCS))
OBJS_PFX		:= $(addprefix $(DIR_OBJS), $(OBJS))
INC				:= -I$(DIR_INC) -I$(DIR_LIBFT) -I$(DIR_MLX)
LIBS			:= -L$(DIR_LIBFT) -L$(DIR_MLX) -lft -lmlx -lX11 -lXext -lm
LIBFT_MLX		:= $(DIR_LIBFT)libft.a $(DIR_MLX)libmlx.a

all: $(NAME)

$(NAME): $(OBJS_PFX) $(LIBS)
	$(CC) $(CFLAGS) $(OBJS_PFX) -o $@ $(LIBS) $(INC)

${DIR_OBJS}%.o: $(DIR_SRCS)%.c $(DIR_OBJS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

${DIR_OBJS}:
	mkdir -p $@

$(LIBS): $(DIR_LIBFT)libft.a $(DIR_MLX)libmlx.a
	
$(DIR_LIBFT)libft.a:	
	@make -C $(DIR_LIBFT)

$(DIR_MLX)libmlx.a:
	@make -C $(DIR_MLX)

clean:
	@make clean -C $(DIR_LIBFT)
	@make clean -C $(DIR_MLX)
	@rm -rf $(DIR_OBJS)

fclean: clean
	@make fclean -C $(DIR_LIBFT)
	@make clean -C $(DIR_MLX)
	@rm -f $(NAME)

re: fclean all

push:
	git add .
	git commit -m "finalised makefile"