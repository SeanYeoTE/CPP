#include "RPN.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Error: Invalid number of arguments." << std::endl;
        return 1;
    }

    RPN rpn(argv[1]);
    try
    {
        std::cout << rpn.calculate() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    return 0;
}