// Hash Table Implementation Template
// Instructions: Implement the missing function definitions for each class.
// Each function has comments indicating what it should do.

#include <functional>
#include <iostream>
#include <list>
#include <stdexcept>
#include <string>

//-------------------- HASH FUNCTION HELPERS --------------------
// Helper function to hash strings using Horner's rule
/*NOTE: in this code, I'll not use these helper funcs, as I found that using
 * std::hash in functional library is more optimal. Nonetheless, I still tried
 * to complete these helper functions as a way to fulfil homework requirements
 * :)
 */

int hashString(const std::string &str, int tableSize) {
  // TODO: Implement string hashing function using Horner's rule
  // Use a prime number as the base (e.g., 31)
  // Return hash value modulo tableSize
  long hashVal = 0;
  for (char ch : str) {
    // Horner's rule: hash = (hash * base + char_val) % tableSize
    hashVal = (hashVal * 31 + ch) % tableSize;
  }
  return static_cast<int>(hashVal);
  // static cast is explicit and check at compile time
}

// Helper function to hash integers
int hashInt(int key, int tableSize) {
  // TODO: Implement simple integer hash function
  // Consider using the division method: h(k) = k mod tableSize
  return (key % tableSize + tableSize) % tableSize; // handle neg int
}

//-------------------- SEPARATE CHAINING HASH TABLE --------------------
// Generic hash table using separate chaining for collision resolution
template <typename K, typename V>

class SeparateChainingHashTable {
private:
  // Each bucket contains a list of key-value pairs
  struct KeyValuePair {
    K key;
    V value;
    KeyValuePair(const K &k, const V &v) : key(k), value(v) {}
  };

  std::list<KeyValuePair> *buckets; // Array of linked lists
  int tableSize;                    // Number of buckets
  int itemCount;                    // Total number of items in the hash table

  // Hash function - will be defined differently for different key types
  int hash(const K &key) const {
    // TODO: Implement hash function selector based on key type
    return std::hash<K>{}(key) % tableSize;
  } // {} creates a temp object

public:
  // Constructor: Initialize hash table with given size
  SeparateChainingHashTable(int size = 101) {
    // TODO: Implement constructor
    buckets = new std::list<KeyValuePair>[size]; // arr of ll
    tableSize = size;
    itemCount = 0;
  }

  // Destructor: Free dynamically allocated memory
  ~SeparateChainingHashTable() {
    // TODO: Implement destructor
    delete[] buckets;
  }

  // Insert a key-value pair into the hash table
  // If key already exists, update its value
  void insert(const K &key, const V &value) {
    // TODO: Implement insert function
    int index = hash(key);
    for (auto &pair : buckets[index]) { // for each pair in bucket
      if (pair.key == key) {
        pair.value = value; // update val
        return;
      }
    }
    buckets[index].push_back(KeyValuePair(key, value));
    itemCount++;
  }

  // Remove a key-value pair from the hash table
  // Throw exception if key not found
  void remove(const K &key) {
    // TODO: Implement remove function
    int index = hash(key);
    auto &list = buckets[index];
    for (auto pairPtr = list.begin(); pairPtr != list.end(); pairPtr++) {
      if (pairPtr->key == key) {
        list.erase(pairPtr); // erase the iterator
        itemCount--;
        return;
      }
    }
    throw std::invalid_argument("key not found");
  }

  // Search for a value associated with the given key
  // Throw exception if key not found
  V search(const K &key) const {
    // TODO: Implement search function
    int index = hash(key);
    for (const auto &pair : buckets[index]) {
      if (pair.key == key) {
        return pair.value;
      }
    }
    throw std::invalid_argument("key not found");
  }

  // Check if the hash table contains the given key
  bool contains(const K &key) const {
    // TODO: Implement contains function
    int index = hash(key);
    for (const auto &pair : buckets[index]) {
      if (pair.key == key) {
        return true;
      }
    }
    return false;
  }

  // Return the current load factor
  float loadFactor() const {
    // TODO: Implement load factor calculation
    return static_cast<float>(itemCount) / tableSize;
  }

  // Return number of items in the hash table
  int size() const {
    // TODO: Implement size function
    return itemCount;
  }

