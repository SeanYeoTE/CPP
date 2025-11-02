#include "utils.hpp"

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

// Explicit template instantiations
template void printpairs<std::vector<int> >(const std::vector<int> &pairs, int depth, int size);
template void printpairs<std::deque<int> >(const std::deque<int> &pairs, int depth, int size);
template void printchains<std::vector<int> >(const std::vector<int> &main_chain, const std::vector<int> &pend_chain, const std::vector<int> &remain_chain);
template void printchains<std::deque<int> >(const std::deque<int> &main_chain, const std::deque<int> &pend_chain, const std::deque<int> &remain_chain);
template void displayArray<std::vector<int> >(const std::vector<int> &original, const std::vector<int> &data);
template void displayArray<std::deque<int> >(const std::deque<int> &original, const std::deque<int> &data);
template void displayResults<std::vector<int> >(const std::vector<int> &original, double time, long comparisons, const std::string &containerType);
template void displayResults<std::deque<int> >(const std::deque<int> &original, double time, long comparisons, const std::string &containerType);
