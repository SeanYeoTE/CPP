#include "Span.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    try {
        std::cout << "=== Basic Test (Original) ===" << std::endl;
        Span sp = Span(5);
        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;

        std::cout << "\n=== Large Scale Test (10,000 numbers) ===" << std::endl;
        
        // Test 1: Sequential numbers (0 to 9999)
        std::cout << "Test 1: Sequential numbers (0 to 9999)" << std::endl;
        Span largeSpan(10000);
        for (int i = 0; i < 10000; ++i) {
            largeSpan.addNumber(i);
        }
        
    
        int shortestSeq = largeSpan.shortestSpan();
        std::cout << "Shortest span: " << shortestSeq << std::endl;
        int longestSeq = largeSpan.longestSpan();
        std::cout << "Longest span: " << longestSeq << std::endl;

        std::cout << "\n=== Test 2: Random numbers ===" << std::endl;
        
        // Test 2: Random numbers (using C++98 compatible random)
        srand(time(NULL));
        
        Span randomSpan(15000);
        
        for (int i = 0; i < 15000; ++i) {
            int randomNum = rand() % 100001 - 50000; // Range: -50000 to 50000
            randomSpan.addNumber(randomNum);
        }
        
        int shortestRand = randomSpan.shortestSpan();
        std::cout << "Shortest span: " << shortestRand << std::endl;
        
        int longestRand = randomSpan.longestSpan();
        std::cout << "Longest span: " << longestRand << std::endl;

        std::cout << "\n=== Test 3: Edge case with duplicates ===" << std::endl;
        
        // Test 3: Many duplicates
        Span duplicateSpan(12000);
        
        // Add 10,000 of the same number
        for (int i = 0; i < 10000; ++i) {
            duplicateSpan.addNumber(42);
        }
        
        // Add some different numbers
        duplicateSpan.addNumber(1);
        duplicateSpan.addNumber(100);

        std::cout << "Shortest span: " << duplicateSpan.shortestSpan() << std::endl;
        std::cout << "Longest span: " << duplicateSpan.longestSpan() << std::endl;

        std::cout << "\n=== Test 4: Capacity limit test ===" << std::endl;
        
        // Test capacity limit
        Span limitSpan(10000);
        for (int i = 0; i < 10000; ++i) {
            limitSpan.addNumber(i * 2);
        }
        
        std::cout << "Successfully added exactly 10,000 numbers" << std::endl;
        
        try {
            limitSpan.addNumber(99999); // This should throw
            std::cout << "ERROR: Should have thrown an exception!" << std::endl;
        } catch (const std::exception &e) {
            std::cout << "Correctly caught capacity exception: " << e.what() << std::endl;
        }

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    // using addRange method
    try {
        std::cout << "\n=== Test 5: Using addRange method ===" << std::endl;
        std::vector<int> nums;
        nums.push_back(5);
        nums.push_back(15);
        nums.push_back(25);
        nums.push_back(35);

        Span span(15); // Span to demonstrate adding multiple numbers in one call
        span.addNumber(10);
        span.addNumber(20);
        span.addNumber(30);
        span.addRange(nums.begin(), nums.end());
        for (int i = 0 ; i < span.size() ; i++)
            std::cout << span[i] << " ";
        std::cout << "Numbers added using addRange." << std::endl;
        std::cout << "Shortest span: " << span.shortestSpan() << std::endl;
        std::cout << "Longest span: " << span.longestSpan() << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Exception in addRange test: " << e.what() << std::endl;
    }
    return 0;
}
