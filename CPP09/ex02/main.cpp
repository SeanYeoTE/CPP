#include "PmergeMe.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <numbers>" << std::endl;
    return 1;
  }

  try {
    PmergeMe<std::vector<int> > pmergeMe;
    pmergeMe.ProcessInput(argc, argv);

    PmergeMe<std::deque<int> > pmergeMeDeque;
    pmergeMeDeque.ProcessInput(argc, argv);

    DisplayArray(pmergeMe.GetOriginal(), pmergeMe.GetData());

    DisplayResults(pmergeMe.GetOriginal(), pmergeMe.GetTime(),
                   pmergeMe.GetComparisons(), "vector");

    // DisplayArray(pmergeMeDeque.GetOriginal(), pmergeMeDeque.GetData());
    DisplayResults(pmergeMeDeque.GetOriginal(), pmergeMeDeque.GetTime(),
                   pmergeMeDeque.GetComparisons(), "deque");
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
