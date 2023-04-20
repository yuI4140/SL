#pragma once
#define DEF
#define NORMAL
#include "core.hpp"
#define HASH_TABLE_SIZE 1024

class HashTable {
public:
  HashTable() : m_size(0) {}

  void insert(const char *key, void *value) {
    if (m_size >= HASH_TABLE_SIZE) {
      std::cerr << "Error: hash table is full\n";
      return;
    }

    int index = hash(key) % HASH_TABLE_SIZE;
    while (m_entries[index].key != nullptr &&
           strcmp(m_entries[index].key, key) != 0) {
      index = (index + 1) % HASH_TABLE_SIZE;
    }

    m_entries[index].key = key;
    m_entries[index].value = value;
    m_size++;
  }

  void *get(const char *key) {
    int index = hash(key) % HASH_TABLE_SIZE;
    while (m_entries[index].key != nullptr) {
      if (strcmp(m_entries[index].key, key) == 0) {
        return m_entries[index].value;
      }
      index = (index + 1) % HASH_TABLE_SIZE;
    }
    return nullptr;
  }

  void remove(const char *key) {
    int index = hash(key) % HASH_TABLE_SIZE;
    while (m_entries[index].key != nullptr) {
      if (strcmp(m_entries[index].key, key) == 0) {
        m_entries[index].key = nullptr;
        m_entries[index].value = nullptr;
        m_size--;
        return;
      }
      index = (index + 1) % HASH_TABLE_SIZE;
    }
  }

  void clear() {
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
      m_entries[i].key = nullptr;
      m_entries[i].value = nullptr;
    }
    m_size = 0;
  }

  int size() const { return m_size; }

  void print() const {
    std::cout << "Hash table contents:\n";
    for (int i = 0; i < HASH_TABLE_SIZE; i++) {
      if (m_entries[i].key != nullptr) {
        std::cout << "Key: " << m_entries[i].key
                  << ", Value: " << m_entries[i].value << "\n";
      }
    }
  }

  ~HashTable() { clear(); }

private:
  struct Entry {
    const char *key = nullptr;
    void *value = nullptr;
  };

  Entry m_entries[HASH_TABLE_SIZE];
  int m_size;

  int hash(const char *key) const {
    const unsigned char *ukey = reinterpret_cast<const unsigned char *>(key);
    int hash = 0;
    for (int i = 0; ukey[i] != '\0'; i++) {
      hash = 31 * hash + ukey[i];
    }
    return hash;
  }
};
