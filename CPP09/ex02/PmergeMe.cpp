#include "PmergeMe.hpp"
#include <cstddef>
#include <iostream>
#include <iterator>




template <typename T>
PmergeMe<T>::PmergeMe() : _data(), _last(-1), _time(0) {}

template <typename T>
PmergeMe<T>::~PmergeMe() {}

template <typename T>
PmergeMe<T>::PmergeMe(const PmergeMe &other) {
    _data = other._data;
    _last = other._last;
    _time = other._time;
    _comparisons = other._comparisons;
}

template <typename T>
PmergeMe<T> &PmergeMe<T>::operator=(const PmergeMe &other) {
    if (this != &other) {
        _data = other._data;
        _last = other._last;
        _time = other._time;
        _comparisons = other._comparisons;
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
    _hasOddElement = false;

    if (_data.size() <= 1)
        return;
    clock_t start = clock();

    pairElements();
    if (!_pairs.empty()) {
        recursiveSort(_pairs, 0, 1);
        printpairs(_pairs, 0, 1);
        // Reconstruct _data
        // _data.clear();
        // for (size_t k = 0; k < _pairs.size(); k += 1) {
        //     _data.push_back(_pairs[k]); 
        // }

        // seperate into main and pend
        // std::vector<int> order = generateJacobsthalSequence(_pairs.size() / 2);
        // for (size_t i = 0; i < order.size(); ++i) {
        //     int idx = order[i];
        //     int pos = idx * 2 + 1;
        //     if (pos >= 0 && pos < (int)_pairs.size()) {
        //         insertElement(_pairs[pos]); // larger elements
        //     }
        // }
    }

    // if (_hasOddElement) {
    //     insertElement(_oddElement);
    // }

    clock_t end = clock();
    _time = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000;
}


template <typename T>
void PmergeMe<T>::pairElements() {
    _pairs.clear();
    _hasOddElement = false;

    for (size_t i = 0; i < _data.size(); i += 2) {
        if (i + 1 < _data.size()) {
            int first = _data[i];
            int second = _data[i + 1];
            // if (first > second)
            //     swap first and second
            _pairs.push_back(first);
            _pairs.push_back(second);
        }
        else {
            _hasOddElement = true;
            _oddElement = _data[i];
        }
    }
    int num_pairs = _pairs.size() / 2;
    if (num_pairs % 2 != 0) {
        // remove the last 2 elements and store them as oddpair
        _oddpair.push_back(_pairs[_pairs.size()-2]);
        _oddpair.push_back(_pairs[_pairs.size()-1]);
        _pairs.pop_back();
        _pairs.pop_back();
    }
}

template <typename T>
void PmergeMe<T>::recursiveSort(std::vector<int>& pairs, int depth, int size) {
    depth ++;
    
    int num_pairs = pairs.size() / size;
    if (num_pairs <= 1) {
        // if (num_pairs == 1 && pairs[0] > pairs[1]) {
        // if (num_pairs == 1 && compare(pairs[0], pairs[1])) {
        //     std::swap(pairs[0], pairs[1]);
        // }
        return;
    }
    size = size * 2;
    printpairs(pairs, depth, size);
    std::vector<int>::iterator start = pairs.begin();

    // std::vector<int>::iterator it = start;
    for (std::vector<int>::iterator it = start; it + size <= pairs.end(); it += size) {
        if (compare(*(it + (size / 2 - 1)), *(it + (size - 1)))) {
            for (int i = 0; i < size / 2; i++) {
                std::swap(*(it + i), *(it + i + size / 2));
            }
        }
    }

    recursiveSort(pairs, depth, size);

//     // write newly arranged pairs back to _data
    _data.clear();
    for (size_t k = 0; k < pairs.size(); k += 1) {
        _data.push_back(pairs[k]);
    }
    // if there is an oddpair, append it back to _data
    if (!_oddpair.empty()) {
        for (size_t k = 0; k < _oddpair.size(); k += 1) {
            _data.push_back(_oddpair[k]);
        }
    }
}
