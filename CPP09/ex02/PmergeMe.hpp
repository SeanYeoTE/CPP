#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <climits>

#define DEBUG 0

template <typename T>
class PmergeMe {
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        void processInput(int argc, char **argv);
        void displayResults() const;
        void displayArray() const;
        void fordJohnsonSort();
        T getData() const;
        void setData(T data);

    private:
        T _data;
        T _original;
        double _time;
        long _comparisons;
        std::vector<int> _pairs;
        bool _hasOddElement;
        int _oddElement;
        
        void printpairs(const std::vector<int> &pairs, int depth, int size);
        bool compare(int a, int b);
        void pairElements();
        void recursiveSort(std::vector<int>& pairs);
        void mergePairs(std::vector<int>& result, const std::vector<int>& left, const std::vector<int>& right);
        void insertion();
        std::vector<int> generateJacobsthalSequence(int n);
        void insertElement(int element);
        template <typename U>
        int binarySearch(int value, int left, int right, const U& arr);
        std::string getContainerType() const;
};

#endif