#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Check if valgrind is installed
VALGRIND_INSTALLED=0
if command -v valgrind &> /dev/null; then
    VALGRIND_INSTALLED=1
else
    echo -e "${YELLOW}Warning: Valgrind is not installed. Memory leak tests will be skipped.${NC}"
    echo -e "${YELLOW}To install Valgrind, run: sudo apt-get install valgrind${NC}"
    echo ""
fi

# Test directory
TEST_DIR="test_files"
mkdir -p $TEST_DIR

# Executable path
EXE="./ex04"

# Make sure the executable exists
if [ ! -f "$EXE" ]; then
    echo -e "${RED}Error: Executable not found. Run 'make' first.${NC}"
    exit 1
fi

# Function to run a test case
run_test() {
    local test_name="$1"
    local filename="$2"
    local s1="$3"
    local s2="$4"
    local expected_result="$5"
    local expected_exit_code="$6"

    echo -e "${YELLOW}Running test: ${test_name}${NC}"
    
    # Run the program
    $EXE "$filename" "$s1" "$s2"
    local exit_code=$?
    
    # Check exit code
    if [ $exit_code -eq $expected_exit_code ]; then
        if [ $expected_exit_code -eq 0 ]; then
            # Check if output file exists
            if [ -f "${filename}.replace" ]; then
                # Check content if expected result is provided
                if [ -n "$expected_result" ]; then
                    if grep -q "$expected_result" "${filename}.replace"; then
                        echo -e "${GREEN}✓ Test passed: Output contains expected result${NC}"
                    else
                        echo -e "${RED}✗ Test failed: Output does not contain expected result${NC}"
                        echo "Expected to find: $expected_result"
                        echo "Actual content:"
                        cat "${filename}.replace"
                    fi
                else
                    echo -e "${GREEN}✓ Test passed: Output file created${NC}"
                fi
            else
                echo -e "${RED}✗ Test failed: Output file not created${NC}"
            fi
        else
            echo -e "${GREEN}✓ Test passed: Program exited with expected error code${NC}"
        fi
    else
        echo -e "${RED}✗ Test failed: Expected exit code $expected_exit_code, got $exit_code${NC}"
    fi
    
    # Run Valgrind test if installed
    if [ $VALGRIND_INSTALLED -eq 1 ]; then
        run_valgrind_test "$filename" "$s1" "$s2"
    fi
    
    echo ""
}

# Function to run Valgrind test
run_valgrind_test() {
    local filename="$1"
    local s1="$2"
    local s2="$3"
    
    echo -e "${BLUE}Running Valgrind test...${NC}"
    
    # Remove any existing .replace file to ensure clean test
    if [ -f "${filename}.replace" ]; then
        rm "${filename}.replace"
    fi
    
    # Run with Valgrind
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1 $EXE "$filename" "$s1" "$s2" > /dev/null 2> valgrind_output.txt
    local valgrind_exit_code=$?
    
    # Check for memory leaks
    if [ $valgrind_exit_code -eq 0 ]; then
        if grep -q "no leaks are possible" valgrind_output.txt; then
            echo -e "${GREEN}✓ Valgrind test passed: No memory leaks detected${NC}"
        else
            echo -e "${YELLOW}⚠ Valgrind test warning: Potential issues detected${NC}"
            cat valgrind_output.txt
        fi
    else
        echo -e "${RED}✗ Valgrind test failed: Memory leaks or errors detected${NC}"
        cat valgrind_output.txt
    fi
    
    # Clean up
    rm -f valgrind_output.txt
}

# Create test files
echo "Creating test files..."

# Test file 1: Simple text
echo "This is a test file. It contains the word 'test' multiple times. test test test." > $TEST_DIR/test1.txt

# Test file 2: Empty file
touch $TEST_DIR/empty.txt

# Test file 3: File with special characters
echo "Special characters: !@#$%^&*()_+ and some text to replace." > $TEST_DIR/special.txt

