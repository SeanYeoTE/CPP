#!/bin/bash

# PmergeMe Iterative Testing Script
# Tests the Ford-Johnson sorting algorithm implementation
# with user-specified input sizes and iteration counts

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m' # No Color

# Program name
PROGRAM="./PmergeMe"

# Function to print colored output
print_header() {
    echo -e "${BLUE}========================================${NC}"
    echo -e "${BLUE}$1${NC}"
    echo -e "${BLUE}========================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${CYAN}$1${NC}"
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
}

# Function to extract timing from program output
extract_timing() {
    local output="$1"
    local time_line=$(echo "$output" | grep "Time to process")
    if [ -z "$time_line" ]; then
        echo "0"
        return 1
    fi

    # Extract the time value (assuming format: "Time to process a range of X elements with std::vector : Y us")
    local time_value=$(echo "$time_line" | sed 's/.*: \([0-9.]*\) us/\1/')
    echo "$time_value"
}

# Function to extract comparisons from program output
extract_comparisons() {
    local output="$1"
    local comp_line=$(echo "$output" | grep "Total comparisons:")
    if [ -z "$comp_line" ]; then
        echo "0"
        return 1
    fi

    # Extract the comparison count
    local comp_value=$(echo "$comp_line" | sed 's/Total comparisons: \([0-9]*\)/\1/')
    echo "$comp_value"
}

# Function to verify sorted output
verify_sorted() {
    local output="$1"
    # Strip ANSI color codes first
    local clean_output=$(echo "$output" | sed 's/\x1b\[[0-9;]*m//g')
    local after_line=$(echo "$clean_output" | grep "After :" | head -1)

    if [ -z "$after_line" ]; then
        return 1
    fi

    # Extract numbers from "After :" line
    local numbers=$(echo "$after_line" | sed 's/After : *//' | tr -s ' ' | sed 's/^ *//')

    if [ -z "$numbers" ]; then
        return 1
    fi

    # Convert to array and check if sorted
    local prev=""
    local is_sorted=true
    local num_array=($numbers)

    for num in "${num_array[@]}"; do
        # Skip empty strings and non-numeric values
        if [ -z "$num" ] || ! [[ $num =~ ^[0-9]+$ ]]; then
            continue
        fi
        if [ -n "$prev" ] && [ "$num" -lt "$prev" ]; then
            is_sorted=false
            break
        fi
        prev="$num"
    done

    $is_sorted
}

# Function to calculate theoretical maximum comparisons F(n)
# F(n) = sum_{k=1 to n} ceil(log2((3/4)*k))
calculate_max_comparisons() {
    local n="$1"
    local sum=0

    for ((k=1; k<=n; k++)); do
        # Calculate (3/4)*k
        local value=$(echo "scale=10; (3.0 / 4.0) * $k" | bc -l 2>/dev/null)
        # Calculate log2(value)
        local log_value=$(echo "scale=10; l($value)/l(2)" | bc -l 2>/dev/null)
        # Calculate ceil(log2(value))
        local ceil_log=$(echo "scale=0; ($log_value + 0.999999) / 1" | bc 2>/dev/null)
        # Add to sum
        sum=$((sum + ceil_log))
    done

    echo "$sum"
}

