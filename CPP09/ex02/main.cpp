#include "PmergeMe.hpp"

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <numbers>" << std::endl;
        return 1;
    }

    try {
        PmergeMe<std::vector<int> > pmergeMe;
        pmergeMe.processInput(argc, argv);

        // PmergeMe<std::deque<int> > pmergeMeDeque;
        // pmergeMeDeque.processInput(argc, argv);

        pmergeMe.displayArray();

        pmergeMe.displayResults();
        // pmergeMeDeque.displayArray();
        // pmergeMeDeque.displayResults();

    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}