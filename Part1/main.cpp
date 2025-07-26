#include "GutenbergHashTable.h"
#include <iostream>

int main() {
    GutenbergHashTable table;

    /**
     * The following code was used to test the hash table
     * On my machine it worked as expected when using a hash table size of 5

    std::cout << "-------------------------------------------------------------------" << std::endl;
    std::cout << "Testing insertion of two strings with the same hash" << std::endl << std::endl;
    table.insert("hello", 1);
    table.insert("world", 2);
    table.print();
    std::cout << "-------------------------------------------------------------------" << std::endl;

    std::cout << "Testing get" << std::endl << std::endl;
    std::cout << "get(\"world\"), expected: 2, actual: " << table.get("world") << std::endl;
    std::cout << "Updating \"world\" to 42..." << std::endl;
    table.insert("world", 42);
    std::cout << "get(\"world\"), expected: 42, actual: " << table.get("world") << std::endl;
    table.print();
    std::cout << "-------------------------------------------------------------------" << std::endl;

    std::cout << "Testing get_first and get_last" << std::endl << std::endl;
    std::cout << "get_first(), expected: hello, actual: " << table.get_first().first << std::endl;
    std::cout << "get_last(), expected: world, actual: " << table.get_last().first << std::endl;
    std::cout << "Updating \"hello\" to 21..." << std::endl;
    table.insert("hello", 21);
    std::cout << "get_first(), expected: hello, actual: " << table.get_first().first << std::endl;
    std::cout << "get_last(), expected: hello, actual: " << table.get_last().first << std::endl;
    table.print();
    std::cout << "-------------------------------------------------------------------" << std::endl;

    std::cout << "Testing remove" << std::endl << std::endl;
    std::cout << "remove(\"hello\"), expected: 21, actual: " << table.remove("hello") << std::endl;
    table.print();
    std::cout << "inserting \"hello\" again... Index reuse is expected" << std::endl;
    table.insert("hello", 21);
    table.print();
    std::cout << "remove(\"world\"), expected: 42, actual: " << table.remove("world") << std::endl;
    table.print();
    std::cout << "-------------------------------------------------------------------" << std::endl;

    */

    std::cout << "Hydrating with gutenberg data..." << std::endl << std::endl;
    table.hydrate();
    table.print();

    return 0;
}
