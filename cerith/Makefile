NAME =		minishell
SRCDIR =	cfiles/
INIT =		init/minishell.c \
			init/take_input.c \
			init/env_init.c 
PARSING =	parsing/parsing.c \
			parsing/parsing_utils.c \
			parsing/env.c \
			parsing/env_vars.c \
			parsing/env_vars_utils.c \
			parsing/fix_input.c \
			parsing/quotes.c \
			parsing/tokens.c \
			parsing/token_utils.c
EXEC =		exec/execution.c \
			exec/execution_utils.c \
			exec/redir.c \
			exec/open_files.c \
			exec/here_doc.c \
			exec/signals.c
BUILTINS =	builtins/builtins.c \
			builtins/dir_builtins.c \
			builtins/env_builtins.c \
			builtins/echo_builtin.c \
			builtins/export_builtin.c \
			builtins/exit_builtin.c
UTILS =		utils/utils.c \
			utils/errors.c \
			utils/list_funcs.c \
			utils/list_utils.c
SRCS =		$(addprefix $(SRCDIR), $(INIT)) $(addprefix $(SRCDIR), $(PARSING)) \
			$(addprefix $(SRCDIR), $(EXEC)) $(addprefix $(SRCDIR), $(BUILTINS)) \
			$(addprefix $(SRCDIR), $(UTILS))
OBJS =		$(SRCS:.c=.o)
LIBFT =		libft/libft.a

CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -fsanitize=address,undefined -g3
CC = cc

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -L/opt/vagrant/embedded/lib/ -Iopt/vagrant/embedded/include/readline $(OBJS) $(LIBFT) -o $(NAME) -lreadline -lhistory

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re