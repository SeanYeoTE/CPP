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


template <typename T>
int PmergeMe<T>::binarySearch(int value, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (_data[mid] < value)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left; // Return the position where the value should be inserted
}


template <typename T>
std::vector<int> PmergeMe<T>::generateJacobsthalSequence(int n) {
    std::vector<int> jacobsthal;
    if (n <= 0)
        return jacobsthal;
    
    std::vector<int> j;
    j.push_back(0);
    if (n > 0)
        j.push_back(1);
    for (int i = 2; j[i - 1] < n; ++i) {
        int next = j[i - 1] + 2 * j[i - 2];
        if (next >= n)
            break;
        j.push_back(next);
    }

    