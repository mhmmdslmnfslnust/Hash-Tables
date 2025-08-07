#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono;

using namespace std;

class DA_HashTable { // Array based Hash Table
private:
    int *table;
    int size;
public:
    DA_HashTable(int s) : size(s) {
        table = new int[size];
        for (int i = 0; i < size; i++) {
            table[i] = -1; // Initialize all slots to -1 (indicating empty)
        }
    }

    ~DA_HashTable() {
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

class LP_HashTable { // Linear Probing Hash Table
private:
    int *table;
    int size; // Using fixed size for now
    int *status; // To track if a slot is occupied or deleted
public:
    LP_HashTable(int s) : size(s) {
        table = new int[size];
        status = new int[size]; // 0: empty, 1: occupied, 2: deleted
        for (int i = 0; i < size; i++) {
            table[i] = -1; // Initialize all slots to -1 (indicating empty)
            status[i] = 0; // All slots are initially empty
        }
    }

    ~LP_HashTable() {
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

class QP_HashTable { // Quadratic Probing Hash Table
private:
    int *table;
    int size; // Using fixed size for now
    int *status; // To track if a slot is occupied or deleted
public:
    QP_HashTable(int s) : size(s) {
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

    ~QP_HashTable() {
        delete[] table;
        delete[] status;
    }
};

class DH_HashTable { // Double Hashing Hash Table
private:
    int *table;
    int size; // Using fixed size for now
    int *status; // To track if a slot is occupied or deleted
public:
    DH_HashTable(int s) : size(s) {
        table = new int[size];
        status = new int[size]; // 0: empty, 1: occupied, 2: deleted
        for (int i = 0; i < size; i++) {
            table[i] = -1; // Initialize all slots to -1 (indicating empty)
            status[i] = 0; // All slots are initially empty
        }
    }

    ~DH_HashTable() {
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
    const int TABLE_SIZE = 997;
    int N = 50;            // Number of keys
    int RANGE = 10000;        // Key range
    int repetitions = 10000;

    vector<int> keys;
    srand(time(0));

    for (int i = 0; i < N; ++i) {
        int key = rand() % RANGE;
        keys.push_back(key);
    }

    // DA_HashTable da(RANGE); // direct addressing needs large table
    DA_HashTable da(10000); // Some large number to reduce collision + to reduce out of bounds error
    LP_HashTable lp(TABLE_SIZE);
    QP_HashTable qp(TABLE_SIZE);
    DH_HashTable dh(TABLE_SIZE);

    // Insert into all hash tables
    for (int key : keys) {
        da.insert(key);
        lp.insert(key);
        qp.insert(key);
        dh.insert(key);
    }

    // Pick a random key to search

    long long total_da = 0, total_lp = 0, total_qp = 0, total_dh = 0;

    // Run repeated searches with random keys from inserted set
    for (int i = 0; i < repetitions; ++i) {
        int search_key = keys[rand() % keys.size()];

        // DA search timing
        auto start = high_resolution_clock::now();
        da.search(search_key);
        auto end = high_resolution_clock::now();
        total_da += duration_cast<nanoseconds>(end - start).count();

        // LP search timing
        start = high_resolution_clock::now();
        lp.search(search_key);
        end = high_resolution_clock::now();
        total_lp += duration_cast<nanoseconds>(end - start).count();

        // QP search timing
        start = high_resolution_clock::now();
        qp.search(search_key);
        end = high_resolution_clock::now();
        total_qp += duration_cast<nanoseconds>(end - start).count();

        // DH search timing
        start = high_resolution_clock::now();
        dh.search(search_key);
        end = high_resolution_clock::now();
        total_dh += duration_cast<nanoseconds>(end - start).count();
    }

    // Output average times
    cout << "Average lookup times over " << repetitions << " repetitions:\n";
    cout << "DA: " << total_da / repetitions << " ns" << endl;
    cout << "LP: " << total_lp / repetitions << " ns" << endl;
    cout << "QP: " << total_qp / repetitions << " ns" << endl;
    cout << "DH: " << total_dh / repetitions << " ns" << endl;

    return 0;
}