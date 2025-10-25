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

    private:
        T _data;
        T _original;
        typename T::value_type _last;
        double _time;
        double _comparisons;
        std::vector<int> _pairs;
        bool _hasOddElement;
        int _oddElement;
        std::vector<int> _oddpair;
        int _size;
        
     
        void printpairs(const std::vector<int> &pairs, int depth, int size);
        bool compare(int a, int b);
        void mergepairs(std::vector<int>& result,
                        const std::vector<int>& left,
                        const std::vector<int>& right);
        void fordJohnsonSort();
        void pairElements();
        void recursiveSort(std::vector<int>& pairs, int depth);
        void insertion(std::vector<int>& pairs, int depth);
        std::vector<int> generateJacobsthalSequence(int n);
        void insertElement(int element);
        template <typename U>
        int binarySearch(int value, int left, int right, const U& arr);
        std::string getContainerType() const;
};

#endif