# Function to run iterative tests for a specific size
run_iterative_test() {
    local size="$1"
    local iterations="$2"
    local mode="$3"

    print_info "Testing with input size: $size elements ($iterations iterations)"

    local total_time=0
    local total_comparisons=0
    local successful_runs=0
    local min_time=""
    local max_time=""
    local min_comp=""
    local max_comp=""

    for ((i=1; i<=iterations; i++)); do
        echo -ne "${YELLOW}  Iteration $i/$iterations...${NC}\r"

        # Generate unique random numbers for this iteration
        # Use a large enough range to ensure uniqueness
        local range_end=$((size * 100))
        if [ $range_end -lt 1000 ]; then
            range_end=1000
        fi
        local numbers=$(shuf -i 1-$range_end | head -n "$size" | tr "\n" " ")

        # Run the program
        local output=$($PROGRAM $numbers 2>&1)
        local exit_code=$?

        if [ $exit_code -ne 0 ]; then
            echo -e "\n${RED}    Iteration $i failed with exit code $exit_code${NC}"
            echo "    Program output: $output"
            continue
        fi

        # Verify the output is sorted
        if ! verify_sorted "$output"; then
            echo -e "\n${RED}    Iteration $i produced unsorted output${NC}"
            # For single test mode, show detailed debugging info when unsorted
            if [ "$mode" = "2" ]; then
                echo -e "${CYAN}Input: $numbers${NC}"

                # Calculate expected sorted output
                local expected_sorted=$(echo "$numbers" | tr ' ' '\n' | sort -n | tr '\n' ' ' | sed 's/ $//')
                echo -e "${CYAN}Expected: $expected_sorted${NC}"

                echo -e "${YELLOW}Program output:${NC}"
                echo "$output"

                # Strip ANSI color codes and extract the After line
                local actual_output=$(echo "$output" | sed 's/\x1b\[[0-9;]*m//g' | grep "After :" | head -1 | sed 's/After : *//' | sed 's/^ *//' | sed 's/ *$//')

                # Normalize whitespace - compress multiple spaces to single spaces
                actual_output=$(echo "$actual_output" | tr -s ' ' | sed 's/^ *//' | sed 's/ *$//')
                expected_sorted=$(echo "$expected_sorted" | tr -s ' ' | sed 's/^ *//' | sed 's/ *$//')

                echo -e "${GREEN}Comparison:${NC}"
                echo "Expected: '$expected_sorted'"
                echo "Actual:   '$actual_output'"

                # Simple string comparison
                if [ "$expected_sorted" = "$actual_output" ]; then
                    echo -e "${GREEN}✓ Output matches expected result!${NC}"
                else
                    echo -e "${RED}✗ Output does not match expected result${NC}"

                    # Show debugging info
                    local expected_len=$(echo -n "$expected_sorted" | wc -c)
                    local actual_len=$(echo -n "$actual_output" | wc -c)
                    echo "Expected length: $expected_len, Actual length: $actual_len"

                    # Show hex dump for debugging
                    echo "Expected hex: $(echo -n "$expected_sorted" | hexdump -C | head -1)"
                    echo "Actual hex:   $(echo -n "$actual_output" | hexdump -C | head -1)"
                fi
                echo
            else
                echo "    Program output: $output"
            fi
            continue
        fi

        # For single test mode, if sorted successfully, don't print anything extra
        # Just continue with the statistics collection

        # Extract timing and comparison data
        local time_value=$(extract_timing "$output")
        local comp_value=$(extract_comparisons "$output")

        if [ "$time_value" = "0" ] || [ "$comp_value" = "0" ]; then
            echo -e "\n${RED}    Iteration $i failed to extract metrics${NC}"
            continue
        fi

        # Update statistics
        total_time=$(echo "$total_time + $time_value" | bc -l 2>/dev/null || echo "$total_time")
        total_comparisons=$(echo "$total_comparisons + $comp_value" | bc 2>/dev/null || echo "$total_comparisons")
        ((successful_runs++))

        # Update min/max times
        if [ -z "$min_time" ] || [ "$(echo "$time_value < $min_time" | bc -l 2>/dev/null)" = "1" ]; then
            min_time=$time_value
        fi
        if [ -z "$max_time" ] || [ "$(echo "$time_value > $max_time" | bc -l 2>/dev/null)" = "1" ]; then
            max_time=$time_value
        fi

        # Update min/max comparisons
        if [ -z "$min_comp" ] || { [[ $comp_value =~ ^[0-9]+$ ]] && [ "$comp_value" -lt "$min_comp" ] 2>/dev/null; }; then
            min_comp=$comp_value
        fi
        if [ -z "$max_comp" ] || { [[ $comp_value =~ ^[0-9]+$ ]] && [ "$comp_value" -gt "$max_comp" ] 2>/dev/null; }; then
            max_comp=$comp_value
        fi
    done

    echo -e "\n${GREEN}  Results for $size elements:${NC}"
    echo "    Successful runs: $successful_runs/$iterations"
    echo -n "    Success rate: "
    printf "%.1f%%\n" $(echo "scale=1; $successful_runs * 100 / $iterations" | bc -l 2>/dev/null || echo "0")

    if [ $successful_runs -gt 0 ]; then
        local avg_time=$(echo "scale=2; $total_time / $successful_runs" | bc -l 2>/dev/null || echo "0")
        local avg_comp=$(echo "scale=0; $total_comparisons / $successful_runs" | bc 2>/dev/null || echo "0")

        # Calculate theoretical maximum comparisons
        local theoretical_max=$(calculate_max_comparisons "$size" | tr -d ' \n\t')

        echo "    Average time: $avg_time μs"
        echo "    Min/Max time: $min_time / $max_time μs"
        echo "    Average comparisons: $avg_comp"
        echo "    Min/Max comparisons: $min_comp / $max_comp"
        echo "    Theoretical max comparisons: $theoretical_max"

        # Check if average comparisons exceed theoretical maximum
        if [[ $theoretical_max =~ ^[0-9]+$ ]] && [ "$avg_comp" -gt "$theoretical_max" ] 2>/dev/null; then
            echo -e "    ${RED}WARNING: Average comparisons ($avg_comp) exceed theoretical maximum ($theoretical_max)!${NC}"
        else
            echo -e "    ${GREEN}✓ Comparisons within theoretical bounds${NC}"
        fi
    else
        echo "    No successful runs to calculate averages"
    fi

    echo

    # Return success if all iterations passed, failure otherwise
    [ $successful_runs -eq $iterations ]
}

