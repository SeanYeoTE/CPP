#include "PmergeMe.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>

template <typename T>
PmergeMe<T>::PmergeMe()
    : _data(), _time(0), _comparisons(0), _hasOddElement(false),
      _oddElement(0) {}

template <typename T> PmergeMe<T>::~PmergeMe() {}

template <typename T> PmergeMe<T>::PmergeMe(const PmergeMe &other) {
  _data = other._data;
  _original = other._original;
  _time = other._time;
  _comparisons = other._comparisons;
  _pairs = other._pairs;
  _hasOddElement = other._hasOddElement;
  _oddElement = other._oddElement;
}

template <typename T>
PmergeMe<T> &PmergeMe<T>::operator=(const PmergeMe &other) {
  if (this != &other) {
    _data = other._data;
    _original = other._original;
    _time = other._time;
    _comparisons = other._comparisons;
    _pairs = other._pairs;
    _hasOddElement = other._hasOddElement;
    _oddElement = other._oddElement;
  }
  return *this;
}

template <typename T> void PmergeMe<T>::setData(T data) { _data = data; }

template <typename T> T PmergeMe<T>::getData() const { return _data; }

template <typename T> void PmergeMe<T>::processInput(int argc, char **argv) {
  _data.clear();
  _original.clear();
  for (int i = 1; i < argc; ++i) {
    char *endptr;
    long value = std::strtol(argv[i], &endptr, 10);
    if (*endptr != '\0' || value < 0 || value > INT_MAX) {
      throw std::invalid_argument("Invalid input: " + std::string(argv[i]));
    }
    _data.push_back(static_cast<int>(value));
    _original.push_back(static_cast<int>(value));
  }

  if (_data.empty()) {
    throw std::invalid_argument("No valid input provided.");
  }
  fordJohnsonSort();
}

template <typename T> void PmergeMe<T>::pairElements() {
  _pairs.clear();
  _hasOddElement = false;

  size_t size = _data.size();
  if (size % 2 != 0) {
    _hasOddElement = true;
    _oddElement = _data[size - 1];
    size--;
  }

  for (size_t i = 0; i < size; i += 2) {
    if (compare(_data[i], _data[i + 1])) {
      _pairs.push_back(_data[i]);
      _pairs.push_back(_data[i + 1]);
    } else {
      _pairs.push_back(_data[i + 1]);
      _pairs.push_back(_data[i]);
    }
  }
}

template <typename T>
void PmergeMe<T>::mergePairs(T &result, const T &left, const T &right) {
  if (compare(left[left.size() - 1], right[right.size() - 1])) {
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return;
  } else {
    result.insert(result.end(), right.begin(), right.end());
    result.insert(result.end(), left.begin(), left.end());
    return;
  }
}

template <typename T> void PmergeMe<T>::recursiveSort(const T &pairs) {
  int n = pairs.size();
  if (n <= 2) {
    return;
  }
  bool proceed = true;
  for (int size = 4; size <= n; size *= 2) {
    for (int left_start = 0; left_start < n; left_start += size) {
      int mid = left_start + size / 2;
      if (mid >= n) {
        continue;
      }
      int right_end = left_start + size;
      if (right_end > n) {
        right_end = n;
        proceed = false;
      }

      T left(pairs.begin() + left_start, pairs.begin() + mid);
      T right(pairs.begin() + mid, pairs.begin() + right_end);
      if (proceed) {
        T merged;
        mergePairs(merged, left, right);
        printpairs(merged, 1, 2);
        for (size_t i = 0; i < merged.size(); ++i) {
          _pairs[left_start + i] = merged[i];
        }
      }
      printpairs(pairs, 100, 2);
    }
    _final_size = size;
  }
}

template <typename T>
void PmergeMe<T>::main_pend_seperation(T &main_chain, T &pend_chain,
                                       T &remain_chain) {

  int groups = 1;
  size_t processed = 0;
  for (size_t i = 0; i < _pairs.size(); ++i) {
    size_t elements_in_group = 0;
    if (i + _final_size - 1 >= _pairs.size())
      break;
    for (size_t j = 0; j < _final_size && (i + j) < _pairs.size(); ++j) {
      if (groups == 1 || groups % 2 == 0) {
        main_chain.push_back(_pairs[i + j]);
      } else {
        pend_chain.push_back(_pairs[i + j]);
      }
      elements_in_group++;
      // std::cout << "elements_in_group: " << elements_in_group << std::endl;
    }
    processed += elements_in_group;
    i += _final_size - 1;
    groups++;
  }
  // Handle remaining elements that couldn't form a full group
  for (size_t k = processed; k < _pairs.size(); ++k) {
    remain_chain.push_back(_pairs[k]);
  }
}

