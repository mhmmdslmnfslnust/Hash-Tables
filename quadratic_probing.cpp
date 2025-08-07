#include <iostream>

using namespace std;

class HashTable { // Quadratic Probing Hash Table
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

        int start = (key % size + size) % size; // It gives one non-negative index for all integers
        int index = start; // Start probing from the original index


        int i = 0; // See if this needs to be 1
        while (status[index] == 1) { // 1 means occupied
            index = (start + i * i) % size; // Quadratic probing
            i++;
        }
        table[index] = key;
        status[index] = 1; // Mark as occupied
    }

    // Deleting a key-value pair
    void remove(int key) {
        int start = (key % size + size) % size; // It gives one non-negative index for all integers
        int index = start; // Start probing from the original index
        int i = 1; // Start from 1
        while (status[index] != 0) { // 0 means empty
            if (status[index] == 1 && table[index] == key) {
                status[index] = 2; // Mark as deleted
                cout << "Key " << key << " removed." << endl;
                return;
            }
            index = (start + i * i) % size; // Quadratic probing
            i++;
        }
        cout << "Key " << key << " not found." << endl;
    }

    // Search for a value using key
    bool search(int key) {
        int start = (key % size + size) % size; // Our origninal index
        int index = start; // Start probing from the original index
        int i = 0;

        while (status[index] != 0) { // 0 means empty, so we stop when we find an empty slot
            if (status[index] == 1 && table[index] == key) { // Condition for finding the key
                return true;
            }
            i++;
            index = (start + i * i) % size; // Quadratic probing

            if (index == start) {
                break; // We've looped back; table fully traversed in probing terms
            }
        }

        return false;
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

    ~HashTable() {
        delete[] table;
        delete[] status;
    }
};

int main() {
    HashTable ht(10); // Create a hash table of size 10

    // Inserting verified pattern
    ht.insert(89);
    ht.insert(18);
    ht.insert(49);
    ht.insert(58);
    ht.insert(79);
    ht.insert(27);

    ht.printTable(); // Print the current state of the hash table

    return 0;
}
