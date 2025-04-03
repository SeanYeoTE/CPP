#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int	main(void)
{
	const Animal *meta = new Animal();
	const Animal *j = new Dog();
	const Animal *i = new Cat();

	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	i->makeSound(); // will output the cat sound!
	j->makeSound();
	meta->makeSound();

	delete meta;
	delete j;
	delete i;

	const WrongAnimal *test = new WrongAnimal();
	const WrongAnimal *wrong = new WrongCat();
	std::cout << test->getType() << " " << std::endl;
	std::cout << wrong->getType() << " " << std::endl;
	test->makeSound();  // will output the WrongAnimal sound!
	wrong->makeSound(); // will output the WrongCat sound!

	delete test;
	delete wrong;
	return (0);
}