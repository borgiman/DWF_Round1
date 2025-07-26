#ifndef GutenbergHashTable_H
#define GutenbergHashTable_H

#include <string>
#include <utility>

static constexpr std::size_t SIZE = 5;

struct Entry {
    std::string key;
    int value = 0;
    bool occupied = false;
    bool deleted = false;
};

class GutenbergHashTable {
public:
    void insert(const std::string& key, int value); // insert a new key-value pair or replace a key's existing value
    int remove(const std::string& key); // removes the corresponding key-value pair
    int get(const std::string& key); // returns the value of the corresponding key
    std::pair<std::string&, int> get_last(); // returns the most recently inserted or changed key-value pair
    std::pair<std::string&, int> get_first(); // returns the least recently inserted or changed key-value pair
    void print(); // for debugging purposes
    void hydrate(); // hydrate with gutenberg data

private:
    Entry entries[SIZE];
    Entry* firstModified = nullptr;
    Entry* lastModified = nullptr;
    std::hash<std::string> hasher;
};

#endif
