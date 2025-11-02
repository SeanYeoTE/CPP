#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <climits>

// ANSI color codes for debug output
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

#define DEBUG 0

template <typename T>
class PmergeMe {
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        void processInput(int argc, char **argv);
        void displayArray() const;
        void fordJohnsonSort();

        // Utility functions moved to utils.hpp
        T getData() const;
        T getOriginal() const;
        double getTime() const;
        long getComparisons() const;
        void setData(T data);

    private:
        T _data;
        T _original;
        double _time;
        long _comparisons;
        T _pairs;
        bool _hasOddElement;
        int _oddElement;
        size_t _final_size;

        bool compare(int a, int b);
        bool check_valid_index(size_t index, size_t size);
        void pairElements();
        void recursiveSort(const T &pairs);
        void mergePairs(T &result, const T &left, const T &right);
        void insertion();
        void main_pend_seperation(T &main_chain, T &pend_chain, T &remain_chain);
        std::vector<int> generateJacobsthalSequence(int n);
        void insertElement(int element);
        template <typename U>
        int binarySearch(int value, int left, int right, const U& arr);
        template <typename U>
        int binarySearchWithBound(int value, int element_size, int right, const U& arr);
        std::string getContainerType() const;
};

#endif
