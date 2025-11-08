#include "PmergeMe.hpp"
#include "utils.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>

template <typename T>
PmergeMe<T>::PmergeMe()
    : _data(), _time(0), _comparisons(0), _hasOddElement(false), _oddElement(0),
      _lastelementused(-1) {}

template <typename T> PmergeMe<T>::~PmergeMe() {}

template <typename T> PmergeMe<T>::PmergeMe(const PmergeMe &other) {
  _data = other._data;
  _original = other._original;
  _time = other._time;
  _comparisons = other._comparisons;
  _pairs = other._pairs;
  _hasOddElement = other._hasOddElement;
  _oddElement = other._oddElement;
  _lastelementused = other._lastelementused;
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
    _lastelementused = other._lastelementused;
  }
  return *this;
}

template <typename T> void PmergeMe<T>::SetData(T data) { _data = data; }

template <typename T> T PmergeMe<T>::GetData() const { return _data; }

template <typename T> T PmergeMe<T>::GetOriginal() const { return _original; }

template <typename T> double PmergeMe<T>::GetTime() const { return _time; }

template <typename T> long PmergeMe<T>::GetComparisons() const {
  return _comparisons;
}

template <typename T> void PmergeMe<T>::ProcessInput(int argc, char **argv) {
  _data.clear();
  _original.clear();
  for (int i = 1; i < argc; ++i) {
    char *endptr;
    long value = std::strtol(argv[i], &endptr, 10);
    if (*endptr != '\0' || value < 0 || value > INT_MAX) {
      throw std::invalid_argument("Invalid input: " + std::string(argv[i]));
    }
    int int_value = static_cast<int>(value);
    // Check for duplicates
    if (std::find(_data.begin(), _data.end(), int_value) != _data.end()) {
      throw std::invalid_argument("Duplicate value found: " +
                                  std::string(argv[i]));
    }
    _data.push_back(int_value);
    _original.push_back(int_value);
  }

  if (_data.empty()) {
    throw std::invalid_argument("No valid input provided.");
  }
  FordJohnsonSort();
}

template <typename T> void PmergeMe<T>::PairElements() {
  _pairs.clear();
  _hasOddElement = false;

  size_t size = _data.size();
  if (size % 2 != 0) {
    _hasOddElement = true;
    _oddElement = _data[size - 1];
    size--;
  }

  for (size_t i = 0; i < size; i += 2) {
    if (Compare(_data[i], _data[i + 1])) {
      _pairs.push_back(_data[i]);
      _pairs.push_back(_data[i + 1]);
    } else {
      _pairs.push_back(_data[i + 1]);
      _pairs.push_back(_data[i]);
    }
  }
}

template <typename T>
void PmergeMe<T>::MergePairs(T &result, const T &left, const T &right) {
  if (Compare(left[left.size() - 1], right[right.size() - 1])) {
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return;
  } else {
    result.insert(result.end(), right.begin(), right.end());
    result.insert(result.end(), left.begin(), left.end());
    return;
  }
}

template <typename T> void PmergeMe<T>::RecursiveSort(const T &pairs) {
  int n = pairs.size();
  if (n <= 2) {
    return;
  }
  for (int size = 4; size <= n; size *= 2) {
    for (int left_start = 0; left_start < n; left_start += size) {
      int mid = left_start + size / 2;
      int right_end = left_start + size;
      if (right_end > n) {
        right_end = n;
        break;
      }
      T left(pairs.begin() + left_start, pairs.begin() + mid);
      T right(pairs.begin() + mid, pairs.begin() + right_end);
        T merged;
        MergePairs(merged, left, right);
        for (size_t i = 0; i < merged.size(); ++i) {
          _pairs[left_start + i] = merged[i];
        }
    }
    _final_size = size;
  }
}

template <typename T> void PmergeMe<T>::Insertion() {
  T main_chain;
  T pend_chain;
  T remain_chain;
  T bounds;

  if (_hasOddElement) {
    _pairs.push_back(_oddElement);
    _hasOddElement = false;
  }
  // }
  MainPendSeperation(main_chain, pend_chain, remain_chain, bounds);
  if (DEBUG)
    PrintChains(main_chain, pend_chain, remain_chain);

  size_t num_pend_elements = pend_chain.size() / _final_size;
  std::vector<int> jacobsthal =
      GenerateJacobsthalSequence(num_pend_elements + 1);

  // Insert pend_chain elements into main_chain based on Jacobsthal sequence
  InsertJacobsthalGroups(main_chain, pend_chain, jacobsthal, num_pend_elements,
                         bounds);

  // Insert any remaining pend_chain groups (not covered by Jacobsthal sequence)
  InsertRemainingGroups(main_chain, pend_chain, bounds);
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
    Insertion();
  } else {
    // Base case: we've reached individual elements, copy to _data
    _data = main_chain;
  }
}

