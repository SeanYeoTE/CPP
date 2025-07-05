#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <ctime>

template <typename T>
class PmergeMe {
    public:
        PmergeMe();
        ~PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);

        void processInput(int argc, char **argv);
        void displayResults() const;

    private:
        T _data;
        T _original;
        typename T::value_type _last;
        double _time;
        struct ComparePairsBySecond {
            bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const;
        };
        
        }
};

#endif
