#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template <typename T>
typename T::iterator easyfind(T &container, int value)
{
    typename T::iterator it = container.begin();
    it = std::find(it, container.end(), value);
    if (it == container.end())
    {
        throw std::runtime_error("Value not found");
    }
    return it;
}

#endif