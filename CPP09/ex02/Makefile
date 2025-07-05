CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD
SRCS = main.cpp PmergeMe.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = PmergeMe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(OBJS:.o=.d)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re