template <typename T> void PmergeMe<T>::FordJohnsonSort() {
  if (_data.size() <= 1)
    return;

  clock_t start = clock();

  PairElements();
  if (_original.size() <= 3) {
    // Special handling for 2 or 3 elements
    _data = _pairs;
    if (_hasOddElement) {
      InsertElement(_oddElement);
    }
  } else {
    RecursiveSort(_pairs);
    if (DEBUG)
    {
      std::cout << RED << "Comparisons: " << _comparisons << RESET << std::endl;
    }
    if (_original.size() > 3) {
      _final_size = _final_size / 2;
      Insertion();
    }
  }
  clock_t end = clock();
  _time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}

template <typename T>
bool PmergeMe<T>::CheckValidIndex(size_t index, size_t size) {
  if (index >= size) {
    return false;
  }
  return true;
}

template <typename T>
void PmergeMe<T>::MainPendSeperation(T &main_chain, T &pend_chain,
                                       T &remain_chain, T &bounds) {
  size_t element_size = _final_size;
  size_t num_elements = _pairs.size() / element_size;
  // main = largest elements from all groups
  // pend = smallest elements from all groups except the first
  for (size_t i = 0; i < num_elements; ++i) {
    size_t largest_idx =
        i * element_size + element_size - 1; // last element (largest)
    size_t smallest_idx = i * element_size;  // first element (smallest)
    bool valid = CheckValidIndex(largest_idx, _pairs.size());
    if (!valid) {
      break;
    } else {
      bounds.push_back(_pairs[largest_idx]);
      if (i == 0 || i % 2 == 1) {
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
  if (DEBUG) {
    std::cout << CYAN << "Bounds: ";
    for (size_t i = 0; i < bounds.size(); ++i) {
      std::cout << bounds[i] << " ";
    }
    std::cout << RESET << std::endl;
  }
  // remain_chain for any leftover elements
  size_t processed = num_elements * element_size;
  remain_chain.insert(remain_chain.end(), _pairs.begin() + processed,
                      _pairs.end());
}

template <typename T> bool PmergeMe<T>::Compare(int a, int b) {
  _comparisons++;
  return a < b;
}

template <typename T>
template <typename U>
int PmergeMe<T>::BinarySearch(int value, int left, int right, const U &arr) {
  while (left <= right) {
    int mid = left + (right - left) / 2;
    if (Compare(value, arr[mid]))
      right = mid - 1;
    else
      left = mid + 1;
  }
  return left;
}

template <typename T>
template <typename U>
int PmergeMe<T>::BinarySearchWithBound(int value, int right, const U &arr, bool hasbond) {
  // Create temporary array with only bound elements (last element of each
  // group)
  int boundelement = -1;
    boundelement = right;
  std::vector<int> bounds;
  for (size_t i = _final_size - 1; i <= static_cast<size_t>(arr.size() - 1);
       i += _final_size) {

    bounds.push_back(arr[i]);
    if (arr[i] == boundelement) {
      if (hasbond) {
        bounds.pop_back();
      }
      break;
    }
  }
  if (DEBUG) {
    std::cout << RED << "comparison array: ";
      for (size_t k = 0; k < bounds.size(); ++k) {
        std::cout << bounds[k] << " ";
      }
    std::cout << std::endl;
  }
  // Perform binary search on the bounds array
  int left = 0;
  int bounds_right = bounds.size() - 1;
  while (left <= bounds_right) {
    int mid = std::floor(left + (bounds_right - left) / 2);
    if (Compare(value, bounds[mid])) {
      bounds_right = mid - 1;
    } else {
      left = mid + 1;
    }
  }
  if (DEBUG)
  {
    std::cout << "Comparisons: " << _comparisons << std::endl;
  }
  // Convert back to original array position by multiplying by _final_size
  return left * _final_size;
}

template <typename T>
std::vector<int> PmergeMe<T>::GenerateJacobsthalSequence(int n) {
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
  if (DEBUG) {
    std::cout << CYAN << "Jacobsthal sequence up to " << n << ": " << RESET;
    for (size_t i = 0; i < jacobsthal.size(); ++i) {
      std::cout << jacobsthal[i] << " ";
    }
    std::cout << std::endl;
  }
  return jacobsthal;
}

template <typename T> void PmergeMe<T>::InsertElement(int element) {
  if (_data.empty()) {
    _data.push_back(element);
    return;
  }
  int pos = BinarySearch(element, 0, static_cast<int>(_data.size()) - 1, _data);
  if (DEBUG) {
    std::cout << MAGENTA << "Debug: InsertElement " << element
              << ", _data.size()=" << _data.size() << ", pos=" << pos << RESET
              << std::endl;
  }
  _data.insert(_data.begin() + pos, element);
}

template <typename T>
void PmergeMe<T>::InsertGroupIntoMainChain(T &main_chain, T &pend_chain,
                                           size_t groupStartIndex,
                                           size_t groupEndIndex, T &bounds) {
  if (DEBUG) {
    std::cout << GREEN << "Pend group to insert: ";
    for (size_t k = groupStartIndex; k <= groupEndIndex; ++k) {
      std::cout << pend_chain[k] << " ";
    }
    std::cout << RESET << std::endl;
  }
  bool hasbond = false;
  int boundValue = main_chain[main_chain.size() - 1];
  int boundIndex = -1;
  if (!bounds.empty()) {
    hasbond = true;
    for (size_t i = 0; i < bounds.size(); ++i) {
      if (bounds[i] == pend_chain[groupEndIndex]) {
        boundIndex = i;
        break;
      }
    }
    boundIndex++; // move to next as the max bound for Insertion
    if (boundIndex > static_cast<int>(bounds.size()) - 1) {
      // If no larger bound, insert at end
      hasbond = false;
      boundValue = -1;
    }
    else {
      boundValue = bounds[boundIndex];
    }
  }
  if (DEBUG) {
    std::cout << "boundvalue:" << boundValue << std::endl;
  }
  int insert_pos =
      BinarySearchWithBound(pend_chain[groupEndIndex], boundValue, main_chain, hasbond);

  // Insert the entire group from pend_chain into main_chain at the found
  // position
  main_chain.insert(main_chain.begin() + insert_pos,
                    pend_chain.begin() + groupStartIndex,
                    pend_chain.begin() + groupEndIndex + 1);

  _lastelementused = pend_chain[groupEndIndex];
  // Remove the inserted elements from pend_chain
  pend_chain.erase(pend_chain.begin() + groupStartIndex,
                   pend_chain.begin() + groupEndIndex + 1);
}

template <typename T>
void PmergeMe<T>::InsertJacobsthalGroups(T &main_chain, T &pend_chain,
                                         const std::vector<int> &jacobsthal,
                                         size_t num_pend_elements, T &bounds) {
  // Insert pend_chain elements into main_chain based on Jacobsthal sequence
  // Start from second Jacobsthal number (index 1)
  for (size_t jacobsthalIndex = 1; jacobsthalIndex < jacobsthal.size();
       ++jacobsthalIndex) {
    _lastelementused = -1;
    int groupsToInsert =
        jacobsthal[jacobsthalIndex] - jacobsthal[jacobsthalIndex - 1];
        if (groupsToInsert > static_cast<int>(num_pend_elements))
      break;
    if (DEBUG) {
      std::cout << YELLOW << "Inserting " << groupsToInsert
                << " groups by jacobsthal" << RESET << std::endl;
    }
    // Insert groups starting from the back (highest index)
    for (int currentGroupIndex = groupsToInsert - 1; currentGroupIndex >= 0;
         --currentGroupIndex) {
      size_t groupEndIndex = currentGroupIndex * _final_size + _final_size - 1;
      size_t groupStartIndex = currentGroupIndex * _final_size;
      InsertGroupIntoMainChain(main_chain, pend_chain, groupStartIndex,
                               groupEndIndex, bounds);

    }
    
  }
}

template <typename T>
void PmergeMe<T>::InsertRemainingGroups(T &main_chain, T &pend_chain, T &bounds) {
  // Insert any remaining pend_chain groups (not covered by Jacobsthal sequence)
  while (!pend_chain.empty()) {
    _lastelementused = -1;
    int num_remaining_groups = pend_chain.size() / _final_size;
    if (DEBUG) {
      std::cout << GREEN << "Inserting remaining " << num_remaining_groups
                << " pend element groups" << RESET << std::endl;
    }
    for (int currentGroupIndex = num_remaining_groups - 1;
         currentGroupIndex >= 0; --currentGroupIndex) {
      size_t groupEndIndex = currentGroupIndex * _final_size + _final_size - 1;
      size_t groupStartIndex = currentGroupIndex * _final_size;
      InsertGroupIntoMainChain(main_chain, pend_chain, groupStartIndex,
                               groupEndIndex, bounds);
    }
    
  }
}

template <> std::string PmergeMe<std::vector<int> >::GetContainerType() const {
  return "vector";
}

template <> std::string PmergeMe<std::deque<int> >::GetContainerType() const {
  return "deque";
}

template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;
