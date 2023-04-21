#pragma once

#define DEF
#define NORMAL

#include "core.hpp"

#define HASH_TABLE_SIZE 1024

class HashTable {
public:
  HashTable();
  void insert(const char* key, void* value);
  void* get(const char* key);
  void remove(const char* key);
  void clear();
  int size() const;
  void print() const;
  ~HashTable();

private:
  struct Entry {
    const char* key = nullptr;
    void* value = nullptr;
  };
  Entry m_entries[HASH_TABLE_SIZE];
  int m_size;
  int hash(const char* key) const;
};

