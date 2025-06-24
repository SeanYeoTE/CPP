#include "Span.hpp"

int main() {
    try {
        Span sp = Span(5);
        sp.addnumber(6);
        sp.addnumber(3);
        sp.addnumber(17);
        sp.addnumber(9);
        sp.addnumber(11);

        std::cout << "Shortest span: " << sp.shortestSpan() << std::endl;
        std::cout << "Longest span: " << sp.longestSpan() << std::endl;

        // Uncommenting the next line will throw an exception
        sp.addnumber(12); // This will throw an exception as the capacity is reached

    } catch (const std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}