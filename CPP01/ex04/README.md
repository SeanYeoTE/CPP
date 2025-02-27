# Sed is for losers - Test Script

This directory contains a C++ program that mimics some of the functionality of the `sed` command. The program takes three parameters:
1. A filename
2. A string to search for (s1)
3. A string to replace with (s2)

It reads the content of the file and creates a new file named `<filename>.replace` with all occurrences of s1 replaced by s2.

## Compilation

To compile the program, run:

```bash
make
```

This will create an executable named `ex04`.

## Usage

```bash
./ex04 <filename> <s1> <s2>
```

Example:
```bash
./ex04 example.txt "hello" "world"
```

This will create a file named `example.txt.replace` with all occurrences of "hello" replaced by "world".

## Testing

A test script is provided to verify the functionality of the program. To run the tests:

```bash
./test.sh
```

The test script will:
1. Create test files with different content
2. Run the executable with various test cases
3. Verify that the output files are created correctly
4. Check that replacements are done correctly
5. Test error handling (e.g., non-existent files, empty strings, etc.)

### Test Cases

The script includes the following test cases:
- Basic string replacement
- Replacing with longer strings
- Replacing with shorter strings
- Replacing special characters
- Multiline file handling
- Replacing with empty strings
- Overlapping pattern handling
- Error handling:
  - Non-existent files
  - Empty search strings
  - Insufficient arguments
  - Too many arguments

### Memory Leak Testing

The test script also includes Valgrind tests to check for memory leaks and other memory-related issues. If Valgrind is installed on your system, each test case will be run through Valgrind with the following options:

```bash
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose
```

This will detect:
- Memory leaks (both possible and definite)
- Use of uninitialized memory
- Memory access errors
- Invalid frees
- Double frees

If Valgrind is not installed, the script will display a warning and skip the memory leak tests.

To install Valgrind on Ubuntu/Debian:
```bash
sudo apt-get install valgrind
```

After running all tests, the script will ask if you want to clean up the test files.
