NAME			:= push_swap
SRCS			:= push_swap.c parsing.c free.c lst_utils.c ps_arithmetic.c ps_arithmetic2.c \
					finder.c

OBJS			:= $(SRCS:.c=.o)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

DIR_LIBFT		:= libft/
DIR_SRCS		:= srcs/
DIR_OBJS		:= objs/
DIR_INC			:= includes/

SRCS_PFX		:= $(addprefix $(DIR_SRCS), $(SRCS))
OBJS_PFX		:= $(addprefix $(DIR_OBJS), $(OBJS))
INC				:= -I$(DIR_INC) -I$(DIR_LIBFT)
LIBS			:= -L$(DIR_LIBFT) -lft
LIBFT			:= $(DIR_LIBFT)libft.a

all: $(NAME)

$(LIBFT):
	make -C $(DIR_LIBFT)

$(NAME): $(OBJS_PFX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_PFX) -o $@ $(LIBS) $(INC)

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(DIR_OBJS):
	mkdir -p $@

clean:
	make clean -C $(DIR_LIBFT)
	rm -rf $(DIR_OBJS)

fclean: clean
	make fclean -C $(DIR_LIBFT)
	rm -f $(NAME)

re: fclean all