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
void printpairs(const T &pairs, int depth, int size) {
  std::cout << CYAN << "Depth " << depth << ": " << RESET;
  std::cout << YELLOW << "Pairs: " << RESET;
  for (size_t i = 0; i < pairs.size(); i = i + size) {
    std::cout << GREEN << "(" << RESET;
    for (size_t j = i; j < i + size; ++j) {
      if (j >= pairs.size())
        break;
      std::cout << pairs[j] << (j == i + size - 1 ? "" : ", ");
    }
    std::cout << GREEN << ") " << RESET;
  }
  std::cout << std::endl;
}

template <typename T>
void printchains(const T &main_chain, const T &pend_chain,
                 const T &remain_chain) {
  std::cout << BLUE << "Main chain: " << RESET;
  for (size_t i = 0; i < main_chain.size(); ++i) {
    std::cout << main_chain[i] << " ";
  }
  std::cout << "\n" << MAGENTA << "Pend chain: " << RESET;
  for (size_t i = 0; i < pend_chain.size(); ++i) {
    std::cout << pend_chain[i] << " ";
  }
  std::cout << "\n" << RED << "Remain chain: " << RESET;
  for (size_t i = 0; i < remain_chain.size(); ++i) {
    std::cout << remain_chain[i] << " ";
  }
  std::cout << std::endl;
}

template <typename T>
void displayArray(const T &original, const T &data) {
  std::cout << RED << "Before:" << RESET;
  for (long unsigned int i = 0; i < original.size(); ++i) {
    std::cout << " ";
    std::cout << original[i];
  }
  std::cout << "\n" << GREEN << "After : " << RESET;
  for (long unsigned int i = 0; i < data.size(); ++i) {
    std::cout << " ";
    std::cout << data[i];
  }
  std::cout << std::endl;
}

template <typename T>
void displayResults(const T &original, double time, long comparisons, const std::string &containerType) {
  std::cout << "Time to process a range of " << original.size()
            << " elements with std::" << containerType << " : " << time
            << " us" << "\n"
            << "Total comparisons: " << comparisons << std::endl;
}

#endif
