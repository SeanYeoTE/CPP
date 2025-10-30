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

template <typename T>
void PmergeMe<T>::setData(T data) {
    _data = data;
}

template <typename T>
T PmergeMe<T>::getData() const {
    return _data;
}

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

template <typename T>
void PmergeMe<T>::pairElements() {
  _pairs.clear();
  _hasOddElement = false;
  
  size_t size = _data.size();
  if (size % 2 != 0) {
    _hasOddElement = true;
    _oddElement = _data[size - 1];
    size--;
  }

  for (size_t i = 0; i < size; i += 2) {
      if (compare(_data[i], _data[i+1])) {
          _pairs.push_back(_data[i]);
          _pairs.push_back(_data[i+1]);
      } else {
          _pairs.push_back(_data[i+1]);
          _pairs.push_back(_data[i]);
      }
  }
}

template <typename T>
void PmergeMe<T>::mergePairs(std::vector<int>& result, const std::vector<int>& left, const std::vector<int>& right) {
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (compare(left[i], right[j])) {
            result.push_back(left[i]);
            result.push_back(left[i+1]);
            i += 2;
        } else {
            result.push_back(right[j]);
            result.push_back(right[j+1]);
            j += 2;
        }
    }

    while (i < left.size()) {
        result.push_back(left[i]);
        result.push_back(left[i+1]);
        i += 2;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        result.push_back(right[j+1]);
        j += 2;
    }
}

template <typename T>
void PmergeMe<T>::recursiveSort(std::vector<int>& pairs) {
    int n = pairs.size();
    if (n <= 2) {
        return;
    }

    for (int size = 4; size <= n; size *= 2) {
        for (int left_start = 0; left_start < n; left_start += size) {
            int mid = left_start + size / 2;
            if (mid >= n) {
                continue;
            }
            int right_end = left_start + size;
            if (right_end > n) {
                right_end = n;
            }

            std::vector<int> left(pairs.begin() + left_start, pairs.begin() + mid);
            std::vector<int> right(pairs.begin() + mid, pairs.begin() + right_end);
            
            std::vector<int> merged;
            mergePairs(merged, left, right);
            printpairs(merged, 1, 2);
            for(size_t i = 0; i < merged.size(); ++i) {
                pairs[left_start + i] = merged[i];
            }
            printpairs(pairs, 100, 2);
        }
    }
}

template <typename T>
void PmergeMe<T>::insertion() {
    T main_chain;
    T pend_chain;

    for(size_t i = 0; i < _pairs.size(); i += 2) {
        main_chain.push_back(_pairs[i]);
        pend_chain.push_back(_pairs[i+1]);
    }

    if (!pend_chain.empty()) {
        main_chain.insert(main_chain.begin(), pend_chain[0]);
    }

    std::vector<int> insertion_order = generateJacobsthalSequence(pend_chain.size());

    for (size_t i = 0; i < insertion_order.size(); ++i) {
        int pend_idx = insertion_order[i];
        if(pend_idx == 0) continue;
        int value_to_insert = pend_chain[pend_idx];
        
        int pos = binarySearch(value_to_insert, 0, main_chain.size() - 1, main_chain);
        main_chain.insert(main_chain.begin() + pos, value_to_insert);
    }
    
    _data = main_chain;
}

template <typename T>
void PmergeMe<T>::fordJohnsonSort() {
    if (_data.size() <= 1) return;

    clock_t start = clock();
    
    pairElements();
    recursiveSort(_pairs);
    insertion();

    if (_hasOddElement) {
        insertElement(_oddElement);
    }

    clock_t end = clock();
    _time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}

template <typename T> void PmergeMe<T>::printpairs(const std::vector<int> &pairs, int depth,
                             int size) {
  std::cout << "Depth " << depth << ": ";
  std::cout << "Pairs: ";
  for (size_t i = 0; i < pairs.size(); i = i + size) {
    std::cout << "(";
    for (size_t j = i; j < i + size; ++j) {
      if (j >= pairs.size())
        break;
      std::cout << pairs[j] << (j == i + size - 1 ? "" : ", ");
    }
    std::cout << ") "
;
  }
  std::cout << std::endl;
}

template <typename T> void PmergeMe<T>::displayArray() const {
  std::cout << "Before:";
  for (long unsigned int i = 0; i < _original.size(); ++i) {
    std::cout << " ";
    std::cout << _original[i];
  }
  std::cout << "\nAfter : ";
  for (long unsigned int i = 0; i < _data.size(); ++i) {
    std::cout << " ";
    std::cout << _data[i];
  }
  std::cout << std::endl;
}

template <typename T> void PmergeMe<T>::displayResults() const {
    std::cout << "Time to process a range of " << _original.size()
              << " elements with std::" << getContainerType() << " : " << _time
              << " us" << "\nTotal comparisons: " << _comparisons << std::endl;
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
    if (n <= 0) return std::vector<int>();

    std::vector<int> jacob;
    jacob.push_back(0);
    if (n > 1) jacob.push_back(1);

    int prev = 0;
    int curr = 1;
    while (true) {
        int next = curr + 2 * prev;
        if (next >= n) break;
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
    std::cout << "Debug: insertElement " << element
              << ", _data.size()=" << _data.size() << ", pos=" << pos
              << std::endl;
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
