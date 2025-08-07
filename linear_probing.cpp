#include <iostream>

using namespace std;

class HashTable { // Linear Probing Hash Table
private:
    int *table;
    int size; // Using fixed size for now
    int *status; // To track if a slot is occupied or deleted
public:
    HashTable(int s) : size(s) {
        table = new int[size];
        status = new int[size]; // 0: empty, 1: occupied, 2: deleted
        for (int i = 0; i < size; i++) {
            table[i] = -1; // Initialize all slots to -1 (indicating empty)
            status[i] = 0; // All slots are initially empty
        }
    }

    ~HashTable() {
        delete[] table;
        delete[] status;
    }

    bool isFull() {
        for (int i = 0; i < size; i++) {
            if (status[i] == 0) { // If any slot is empty
                return false;
            }
        }
        return true; // All slots are occupied
    }

    // Solving the previous error of collision in direct addressing
    void insert(int key) {
        if (isFull()) {
            cout << "Hash table is full! Cannot insert key " << key << endl;
            return;
        }

        int index = (key % size + size) % size; // It gives one non-negative index for all integers

        while (status[index] == 1) { // 1 means occupied
            index = (index + 1) % size; // Linear probing
        }
        table[index] = key;
        status[index] = 1; // Mark as occupied
    }

    // Deleting a key-value pair
    void remove(int key) {
        int index = (key % size + size) % size; // It gives one non-negative index for all integers

        while (status[index] != 0) { // 0 means empty
            if (status[index] == 1 && table[index] == key) {
                status[index] = 2; // Mark as deleted
                cout << "Key " << key << " removed." << endl;
                return;
            }
            index = (index + 1) % size; // Linear probing
        }
        cout << "Key " << key << " not found." << endl;
    }

    // Search for a value using key
    bool search(int key) {
        int index = (key % size + size) % size; // It gives one non-negative index for all integers

        int counter = 0; // To prevent infinite loop in case of full table
        while (status[index] != 0) { // 0 means empty, this works only if table is not full, so I used counter
            if (status[index] == 1 && table[index] == key) {
                return true; // Key found
            }
            index = (index + 1) % size; // Linear probing
            counter++;
            if (counter >= size) {break;} // Break out after one full loop
        }
        return false; // Key not found
    }

    void printTable() {
        for (int i = 0; i < size; i++) {
            if (status[i] == 1) {
                cout << "Index " << i << ": " << table[i] << endl;
            } else if (status[i] == 2) {
                cout << "Index " << i << ": Deleted" << endl;
            } else {
                cout << "Index " << i << ": Empty" << endl;
            }
        }
    }
};

int main() {
    HashTable ht(10); // Create a hash table of size 10

    ht.insert(3);
    ht.insert(5);
    ht.insert(7);
    ht.insert(13); // This will be inserted at index 3 due to linear probing
    ht.insert(-47);

    cout << "Searching for 5: " << (ht.search(5) ? "Found" : "Not Found") << endl;
    cout << "Searching for 8: " << (ht.search(8) ? "Found" : "Not Found") << endl;

    ht.remove(5);
    cout << "Searching for 5: " << (ht.search(5) ? "Found" : "Not Found") << endl;
    ht.insert(25);
    ht.insert(75);
    ht.insert(77);
    ht.insert(54);
    ht.insert(-7);
    ht.insert(25);
    ht.insert(-25); // <-- Will not be inserted as the table is full

    ht.printTable(); // Print the current state of the hash table

    return 0;
}
