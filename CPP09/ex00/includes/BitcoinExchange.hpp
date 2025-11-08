#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

// #include <cstdlib>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <cctype>
#include <cstdlib>

class BitcoinExchange {
    private:
        std::map<std::string, std::string> _data;

        std::string Trim(const std::string &str);
        bool ValidDate(const std::string &date);
        void ValidateValue(const std::string &value);
        void ProcessLine(const std::string& date, const std::string& value);
        double FindExchangeRate(const std::string& date);


    public:
        BitcoinExchange();
        BitcoinExchange(const BitcoinExchange &other);
        BitcoinExchange &operator=(const BitcoinExchange &other);
        ~BitcoinExchange();

        void Run(const std::string filename);
};

#endif
