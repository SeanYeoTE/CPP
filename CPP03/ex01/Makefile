# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 15:24:04 by seayeo            #+#    #+#              #
#    Updated: 2025/03/15 17:26:03 by seayeo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler and flags
CC      = c++
CFLAGS  = -Wall -Wextra -Werror -std=c++98 -I includes

# Directories
SRC_DIR  = srcs
OBJ_DIR  = objs
INC_DIR  = includes

# Source files
SRC_FILES = main.cpp ClapTrap.cpp ScavTrap.cpp

# List of source files with directory prefix
SRCS     = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Corresponding object files with directory prefix
OBJS     = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

RM       = rm -f

# Dependency files
DEPS     = $(OBJS:.o=.d)

# Program name (of executable)
NAME     = ex01

# Targets
.PHONY: all clean fclean re
all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re: fclean all