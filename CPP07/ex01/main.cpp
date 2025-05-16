#include "iter.hpp"

int main()
{
    int arr[] = {1, 2, 3, 4, 5};
    std::string strArr[] = {"Hello", "World", "!"};

    // Test with int array
    iter(arr, 5, printElement);

    // Test with string array
    iter(strArr, 3, printElement);

    return 0;
}