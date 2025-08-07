#include <iostream>

using namespace std;

class HashTable { // Array based Hash Table
private:
    int *table;
    int size;
public:
    HashTable(int s) : size(s) {
        table = new int[size];
        for (int i = 0; i < size; i++) {
            table[i] = -1; // Initialize all slots to -1 (indicating empty)
        }
    }

    ~HashTable() {
        delete[] table;
    }

    // Using direct addressing for simplicity
    void insert(int key) {
        if (key < 0 || key >= size) {
            cout << "Key out of bounds!" << endl;
            return;
        }
        table[key] = key; // Insert the key directly into the table
    }

    // Search for a value using key
    bool search(int key) {
        if (key < 0 || key >= size) {
            cout << "Key out of bounds!" << endl;
            return false;
        }
        return table[key] != -1; // Return true if key is found
    }

    // Deleting a key-value pair
    void remove(int key) {
        if (key < 0 || key >= size) {
            cout << "Key out of bounds!" << endl;
            return;
        }
        table[key] = -1; // Set the slot to -1 to indicate it's empty
    }
};



int main() {
    HashTable ht(10); // Create a hash table of size 10

    ht.insert(3);
    ht.insert(5);
    ht.insert(7);
    ht.insert(17); // <-- This will not be inserted as it is out of bounds, we will fix it in later versions

    cout << "Searching for 5: " << (ht.search(5) ? "Found" : "Not Found") << endl;
    cout << "Searching for 8: " << (ht.search(8) ? "Found" : "Not Found") << endl;

    ht.remove(5);
    cout << "Searching for 5 after removal: " << (ht.search(5) ? "Found" : "Not Found") << endl;

    return 0;
}