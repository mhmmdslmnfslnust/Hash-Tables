# Hash Tables Implementation & Performance Analysis

This repository contains comprehensive implementations of various hash table data structures in C++, along with performance analysis and visualization tools. The project demonstrates different collision resolution techniques and provides empirical performance comparisons.

## 📁 Project Structure

```
Hash-Tables/
├── direct_addressing.cpp        # Basic hash table using direct addressing
├── linear_probing.cpp          # Hash table with linear probing collision resolution
├── quadratic_probing.cpp       # Hash table with quadratic probing collision resolution
├── double_hashing.cpp          # Hash table with double hashing collision resolution
├── comparison.cpp              # Performance comparison of all hash table implementations
├── comparison_with_inheritence.cpp  # Empty file (placeholder)
├── comparison.xlsx             # Excel analysis of performance data
├── exec.exe                    # Compiled executable
└── To Infinity/
    ├── andBeyond.cpp          # Comprehensive performance analysis program
    ├── hash_performance.csv   # Performance data (997 test cases)
    └── python.py              # Python script for data visualization
```

## 🔧 Implemented Hash Table Variants

### 1. Direct Addressing (`direct_addressing.cpp`)
- **Class**: `HashTable`
- **Method**: Uses keys directly as array indices
- **Limitation**: Keys must be within table size bounds (0 to size-1)
- **Time Complexity**: O(1) for all operations
- **Space Complexity**: O(universe size)
- **Features**:
  - Insert, search, and remove operations
  - Bounds checking for key validation
  - Simple array-based implementation

### 2. Linear Probing (`linear_probing.cpp`)
- **Class**: `HashTable`
- **Method**: Sequential probing to resolve collisions
- **Hash Function**: `(key % size + size) % size`
- **Collision Resolution**: Increment index by 1 until empty slot found
- **Features**:
  - Status array tracking (empty=0, occupied=1, deleted=2)
  - Full table detection
  - Lazy deletion support
  - Infinite loop prevention in search

### 3. Quadratic Probing (`quadratic_probing.cpp`)
- **Class**: `HashTable`
- **Method**: Quadratic function for probing sequence
- **Hash Function**: `(key % size + size) % size`
- **Collision Resolution**: `index = (start + i²) % size`
- **Features**:
  - Reduces primary clustering compared to linear probing
  - Status tracking for occupied/deleted slots
  - Loop detection to prevent infinite probing

### 4. Double Hashing (`double_hashing.cpp`)
- **Class**: `HashTable`
- **Method**: Uses two hash functions for probing
- **Primary Hash**: `(key % size + size) % size`
- **Secondary Hash**: `1 + ((key / size) % (size - 1))`
- **Collision Resolution**: `index = (hash1 + i * hash2) % size`
- **Features**:
  - Minimizes clustering effects
  - Better distribution than linear/quadratic probing
  - Note: Implementation shows potential infinite loop with non-prime table sizes

## 📊 Performance Analysis

### Comparison Program (`comparison.cpp`)
- **Test Configuration**:
  - Table size: 997 (prime number)
  - Number of keys: 50
  - Key range: 0-9999
  - Repetitions: 10,000 searches per test
- **Metrics**: Average lookup time in nanoseconds
- **Hash Tables Tested**:
  - DA_HashTable (Direct Addressing)
  - LP_HashTable (Linear Probing)
  - QP_HashTable (Quadratic Probing)
  - DH_HashTable (Double Hashing)

### Comprehensive Analysis (`To Infinity/andBeyond.cpp`)
- **Extended Testing**: Tests all techniques with varying number of keys (N = 1 to 997)
- **Data Output**: Generates `hash_performance.csv` with performance metrics
- **Configuration**:
  - Table size: 997 (prime)
  - Key range: 0-9999
  - 10,000 repetitions per data point
  - 997 different load factor scenarios

### Performance Data (`hash_performance.csv`)
- Contains 997 rows of performance data
- Columns: N, Direct Addressing, Linear Probing, Quadratic Probing, Double Hashing
- Values represent average lookup times in nanoseconds
- Shows performance degradation as load factor increases

## 📈 Visualization (`To Infinity/python.py`)
Python script using pandas and matplotlib to visualize performance data:
- Plots average lookup time vs. number of keys for all hash table types
- Demonstrates performance characteristics under different load factors
- Requires: `pandas`, `matplotlib`

## 🚀 Key Implementation Features

### Common Features Across All Implementations:
1. **Dynamic Memory Management**: Proper constructor/destructor patterns
2. **Status Tracking**: Three-state system (empty, occupied, deleted)
3. **Collision Handling**: Different strategies for resolving hash collisions
4. **Error Handling**: Bounds checking and full table detection
5. **Debug Support**: `printTable()` methods for visualization

### Hash Function Design:
- All implementations use modular arithmetic: `(key % size + size) % size`
- Ensures non-negative indices for negative keys
- Prime table sizes (997) used in performance testing for better distribution

### Memory Layout:
- **Direct Addressing**: Single array with -1 indicating empty slots
- **Other Methods**: Dual array system (data + status) for better state management

## 📋 Performance Insights

Based on the implemented analysis:

1. **Direct Addressing**: Fastest but requires large memory for sparse key sets
2. **Double Hashing**: Generally provides good performance with minimal clustering
3. **Quadratic Probing**: Better than linear probing for reducing primary clustering
4. **Linear Probing**: Simplest but suffers from clustering at high load factors

## ⚠️ Known Limitations

1. **Double Hashing**: May enter infinite loops with composite table sizes
2. **Quadratic Probing**: May not probe all positions in non-prime sized tables
3. **Direct Addressing**: Limited to small, dense key universes
4. **General**: Fixed-size implementations (no dynamic resizing)

## 🛠️ Compilation & Usage

```bash
# Compile individual implementations
g++ -o direct_addressing direct_addressing.cpp
g++ -o linear_probing linear_probing.cpp
g++ -o quadratic_probing quadratic_probing.cpp
g++ -o double_hashing double_hashing.cpp

# Compile performance comparison
g++ -o comparison comparison.cpp

# Compile comprehensive analysis
g++ -o andBeyond "To Inifinity/andBeyond.cpp"
```

This implementation serves as an educational tool for understanding hash table mechanics, collision resolution techniques, and empirical performance analysis of different hashing strategies.
