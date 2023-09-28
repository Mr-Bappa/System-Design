#include <iostream>
#include <vector>

class Item {
public:
    Item(int key, int value) : key(key), value(value) {}
    int key;
    int value;
};

class HashTable {
public:
    HashTable(int size) : size(size), table(size) {}

    void set(int key, int value) {
        int hash_index = _hash_function(key);
        for (Item& item : table[hash_index]) {
            if (item.key == key) {
                item.value = value;
                return;
            }
        }
        table[hash_index].emplace_back(key, value);
    }

    int get(int key) {
        int hash_index = _hash_function(key);
        for (const Item& item : table[hash_index]) {
            if (item.key == key) {
                return item.value;
            }
        }
        throw std::runtime_error("Key not found");
    }

    void remove(int key) {
        int hash_index = _hash_function(key);
        for (size_t index = 0; index < table[hash_index].size(); ++index) {
            if (table[hash_index][index].key == key) {
                table[hash_index].erase(table[hash_index].begin() + index);
                return;
            }
        }
        throw std::runtime_error("Key not found");
    }

private:
    int _hash_function(int key) {
        return key % size;
    }

    int size;
    std::vector<std::vector<Item>> table;
};

int main() {
    HashTable hash_table(10);

    hash_table.set(42, 100);
    hash_table.set(15, 200);
    hash_table.set(23, 300);

    std::cout << "Value for key 42: " << hash_table.get(42) << std::endl;
    std::cout << "Value for key 15: " << hash_table.get(15) << std::endl;

    hash_table.remove(42);

    try {
        std::cout << "Value for key 42: " << hash_table.get(42) << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
