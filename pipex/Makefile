NAME		= pipex
LIB			= pipex.a
LIBFT		= ./libft/libft.a
LIBFT_DIR	= ./libft
MAIN		= pipex.c
SRCS		= pipex_utils.c
OBJS		= $(SRCS:.c=.o)
CC			= cc
CFLAGS		= -Wall -Wextra -Werror

all: $(LIBFT) $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB): $(OBJS)
	@ar -rcs $@ $^

$(LIBFT): $(LIBFT_DIR)
	@make re -C $<

$(NAME): $(MAIN) $(LIB)
	$(CC) $(CFLAGS) -I$(LIBFT_DIR) $< $(LIB) -L$(LIBFT_DIR) -lft -o $@ 

clean:
	@make fclean -C $(LIBFT_DIR)
	@rm -f $(OBJS)

fclean: clean
	@make fclean -C ./libft
	@rm -f $(NAME) $(LIB)

re: fclean all
