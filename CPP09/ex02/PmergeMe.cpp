#include "PmergeMe.hpp"
#include "utils.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>
#include <vector>

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

template <typename T> T PmergeMe<T>::getOriginal() const { return _original; }

template <typename T> double PmergeMe<T>::getTime() const { return _time; }

template <typename T> long PmergeMe<T>::getComparisons() const {
  return _comparisons;
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
        // printpairs(merged, 1, 2);
        for (size_t i = 0; i < merged.size(); ++i) {
          _pairs[left_start + i] = merged[i];
        }
      }
      // printpairs(pairs, 100, 2);
    }
    _final_size = size;
  }
}

template <typename T> void PmergeMe<T>::insertion() {
  T main_chain;
  T pend_chain;
  T remain_chain;

  std::cout << YELLOW << "Final size: " << _final_size << RESET << std::endl;
  main_pend_seperation(main_chain, pend_chain, remain_chain);
  printchains(main_chain, pend_chain, remain_chain);

  size_t element_size = _final_size; // pend_chain contains individual elements

  size_t num_pend_elements = pend_chain.size() / element_size;
  std::vector<int> jacobsthal = generateJacobsthalSequence(num_pend_elements + 1);
  
  // Insert pend_chain elements into main_chain based on Jacobsthal sequence
  // Start from second Jacobsthal number (index 1)
  // do binary search on the bound numbers in main_chain
  // insert the group of elements from pend_chain into main_chain
  // make sure not to break up element groups in main_chain
  for (size_t j_idx = 1; j_idx < jacobsthal.size(); ++j_idx) {
    int j = jacobsthal[j_idx] - jacobsthal[j_idx - 1]; // number of pend element groups to insert
    std::cout << GREEN << "Inserting " << j << " pend element groups"
              << RESET << std::endl;
    if (j > static_cast<int>(num_pend_elements))
      break;
    // Insert groups starting from the back (highest index)
    for (int group = j - 1; group >= 0; --group) {
      int pend_bound_end_idx = group * element_size + element_size - 1; // need to use -1 for 0-based index
      int pend_bound_start_idx = group * element_size;
      std::cout << GREEN << "Pend group to insert: ";
      for (int k = pend_bound_start_idx; k <= pend_bound_end_idx; ++k) {
        std::cout << pend_chain[k] << " ";
      }
      std::cout << RESET << std::endl;
      // Find insertion position using binary search on bounds
      int insert_pos = binarySearchWithBound(pend_chain[pend_bound_end_idx], element_size,
                                             main_chain.size() - 1, main_chain);

      // Insert the entire group from pend_chain into main_chain at the found position
      main_chain.insert(main_chain.begin() + insert_pos,
                        pend_chain.begin() + pend_bound_start_idx,
                        pend_chain.begin() + pend_bound_end_idx + 1);
      printpairs(main_chain, 1, 2);
      // need to remove the inserted elements from pend_chain
      pend_chain.erase(pend_chain.begin() + pend_bound_start_idx,
                       pend_chain.begin() + pend_bound_end_idx + 1);
    }
  }
  // Insert any remaining pend_chain groups (not covered by Jacobsthal sequence)
  // could be more than one group
  while (!pend_chain.empty()) {
    int pend_bound_end_idx = element_size - 1; // need to use -1 for 0-based index
    int pend_bound_start_idx = 0;
    int num_remaining_groups = pend_chain.size() / element_size;
    std::cout << GREEN << "Inserting remaining " << num_remaining_groups
              << " pend element groups" << RESET << std::endl;

    for (int group = num_remaining_groups - 1; group >= 0; --group) {
      pend_bound_end_idx = group * element_size + element_size - 1;
      pend_bound_start_idx = group * element_size;
      std::cout << GREEN << "Pend group to insert: ";
      for (int k = pend_bound_start_idx; k <= pend_bound_end_idx; ++k) {
        std::cout << pend_chain[k] << " ";
      }
      std::cout << RESET << std::endl;
      // Find insertion position using binary search on bounds
      int insert_pos = binarySearchWithBound(pend_chain[pend_bound_end_idx], element_size,
                                             main_chain.size() - 1, main_chain);

      // Insert the entire group from pend_chain into main_chain at the found position
      main_chain.insert(main_chain.begin() + insert_pos,
                        pend_chain.begin() + pend_bound_start_idx,
                        pend_chain.begin() + pend_bound_end_idx + 1);
      printpairs(main_chain, 1, 2);
      // need to remove the inserted elements from pend_chain
      pend_chain.erase(pend_chain.begin() + pend_bound_start_idx,
                       pend_chain.begin() + pend_bound_end_idx + 1);
    }
  }
  // Handle remain_chain - just append to back of main_chain
  if (!remain_chain.empty()) {
    main_chain.insert(main_chain.end(), remain_chain.begin(),
                      remain_chain.end());
  }

  // Check if we need to continue with smaller element sizes
  if (_final_size >= 2) {
    // Prepare for next recursion level: main_chain becomes the new _pairs
    _pairs = main_chain;
    _final_size = _final_size / 2;
    printpairs(_pairs, 1, 2);
    insertion();
  } else {
    // Base case: we've reached individual elements, copy to _data
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
bool PmergeMe<T>::check_valid_index(size_t index, size_t size) {
  if (index >= size) {
    return false;
  }
  return true;
}

template <typename T>
void PmergeMe<T>::main_pend_seperation(T &main_chain, T &pend_chain,
                                       T &remain_chain) {
  size_t element_size = _final_size;
  size_t num_elements = _pairs.size() / element_size;

  // main = largest elements from all groups
  // pend = smallest elements from all groups except the first
  for (size_t i = 0; i < num_elements; ++i) {
    size_t largest_idx =
        i * element_size + element_size - 1; // last element (largest)
    size_t smallest_idx = i * element_size;  // first element (smallest)
    bool valid = check_valid_index(largest_idx, _pairs.size());
    if (!valid) {
      break;
    } else {
      if (i == 0  || i % 2 == 1) {
        // push all elements from smallestindx to largestidx into main_chain
        for (size_t j = smallest_idx; j <= largest_idx; ++j) {
          main_chain.push_back(_pairs[j]);
        }
      }

      // Add smallest to pend_chain only if not the first group
      if (i > 0 && i % 2 == 0) {
        for (size_t j = smallest_idx; j <= largest_idx; ++j) {
          pend_chain.push_back(_pairs[j]);
        }
      }
    }
  }

  // remain_chain for any leftover elements
  size_t processed = num_elements * element_size;
  remain_chain.insert(remain_chain.end(), _pairs.begin() + processed,
                      _pairs.end());
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
template <typename U>
int PmergeMe<T>::binarySearchWithBound(int value, int element_size, int right,
                                       const U &arr) {
  // Create temporary array with only bound elements (last element of each group)
  std::vector<int> bounds;
  for (size_t i = element_size - 1; i <= static_cast<size_t>(right); i += element_size) {
    bounds.push_back(arr[i]);
  }

  // Perform binary search on the bounds array
  int left = 0;
  int bounds_right = bounds.size() - 1;
  while (left <= bounds_right) {
    int mid = left + (bounds_right - left) / 2;
    if (compare(value, bounds[mid])) {
      bounds_right = mid - 1;
    } else {
      left = mid + 1;
    }
  }

  // Convert back to original array position by multiplying by element_size
  return left * element_size;
}

template <typename T>
std::vector<int> PmergeMe<T>::generateJacobsthalSequence(int n) {
  if (n <= 0)
    return std::vector<int>();
  std::vector<int> jacobsthal;
  jacobsthal.push_back(1);
  jacobsthal.push_back(3);
  while (true) {
    int next = jacobsthal.back() + 2 * jacobsthal[jacobsthal.size() - 2];
    if (next > n)
      break;
    jacobsthal.push_back(next);
  }
  std::cout << CYAN << "Jacobsthal sequence up to " << n << ": " << RESET;
  for (size_t i = 0; i < jacobsthal.size(); ++i) {
    std::cout << jacobsthal[i] << " ";
  }
  std::cout << std::endl;

  return jacobsthal;
}

template <typename T> void PmergeMe<T>::insertElement(int element) {
  if (_data.empty()) {
    _data.push_back(element);
    return;
  }
  int pos = binarySearch(element, 0, static_cast<int>(_data.size()) - 1, _data);
  if (DEBUG) {
    std::cout << MAGENTA << "Debug: insertElement " << element
              << ", _data.size()=" << _data.size() << ", pos=" << pos << RESET
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
