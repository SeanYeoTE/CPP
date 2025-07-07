#include "PmergeMe.hpp"


template <typename T>
PmergeMe<T>::PmergeMe() : _data(), _last(-1), _time(0) {}

template <typename T>
PmergeMe<T>::~PmergeMe() {}

template <typename T>
PmergeMe<T>::PmergeMe(const PmergeMe &other) {
    _data = other._data;
    _last = other._last;
    _time = other._time;
}

template <typename T>
PmergeMe<T> &PmergeMe<T>::operator=(const PmergeMe &other) {
    if (this != &other) {
        _data = other._data;
        _last = other._last;
        _time = other._time;
    }
    return *this;
}

template <typename T>
void PmergeMe<T>::processInput(int argc, char **argv) {
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

template <typename T>
std::string PmergeMe<T>::getContainerType() const {
    return "unknown";
}

// Template specializations (add in .cpp file after template class definitions)
template <>
std::string PmergeMe<std::vector<int> >::getContainerType() const {
    return "vector";
}

template <>
std::string PmergeMe<std::deque<int> >::getContainerType() const {
       return "deque";
}

template <typename T>
void PmergeMe<T>::fordJohnsonSort() {
    _original = _data;

    if (_data.size() <= 1)
        return;
    clock_t start = clock();
    
    pairing();
    if (!_pairs.empty()) {
        recursiveSort(_pairs);
        insertRemainingElements(extractSmallerElements());
    }

    if (_hasOddElement) {
        insertElement(_oddElement);
    };

    clock_t end = clock();
    _time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}


template <typename T>
void PmergeMe<T>::pairing() {
    _pairs.clear();
    _hasOddElement = false;

    for (size_t i = 0; i < _data.size(); i += 2) {
        if (i + 1 < _data.size()) {
            int first = _data[i];
            int second = _data[i + 1];
            if (first > second)
                _pairs.push_back(std::make_pair(second, first));
            else
                _pairs.push_back(std::make_pair(first, second));
        }
        else {
            _hasOddElement = true;
            _oddElement = _data[i];
        }
    }
}

template <typename T>
void PmergeMe<T>::recursiveSort(std::vector<std::pair<int, int> > &pairs) {
    if (pairs.size() <= 1)
        return;
    // Recursive Ford-Johnson approach: divide into sub-sequences
    size_t mid = pairs.size() / 2;
    
    // Create left and right sub-sequences
    std::vector<std::pair<int, int> > left(pairs.begin(), pairs.begin() + mid);
    std::vector<std::pair<int, int> > right(pairs.begin() + mid, pairs.end());
    
    // Recursively sort both halves
    recursiveSort(left);
    recursiveSort(right);
    
    // Merge the sorted halves using Ford-Johnson merge strategy
    mergeSequences(pairs, left, right);
}


template <typename T>
void PmergeMe<T>::mergeSequences(std::vector<std::pair<int, int> > &result,
                                const std::vector<std::pair<int, int> > &left,
                                const std::vector<std::pair<int, int> > &right) {
    size_t leftIdx = 0, rightIdx = 0, resultIdx = 0;
    
    // Merge the two sorted sequences by comparing the larger elements (second values)
    while (leftIdx < left.size() && rightIdx < right.size()) {
        if (left[leftIdx].second <= right[rightIdx].second) {
            result[resultIdx] = left[leftIdx];
            leftIdx++;
        } else {
            result[resultIdx] = right[rightIdx];
            rightIdx++;
        }
        resultIdx++;
    }
    
    // Copy remaining elements from left sequence
    while (leftIdx < left.size()) {
        result[resultIdx] = left[leftIdx];
        leftIdx++;
        resultIdx++;
    }
    
    // Copy remaining elements from right sequence
    while (rightIdx < right.size()) {
        result[resultIdx] = right[rightIdx];
        rightIdx++;
        resultIdx++;
    }
}

template <typename T>
std::vector<int> PmergeMe<T>::extractSmallerElements() const {
    std::vector <int> smaller;

    for (std::vector<std::pair<int, int> >::const_iterator it = _pairs.begin();
         it != _pairs.end(); ++it) {
        smaller.push_back(it->first);
    }
    return smaller;
}

template <typename T>
void PmergeMe<T>::insertRemainingElements(const std::vector<int> &smaller) {
    _data.clear();
    for (std::vector<std::pair<int, int> >::const_iterator it = _pairs.begin();
         it != _pairs.end(); ++it) {
        _data.push_back(it->second);
    }

    std::vector<int> jacobsthal = generateJacobsthalSequence(smaller.size());

    for (std::vector<int>::const_iterator it = jacobsthal.begin();
         it != jacobsthal.end(); ++it) {
        int index = *it;
        if (index >= 0 && index < static_cast<int>(smaller.size())) {
            int value = smaller[index];
            int pos = binarySearch(value, 0, static_cast<int>(_data.size()) - 1);
            _data.insert(_data.begin() + pos, value);
        }
    }
}






