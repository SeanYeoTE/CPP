#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <vector>
#include <deque>

// ANSI color codes for debug output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

template <typename T>
void printpairs(const T &pairs, int depth, int size);

template <typename T>
void printchains(const T &main_chain, const T &pend_chain, const T &remain_chain);

template <typename T>
void displayArray(const T &original, const T &data);

template <typename T>
void displayResults(const T &original, double time, long comparisons, const std::string &containerType);

#endif
