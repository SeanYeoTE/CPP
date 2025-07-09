#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include "Brain.hpp"
#include <cstdlib> // For system("clear")
#include <limits>

// Color codes for terminal output
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"

void	waitForUserInput(void)
{
	std::cout << "Press Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int	main(void)
{
	system("clear");
	// Basic Animal tests
	{
		std::cout << std::endl << YELLOW << "=== Testing Basic Animal Functionality ===" << RESET << std::endl;
		// const Animal *meta = new Animal();
		const Animal *j = new Dog();
		const Animal *i = new Cat();

		std::cout << GREEN << "Animal types:" << RESET << std::endl;
		std::cout << "j type: " << j->getType() << std::endl;
		std::cout << "i type: " << i->getType() << std::endl;
		
		std::cout << GREEN << "Animal sounds:" << RESET << std::endl;
		std::cout << "i sound: "; i->makeSound(); // will output the cat sound!
		std::cout << "j sound: "; j->makeSound();
		// std::cout << "meta sound: "; meta->makeSound();

		// delete meta;
		delete j;
		delete i;
	}

	waitForUserInput();
	system("clear");
	// Wrong Animal tests
	{
		std::cout << std::endl << YELLOW << "=== Testing Wrong Animal Functionality ===" << RESET << std::endl;
		const WrongAnimal *test = new WrongAnimal();
		const WrongAnimal *wrong = new WrongCat();
		
		std::cout << GREEN << "Wrong Animal types:" << RESET << std::endl;
		std::cout << "test type: " << test->getType() << std::endl;
		std::cout << "wrong type: " << wrong->getType() << std::endl;
		
		std::cout << GREEN << "Wrong Animal sounds:" << RESET << std::endl;
		std::cout << "test sound: "; test->makeSound();  // will output the WrongAnimal sound!
		std::cout << "wrong sound: "; wrong->makeSound(); // will output the WrongAnimal sound!

		delete test;
		delete wrong;
	}

	waitForUserInput();
	system("clear");
	// Cat Deep Copy tests
	{
		std::cout << std::endl << YELLOW << "=== Testing Cat Deep Copy Functionality ===" << RESET << std::endl;
		
		// Create original cat
		std::cout << GREEN << "Creating original Cat and adding ideas:" << RESET << std::endl;
		Cat *originalCat = new Cat();
		originalCat->addIdea("I want to catch a mouse");
		originalCat->addIdea("I need a nap");
		
		// Create a copy using the copy constructor
		std::cout << GREEN << "Creating a copy Cat using copy constructor:" << RESET << std::endl;
		Cat *copyCat = new Cat(*originalCat);
		
		// Show that both cats have the same ideas
		std::cout << BLUE << "\nOriginal cat's ideas:" << RESET << std::endl;
		std::cout << "Idea 0: " << originalCat->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << originalCat->getIdea(1) << std::endl;
		
		std::cout << BLUE << "\nCopy cat's ideas:" << RESET << std::endl;
		std::cout << "Idea 0: " << copyCat->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << copyCat->getIdea(1) << std::endl;
		
		// Modify the copy's ideas to demonstrate deep copy
		std::cout << GREEN << "\nModifying copy cat's ideas..." << RESET << std::endl;
		copyCat->getBrain()->ideas[0] = "I want to play with yarn"; // Direct access for demonstration
		copyCat->getBrain()->ideas[1] = "I'm hungry";               // Direct access for demonstration
		
		// Show that the original cat's ideas remain unchanged
		std::cout << BLUE << "\nOriginal cat's ideas after modification:" << RESET << std::endl;
		std::cout << "Idea 0: " << originalCat->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << originalCat->getIdea(1) << std::endl;
		
		std::cout << BLUE << "\nCopy cat's ideas after modification:" << RESET << std::endl;
		std::cout << "Idea 0: " << copyCat->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << copyCat->getIdea(1) << std::endl;
		
		// Clean up
		delete originalCat;
		delete copyCat;
	}
	
	waitForUserInput();
	system("clear");
	// Dog Deep Copy tests
	{
		std::cout << std::endl << YELLOW << "=== Testing Dog Deep Copy Functionality ===" << RESET << std::endl;
		
		// Create original dog
		std::cout << GREEN << "Creating original Dog and adding ideas:" << RESET << std::endl;
		Dog *originalDog = new Dog();
		originalDog->addIdea("I want to chase a ball");
		originalDog->addIdea("I need a walk");
		
		// Create a copy using assignment operator
		std::cout << GREEN << "Creating a copy Dog using assignment operator:" << RESET << std::endl;
		Dog *copyDog = new Dog();
		*copyDog = *originalDog;
		
		// Show that both dogs have the same ideas
		std::cout << BLUE << "\nOriginal dog's ideas:" << RESET << std::endl;
		std::cout << "Idea 0: " << originalDog->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << originalDog->getIdea(1) << std::endl;
		
		std::cout << BLUE << "\nCopy dog's ideas:" << RESET << std::endl;
		std::cout << "Idea 0: " << copyDog->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << copyDog->getIdea(1) << std::endl;
		
		// Modify the copy's ideas to demonstrate deep copy
		std::cout << GREEN << "\nModifying copy dog's ideas..." << RESET << std::endl;
		copyDog->getBrain()->ideas[0] = "I want to dig a hole";      // Direct access for demonstration
		copyDog->getBrain()->ideas[1] = "I want to bark at the mailman"; // Direct access for demonstration
		
		// Show that the original dog's ideas remain unchanged
		std::cout << BLUE << "\nOriginal dog's ideas after modification:" << RESET << std::endl;
		std::cout << "Idea 0: " << originalDog->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << originalDog->getIdea(1) << std::endl;
		
		std::cout << BLUE << "\nCopy dog's ideas after modification:" << RESET << std::endl;
		std::cout << "Idea 0: " << copyDog->getIdea(0) << std::endl;
		std::cout << "Idea 1: " << copyDog->getIdea(1) << std::endl;
		
		// Clean up
		delete originalDog;
		delete copyDog;
	}
	
	waitForUserInput();
	system("clear");
	// Array of Animals test
	{
		std::cout << std::endl << YELLOW << "=== Testing Array of Animals ===" << RESET << std::endl;
		
		const int arraySize = 4;
		std::cout << GREEN << "Creating an array of " << arraySize << " animals (half Dogs, half Cats):" << RESET << std::endl;
		
		Animal *animals[arraySize];
		
		// Create half dogs and half cats
		for (int i = 0; i < arraySize; i++) {
			if (i < arraySize / 2) {
				animals[i] = new Dog();
				std::cout << "Created Dog at index " << i << std::endl;
			} else {
				animals[i] = new Cat();
				std::cout << "Created Cat at index " << i << std::endl;
			}
		}
		
		// Make all animals sound
		std::cout << GREEN << "\nMaking all animals sound:" << RESET << std::endl;
		for (int i = 0; i < arraySize; i++) {
			std::cout << "Animal " << i << " (" << animals[i]->getType() << "): ";
			animals[i]->makeSound();
		}
		
		// Clean up
		std::cout << GREEN << "\nDeleting all animals:" << RESET << std::endl;
		for (int i = 0; i < arraySize; i++) {
			std::cout << "Deleting animal " << i << " (" << animals[i]->getType() << ")" << std::endl;
			delete animals[i];
		}
	}
	
	return (0);
}