  // Display the hash table (for debugging)
  void display() const {
    for (int i{0}; i < tableSize; i++) {
      std::cout << '[' << i << "] ";
      for (const auto &pair : buckets[i]) {
        std::cout << '{' << pair.key << ": " << pair.value << '}' << " -> ";
      }
      std::cout << "nullptr" << std::endl;
    }
  }
};

//-------------------- OPEN ADDRESSING HASH TABLE --------------------
// Generic hash table using open addressing for collision resolution
template <typename K, typename V> class OpenAddressingHashTable {
private:
  enum EntryStatus { EMPTY, OCCUPIED, DELETED };

  struct Entry {
    K key;
    V value;
    EntryStatus status;

    Entry() : status(EMPTY) {}
  };

  Entry *table;  // Array of entries
  int tableSize; // Size of the table
  int itemCount; // Number of items in the table

  // Hash function
  int hash(const K &key) const {
    // TODO: Implement hash function selector based on key type
    return std::hash<K>{}(key) % tableSize;
  }

  // Probe function for collision resolution (linear probing)
  int probe(int hash, int i) const {
    // TODO: Implement linear probing
    return (hash + i) % tableSize; // i will be defined in the loop
  }

public:
  // Constructor: Initialize hash table with given size
  OpenAddressingHashTable(int size = 101) {
    // TODO: Implement constructor
    tableSize = size;
    itemCount = 0;
    table = new Entry[size]; // [] to allocate an arr, () to set nullptr
  }

  // Destructor: Free dynamically allocated memory
  ~OpenAddressingHashTable() {
    // TODO: Implement destructor
    delete[] table;
  }

  // Insert a key-value pair into the hash table
  // If key already exists, update its value
  // If table is full, throw an exception
  void insert(const K &key, const V &value) {
    // TODO: Implement insert function
    if (itemCount >= tableSize) {
      throw std::overflow_error("hash table is full");
    }
    int hashVal = hash(key); // original index
    int i{0};
    int index = probe(hashVal, i); // actual index
    int firstDeleted = -1;
    while (table[index].status != EntryStatus::EMPTY && i < tableSize) {
      // move pair to empty slot
      if (table[index].status == EntryStatus::OCCUPIED &&
          table[index].key == key) {
        // if pair has resemble key, update val
        table[index].value = value;
        return;
      } else if (table[index].status == EntryStatus::DELETED &&
                 firstDeleted == -1) {
        firstDeleted = index;
      }
      i++;
      index = probe(hashVal, i);
    }
    if (firstDeleted != -1)
      index = firstDeleted; // prioritize deleted first then empty
    table[index].key = key;
    table[index].value = value;
    table[index].status = EntryStatus::OCCUPIED;
    itemCount++;
  }

  // Remove a key-value pair from the hash table
  // Throw exception if key not found
  void remove(const K &key) {
    // TODO: Implement remove function
    int hashVal = hash(key);
    int i{0};
    int index = probe(hashVal, i);
    while (table[index].status != EntryStatus::EMPTY && i < tableSize) {
      if (table[index].status == EntryStatus::OCCUPIED &&
          table[index].key == key) {
        table[index].status = DELETED;
        itemCount--;
        return;
      }
      i++;
      index = probe(hashVal, i);
    }
    throw std::invalid_argument("key not found");
  }

  // Search for a value associated with the given key
  // Throw exception if key not found
  V search(const K &key) const {
    // TODO: Implement search function
    int hashVal = hash(key);
    int i{0};
    int index = probe(hashVal, i);
    while (table[index].status != EntryStatus::EMPTY && i < tableSize) {
      if (table[index].status == EntryStatus::OCCUPIED &&
          table[index].key == key) {
        return table[index].value;
      }
      i++;
      index = probe(hashVal, i);
    }
    throw std::invalid_argument("key not found");
  }

  // Check if the hash table contains the given key
  bool contains(const K &key) const {
    // TODO: Implement contains function
    int hashVal = hash(key);
    int i{0};
    int index = probe(hashVal, i);
    while (table[index].status != EntryStatus::EMPTY && i < tableSize) {
      if (table[index].status == EntryStatus::OCCUPIED &&
          table[index].key == key) {
        return true;
      }
      i++;
      index = probe(hashVal, i);
    }
    return false;
  }

  // Return the current load factor
  float loadFactor() const {
    // TODO: Implement load factor calculation
    return static_cast<float>(itemCount) / tableSize;
  }

  // Return number of items in the hash table
  int size() const {
    // TODO: Implement size function
    return itemCount;
  }

  // Display the hash table (for debugging)
  void display() const {
    for (int i{0}; i < tableSize; i++) {
      std::cout << '[' << i << "]: ";
      if (table[i].status == EntryStatus::OCCUPIED) {
        std::cout << table[i].key << "-->" << table[i].value;
      } else if (table[i].status == EntryStatus::DELETED) {
        std::cout << "DELETED";
      } else {
        std::cout << "EMPTY";
      }
      std::cout << std::endl;
    }
  }
};

