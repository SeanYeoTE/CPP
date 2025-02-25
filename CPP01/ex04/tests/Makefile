CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Werror

SRCS = test_main.cpp replace.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = run_tests

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
