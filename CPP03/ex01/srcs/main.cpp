#include "../includes/ClapTrap.hpp"
#include "../includes/ScavTrap.hpp"
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
    // Test ClapTrap
    {
        std::cout << std::endl
                  << YELLOW << "=== Testing ClapTrap ===" << RESET << std::endl;
        ClapTrap clapTrap("ClapTrap1");
        clapTrap.attack("target");
        clapTrap.takeDamage(5);
        clapTrap.beRepaired(2);
    } // clapTrap is destroyed here

    waitForUserInput();
    system("clear");
    // Test for max health points limit
    {
        std::cout << std::endl
                  << YELLOW << "=== Testing ClapTrap max health points limit ===" << RESET << std::endl;
        ClapTrap healthTest("HealthTest");
        std::cout << "Initial state, should have 10 hit points" << std::endl;

        // Try to repair for more than max health
        std::cout << GREEN << "Attempting to repair 5 points (should work fully):" << RESET << std::endl;
        healthTest.beRepaired(5);

        // Take some damage
        std::cout << GREEN << "Taking 15 points of damage (should not go below 0):" << RESET << std::endl;
        healthTest.takeDamage(15);
        std::cout << "HealthTest current hit points: " << healthTest.getHitPoints() << std::endl;
    } // healthTest is destroyed here

    waitForUserInput();
    system("clear");
    // Test for 0 hit points behavior
    {
        std::cout << std::endl
                  << YELLOW << "=== Testing ClapTrap 0 hit points behavior ===" << RESET << std::endl;
        ClapTrap healthTest("HealthTest");
        
        // Take damage to reduce hit points to 0
        std::cout << GREEN << "Taking 10 points of damage to reduce hit points to 0:" << RESET << std::endl;
        healthTest.takeDamage(10);
        std::cout << "HealthTest current hit points: " << healthTest.getHitPoints() << std::endl;
        
        // These should fail due to 0 hit points
        std::cout << RED << "Attempting actions with 0 hit points:" << RESET << std::endl;
        healthTest.attack("dummy");
        healthTest.beRepaired(5);
        
        // Test taking additional damage when already at 0 hit points
        std::cout << GREEN << "Taking additional damage when already at 0 hit points:" << RESET << std::endl;
        healthTest.takeDamage(5);
        std::cout << "HealthTest current hit points: " << healthTest.getHitPoints() << std::endl;
    } // healthTest is destroyed here

    waitForUserInput();
    system("clear");
    // Test ScavTrap
    {
        std::cout << std::endl
                  << YELLOW << "=== Testing ScavTrap ===" << RESET << std::endl;
        ScavTrap scavTrap("ScavTrap1");
        scavTrap.attack("target");
        scavTrap.takeDamage(5);
        scavTrap.beRepaired(2);
        scavTrap.guardGate();
    } // scavTrap is destroyed here

    waitForUserInput();
    system("clear");
    // Test for 0 energy points behavior
    {
        std::cout << std::endl
                  << YELLOW << "=== Testing ScavTrap 0 energy points behavior ===" << RESET << std::endl;
        ScavTrap scavEnergyTest("ScavEnergyTest");
        for (int i = 0; i < 50; i++)
        {
            scavEnergyTest.attack("dummy");
        }
        std::cout << RED << "Attempting actions with 0 energy points:" << RESET << std::endl;
        scavEnergyTest.attack("dummy");
        scavEnergyTest.beRepaired(5);
    } // scavEnergyTest is destroyed here

    waitForUserInput();
    system("clear");
    // Test for max health points limit
    {
        std::cout << std::endl
                  << YELLOW << "=== Testing ScavTrap max health points limit ===" << RESET << std::endl;
        ScavTrap scavHealthTest("ScavHealthTest");
        std::cout << "Initial state, should have 100 hit points" << std::endl;

        // Take some damage first
        std::cout << GREEN << "Taking 50 points of damage:" << RESET << std::endl;
        scavHealthTest.takeDamage(50);
        std::cout << "ScavHealthTest current hit points: " << scavHealthTest.getHitPoints() << std::endl;

        // Try to repair
        std::cout << GREEN << "Attempting to repair 30 points:" << RESET << std::endl;
        scavHealthTest.beRepaired(30);
        std::cout << "ScavHealthTest current hit points: " << scavHealthTest.getHitPoints() << std::endl;

        // Take more damage
        std::cout << GREEN << "Taking 100 points of damage (should not go below 0):" << RESET << std::endl;
        scavHealthTest.takeDamage(100);
        std::cout << "ScavHealthTest current hit points: " << scavHealthTest.getHitPoints() << std::endl;
    } // scavHealthTest is destroyed here

    waitForUserInput();
    system("clear");
    // Test for 0 hit points behavior
    {
        std::cout << std::endl
                  << YELLOW << "=== Testing ScavTrap 0 hit points behavior ===" << RESET << std::endl;
        ScavTrap scavHealthTest("ScavHealthTest");
        
        // Take damage to reduce hit points to 0
        std::cout << GREEN << "Taking 100 points of damage to reduce hit points to 0:" << RESET << std::endl;
        scavHealthTest.takeDamage(100);
        std::cout << "ScavHealthTest current hit points: " << scavHealthTest.getHitPoints() << std::endl;
        
        // These should fail due to 0 hit points
        std::cout << RED << "Attempting actions with 0 hit points:" << RESET << std::endl;
        scavHealthTest.attack("dummy");
        scavHealthTest.beRepaired(5);
        scavHealthTest.guardGate();
        
        // Test taking additional damage when already at 0 hit points
        std::cout << GREEN << "Taking additional damage when already at 0 hit points:" << RESET << std::endl;
        scavHealthTest.takeDamage(50);
        std::cout << "ScavHealthTest current hit points: " << scavHealthTest.getHitPoints() << std::endl;
    } // scavHealthTest is destroyed here

    return 0;
}
