#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <climits>

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
        std::vector<std::pair<int, int> > _pairs;
        bool _hasOddElement;
        int _oddElement;
        
        struct ComparePairsBySecond {
            bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const;
        };
        
    
        void fordJohnsonSort();
        void pairing();
        void recursiveSort(std::vector<std::pair<int, int> > &pairs);
        void mergeSequences(std::vector<std::pair<int, int> > &result, 
                           const std::vector<std::pair<int, int> > &left,
                           const std::vector<std::pair<int, int> > &right);
        std::vector<int> extractSmallerElements() const;
        void insertRemainingElements(const std::vector<int> &smaller);
        int binarySearch(int value, int left, int right);
        std::vector<int> generateJacobsthalSequence(int n);
        void insertElement(int element);
        std::string getContainerType() const;
};

#endif
