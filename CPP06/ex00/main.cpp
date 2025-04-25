#include "scalar.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		std::cout << "only 1 argument allowed" << std::endl;
		return (1);
	}
	try
	{
		ScalarConverter::convert(argv[1]);
		ScalarConverter::display();
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return (0);
}