template <typename T> void PmergeMe<T>::insertion() {
  T main_chain;
  T pend_chain;
  T remain_chain;
  std::cout << YELLOW << "Final size: " << _final_size << RESET << std::endl;
  main_pend_seperation(main_chain, pend_chain, remain_chain);
  printchains(main_chain, pend_chain, remain_chain);
  // if (!pend_chain.empty()) {
  //   main_chain.insert(main_chain.begin(), pend_chain[0]);
  // }
  std::vector<int> insertion_order =
      generateJacobsthalSequence(pend_chain.size());
  std::cout << CYAN << "Insertion order: " << RESET;

  for (size_t i = 0; i < insertion_order.size(); ++i)
    std::cout << insertion_order[i] << " ";
  std::cout << std::endl;

  for (size_t i = 0; i < insertion_order.size(); ++i) {
    int pend_idx = insertion_order[i];
    int value_to_insert = pend_chain[pend_idx];
    std::cout << GREEN << "Inserting pend_chain[" << pend_idx << "] = "
              << value_to_insert << RESET << std::endl;
    int pos = binarySearch(value_to_insert, 0, main_chain.size() - 1, main_chain);
    main_chain.insert(main_chain.begin() + pos, value_to_insert);
    printpairs(main_chain, 1, 2);
    // printchains(main_chain, pend_chain, remain_chain);
  }
  // Insert remain_chain elements
  // for (size_t i = 0; i < remain_chain.size(); ++i) {
  //   int value_to_insert = remain_chain[i];
  //   int pos =
  //       binarySearch(value_to_insert, 0, main_chain.size() - 1, main_chain);
  //   main_chain.insert(main_chain.begin() + pos, value_to_insert);
  // }

  if (_final_size / 2 >= 1) {
    if (!remain_chain.empty()) {
      for (size_t i = 0; i < remain_chain.size(); ++i) {
        main_chain.push_back(remain_chain[i]);
      }
    }
    _pairs = main_chain;
    _final_size = _final_size / 2;
    
    printpairs(_pairs, 1, 2);
    insertion();
  }
  else {
    if (!remain_chain.empty()) {
      for (size_t i = 0; i < remain_chain.size(); ++i) {
        int value_to_insert = remain_chain[i];
        int pos =
            binarySearch(value_to_insert, 0, main_chain.size() - 1, main_chain);
        main_chain.insert(main_chain.begin() + pos, value_to_insert);
      }
    }
    _pairs = main_chain;
    printpairs(_pairs, 1, 2);
    _data = main_chain;
  }
}

template <typename T> void PmergeMe<T>::fordJohnsonSort() {
  if (_data.size() <= 1)
    return;

  clock_t start = clock();

  pairElements();
  recursiveSort(_pairs);
  std::cout << MAGENTA << "After recursiveSort:" << RESET << std::endl;
  printpairs(_pairs, 1, 2);
  _final_size = _final_size / 2;
  insertion();

  if (_hasOddElement) {
    insertElement(_oddElement);
  }

  clock_t end = clock();
  _time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}

template <typename T>
void PmergeMe<T>::printpairs(const T &pairs, int depth,
                             int size) {
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
void PmergeMe<T>::printchains(const T &main_chain, const T &pend_chain,
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

template <typename T> void PmergeMe<T>::displayArray() const {
  std::cout << RED << "Before:" << RESET;
  for (long unsigned int i = 0; i < _original.size(); ++i) {
    std::cout << " ";
    std::cout << _original[i];
  }
  std::cout << "\n" << GREEN << "After : " << RESET;
  for (long unsigned int i = 0; i < _data.size(); ++i) {
    std::cout << " ";
    std::cout << _data[i];
  }
  std::cout << std::endl;
}

template <typename T> void PmergeMe<T>::displayResults() const {
  std::cout << BLUE << "Time to process a range of " << _original.size()
            << " elements with std::" << getContainerType() << " : " << _time
            << " us" << RESET << "\n" << YELLOW << "Total comparisons: " << _comparisons << RESET << std::endl;
}

template <typename T> bool PmergeMe<T>::compare(int a, int b) {
  _comparisons++;
  return a < b;
}

template <typename T>
template <typename U>
int PmergeMe<T>::binarySearch(int value, int left, int right, const U &arr) {
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (compare(value, arr[mid]))
      right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}

template <typename T>
std::vector<int> PmergeMe<T>::generateJacobsthalSequence(int n) {
  if (n <= 0)
    return std::vector<int>();

  std::vector<int> jacob;
  jacob.push_back(0);
  if (n > 1)
    jacob.push_back(1);

  int prev = 0;
  int curr = 1;
  while (true) {
    int next = curr + 2 * prev;
    if (next >= n)
      break;
    jacob.push_back(next);
    prev = curr;
    curr = next;
  }

  std::vector<int> insertion_order;
  std::vector<bool> inserted(n + 1, false);

  int last_jacob_idx = 0;
  for (size_t i = 0; i < jacob.size(); ++i) {
    int current_jacob_idx = jacob[i];
    for (int k = current_jacob_idx; k > last_jacob_idx; --k) {
      if (k < n) {
        insertion_order.push_back(k);
        inserted[k] = true;
      }
    }
    last_jacob_idx = current_jacob_idx;
  }

  for (int i = 0; i < n; ++i) {
    if (!inserted[i]) {
      insertion_order.push_back(i);
    }
  }

  return insertion_order;
}

template <typename T> void PmergeMe<T>::insertElement(int element) {
  if (_data.empty()) {
    _data.push_back(element);
    return;
  }
  int pos = binarySearch(element, 0, static_cast<int>(_data.size()) - 1, _data);
  if (DEBUG) {
    std::cout << MAGENTA << "Debug: insertElement " << element
              << ", _data.size()=" << _data.size() << ", pos=" << pos
              << RESET << std::endl;
  }
  _data.insert(_data.begin() + pos, element);
}

template <> std::string PmergeMe<std::vector<int> >::getContainerType() const {
  return "vector";
}

template <> std::string PmergeMe<std::deque<int> >::getContainerType() const {
  return "deque";
}

template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;