# Test file 4: Long file with multiple lines
cat > $TEST_DIR/multiline.txt << EOF
Line 1: This line has the word apple in it.
Line 2: This line has the word banana in it.
Line 3: This line has both apple and banana in it.
Line 4: This line has neither of those words.
Line 5: apple at the beginning of the line.
Line 6: End of line has apple
EOF

# Test file 5: File with overlapping patterns
echo "abababababa" > $TEST_DIR/overlap.txt

echo -e "${GREEN}Test files created in $TEST_DIR directory${NC}"
echo ""

# Run tests
echo -e "${YELLOW}Starting tests...${NC}"
echo ""

# Test 1: Basic replacement
run_test "Basic replacement" "$TEST_DIR/test1.txt" "test" "example" "example example example" 0

# Test 2: Replace with longer string
run_test "Replace with longer string" "$TEST_DIR/test1.txt" "test" "verylongexample" "verylongexample verylongexample verylongexample" 0

# Test 3: Replace with shorter string
run_test "Replace with shorter string" "$TEST_DIR/test1.txt" "test" "x" "x x x" 0

# Test 4: Replace special characters
run_test "Replace special characters" "$TEST_DIR/special.txt" "!@#$%^&*()_+" "REPLACED" "Special characters: REPLACED" 0

# Test 5: Replace in multiline file
run_test "Replace in multiline file" "$TEST_DIR/multiline.txt" "apple" "orange" "orange at the beginning of the line" 0

# Test 6: Replace with empty string
run_test "Replace with empty string" "$TEST_DIR/test1.txt" "test" "" "" 0

# Test 7: Replace overlapping patterns
run_test "Replace overlapping patterns" "$TEST_DIR/overlap.txt" "aba" "XYZ" "XYZbXYZbXYZ" 0

# Error tests
echo -e "${YELLOW}Testing error handling...${NC}"
echo ""

# Test 8: Non-existent file
echo -e "${YELLOW}Running test: Non-existent file${NC}"
$EXE "nonexistent.txt" "test" "example"
if [ $? -eq 1 ]; then
    echo -e "${GREEN}✓ Test passed: Program correctly handled non-existent file${NC}"
else
    echo -e "${RED}✗ Test failed: Program did not handle non-existent file correctly${NC}"
fi

# Run Valgrind test for non-existent file
if [ $VALGRIND_INSTALLED -eq 1 ]; then
    echo -e "${BLUE}Running Valgrind test for non-existent file...${NC}"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=2 $EXE "nonexistent.txt" "test" "example" > /dev/null 2> valgrind_output.txt
    valgrind_exit_code=$?
    
    # For error cases, we expect the program to exit with code 1, but we still want to check for memory leaks
    if grep -q "no leaks are possible" valgrind_output.txt; then
        echo -e "${GREEN}✓ Valgrind test passed: No memory leaks detected${NC}"
    elif grep -q "ERROR SUMMARY: 0 errors" valgrind_output.txt; then
        echo -e "${GREEN}✓ Valgrind test passed: No memory errors detected${NC}"
    else
        echo -e "${RED}✗ Valgrind test failed: Memory issues detected${NC}"
        cat valgrind_output.txt
    fi
    
    rm -f valgrind_output.txt
fi
echo ""

# Test 9: Empty search string
echo -e "${YELLOW}Running test: Empty search string${NC}"
$EXE "$TEST_DIR/test1.txt" "" "example"
if [ $? -eq 1 ]; then
    echo -e "${GREEN}✓ Test passed: Program correctly handled empty search string${NC}"
else
    echo -e "${RED}✗ Test failed: Program did not handle empty search string correctly${NC}"
fi

