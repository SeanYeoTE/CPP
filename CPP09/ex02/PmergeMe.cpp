#include "PmergeMe.hpp"
#include <cstdlib>

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
    for (int i = 1; i < argc; ++i) {
        int num = std::atoi(argv[i]);
        if (num < 0) {
            throw std::invalid_argument("Negative numbers are not allowed.");
        }
        _data.push_back(num);
    }
    if (_data.empty()) {
        throw std::invalid_argument("No valid numbers provided.");
    }
    _last = _data.back();
}

template <typename T>
void PmergeMe<T>::displayResults() const {
    std::cout << "Before:";
    for (long unsigned int i = 0; i < _data.size(); ++i) {
        std::cout << " ";
        std::cout << _data[i];
    }
    std::cout << "\nAfter: ";
    for (long unsigned int i = 0; i < _data.size(); ++i) {
        std::cout << " ";
        std::cout << _data[i];
    }
    std::cout << std::endl;
}

// Explicit template instantiation for the types you need
template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;


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
        insertElement(_oddElements)
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
bool PmergeMe<T>::ComparePairsBySecond::operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const
{
    return a.second < b.second;
}


template <typename T>
void PmergeMe<T>::recursiveSort(std::vector<std::pair<int, int>> &pairs) {
    if (pairs.size() <= 1)
        return;
    
    std::sort(pairs.begin(), pairs.end(), ComparePairsBySecond());
}
