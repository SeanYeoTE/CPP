# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/10 15:24:04 by seayeo            #+#    #+#              #
#    Updated: 2025/03/11 18:42:33 by seayeo           ###   ########.fr        #
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
.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

-include $(DEPS)

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all