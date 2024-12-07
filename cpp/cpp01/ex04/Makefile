NAME			:= sed
SRCS			:= main.cpp #main.cppmain.cpp
OBJS			:= $(SRCS:.cpp=.o)
CC				:= c++
CPPFLAGS		:= -Wall -Wextra -Werror -std=c++98

all: $(NAME) #main.cpp

$(NAME): $(OBJS)
	$(CC) $(CPPFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all