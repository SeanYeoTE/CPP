// Implementation of the string replacement program
#include <iostream>
#include <fstream>
#include <string>

int replace_main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Error: Invalid arguments" << std::endl;
        return 1;
    }
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    if (s1.empty()) {
        std::cout << "Error: Search string cannot be empty" << std::endl;
        return 1;
    }
    
    std::ifstream infile(filename.c_str());
    if (!infile) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }

    std::string outfilename = filename + ".replace";
    std::ofstream outfile(outfilename.c_str());
    if (!outfile) {
        std::cerr << "Error: Could not create output file " << outfilename << std::endl;
        return 1;
    }

    std::string line;
    while (std::getline(infile, line)) {
        size_t pos = 0;
        while ((pos = line.find(s1, pos)) != std::string::npos) {
            line = line.substr(0, pos) + s2 + line.substr(pos + s1.length());
            pos += s2.length();
        }
        outfile << line;
        if (!infile.eof()) outfile << '\n';
    }

    return 0;
}
