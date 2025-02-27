/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seayeo <seayeo@42.sg>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 13:19:17 by seayeo            #+#    #+#             */
/*   Updated: 2025/02/27 14:04:32 by seayeo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>

int input_error_checks(int argc, char **argv)
{
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
    
    

    return 0;
}

int main(int argc, char **argv) {
    if (input_error_checks(argc, argv))
        return 1;
        
    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

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