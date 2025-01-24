# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/22 13:58:07 by seayeo            #+#    #+#              #
#    Updated: 2025/01/24 13:59:42 by seayeo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = phone
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS = PhoneBook.cpp Contact.cpp Main.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
