CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -Iincludes
SRCDIR = src
SRCS = main.cpp BitcoinExchange.cpp
OBJS = $(addprefix $(SRCDIR)/, $(SRCS:.cpp=.o))
TARGET = btc

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS:.o=.d)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re