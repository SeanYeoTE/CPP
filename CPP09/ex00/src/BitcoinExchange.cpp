#include "../includes/BitcoinExchange.hpp"


BitcoinExchange::BitcoinExchange() {
    std::ifstream file("data.csv");
    std::string line;

    std::getline(file, line);
    while (std::getline(file, line))
    {
        size_t delimiter = line.find(',');
        std::string date = trim(line.substr(0, delimiter));
        std::string value = trim(line.substr(delimiter + 1, line.length()));

        _data[date] = value;
    }
    file.close();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
    *this = other;
}

BitcoinExchange &BitcoinExchange::operator= (const BitcoinExchange &other)
{
    if (this != &other)
    {
        _data = other._data;
    }
    return *this;
}

BitcoinExchange::~BitcoinExchange() {}


std::string BitcoinExchange::trim(const std::string &str)
{
    size_t first = str.find_first_not_of(' ');
    if (std::string::npos == first)
        return str;
    
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}
bool BitcoinExchange::valid_date(const std::string &date)
{
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;
    
}

void BitcoinExchange::valuechecks(std::string date, std::string value)
{
    try {
        if (!valid_date(date))
            throw std::invalid_argument("invalid date: " + date);
        if (value.empty())
            throw std::invalid_argument("invalid value: " + value);
        validate_value();
    }
    catch (std::exception &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
}

void BitcoinExchange::run(const std::string filename)
{
    // check file;
    // file exists?
    // file cna open 
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open())
    {
        std::cout << "Error: file does not exist" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (file.peek() == std::ifstream::traits_type::eof())
    {
        std::cout << "Error: file is empty" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::getline(file, line);
    if (line != "date | value") {
        std::cout << "Error: invalid file format" << std::endl;
        exit(1);
    }

    // read loop here
    while (std::getline(file, line))
    {
        size_t delimiter = line.find('|');
        if (delimiter == std::string::npos) {
            std::cout << "Error: bad input => " << line << std::endl; 
            continue;
        }
        std::string date = trim(line.substr(0, delimiter));
        std::string value = trim(line.substr(delimiter + 1));
    }

}