# Run Valgrind test for empty search string
if [ $VALGRIND_INSTALLED -eq 1 ]; then
    echo -e "${BLUE}Running Valgrind test for empty search string...${NC}"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1 $EXE "$TEST_DIR/test1.txt" "" "example" > /dev/null 2> valgrind_output.txt
    valgrind_exit_code=$?
    
    # For error cases, we expect the program to exit with code 1, but we still want to check for memory leaks
    if grep -q "no leaks are possible" valgrind_output.txt; then
        echo -e "${GREEN}✓ Valgrind test passed: No memory leaks detected${NC}"
    elif grep -q "ERROR SUMMARY: 0 errors" valgrind_output.txt; then
        echo -e "${GREEN}✓ Valgrind test passed: No memory errors detected${NC}"
    else
        echo -e "${RED}✗ Valgrind test failed: Memory issues detected${NC}"
        cat valgrind_output.txt
    fi
    
    rm -f valgrind_output.txt
fi
echo ""

# Test 10: Insufficient arguments
echo -e "${YELLOW}Running test: Insufficient arguments${NC}"
$EXE "$TEST_DIR/test1.txt" "test"
if [ $? -eq 1 ]; then
    echo -e "${GREEN}✓ Test passed: Program correctly handled insufficient arguments${NC}"
else
    echo -e "${RED}✗ Test failed: Program did not handle insufficient arguments correctly${NC}"
fi

# Run Valgrind test for insufficient arguments
if [ $VALGRIND_INSTALLED -eq 1 ]; then
    echo -e "${BLUE}Running Valgrind test for insufficient arguments...${NC}"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1 $EXE "$TEST_DIR/test1.txt" "test" > /dev/null 2> valgrind_output.txt
    if [ $? -eq 0 ] || [ $? -eq 1 ]; then  # Accept both 0 and 1 as valid exit codes
        if grep -q "no leaks are possible" valgrind_output.txt; then
            echo -e "${GREEN}✓ Valgrind test passed: No memory leaks detected${NC}"
        else
            echo -e "${YELLOW}⚠ Valgrind test warning: Potential issues detected${NC}"
            cat valgrind_output.txt
        fi
    else
        echo -e "${RED}✗ Valgrind test failed: Memory leaks or errors detected${NC}"
        cat valgrind_output.txt
    fi
    rm -f valgrind_output.txt
fi
echo ""

# Test 11: Too many arguments
echo -e "${YELLOW}Running test: Too many arguments${NC}"
$EXE "$TEST_DIR/test1.txt" "test" "example" "extra"
if [ $? -eq 1 ]; then
    echo -e "${GREEN}✓ Test passed: Program correctly handled too many arguments${NC}"
else
    echo -e "${RED}✗ Test failed: Program did not handle too many arguments correctly${NC}"
fi

# Run Valgrind test for too many arguments
if [ $VALGRIND_INSTALLED -eq 1 ]; then
    echo -e "${BLUE}Running Valgrind test for too many arguments...${NC}"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --error-exitcode=1 $EXE "$TEST_DIR/test1.txt" "test" "example" "extra" > /dev/null 2> valgrind_output.txt
    if [ $? -eq 0 ] || [ $? -eq 1 ]; then  # Accept both 0 and 1 as valid exit codes
        if grep -q "no leaks are possible" valgrind_output.txt; then
            echo -e "${GREEN}✓ Valgrind test passed: No memory leaks detected${NC}"
        else
            echo -e "${YELLOW}⚠ Valgrind test warning: Potential issues detected${NC}"
            cat valgrind_output.txt
        fi
    else
        echo -e "${RED}✗ Valgrind test failed: Memory leaks or errors detected${NC}"
        cat valgrind_output.txt
    fi
    rm -f valgrind_output.txt
fi
echo ""

# Clean up
echo -e "${YELLOW}Tests completed. Do you want to clean up test files? (y/n)${NC}"
read -n 1 -r
echo ""
if [[ $REPLY =~ ^[Yy]$ ]]; then
    rm -rf $TEST_DIR
    echo -e "${GREEN}Test files removed.${NC}"
else
    echo -e "${GREEN}Test files kept in $TEST_DIR directory.${NC}"
fi
