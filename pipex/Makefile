NAME		= pipex
LIB			= pipex.a
LIBFT_DIR	= ./libft
LIBFT		= $(LIBFT_DIR)/libft.a
MAIN		= pipex.c
MAIN_BONUS	= ./bonus/pipex_bonus.c
SRCS		= pipex_utils_executing.c pipex_utils_parsing.c
SRCS_BONUS	= ./bonus/pipex_utils_executing_bonus.c ./bonus/pipex_utils_parsing_bonus.c ./bonus/here_doc.c
OBJS		= $(SRCS:.c=.o)
OBJS_BONUS	= $(SRCS_BONUS:.c=.o)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	@ar -rcs $@ $^

$(LIBFT): $(LIBFT_DIR)
	@make re -C $<

$(NAME): $(LIB)
	$(CC) $(CFLAGS) $(MAIN) $(LIB) -L$(LIBFT_DIR) -lft -o $@

clean:
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(OBJS) $(OBJS_BONUS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(NAME) $(LIB)

re: fclean all

bonus: $(LIBFT) $(OBJS_BONUS)
	ar -rcs $(LIB) $(OBJS_BONUS)
	$(CC) $(CFLAGS) $(MAIN_BONUS) $(LIB) -L$(LIBFT_DIR) -lft -o $(NAME)