//-------------------- TESTING FUNCTION --------------------
void testHashTables() {
  // Test separate chaining hash table with string keys
  std::cout << "Testing Separate Chaining Hash Table with string keys:\n";
  SeparateChainingHashTable<std::string, int> scHashTable(10);

  // Insert some key-value pairs
  scHashTable.insert("apple", 5);
  scHashTable.insert("banana", 8);
  scHashTable.insert("cherry", 12);
  scHashTable.insert("date", 15);
  scHashTable.insert("elderberry", 20);
  scHashTable.insert("fig", 25);

  // Display the table
  std::cout << "After insertions:\n";
  scHashTable.display();

  // Search for some keys
  try {
    std::cout << "Value for 'apple': " << scHashTable.search("apple")
              << std::endl;
    std::cout << "Value for 'banana': " << scHashTable.search("banana")
              << std::endl;
    std::cout << "Value for 'grape': " << scHashTable.search("grape")
              << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  // Remove a key
  std::cout << "Removing 'banana'..." << std::endl;
  scHashTable.remove("banana");

  // Display the table again
  std::cout << "After removal:\n";
  scHashTable.display();

  // Test contains method
  std::cout << "Contains 'apple': "
            << (scHashTable.contains("apple") ? "Yes" : "No") << std::endl;
  std::cout << "Contains 'banana': "
            << (scHashTable.contains("banana") ? "Yes" : "No") << std::endl;

  // Test load factor
  std::cout << "Load factor: " << scHashTable.loadFactor() << std::endl;
  std::cout << "Size: " << scHashTable.size() << std::endl;

  // Test open addressing hash table with integer keys
  std::cout << "\nTesting Open Addressing Hash Table with integer keys:\n";
  OpenAddressingHashTable<int, std::string> oaHashTable(10);

  // Insert some key-value pairs
  oaHashTable.insert(5, "five");
  oaHashTable.insert(15, "fifteen");
  oaHashTable.insert(25, "twenty-five");
  oaHashTable.insert(35, "thirty-five");
  oaHashTable.insert(45, "forty-five");

  // Display the table
  std::cout << "After insertions:\n";
  oaHashTable.display();

  // Search for some keys
  try {
    std::cout << "Value for 5: " << oaHashTable.search(5) << std::endl;
    std::cout << "Value for 15: " << oaHashTable.search(15) << std::endl;
    std::cout << "Value for 100: " << oaHashTable.search(100) << std::endl;
  } catch (const std::exception &e) {
    std::cout << "Exception caught: " << e.what() << std::endl;
  }

  // Remove a key
  std::cout << "Removing 15..." << std::endl;
  oaHashTable.remove(15);

  // Display the table again
  std::cout << "After removal:\n";
  oaHashTable.display();

  // Test contains method
  std::cout << "Contains 5: " << (oaHashTable.contains(5) ? "Yes" : "No")
            << std::endl;
  std::cout << "Contains 15: " << (oaHashTable.contains(15) ? "Yes" : "No")
            << std::endl;

  // Test load factor
  std::cout << "Load factor: " << oaHashTable.loadFactor() << std::endl;
  std::cout << "Size: " << oaHashTable.size() << std::endl;
}

int main() {
  testHashTables();
  return 0;
}