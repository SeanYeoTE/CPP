NAME = ex00

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = main.cpp Dog.cpp Cat.cpp Animal.cpp
OBJS = $(SRCS:.cpp=.o)
RM = rm -f

DEPS = $(OBJS:.o=.d)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.cpp
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re