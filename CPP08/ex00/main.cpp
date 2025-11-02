#include "easyfind.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <set>


int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    std::vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));
    std::deque<int> deq(arr, arr + sizeof(arr) / sizeof(arr[0]));
    std::list<int> lst(arr, arr + sizeof(arr) / sizeof(arr[0]));
    std::set<int> st(arr, arr + sizeof(arr) / sizeof(arr[0]));

    

    try
    {
        std::vector<int>::iterator it;
        it = easyfind(vec, 3);
        std::cout << "Found: " << *it << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        std::vector<int>::iterator it;
        it = easyfind(vec, 6);
        std::cout << "Found: " << *it << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }

    try
    {
        std::deque<int>::iterator it;
        it = easyfind(deq, 3);
        std::cout << "Found: " << *it << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
        std::list<int>::iterator it;
        it = easyfind(lst, 5);
        std::cout << "Found: " << *it << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
        std::set<int>::iterator it;
        it = easyfind(st, 1);
        std::cout << "Found: " << *it << std::endl;
    }
    catch (const std::runtime_error &e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}