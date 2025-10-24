#!/bin/bash

# PmergeMe Testing Script
# Tests the Ford-Johnson sorting algorithm implementation
# with various input sizes and edge cases

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Program name
PROGRAM="./PmergeMe"

# Valgrind settings
USE_VALGRIND=false
VALGRIND_CMD="valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --error-exitcode=42"

# Function to print colored output
print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

print_test() {
    echo -e "${YELLOW}Test: $1${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

# Function to check if program exists
check_program() {
    if [ ! -f "$PROGRAM" ]; then
        print_error "Program $PROGRAM not found. Please compile first with 'make'."
        exit 1
    fi
    
    if [ ! -x "$PROGRAM" ]; then
        print_error "Program $PROGRAM is not executable."
        exit 1
    fi
    
    # Check if valgrind is available when USE_VALGRIND is true
    if [ "$USE_VALGRIND" = true ]; then
        if ! command -v valgrind &> /dev/null; then
            print_error "Valgrind is not installed or not in PATH"
            exit 1
        fi
        echo -e "${YELLOW}Running tests with Valgrind memory checking enabled${NC}"
    fi
}

# Function to verify sorted output
verify_sorted() {
    local output="$1"
    local after_line=$(echo "$output" | grep "After:" | head -1)
    
    if [ -z "$after_line" ]; then
        print_error "No 'After:' line found in output"
        return 1
    fi
    
    # Extract numbers from "After:" line
    local numbers=$(echo "$after_line" | sed 's/After://' | tr -s ' ' | sed 's/^ *//')
    
    if [ -z "$numbers" ]; then
        print_error "No numbers found in 'After:' line"
        return 1
    fi
    
    # Convert to array and check if sorted
    local prev=""
    local is_sorted=true
    
    for num in $numbers; do
        if [ -n "$prev" ] && [ "$num" -lt "$prev" ]; then
            is_sorted=false
            break
        fi
        prev="$num"
    done
    
    if $is_sorted; then
        return 0
    else
        return 1
    fi
}

# Function to run a test
run_test() {
    local test_name="$1"
    local test_input="$2"
    local expect_error="$3"
    
    print_test "$test_name"
    echo "Input: $test_input"
    
    # Choose command based on valgrind setting
    local cmd="$PROGRAM"
    if [ "$USE_VALGRIND" = true ]; then
        cmd="$VALGRIND_CMD $PROGRAM"
    fi
    
    if [ "$expect_error" = "true" ]; then
        # Test should fail
        if $cmd $test_input >/dev/null 2>&1; then
            print_error "Expected error but test passed"
            return 1
        else
            print_success "Correctly failed as expected"
            return 0
        fi
    else
        # Test should succeed
        local output=$($cmd $test_input 2>&1)
        local exit_code=$?
        
        # Check for valgrind memory errors (exit code 42)
        if [ "$USE_VALGRIND" = true ] && [ $exit_code -eq 42 ]; then
            print_error "Valgrind detected memory errors"
            echo "Valgrind output:"
            echo "$output"
            return 1
        fi
        
        if [ $exit_code -ne 0 ]; then
            print_error "Program failed with exit code $exit_code"
            echo "Output: $output"
            return 1
        fi
        
        # Filter out valgrind output for sorting verification
        local program_output="$output"
        if [ "$USE_VALGRIND" = true ]; then
            program_output=$(echo "$output" | grep -v "^==" | grep -v "^--")
        fi
        
        if verify_sorted "$program_output"; then
            print_success "Output is correctly sorted"
            if [ "$USE_VALGRIND" = true ]; then
                echo "Program output:"
                echo "$program_output"
                echo "Memory check: PASSED"
            else
                echo "$program_output"
            fi
            return 0
        else
            print_error "Output is not sorted correctly"
            # echo "Output: $program_output"
            echo "$program_output"
            return 1
        fi
    fi
    echo
}

# Function to run performance test
run_performance_test() {
    local size="$1"
    local test_name="Performance test with $size elements"
    
    print_test "$test_name"
    
    # Generate random numbers
    local numbers=$(shuf -i 1-100000 -n "$size" | tr "\n" " ")
    
    echo "Testing with $size random numbers..."
    
    # Choose command based on valgrind setting
    local cmd="$PROGRAM"
    if [ "$USE_VALGRIND" = true ]; then
        cmd="$VALGRIND_CMD $PROGRAM"
    fi
    
    # Run the test and capture timing
    local start_time=$(date +%s.%N)
    local output=$($cmd $numbers 2>&1)
    local end_time=$(date +%s.%N)
    local exit_code=$?
    
    # Check for valgrind memory errors (exit code 42)
    if [ "$USE_VALGRIND" = true ] && [ $exit_code -eq 42 ]; then
        print_error "Valgrind detected memory errors"
        echo "Valgrind output:"
        echo "$output"
        return 1
    fi
    
    if [ $exit_code -ne 0 ]; then
        print_error "Program failed with exit code $exit_code"
        echo "Output: $output"
        return 1
    fi
    
    # Calculate total runtime
    local runtime=$(echo "$end_time - $start_time" | bc -l)
    
    # Filter out valgrind output for sorting verification
    local program_output="$output"
    if [ "$USE_VALGRIND" = true ]; then
        program_output=$(echo "$output" | grep -v "^==" | grep -v "^--")
    fi
    
    if verify_sorted "$program_output"; then
        print_success "Correctly sorted $size elements"
        printf "Total runtime: %.3f seconds\n" "$runtime"
        
        # Extract timing information from program output
        echo "Program timing information:"
        echo "$program_output" | grep "Time to process"
        
        if [ "$USE_VALGRIND" = true ]; then
            echo "Memory check: PASSED"
        fi
        
        return 0
    else
        print_error "Output is not sorted correctly"
        return 1
    fi
    echo
}

# Main testing function
main() {
    # Check for command line arguments
    while [[ $# -gt 0 ]]; do
        case $1 in
            -v|--valgrind)
                USE_VALGRIND=true
                shift
                ;;
            -h|--help)
                echo "Usage: $0 [OPTIONS]"
                echo "Options:"
                echo "  -v, --valgrind    Run tests with Valgrind memory checking"
                echo "  -h, --help        Show this help message"
                exit 0
                ;;
            *)
                echo "Unknown option: $1"
                echo "Use -h or --help for usage information"
                exit 1
                ;;
        esac
    done
    
    print_header "PmergeMe Test Suite"
    
    # Ask user if they want to use valgrind (only if not already set via command line)
    if [ "$USE_VALGRIND" = false ]; then
        read -p "Run tests with Valgrind memory checking? (y/n): " -n 1 -r
        echo
        if [[ $REPLY =~ ^[Yy]$ ]]; then
            USE_VALGRIND=true
        fi
    fi
    
    # Check if program exists
    check_program
    
    local total_tests=0
    local passed_tests=0
    
    # Phase 1: Basic Edge Cases
    print_header "Phase 1: Edge Cases and Error Handling"
    
    # Test 1: No arguments
    ((total_tests++))
    if run_test "No arguments" "" "true"; then
        ((passed_tests++))
    fi
    
    # Test 2: Single number
    ((total_tests++))
    if run_test "Single number" "42" "false"; then
        ((passed_tests++))
    fi
    
    # Test 3: Two numbers (ascending)
    ((total_tests++))
    if run_test "Two numbers (ascending)" "1 2" "false"; then
        ((passed_tests++))
    fi
    
    # Test 4: Two numbers (descending)
    ((total_tests++))
    if run_test "Two numbers (descending)" "2 1" "false"; then
        ((passed_tests++))
    fi
    
    # Test 5: Negative number (should error)
    ((total_tests++))
    if run_test "Negative number" "1 -2 3" "true"; then
        ((passed_tests++))
    fi
    
    # Test 6: Non-integer input (should error)
    ((total_tests++))
    if run_test "Non-integer input" "1 abc 3" "true"; then
        ((passed_tests++))
    fi
    
    # Phase 2: Small Sequences
    print_header "Phase 2: Small Sequences"
    
    # Test 7: Three numbers
    ((total_tests++))
    if run_test "Three numbers" "3 1 2" "false"; then
        ((passed_tests++))
    fi
    
    # Test 8: Five numbers (from PDF example)
    ((total_tests++))
    if run_test "Five numbers (PDF example)" "3 5 9 7 4" "false"; then
        ((passed_tests++))
    fi
    
    # Test 9: Already sorted sequence
    ((total_tests++))
    if run_test "Already sorted" "1 2 3 4 5 6" "false"; then
        ((passed_tests++))
    fi
    
    # Test 10: Reverse sorted sequence
    ((total_tests++))
    if run_test "Reverse sorted" "6 5 4 3 2 1" "false"; then
        ((passed_tests++))
    fi
    
    # Test 11: Duplicates
    ((total_tests++))
    if run_test "Duplicates" "1 1 2 2 3 3" "false"; then
        ((passed_tests++))
    fi
    
    # Test 12: Large numbers
    ((total_tests++))
    if run_test "Large numbers" "2147483647 1000000 500000 1" "false"; then
        ((passed_tests++))
    fi
    
    # Phase 3: Medium Sequences
    print_header "Phase 3: Medium Sequences"
    
    # Test 13: PDF example sequence
    ((total_tests++))
    if run_test "PDF sequence" "41 67 34 0 69 24 78 58 62 64 5 45 81 27 61" "false"; then
        ((passed_tests++))
    fi
    
    # Test 14: 20 random numbers
    # ((total_tests++))
    # local random_20=$(shuf -i 1-1000 -n 20 | tr "\n" " ")
    # if run_test "20 random numbers" "$random_20" "false"; then
    #     ((passed_tests++))
    # fi
    
    # Test 15: 50 random numbers
    # ((total_tests++))
    # local random_50=$(shuf -i 1-5000 -n 50 | tr "\n" " ")
    # if run_test "50 random numbers" "$random_50" "false"; then
    #     ((passed_tests++))
    # fi
    
    # Phase 4: Performance Tests
    # print_header "Phase 4: Performance Tests"
    
    # # Check if bc is available for timing calculations
    # if ! command -v bc &> /dev/null; then
    #     print_error "bc command not found. Skipping precise timing calculations."
    #     print_error "Install bc with: sudo apt-get install bc"
    # fi
    
    # Performance test sizes
    # local sizes=(100 500 1000 3000 5000)
    
    # for size in "${sizes[@]}"; do
    #     ((total_tests++))
    #     if run_performance_test "$size"; then
    #         ((passed_tests++))
    #     fi
    # done
    
    # Phase 5: Stress Tests (optional, only if previous tests passed)
    # if [ $passed_tests -eq $total_tests ]; then
    #     print_header "Phase 5: Stress Tests"
        
    #     read -p "Run stress tests with very large inputs? (y/n): " -n 1 -r
    #     echo
    #     if [[ $REPLY =~ ^[Yy]$ ]]; then
    #         local stress_sizes=(10000 20000 50000 100000 250000 500000)
            
    #         echo -e "${YELLOW}Warning: Testing with very large inputs (up to 500K elements)${NC}"
    #         echo -e "${YELLOW}This may take several minutes and could reveal stack overflow issues${NC}"
            
    #         for size in "${stress_sizes[@]}"; do
    #             ((total_tests++))
    #             echo -e "${BLUE}Testing with $size elements (this may take a while...)${NC}"
    #             if run_performance_test "$size"; then
    #                 ((passed_tests++))
    #             else
    #                 echo -e "${RED}Failed at $size elements - consider this the limit${NC}"
    #                 break
    #             fi
    #         done
    #     fi
    # fi
    
    # Summary
    print_header "Test Summary"
    echo "Total tests: $total_tests"
    echo "Passed: $passed_tests"
    echo "Failed: $((total_tests - passed_tests))"
    
    if [ $passed_tests -eq $total_tests ]; then
        print_success "All tests passed!"
        exit 0
    else
        print_error "Some tests failed!"
        exit 1
    fi
}

# Run the main function
main "$@"
