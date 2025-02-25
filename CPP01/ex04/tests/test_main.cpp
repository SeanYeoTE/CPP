#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Declare the function we're testing from replace.cpp
extern int replace_main(int argc, char **argv);

// Helper function to create a test file with content
void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename.c_str());
    file << content;
    file.close();
}

// Helper function to read file content
std::string readFileContent(const std::string& filename) {
    std::ifstream file(filename.c_str());
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Helper function to run a test and report result
void runTest(const std::string& testName, bool condition) {
    std::cout << testName << ": " << (condition ? "PASS" : "FAIL") << std::endl;
}

// Function to run all tests
int run_tests() {
    std::cout << "Running tests...\n" << std::endl;
    
    int failed_tests = 0;

    // Test 1: Invalid Arguments
    {
        char* argv[] = {(char*)"./ex04"};
        int result = replace_main(1, argv);
        if (result != 1) {
            std::cout << "FAIL: Invalid Arguments Test" << std::endl;
            failed_tests++;
        } else {
            std::cout << "PASS: Invalid Arguments Test" << std::endl;
        }
    }

    // Test 2: File Not Found
    {
        char* argv[] = {(char*)"./ex04", (char*)"nonexistent.txt", (char*)"old", (char*)"new"};
        int result = replace_main(4, argv);
        if (result != 1) {
            std::cout << "FAIL: File Not Found Test" << std::endl;
            failed_tests++;
        } else {
            std::cout << "PASS: File Not Found Test" << std::endl;
        }
    }

    // Test 3: Basic Replacement
    {
        createTestFile("test.txt", "Hello World! Hello Universe!");
        char* argv[] = {(char*)"./ex04", (char*)"test.txt", (char*)"Hello", (char*)"Hi"};
        replace_main(4, argv);
        std::string replacedContent = readFileContent("test.txt.replace");
        if (replacedContent != "Hi World! Hi Universe!") {
            std::cout << "FAIL: Basic Replacement Test" << std::endl;
            failed_tests++;
        } else {
            std::cout << "PASS: Basic Replacement Test" << std::endl;
        }
        std::remove("test.txt");
        std::remove("test.txt.replace");
    }

    // Test 4: Empty File
    {
        createTestFile("empty.txt", "");
        char* argv[] = {(char*)"./ex04", (char*)"empty.txt", (char*)"any", (char*)"thing"};
        replace_main(4, argv);
        std::string replacedContent = readFileContent("empty.txt.replace");
        if (replacedContent != "") {
            std::cout << "FAIL: Empty File Test" << std::endl;
            failed_tests++;
        } else {
            std::cout << "PASS: Empty File Test" << std::endl;
        }
        std::remove("empty.txt");
        std::remove("empty.txt.replace");
    }

    // Test 5: No Occurrences
    {
        createTestFile("test.txt", "Hello World!");
        char* argv[] = {(char*)"./ex04", (char*)"test.txt", (char*)"Goodbye", (char*)"Hi"};
        replace_main(4, argv);
        std::string replacedContent = readFileContent("test.txt.replace");
        if (replacedContent != "Hello World!") {
            std::cout << "FAIL: No Occurrences Test" << std::endl;
            failed_tests++;
        } else {
            std::cout << "PASS: No Occurrences Test" << std::endl;
        }
        std::remove("test.txt");
        std::remove("test.txt.replace");
    }

    std::stringstream result;
    result << "\nTests completed. ";
    if (failed_tests == 0) {
        result << "All tests passed!";
    } else {
        result << failed_tests << " tests failed.";
    }
    std::cout << result.str() << std::endl;
    return failed_tests;
}

int main() {
    return run_tests();
}
