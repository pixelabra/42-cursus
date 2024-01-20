NAME	= libftprintf.a

SRCS	= ft_printf.c funcs/ft_putchar.c funcs/ft_putmem.c funcs/ft_putnbr_base.c funcs/ft_putnbr.c funcs/ft_putstr.c funcs/ft_strlen.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar -rcs $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all