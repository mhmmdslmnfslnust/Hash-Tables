#include <iostream>

using namespace std;

class HashTable { // Double Hashing Hash Table
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

    int hashFunction(int key) {
        return (key % size + size) % size; // Ensures non-negative index
    }

    int secondHashFunction(int key) {
        // Hash Function 01
        // return 7 - (key % 7); // Example secondary hash function
        // Hash Function 02
        // return 11 - (key % 11); // Another example secondary hash function
        // Hash Function 03
        return 1 + ((key / size) % (size - 1)); // Yet another example secondary hash function, this was verified in class so used this one
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

        int hash1 = hashFunction(key); // Primary hash function
        int hash2 = secondHashFunction(key); // Secondary hash function
        int index = hash1; // Start probing from the primary hash index

        int i = 0;
        while (status[index] == 1) { // 1 means occupied
            i++;
            index = (hash1 + i * hash2) % size; // Double hashing
        }
        table[index] = key;
        status[index] = 1; // Mark as occupied
    }

    // Deleting a key-value pair
    void remove(int key) {
        int hash1 = hashFunction(key); // Primary hash function
        int hash2 = secondHashFunction(key); // Secondary hash function
        int index = hash1; // Start probing from the primary hash index
        
        int i = 0;
        while (status[index] != 0) { // 0 means empty
            if (status[index] == 1 && table[index] == key) {
                status[index] = 2; // Mark as deleted
                cout << "Key " << key << " removed." << endl;
                return;
            }
            i++;
            index = (hash1 + i * hash2) % size; // Double hashing
        }
        cout << "Key " << key << " not found." << endl;
    }

    // Search for a value using key
    bool search(int key) {
        int hash1 = hashFunction(key); // Primary hash function
        int hash2 = secondHashFunction(key); // Secondary hash function
        int index = hash1; // Start probing from the primary hash index
        
        int i = 0;
        while (status[index] != 0) { // 0 means empty, so we stop when we find an empty slot
            if (status[index] == 1 && table[index] == key) { // Condition for finding the key
                return true;
            }
            i++;
            index = (hash1 + i * hash2) % size; // Double hashing

            if (i >= size) {
                break; // We've checked all possible positions
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
};

int main() {
    HashTable ht(10); // Create a hash table of size 10, using double hashing

    // 13, 28, 33, 147, 43
    ht.insert(13);
    ht.insert(28);
    ht.insert(33);
    ht.insert(147);
    ht.insert(43); // <-- Gets into a loop and does not get inserted, and apparently this is the reason we normally use a prime number for the size of the hash table

    ht.printTable(); // Print the current state of the hash table

    return 0;
}
