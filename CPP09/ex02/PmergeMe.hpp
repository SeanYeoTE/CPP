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

        void ProcessInput(int argc, char **argv);
        void DisplayArray() const;
        void FordJohnsonSort();

        // Utility functions moved to utils.hpp
        T GetData() const;
        T GetOriginal() const;
        double GetTime() const;
        long GetComparisons() const;
        void SetData(T data);

    private:
        T _data;
        T _original;
        double _time;
        long _comparisons;
        T _pairs;
        bool _hasOddElement;
        int _oddElement;
        size_t _final_size;
        int _lastelementused;

        bool Compare(int a, int b);
        bool CheckValidIndex(size_t index, size_t size);
        void UpdateBound(T &bounds);
        void PairElements();
        void RecursiveSort(const T &pairs);
        void MergePairs(T &result, const T &left, const T &right);
        void Insertion();
        void MainPendSeperation(T &main_chain, T &pend_chain, T &remain_chain, T &bounds);
        std::vector<int> GenerateJacobsthalSequence(int n);
        void InsertElement(int element);
        void InsertGroupIntoMainChain(T &main_chain, T &pend_chain, size_t groupStartIndex, size_t groupEndIndex, T &bounds);
        void InsertJacobsthalGroups(T &main_chain, T &pend_chain, const std::vector<int>& jacobsthal, size_t num_pend_elements, T &bounds);
        void InsertRemainingGroups(T &main_chain, T &pend_chain, T &bounds);
        template <typename U>
        int BinarySearch(int value, int left, int right, const U& arr);
        template <typename U>
        int BinarySearchWithBound(int value, int right, const U& arr, bool hasbond);
        std::string GetContainerType() const;
};

#endif
