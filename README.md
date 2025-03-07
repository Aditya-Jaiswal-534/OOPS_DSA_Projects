# DSA Project Suite - 6 C++ Implementations

## 📦 Project Overview
**Language**: C++14/17  
**Key Concepts**: OOP, File I/O, Algorithm Optimization  
**Custom DS Implementations**:
- Red-Black Trees • AVL Trees • Binary Search Trees
- Hash Tables (Separate Chaining) • Max Heaps
- Graphs (Adjacency List) • Linked Lists

---

## 🚀 Project Catalog

### 1. Logistics Network Simulator
**File**: `real.cpp`  
**Data Structures**: Graph, Max Heap  
**Core Features**:
- City network modeling with freight routes
- Priority-based parcel routing system
- BFS/DFS pathfinding algorithms
- Time-tick simulation engine
- Stranded parcel detection

### 2. Student Record Manager
**File**: `interface_template.h`  
**Data Structures**: Linked List  
**Core Features**:
- CRUD operations for student entities
- CSV file I/O management
- Entity-component architecture
- Memory-efficient node structure

### 3. Lexicon Index System
**File**: `real.cpp`  
**Data Structures**: Red-Black Tree  
**Core Features**:
- Balanced tree insertion/deletion
- Chapter-based word counting
- Cross-chapter index pruning
- Multi-source text processing

### 4. Travel Desk System
**File**: `interface_template-2.cpp`  
**Data Structures**: BST, Vectors  
**Core Features**:
- Time-range trip queries
- Vehicle capacity management
- Location-based trip filtering
- OOP-based trip booking system

### 5. Metro Network Analyzer
**File**: `submitted.cpp`  
**Data Structures**: AVL Tree, BFS  
**Core Features**:
- Station management with AVL trees
- Bidirectional pathfinding
- Inter-line fare calculation
- Junction handling system

### 6. Phone Directory
**File**: `interface_template.cpp`  
**Data Structures**: Hash Table  
**Core Features**:
- Polynomial rolling hash (p=263)
- Partial name search
- Contact ranking system
- Collision resolution with chaining

---

## 🧠 Technical Highlights

### Advanced Algorithms
- Red-Black Tree double-red correction
- AVL tree rebalancing operations
- Max Heapify with O(log n) complexity
- BFS/DFS pathfinding variants
- Hash table collision resolution

### Memory Management
- Manual pointer handling in tree structures
- Object recycling in freight simulation
- STL-alternative custom containers
- Efficient node allocation/deallocation

### Optimization Techniques
- Bidirectional search in metro network
- Heap-based priority management
- Pruning for redundant word removal
- Lookup acceleration with hashing

---

## 🖥️ Compilation & Usage
```
# Build all projects
g++ -std=c++17 real.cpp interface_template*.cpp submitted.cpp -o dsa_suite

# Execution format
./dsa_suite [graph_file] [bookings_file] [chapter_files...]
```

**Input Formats**:
- Logistics: `SOURCE DESTINATION MIN_CARS MAX_CAPACITY`
- Student Records: `Name,RollNumber,Organization`
- Lexicon: `CHAPTER_TEXT_WITH_WORDS`

---

## 📂 Project Structure
```
DSA-Suite/
├── Logistics/               # Parcel routing system
├── Academic/                # Student records
├── TextProcessing/          # Word indexing
├── Transportation/          # Travel & metro systems
├── Contacts/                # Phone directory
└── samples/                 # Test datasets
     ├── graphs/             # Route maps
     ├── bookings/           # Parcel data
     └── chapters/           # Text files
```

---

## 📊 Complexity Analysis
| Project         | Insertion       | Deletion        | Search          |
|-----------------|-----------------|-----------------|-----------------|
| Red-Black Tree  | O(log n)        | O(log n)        | O(log n)        |
| AVL Tree        | O(log n)        | O(log n)        | O(log n)        |
| Hash Table      | O(1) avg        | O(1) avg        | O(1) avg        |
| Max Heap        | O(log n)        | O(log n)        | O(1)            |

---

## 🔍 Unique Features
1. **Self-Healing Structures**: Automatic tree rebalancing
2. **Multi-Paradigm Design**: Combines OOP with STL
3. **Persistent Storage**: CSV/text file integration
4. **Simulation Systems**: Time-based logistics modeling
5. **Hybrid Indexing**: Combined tree-list structures

---

> **Note**: Contains 6 independent but interoperable systems demonstrating core DSA concepts through practical implementations
