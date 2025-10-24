#include "PmergeMe.hpp"

template <typename T>
void PmergeMe<T>::printpairs(const std::vector<int> &pairs, int depth, int size) {
    std::cout << "Depth " << depth << ": ";
    std::cout << "Pairs: ";
    for (size_t i = 0; i < pairs.size(); i = i + size) {
        std::cout << "(";
        for (size_t j = i; j < i + size; ++j) {
            if (j >= pairs.size())
                break;
            std::cout << pairs[j] << (j == i + size - 1 ? "" : ", ");
        }
        std::cout << ") ";
    }
    std::cout << std::endl;
}

template <typename T>
void PmergeMe<T>::displayArray() const {
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

template <typename T>
void PmergeMe<T>::displayResults() const {
    if (DEBUG) {
        std::cout << "Time to process a range of " << _original.size() 
                 << " elements with std::" << getContainerType() 
                 << " : " << _time << " us " <<  "Total comparisons: " << _comparisons << std::endl;
    }
    else {
        std::cout << "Time to process a range of " << _original.size() 
                 << " elements with std::" << getContainerType() 
                 << " : " << _time << " us" << std::endl;
}
}

template <typename T>
bool PmergeMe<T>::compare(int a, int b) {
    _comparisons++;
    return a > b;
}


template <typename T>
int PmergeMe<T>::binarySearch(int value, int left, int right) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (compare(value, _data[mid]))
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

    std::vector <bool> used(n, false);
    
    // Handle the first Jacobsthal number separately
    if (!j.empty() && j[0] < n) {
        jacobsthal.push_back(j[0]);
        used[j[0]] = true;
    }
    
    for (size_t i = 1; i < j.size(); ++i) {
        for (int idx = j[i] -1 ; idx >= j[i - 1]; --idx) {
            if (idx < n && !used[idx]) {
                jacobsthal.push_back(idx);
                used[idx] = true;
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            jacobsthal.push_back(i);
        }
    }

    return jacobsthal;
}


template <typename T>
void PmergeMe<T>::insertElement(int element) {
    if (_data.empty()) {
        _data.push_back(element);
        return;
    }
    int pos = binarySearch(element, 0, static_cast<int>(_data.size()) - 1);
    _data.insert(_data.begin() + pos, element);
}

// Explicit template instantiation for the types you need
template class PmergeMe<std::vector<int> >;
template class PmergeMe<std::deque<int> >;