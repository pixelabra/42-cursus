NAME			:= push_swap
NAME_BONUS		:= checker
SRCS			:= parsing.c free.c lst_utils.c ps_arithmetics.c ps_arithmetics2.c \
					target_finder.c algorithm.c moves.c algorithm_utils.c moves_back.c
SRCS_BONUS		:= checker.c
OBJS			:= $(SRCS:.c=.o)
OBJS_BONUS		:= $(SRCS_BONUS:.c=.o)
CC				:= cc
CFLAGS			:= -Wall -Wextra -Werror

DIR_LIBFT		:= libft/
DIR_SRCS		:= srcs/
DIR_OBJS		:= objs/
DIR_INC			:= includes/

SRCS_PFX		:= $(addprefix $(DIR_SRCS), $(SRCS)) srcs/push_swap.c
OBJS_PFX		:= $(addprefix $(DIR_OBJS), $(OBJS))
OBJS_PFX_BONUS	:= $(addprefix $(DIR_OBJS), $(OBJS_BONUS))
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

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJS_PFX_BONUS) $(OBJS_PFX) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS_PFX_BONUS) $(OBJS_PFX) -o $@ $(LIBS) $(INC)

clean:
	make clean -C $(DIR_LIBFT)
	rm -rf $(DIR_OBJS)

fclean: clean
	make fclean -C $(DIR_LIBFT)
	rm -f $(NAME)
	rm -f $(NAME_BONUS)

re: fclean all