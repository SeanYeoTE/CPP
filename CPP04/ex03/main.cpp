#include "AMateria.hpp"
#include "Character.hpp"
#include "Cure.hpp"
#include "ICharacter.hpp"
#include "IMateriaSource.hpp"
#include "Ice.hpp"
#include "MateriaSource.hpp"
#include <iostream>
#include <string>
#include <limits>
#include <cstdlib> // for system("clear")
#include <iomanip> // for std::setw

// Color definitions
#define RESET   "\033[0m"
#define RED     "\033[31m"      // Errors and invalid operations
#define GREEN   "\033[32m"      // Actions and operations
#define YELLOW  "\033[33m"      // Section headers
#define BLUE    "\033[34m"      // Normal output
#define CYAN    "\033[36m"      // Constructors
#define MAGENTA "\033[35m"      // Destructors

void waitForUserInput(void)
{
	std::cout << "Press Enter to continue...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main(void)
{
	system("clear");
	// Basic test from subject
	{
		std::cout << std::endl << YELLOW << "=== BASIC TEST (from subject) ===" << RESET << std::endl;
		
		std::cout << CYAN << "Creating MateriaSource" << RESET << std::endl;
		IMateriaSource *src = new MateriaSource();
		std::cout << GREEN << "Learning Ice materia" << RESET << std::endl;
		src->learnMateria(new Ice());
		std::cout << GREEN << "Learning Cure materia" << RESET << std::endl;
		src->learnMateria(new Cure());

		std::cout << CYAN << "Creating Character 'me'" << RESET << std::endl;
		ICharacter *me = new Character("me");

		AMateria *tmp;
		std::cout << GREEN << "Creating and equipping Ice materia" << RESET << std::endl;
		tmp = src->createMateria("ice");
		me->equip(tmp);
		std::cout << GREEN << "Creating and equipping Cure materia" << RESET << std::endl;
		tmp = src->createMateria("cure");
		me->equip(tmp);

		std::cout << CYAN << "Creating Character 'bob'" << RESET << std::endl;
		ICharacter *bob = new Character("bob");

		std::cout << BLUE << "Using materia at slot 0 on bob" << RESET << std::endl;
		me->use(0, *bob);
		std::cout << BLUE << "Using materia at slot 1 on bob" << RESET << std::endl;
		me->use(1, *bob);

		std::cout << MAGENTA << "Destroying bob" << RESET << std::endl;
		delete bob;
		std::cout << MAGENTA << "Destroying me" << RESET << std::endl;
		delete me;
		std::cout << MAGENTA << "Destroying MateriaSource" << RESET << std::endl;
		delete src;
	} // All objects are destroyed here

	waitForUserInput();
	system("clear");
	// Testing MateriaSource
	{
		std::cout << std::endl << YELLOW << "=== Testing MateriaSource ===" << RESET << std::endl;
		
		std::cout << CYAN << "Creating MateriaSource" << RESET << std::endl;
		MateriaSource *src = new MateriaSource();
		
		// Learn materias
		std::cout << GREEN << "Learning materias:" << RESET << std::endl;
		std::cout << BLUE << "  Learning Ice materia (1/4)" << RESET << std::endl;
		src->learnMateria(new Ice());
		std::cout << BLUE << "  Learning Cure materia (2/4)" << RESET << std::endl;
		src->learnMateria(new Cure());
		std::cout << BLUE << "  Learning Ice materia (3/4)" << RESET << std::endl;
		src->learnMateria(new Ice());
		std::cout << BLUE << "  Learning Cure materia (4/4)" << RESET << std::endl;
		src->learnMateria(new Cure());
		
		// Try to learn more than 4 materias
		std::cout << RED << "Attempting to learn more than 4 materias:" << RESET << std::endl;
		src->learnMateria(new Ice()); // Should print "MateriaSource is full"
		
		std::cout << MAGENTA << "Destroying MateriaSource" << RESET << std::endl;
		delete src;
	} // MateriaSource is destroyed here

	waitForUserInput();
	system("clear");
	// Testing Character Equipment
	{
		std::cout << std::endl << YELLOW << "=== Testing Character Equipment ===" << RESET << std::endl;
		
		std::cout << CYAN << "Creating MateriaSource" << RESET << std::endl;
		MateriaSource *src = new MateriaSource();
		std::cout << BLUE << "Learning Ice and Cure materias" << RESET << std::endl;
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		
		std::cout << CYAN << "Creating Character 'Alice'" << RESET << std::endl;
		Character *alice = new Character("Alice");
		
		// Equip materias
		std::cout << GREEN << "Equipping materias:" << RESET << std::endl;
		std::cout << BLUE << "  Creating Ice materia (m1)" << RESET << std::endl;
		AMateria *m1 = src->createMateria("ice");
		std::cout << BLUE << "  Creating Cure materia (m2)" << RESET << std::endl;
		AMateria *m2 = src->createMateria("cure");
		std::cout << BLUE << "  Creating Ice materia (m3)" << RESET << std::endl;
		AMateria *m3 = src->createMateria("ice");
		std::cout << BLUE << "  Creating Cure materia (m4)" << RESET << std::endl;
		AMateria *m4 = src->createMateria("cure");
		std::cout << BLUE << "  Creating Ice materia (m5) for later use" << RESET << std::endl;
		AMateria *m5 = src->createMateria("ice");
		
		std::cout << BLUE << "  Equipping m1 to slot 0" << RESET << std::endl;
		alice->equip(m1);
		std::cout << BLUE << "  Equipping m2 to slot 1" << RESET << std::endl;
		alice->equip(m2);
		std::cout << BLUE << "  Equipping m3 to slot 2" << RESET << std::endl;
		alice->equip(m3);
		std::cout << BLUE << "  Equipping m4 to slot 3" << RESET << std::endl;
		alice->equip(m4);
		
		// Try to equip more than 4 materias
		std::cout << RED << "Attempting to equip more than 4 materias:" << RESET << std::endl;
		alice->equip(m5); // Should print "Alice's inventory is full"
		
		std::cout << MAGENTA << "Destroying Alice" << RESET << std::endl;
		delete alice;
		std::cout << MAGENTA << "Destroying MateriaSource" << RESET << std::endl;
		delete src;
		std::cout << MAGENTA << "Destroying unequipped materia m5" << RESET << std::endl;
		delete m5; // Need to delete m5 as it wasn't equipped
	} // All objects are destroyed here

	waitForUserInput();
	system("clear");
	// Testing Character Use
	{
		std::cout << std::endl << YELLOW << "=== Testing Character Use ===" << RESET << std::endl;
		
		std::cout << CYAN << "Creating MateriaSource" << RESET << std::endl;
		MateriaSource *src = new MateriaSource();
		std::cout << BLUE << "Learning Ice and Cure materias" << RESET << std::endl;
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		
		std::cout << CYAN << "Creating Character 'Alice'" << RESET << std::endl;
		Character *alice = new Character("Alice");
		std::cout << CYAN << "Creating Character 'Bob'" << RESET << std::endl;
		Character *bob = new Character("Bob");
		
		// Equip materias
		std::cout << BLUE << "Creating and equipping materias" << RESET << std::endl;
		AMateria *m1 = src->createMateria("ice");
		AMateria *m2 = src->createMateria("cure");
		alice->equip(m1);
		alice->equip(m2);
		
		// Test use with valid indices
		std::cout << GREEN << "Using materias with valid indices:" << RESET << std::endl;
		std::cout << BLUE << "  Using Ice materia at slot 0 on Bob" << RESET << std::endl;
		alice->use(0, *bob); // Should use ice
		std::cout << BLUE << "  Using Cure materia at slot 1 on Bob" << RESET << std::endl;
		alice->use(1, *bob); // Should use cure
		
		// Test use with invalid indices
		std::cout << RED << "Using materias with invalid indices:" << RESET << std::endl;
		std::cout << BLUE << "  Attempting to use materia at slot 4 (out of bounds)" << RESET << std::endl;
		alice->use(4, *bob); // Should print "Invalid index"
		std::cout << BLUE << "  Attempting to use materia at slot -1 (out of bounds)" << RESET << std::endl;
		alice->use(-1, *bob); // Should print "Invalid index"
		
		std::cout << MAGENTA << "Destroying Alice" << RESET << std::endl;
		delete alice;
		std::cout << MAGENTA << "Destroying Bob" << RESET << std::endl;
		delete bob;
		std::cout << MAGENTA << "Destroying MateriaSource" << RESET << std::endl;
		delete src;
	} // All objects are destroyed here

	waitForUserInput();
	system("clear");
	// Testing Character Unequip
	{
		std::cout << std::endl << YELLOW << "=== Testing Character Unequip ===" << RESET << std::endl;
		
		std::cout << CYAN << "Creating MateriaSource" << RESET << std::endl;
		MateriaSource *src = new MateriaSource();
		std::cout << BLUE << "Learning Ice and Cure materias" << RESET << std::endl;
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		
		std::cout << CYAN << "Creating Character 'Alice'" << RESET << std::endl;
		Character *alice = new Character("Alice");
		std::cout << CYAN << "Creating Character 'Bob'" << RESET << std::endl;
		Character *bob = new Character("Bob");
		
		// Equip materias
		std::cout << BLUE << "Creating and equipping materias" << RESET << std::endl;
		AMateria *m1 = src->createMateria("ice");
		AMateria *m2 = src->createMateria("cure");
		AMateria *m3 = src->createMateria("ice");
		AMateria *m4 = src->createMateria("cure");
		AMateria *m5 = src->createMateria("ice");
		
		alice->equip(m1);
		alice->equip(m2);
		alice->equip(m3);
		alice->equip(m4);
		
		// Test unequip
		std::cout << GREEN << "Testing unequip:" << RESET << std::endl;
		std::cout << BLUE << "  Using Ice materia at slot 2 before unequipping" << RESET << std::endl;
		alice->use(2, *bob); // Should use ice
		std::cout << BLUE << "  Unequipping materia at slot 2" << RESET << std::endl;
		alice->unequip(2);
		
		std::cout << RED << "Using unequipped slot:" << RESET << std::endl;
		alice->use(2, *bob); // Should print "Alice has no materia in slot 2"
		
		// Now we can equip m5
		std::cout << GREEN << "Equipping new materia in empty slot:" << RESET << std::endl;
		alice->equip(m5);
		std::cout << BLUE << "  Using newly equipped Ice materia at slot 2" << RESET << std::endl;
		alice->use(2, *bob); // Should use ice
		
		std::cout << MAGENTA << "Destroying Alice" << RESET << std::endl;
		delete alice;
		std::cout << MAGENTA << "Destroying Bob" << RESET << std::endl;
		delete bob;
		std::cout << MAGENTA << "Destroying MateriaSource" << RESET << std::endl;
		delete src;
		std::cout << MAGENTA << "Destroying unequipped materia m3" << RESET << std::endl;
		delete m3; // Need to delete m3 as it was unequipped
	} // All objects are destroyed here

	waitForUserInput();
	system("clear");
	// Testing Copy Constructor
	{
		std::cout << std::endl << YELLOW << "=== Testing Copy Constructor ===" << RESET << std::endl;
		
		std::cout << CYAN << "Creating MateriaSource" << RESET << std::endl;
		MateriaSource *src = new MateriaSource();
		std::cout << BLUE << "Learning Ice and Cure materias" << RESET << std::endl;
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		
		std::cout << CYAN << "Creating Character 'Alice'" << RESET << std::endl;
		Character *alice = new Character("Alice");
		std::cout << CYAN << "Creating Character 'Bob'" << RESET << std::endl;
		Character *bob = new Character("Bob");
		
		// Equip materias
		std::cout << BLUE << "Creating and equipping materias for Alice" << RESET << std::endl;
		AMateria *m1 = src->createMateria("ice");
		AMateria *m2 = src->createMateria("cure");
		AMateria *m3 = src->createMateria("ice");
		AMateria *m4 = src->createMateria("cure");
		
		alice->equip(m1);
		alice->equip(m2);
		alice->equip(m3);
		alice->equip(m4);
		
		// Test copy constructor
		std::cout << CYAN << "Creating a copy of Alice using copy constructor" << RESET << std::endl;
		Character *alice_copy = new Character(*alice);
		
		std::cout << GREEN << "Original Alice:" << RESET << std::endl;
		std::cout << BLUE << "  Using materia at slot 0" << RESET << std::endl;
		alice->use(0, *bob);
		std::cout << BLUE << "  Using materia at slot 1" << RESET << std::endl;
		alice->use(1, *bob);
		std::cout << BLUE << "  Using materia at slot 2" << RESET << std::endl;
		alice->use(2, *bob);
		std::cout << BLUE << "  Using materia at slot 3" << RESET << std::endl;
		alice->use(3, *bob);
		
		std::cout << GREEN << "Copied Alice:" << RESET << std::endl;
		std::cout << BLUE << "  Using materia at slot 0" << RESET << std::endl;
		alice_copy->use(0, *bob);
		std::cout << BLUE << "  Using materia at slot 1" << RESET << std::endl;
		alice_copy->use(1, *bob);
		std::cout << BLUE << "  Using materia at slot 2" << RESET << std::endl;
		alice_copy->use(2, *bob);
		std::cout << BLUE << "  Using materia at slot 3" << RESET << std::endl;
		alice_copy->use(3, *bob);
		
		std::cout << MAGENTA << "Destroying Alice" << RESET << std::endl;
		delete alice;
		std::cout << MAGENTA << "Destroying Alice copy" << RESET << std::endl;
		delete alice_copy;
		std::cout << MAGENTA << "Destroying Bob" << RESET << std::endl;
		delete bob;
		std::cout << MAGENTA << "Destroying MateriaSource" << RESET << std::endl;
		delete src;
	} // All objects are destroyed here

	waitForUserInput();
	system("clear");
	// Testing Assignment Operator
	{
		std::cout << std::endl << YELLOW << "=== Testing Assignment Operator ===" << RESET << std::endl;
		
		std::cout << CYAN << "Creating MateriaSource" << RESET << std::endl;
		MateriaSource *src = new MateriaSource();
		std::cout << BLUE << "Learning Ice and Cure materias" << RESET << std::endl;
		src->learnMateria(new Ice());
		src->learnMateria(new Cure());
		
		std::cout << CYAN << "Creating Character 'Alice'" << RESET << std::endl;
		Character *alice = new Character("Alice");
		std::cout << CYAN << "Creating Character 'Bob'" << RESET << std::endl;
		Character *bob = new Character("Bob");
		std::cout << CYAN << "Creating Character 'Charlie'" << RESET << std::endl;
		Character *charlie = new Character("Charlie");
		
		// Equip materias
		std::cout << BLUE << "Creating and equipping materias for Alice" << RESET << std::endl;
		AMateria *m1 = src->createMateria("ice");
		AMateria *m2 = src->createMateria("cure");
		
		alice->equip(m1);
		alice->equip(m2);
		
		// Test assignment operator
		std::cout << GREEN << "Assigning Alice to Charlie using assignment operator" << RESET << std::endl;
		*charlie = *alice;
		
		std::cout << GREEN << "Original Alice:" << RESET << std::endl;
		std::cout << BLUE << "  Using materia at slot 0" << RESET << std::endl;
		alice->use(0, *bob);
		std::cout << BLUE << "  Using materia at slot 1" << RESET << std::endl;
		alice->use(1, *bob);
		
		std::cout << GREEN << "Assigned Charlie:" << RESET << std::endl;
		std::cout << BLUE << "  Using materia at slot 0" << RESET << std::endl;
		charlie->use(0, *bob);
		std::cout << BLUE << "  Using materia at slot 1" << RESET << std::endl;
		charlie->use(1, *bob);
		
		std::cout << MAGENTA << "Destroying Alice" << RESET << std::endl;
		delete alice;
		std::cout << MAGENTA << "Destroying Bob" << RESET << std::endl;
		delete bob;
		std::cout << MAGENTA << "Destroying Charlie" << RESET << std::endl;
		delete charlie;
		std::cout << MAGENTA << "Destroying MateriaSource" << RESET << std::endl;
		delete src;
	} // All objects are destroyed here

	return 0;
}
