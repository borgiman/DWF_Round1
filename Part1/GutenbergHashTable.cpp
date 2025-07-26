#include "GutenbergHashTable.h"
#include <iostream>
#include <stdexcept>

void GutenbergHashTable::insert(const std::string& key, const int value) {
    size_t index = hasher(key) % SIZE;
    std::cout << "Initial index for " << key << " is " << index << std::endl;

    // linear probing for index up to (index + SIZE - 1)
    for (auto i = 0; i < SIZE; i++) {
        size_t probeIndex = (index + i) % SIZE;
        Entry& entry = entries[probeIndex];

        // update alive and existing entry
        if (entry.occupied && !entry.deleted && entry.key == key) {
            entry.value = value;
            lastModified = &entry;
            return;
        }

        // insert into free or deleted entry
        if (!entry.occupied || entry.deleted) {
            entry.key = key;
            entry.value = value;
            entry.occupied = true;
            entry.deleted = false;
            lastModified = &entry;

            if (firstModified == nullptr) {
                firstModified = &entry;
            }

            return;
        }
    }

    throw std::overflow_error("No space for new entries");
}

int GutenbergHashTable::remove(const std::string& key) {
    throw std::runtime_error("Not implemented");
}

int GutenbergHashTable::get(const std::string& key) {
    throw std::runtime_error("Not implemented");
}

std::pair<std::string&, int> GutenbergHashTable::get_last() {
    throw std::runtime_error("Not implemented");
}

std::pair<std::string&, int> GutenbergHashTable::get_first() {
    throw std::runtime_error("Not implemented");
}

void GutenbergHashTable::print() {
    for (int i = 0; i < SIZE; i++) {
        std::cout << "[" << i << "] -> (key: " << entries[i].key << ", value: " << entries[i].value << ", occupied: " << entries[i].occupied << ", deleted: " << entries[i].deleted << ")" << std::endl;
    }
}

void GutenbergHashTable::hydrate() {
    throw std::runtime_error("Not implemented");
}
