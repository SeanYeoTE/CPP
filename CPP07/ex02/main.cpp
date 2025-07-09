#include "Array.hpp"

#define MAX_VAL 750

// Custom class for testing
class TestClass {
private:
    int _value;
public:
    TestClass(int val = 0) : _value(val) {}
    int getValue() const { return _value; }
    void setValue(int val) { _value = val; }
    
    bool operator==(const TestClass& other) const {
        return _value == other._value;
    }
};

std::ostream& operator<<(std::ostream& os, const TestClass& obj) {
    os << "TestClass(" << obj.getValue() << ")";
    return os;
}

void testIntArray() {
    std::cout << "\n===== Testing with int arrays =====\n" << std::endl;
    
    // Test default constructor (empty array)
    Array<int> emptyArray;
    std::cout << "Empty array size: " << emptyArray.size() << std::endl;
    
    // Test constructor with size
    Array<int> numbers(5);
    std::cout << "Array with size 5 created. Size: " << numbers.size() << std::endl;
    
    // Test element access and modification
    std::cout << "Initial values:" << std::endl;
    for (size_t i = 0; i < numbers.size(); i++) {
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }
    
    // Modify elements
    for (size_t i = 0; i < numbers.size(); i++) {
        numbers[i] = i * 10;
    }
    
    std::cout << "\nAfter modification:" << std::endl;
    for (size_t i = 0; i < numbers.size(); i++) {
        std::cout << "numbers[" << i << "] = " << numbers[i] << std::endl;
    }
    
    // Test copy constructor
    Array<int> numbersCopy(numbers);
    std::cout << "\nCopy created. Testing if copy is independent:" << std::endl;
    
    // Modify original to see if copy is affected
    numbers[0] = 999;
    
    std::cout << "Original after modification: numbers[0] = " << numbers[0] << std::endl;
    std::cout << "Copy after original was modified: numbersCopy[0] = " << numbersCopy[0] << std::endl;
    
    // Test assignment operator
    Array<int> numbersAssigned;
    numbersAssigned = numbers;
    std::cout << "\nAssignment done. Testing if assigned copy is independent:" << std::endl;
    
    // Modify original to see if assigned copy is affected
    numbers[1] = 888;
    
    std::cout << "Original after modification: numbers[1] = " << numbers[1] << std::endl;
    std::cout << "Assigned copy after original was modified: numbersAssigned[1] = " << numbersAssigned[1] << std::endl;
    
    // Test exception handling
    try {
        std::cout << "\nTrying to access out-of-bounds index..." << std::endl;
        std::cout << numbers[numbers.size()] << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void testStringArray() {
    std::cout << "\n===== Testing with string arrays =====\n" << std::endl;
    
    // Test constructor with size
    Array<std::string> strings(3);
    std::cout << "Array with size 3 created. Size: " << strings.size() << std::endl;
    
    // Test element access and modification
    strings[0] = "Hello";
    strings[1] = "World";
    strings[2] = "!";
    
    std::cout << "After setting values:" << std::endl;
    for (size_t i = 0; i < strings.size(); i++) {
        std::cout << "strings[" << i << "] = " << strings[i] << std::endl;
    }
    
    // Test copy constructor
    Array<std::string> stringsCopy(strings);
    std::cout << "\nCopy created. Testing if copy is independent:" << std::endl;
    
    // Modify original to see if copy is affected
    strings[0] = "Modified";
    
    std::cout << "Original after modification: strings[0] = " << strings[0] << std::endl;
    std::cout << "Copy after original was modified: stringsCopy[0] = " << stringsCopy[0] << std::endl;
}

void testCustomClassArray() {
    std::cout << "\n===== Testing with custom class arrays =====\n" << std::endl;
    
    // Test constructor with size
    Array<TestClass> objects(3);
    std::cout << "Array with size 3 created. Size: " << objects.size() << std::endl;
    
    // Test element access and modification
    objects[0].setValue(10);
    objects[1].setValue(20);
    objects[2].setValue(30);
    
    std::cout << "After setting values:" << std::endl;
    for (size_t i = 0; i < objects.size(); i++) {
        std::cout << "objects[" << i << "] = " << objects[i] << std::endl;
    }
    
    // Test copy constructor
    Array<TestClass> objectsCopy(objects);
    std::cout << "\nCopy created. Testing if copy is independent:" << std::endl;
    
    // Modify original to see if copy is affected
    objects[0].setValue(999);
    
    std::cout << "Original after modification: objects[0] = " << objects[0] << std::endl;
    std::cout << "Copy after original was modified: objectsCopy[0] = " << objectsCopy[0] << std::endl;
}

void testConstArray() {
    std::cout << "\n===== Testing with const arrays =====\n" << std::endl;
    
    // Part 1: Test const reference to an array
    std::cout << "Part 1: Testing const reference to an array" << std::endl;
    
    // Create a non-const array and initialize it
    Array<int> numbers(5);
    for (size_t i = 0; i < numbers.size(); i++) {
        numbers[i] = i * 100;
    }
    
    // Create a const reference to the array
    const Array<int>& constRef = numbers;
    
    // Test accessing elements through the const reference
    std::cout << "Accessing const array elements:" << std::endl;
    for (size_t i = 0; i < constRef.size(); i++) {
        std::cout << "constRef[" << i << "] = " << constRef[i] << std::endl;
    }
    
    // The following line would not compile because constRef is const:
    // constRef[0] = 999; // This would cause a compilation error
    
    // Modify the original array and verify const reference sees changes
    numbers[0] = 999;
    std::cout << "\nAfter modifying original array:" << std::endl;
    std::cout << "numbers[0] = " << numbers[0] << std::endl;
    std::cout << "constRef[0] = " << constRef[0] << std::endl;
    
    // Test exception handling with const array
    try {
        std::cout << "\nTrying to access out-of-bounds index in const array..." << std::endl;
        std::cout << constRef[constRef.size()] << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
    
    // Part 2: Test const array object (not just a const reference)
    std::cout << "\nPart 2: Testing const array object" << std::endl;
    
    // Create and initialize a non-const array
    Array<int> mutableArray(3);
    mutableArray[0] = 111;
    mutableArray[1] = 222;
    mutableArray[2] = 333;
    
    // Create a const array using copy constructor
    const Array<int> constArray(mutableArray);
    
    // The following would not compile because constArray is const:
    // constArray[0] = 999; // This would cause a compilation error
    
    // But we can read from the const array
    std::cout << "Accessing const array object:" << std::endl;
    for (size_t i = 0; i < constArray.size(); i++) {
        std::cout << "constArray[" << i << "] = " << constArray[i] << std::endl;
    }
    
    // Test exception handling with const array object
    try {
        std::cout << "\nTrying to access out-of-bounds index in const array object..." << std::endl;
        std::cout << constArray[constArray.size()] << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
    }
}

void testRandomValues() {
    std::cout << "\n===== Testing with random values =====\n" << std::endl;
    
    const int size = MAX_VAL;
    Array<int> numbers(size);
    int* mirror = new int[size];
    
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    
    // Verify values are still correct
    for (int i = 0; i < size; i++) {
        if (mirror[i] != numbers[i]) {
            std::cerr << "Values don't match at index " << i << std::endl;
            delete[] mirror;
            return;
        }
    }
    
    std::cout << "All " << size << " random values match!" << std::endl;
    
    // Test exception handling
    try {
        numbers[-2] = 0;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught for negative index: " << e.what() << std::endl;
    }
    
    try {
        numbers[size] = 0;
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught for out-of-bounds index: " << e.what() << std::endl;
    }
    
    delete[] mirror;
}

int main(void)
{
    testIntArray();
    testStringArray();
    testCustomClassArray();
    testConstArray();
    testRandomValues();
    
    std::cout << "\nAll tests completed successfully!" << std::endl;
    return 0;
}
