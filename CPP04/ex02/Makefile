NAME = ex01

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS_CPP = main.cpp Dog.cpp Cat.cpp AAnimal.cpp \
		 WrongAnimal.cpp WrongCat.cpp Brain.cpp
OBJS = $(SRCS_CPP:.cpp=.o)
RM = rm -f

DEPS = $(OBJS:.o=.d)

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	
%.o: %.cpp
	$(CC) $(CFLAGS) -MMD -c $< -o $@

%.o: %.c
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