# Main function
main() {
    print_header "PmergeMe Iterative Testing Script"

    # Check if program exists
    check_program

    # Check if bc is available
    if ! command -v bc &> /dev/null; then
        print_error "bc command not found. This script requires bc for calculations."
        print_error "Install bc with: sudo apt-get install bc"
        exit 1
    fi

    # Choose testing mode
    echo -e "${CYAN}Choose testing mode:${NC}"
    echo "1. Test sizes from 2 to a maximum size"
    echo "2. Test only a single specific size"
    echo -e "${CYAN}Enter your choice (1 or 2):${NC}"
    read -r mode_choice

    case $mode_choice in
        1)
            # Get user input for maximum test size
            echo -e "${CYAN}Enter the maximum input size to test:${NC}"
            read -r max_size_input

            # Validate maximum size
            if ! [[ $max_size_input =~ ^[0-9]+$ ]] || [ "$max_size_input" -lt 2 ]; then
                print_error "Invalid maximum size: $max_size_input (must be an integer >= 2)"
                exit 1
            fi

            local max_size="$max_size_input"

            # Generate sizes from 2 to max_size
            local valid_sizes=()
            for ((size=2; size<=max_size; size++)); do
                valid_sizes+=("$size")
            done
            ;;
        2)
            # Get user input for single test size
            echo -e "${CYAN}Enter the input size to test:${NC}"
            read -r single_size_input

            # Validate single size
            if ! [[ $single_size_input =~ ^[0-9]+$ ]] || [ "$single_size_input" -lt 1 ]; then
                print_error "Invalid size: $single_size_input (must be an integer >= 1)"
                exit 1
            fi

            local valid_sizes=("$single_size_input")
            ;;
        *)
            print_error "Invalid choice. Please enter 1 or 2."
            exit 1
            ;;
    esac

    # Set iterations based on mode
    local iterations=20
    if [ "$mode_choice" = "2" ]; then
        iterations=1  # Single iteration for individual testing
    fi

    # Confirm test parameters
    echo -e "${YELLOW}Test Configuration:${NC}"
    echo "  Sizes to test: ${valid_sizes[*]}"
    echo "  Iterations per size: $iterations"
    local total_tests=$((${#valid_sizes[@]} * iterations))
    echo "  Total test runs: $total_tests"

    echo -e "${CYAN}Start testing? (y/n):${NC}"
    read -n 1 -r
    echo
    if [[ ! $REPLY =~ ^[Yy]$ ]]; then
        print_info "Testing cancelled."
        exit 0
    fi

    # Run the tests
    print_header "Running Iterative Tests"

    local start_time=$(date +%s)
    local failed_sizes=()

    for size in "${valid_sizes[@]}"; do
        # Capture the return value from run_iterative_test to check if it was successful
        if ! run_iterative_test "$size" "$iterations" "$mode_choice"; then
            failed_sizes+=("$size")
        fi
    done

    local end_time=$(date +%s)
    local total_duration=$((end_time - start_time))

    # Summary
    print_header "Testing Complete"
    echo -e "${GREEN}Total testing time: $total_duration seconds${NC}"
    echo -e "${GREEN}Tested sizes: ${valid_sizes[*]}${NC}"
    echo -e "${GREEN}Iterations per size: $iterations${NC}"
    echo -e "${GREEN}Total test runs: $total_tests${NC}"

    # Report failed sizes
    if [ ${#failed_sizes[@]} -gt 0 ]; then
        echo -e "${RED}Sizes that did not achieve 100% success rate ($iterations/$iterations):${NC}"
        for size in "${failed_sizes[@]}"; do
            echo -e "${RED}  - Size $size${NC}"
        done
    else
        echo -e "${GREEN}All sizes achieved 100% success rate!${NC}"
    fi

    print_success "Iterative testing completed successfully!"
}

# Run the main function
main "$@"
