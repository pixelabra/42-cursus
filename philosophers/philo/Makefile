NAME				:= philo
SRCS				:= main.c

OBJS				:= $(SRCS:.c=.o)
CC					:= cc
CFLAGS				:= -Wall -Wextra -Werror -pthread

DIR_SRCS			:= srcs/
DIR_OBJS			:= objs/
DIR_INC				:= includes/

SRCS_PFX			:= $(addprefix $(DIR_SRCS), $(SRCS))
OBJS_PFX			:= $(addprefix $(DIR_OBJS), $(OBJS))

all: $(NAME)

$(NAME): $(OBJS_PFX)
	$(CC) $(CFLAGS) $(OBJS_PFX) -o $@

$(DIR_OBJS):
	mkdir -p $@

$(DIR_OBJS)%.o: $(DIR_SRCS)%.c | $(DIR_OBJS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(DIR_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
