#include "GutenbergHashTable.h"
#include <iostream>

int main() {
    GutenbergHashTable table;

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "Testing insertion of two strings with the same hash" << std::endl;
    table.insert("hello", 1);
    table.insert("world", 1);
    table.print();
    std::cout << "---------------------------------------------------" << std::endl;

    return 0;
}
