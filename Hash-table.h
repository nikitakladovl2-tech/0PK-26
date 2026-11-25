#ifndef Hash-table_H
#define Hash-table_H
#include <stdbool.h>

typedef void *Pointer;
typedef unsigned (*HashFunction)(char *key);
typedef void (*Destructor)(Pointer);

typedef struct node_data{
    void *data;
    char *key;
} node_data;

typedef struct HashTable {
    Slist *buckets;
    size_t capacity;
    size_t size;

    HashFunction hash;
    Destructor dtor;
} HashTable;

typedef struct pair {
    char *key;
    Pointer data;
} pair;



bool to_pair(pair *p, char *key_, Pointer data);

int compare_key(Pointer pair_, Pointer key_);

// Example dtor
void destor(Pointer data);

void delete_user_data(Pointer pair_, Pointer ht_);
// dtor - деструктор. Этой функции будут передаваться data удаляемых элементов
// (в ht_destroy, ht_delete, а также при перезаписи элементов в ht_set).
// Если hf=0, берется стандартная функция (Дженкинс).
// Если dtor=0, деструктор отсутствует (не будет вызываться).
unsigned jenkins_one_at_a_time_hash(char *key);
void ht_init(HashTable *ht, size_t capacity , HashFunction hf, Destructor dtor);
void ht_destroy(HashTable *ht);
Pointer ht_set(HashTable *ht, char *key, Pointer data);
Pointer ht_get(HashTable *ht, char *key);
bool ht_contains(HashTable *ht, char *key, Pointer *out);
void ht_delete(HashTable *ht, char *key);
void ht_traverse(HashTable *ht, void (*f)(char *key, Pointer data));
void ht_resize(HashTable *ht, size_t new_size);

#endif