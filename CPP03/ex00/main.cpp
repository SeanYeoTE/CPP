#include "ClapTrap.hpp"
#include <limits>
#include <cstdlib> // For system("clear")

void waitForUserInput()
{
    std::cout << "Press Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
    system("clear");
    std::cout << std::endl
              << YELLOW << "=== Testing base case ===" << RESET << std::endl;
    ClapTrap clapTrap("ClapTrap1");
    clapTrap.attack("target");
    clapTrap.takeDamage(5);
    clapTrap.beRepaired(2);

    waitForUserInput();
    system("clear");
    // more tests
    // Test for 0 energy points behavior
    std::cout << std::endl
              << YELLOW << "=== Testing 0 energy points behavior ===" << RESET << std::endl;
    ClapTrap energyTest("EnergyTest");
    // Perform 10 attacks to drain all energy points
    for (int i = 0; i < 10; i++)
    {
        energyTest.attack("dummy");
    }
    // These should fail due to no energy points
    std::cout << RED << "Attempting actions with 0 energy points:" << RESET << std::endl;
    energyTest.attack("dummy");
    energyTest.beRepaired(5);

    waitForUserInput();
    system("clear");
    // Test for max health points limit
    std::cout << std::endl
              << YELLOW << "=== Testing max health points limit ===" << RESET << std::endl;
    ClapTrap healthTest("HealthTest");
    std::cout << "Initial state, should have 10 hit points" << std::endl;
    // Try to repair for more than max health
    std::cout << GREEN << "Attempting to repair 5 points (should work fully):" << RESET << std::endl;
    healthTest.beRepaired(5);

    // Take some damage
    std::cout << GREEN << "Taking 2 points of damage:" << RESET << std::endl;
    healthTest.takeDamage(2);

    // Try to overheal
    std::cout << GREEN << "Attempting to repair 5 points (should be limited to prevent overheal):" << RESET << std::endl;
    healthTest.beRepaired(5);

    waitForUserInput();
    system("clear");
    // Test canonical form functionality
    std::cout << std::endl
              << YELLOW << "=== Testing Canonical Form Functionality ===" << RESET << std::endl;
    // Test copy constructor
    std::cout << CYAN << "Testing copy constructor:" << RESET << std::endl;
    ClapTrap original("Original");
    original.attack("dummy"); // Reduce energy points to test deep copy
    std::cout << "Original ClapTrap state:" << std::endl
              << original << std::endl;

    ClapTrap copy(original); // Copy constructor
    std::cout << "Copied ClapTrap state:" << std::endl
              << copy << std::endl;

    // Test assignment operator
    std::cout << std::endl
              << CYAN << "Testing assignment operator:" << RESET << std::endl;
    ClapTrap assigned("ToBeAssigned");
    std::cout << "Before assignment:" << std::endl
              << assigned << std::endl;

    assigned = original; // Assignment operator
    std::cout << "After assignment:" << std::endl
              << assigned << std::endl;

    // Test self-assignment
    std::cout << std::endl
              << CYAN << "Testing self-assignment:" << RESET << std::endl;
    assigned = assigned; // Self-assignment should be safe
    std::cout << "After self-assignment:" << std::endl
              << assigned << std::endl;
}
