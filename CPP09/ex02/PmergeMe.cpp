#include "PmergeMe.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>

template <typename T>
PmergeMe<T>::PmergeMe()
    : _data(), _last(-1), _time(0), _comparisons(0), _hasOddElement(false),
      _oddElement(0), _size(0) {}

template <typename T> PmergeMe<T>::~PmergeMe() {}

template <typename T> PmergeMe<T>::PmergeMe(const PmergeMe &other) {
  _data = other._data;
  _last = other._last;
  _time = other._time;
  _comparisons = other._comparisons;
  _pairs = other._pairs;
  _hasOddElement = other._hasOddElement;
  _oddElement = other._oddElement;
  _oddpair = other._oddpair;
  _size = other._size;
}

template <typename T>
PmergeMe<T> &PmergeMe<T>::operator=(const PmergeMe &other) {
  if (this != &other) {
    _data = other._data;
    _last = other._last;
    _time = other._time;
    _comparisons = other._comparisons;
    _pairs = other._pairs;
    _hasOddElement = other._hasOddElement;
    _oddElement = other._oddElement;
    _oddpair = other._oddpair;
    _size = other._size;
  }
  return *this;
}

template <typename T> void PmergeMe<T>::processInput(int argc, char **argv) {
  _data.clear();

  for (int i = 1; i < argc; ++i) {
    char *endptr;
    long value = std::strtol(argv[i], &endptr, 10);
    if (*endptr != '\0' || value < 0 || value > INT_MAX) {
      throw std::invalid_argument("Invalid input: " + std::string(argv[i]));
    }
    _data.push_back(static_cast<int>(value));
  }

  if (_data.empty()) {
    throw std::invalid_argument("No valid input provided.");
  }
  fordJohnsonSort();
}

// Explicit template instantiation for the types you need
template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;

// Template specializations (add in .cpp file after template class definitions)
template <> std::string PmergeMe<std::vector<int> >::getContainerType() const {
  return "vector";
}

template <> std::string PmergeMe<std::deque<int> >::getContainerType() const {
  return "deque";
}

template <typename T> void PmergeMe<T>::fordJohnsonSort() {
  _original = _data;
  _hasOddElement = false;

  if (_data.size() <= 1)
    return;
  clock_t start = clock();

  pairElements();
  if (!_pairs.empty()) {
    _size = 1;
    recursiveSort(_pairs, 0);
    std::cout << "After recursiveSort:";
    // printpairs(_pairs, 0, 1);

    _size = _size / 2;
    insertion(_pairs, 0);
    // printpairs(_pairs, 0, 1);

    //     // write newly arranged pairs back to _data
    
  }
  _data.clear();
    for (size_t k = 0; k < _pairs.size(); k += 1) {
      _data.push_back(_pairs[k]);
    }
  if (!_oddpair.empty()) {
    for (size_t k = 0; k < _oddpair.size(); k += 1) {
      insertElement(_oddpair[k]);
    }
  }
  if (_hasOddElement) {
    insertElement(_oddElement);
  }

  clock_t end = clock();
  _time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}

template <typename T> void PmergeMe<T>::pairElements() {
  _pairs.clear();
  _hasOddElement = false;

  for (size_t i = 0; i < _data.size(); i += 2) {
    if (i + 1 < _data.size()) {
      int first = _data[i];
      int second = _data[i + 1];
      _pairs.push_back(first);
      _pairs.push_back(second);
    } else {
      _hasOddElement = true;
      _oddElement = _data[i];
    }
  }
  int num_pairs = _pairs.size() / 2;
  if (num_pairs % 2 != 0) {
    // remove the last 2 elements and store them as oddpair
    _oddpair.push_back(_pairs[_pairs.size() - 2]);
    _oddpair.push_back(_pairs[_pairs.size() - 1]);
    _pairs.pop_back();
    _pairs.pop_back();
    // Sort the oddpair elements by swapping if out of order
    if (compare(_oddpair[0], _oddpair[1])) {
      std::swap(_oddpair[0], _oddpair[1]);
    }
  }
}

template <typename T>
void PmergeMe<T>::recursiveSort(std::vector<int> &pairs, int depth) {
  depth++;

  int num_pairs = pairs.size() / _size;
  if (num_pairs <= 1) {
    return;
  }
  _size = _size * 2;
  //   printpairs(pairs, depth, _size);
  std::vector<int>::iterator start = pairs.begin();

  // std::vector<int>::iterator it = start;
  for (std::vector<int>::iterator it = start; it + _size <= pairs.end();
       it += _size) {
    if (compare(*(it + (_size / 2 - 1)), *(it + (_size - 1)))) {
      for (int i = 0; i < _size / 2; i++) {
        std::swap(*(it + i), *(it + i + _size / 2));
      }
    }
  }

  recursiveSort(pairs, depth);
}

template <typename T>
void PmergeMe<T>::insertion(std::vector<int> &pairs, int depth) {
  // make groups based on _size
  // main consists of first group and all even groups after that
  // pend consists of all odd groups after first group
  if (_size <= 1) {
    return;
  }

  std::vector<int> main;
  std::vector<int> pend;
  int group_size = _size;
  int num_groups = (pairs.size() / group_size) + 1;
  depth++;
  for (int i = 0; i < num_groups; ++i) {
    if (i == 0) {
      for (int j = 0; j < group_size; ++j) {
        int idx = i * group_size + j;
        if (idx >= static_cast<int>(pairs.size()))
          break;
        main.push_back(pairs[idx]);
      }
    } else if (i % 2 == 1) {
      // add to main
      for (int j = 0; j < group_size; ++j) {
        int idx = i * group_size + j;
        if (idx >= static_cast<int>(pairs.size()))
          break;
        main.push_back(pairs[idx]);
      }
    } else {
      for (int j = 0; j < group_size; ++j) {
        int idx = i * group_size + j;
        if (idx >= static_cast<int>(pairs.size()))
          break;
        pend.push_back(pairs[idx]);
      }
    }
  }
  //   std::cout << "After grouping: main.size()=" << main.size()
  // 			<< ", pend.size()=" << pend.size() << ", _size=" <<
  // _size
  // 			<< std::endl;
  //   // custom print for main and pend elements
  //   std::cout << "Depth " << depth << " - Main elements: ";
  //   for (size_t i = 0; i < main.size(); ++i) {
  // 	std::cout << main[i] << " ";
  //   }
  //   std::cout << std::endl;
  //   std::cout << "Depth " << depth << " - Pend elements: ";
  //   for (size_t i = 0; i < pend.size(); ++i) {
  // 	std::cout << pend[i] << " ";
  //   }
  //   std::cout << std::endl;

  // custom insert into _pairs
  pairs.clear();
  // first add main elements
  for (size_t i = 0; i < main.size(); ++i) {
    pairs.push_back(main[i]);
  }
  // then add pend elements one by one using binary search
  for (size_t i = 0; i < pend.size(); ++i) {
    int pos =
        binarySearch(pend[i], 0, static_cast<int>(pairs.size()) - 1, pairs);
    pairs.insert(pairs.begin() + pos, pend[i]);
  }
  //   printpairs(pairs, depth, _size);
  _size = _size / 2;
  insertion(pairs, depth);
}
