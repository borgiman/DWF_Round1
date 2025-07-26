#include "GutenbergHashTable.h"
#include <iostream>

int main() {
    GutenbergHashTable table;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Testing insertion of two strings with the same hash" << std::endl;
    table.insert("hello", 1);
    table.insert("world", 2);
    table.print();
    std::cout << "---------------------------------------------------" << std::endl;

    std::cout << "------------------------------" << std::endl;
    std::cout << "Testing get_first and get_last" << std::endl;
    std::cout << "get_first() expected: hello, actual: " << table.get_first().first << std::endl;
    std::cout << "get_last() expected: world, actual: " << table.get_last().first << std::endl;
    std::cout << "Updating hello..." << std::endl;
    table.insert("hello", 42);
    std::cout << "get_first() expected: hello, actual: " << table.get_first().first << std::endl;
    std::cout << "get_last() expected: hello, actual: " << table.get_last().first << std::endl;
    table.print();
    std::cout << "------------------------------" << std::endl;

    return 0;
}
