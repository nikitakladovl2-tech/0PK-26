#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Slist.h"
#include <string.h>
#include "Hash-table.h"


bool to_pair(pair *p, char *key_, Pointer data){
    if (p == NULL || key_ == NULL){return false;}
    char *key = malloc(strlen(key_) + 1);
    if (key == NULL){return false;}
    strcpy(key, key_);
    p->key = key;
    p->data = data;
    return true;
}

int compare_key(Pointer pair_, Pointer key_){
    if(pair_ == NULL || key_ == NULL){return 0;}
    pair *p = pair_;
    char *key = key_;
    return strcmp(key, p->key) == 0;
}

void destor(Pointer data){
    free(data);
}

void delete_user_data(Pointer pair_, Pointer ht_){
    pair *p = pair_;
    HashTable *ht = ht_;
    if(ht->dtor != NULL){
        ht->dtor(p->data);
        
    }
    free(p->key);
    free(p);  
}

unsigned jenkins_one_at_a_time_hash(char *key) {
    unsigned hash = 0;
    for (; *key; ++key) {
        hash += *key;
        hash += (hash << 10);
        hash ^= (hash >> 6);
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

void ht_init(HashTable *ht, size_t capacity , HashFunction hf, Destructor dtor){
    if(ht == NULL){
        printf("Некорректный указатель на хеш-таблицу");
        return;
    }
    ht->capacity = 0;
    ht->size = 0;
    ht->buckets = NULL;
    if (hf == 0){
        hf = jenkins_one_at_a_time_hash;
    }
    ht->hash = hf;
    // не делаем проверку на dtor, тк по условию если он равен нулю, то он не будет вызываться
    ht->dtor = dtor;
    if (capacity == 0){
        printf("Задайте ненулевое значение емкости, cоздать таблицу не удалось");
        return;
    }
    ht->capacity = capacity;
    
    ht->buckets = malloc(capacity*sizeof(Slist));
    if (ht->buckets == NULL){
        printf("Не удалось выделить память");
        ht->capacity = 0;
        return;
    }
    for (size_t i = 0 ; i < capacity ; i++){
        slist_create(&ht->buckets[i]);

    }
}

void ht_destroy(HashTable *ht){
    if (ht == NULL){
        printf("Некорректный указатель на хеш-таблицу");
        return;
    }

    // cначала чистим пользовательские данные, затем пары, затем ноды и листы ( последнее просто через дестрой функции)
    
    for (size_t i = 0; i < ht->capacity ; i++){
        Slist *list = &ht->buckets[i];
        slist_foreach(list, delete_user_data, ht);
        slist_destroy(list);   
    }
    free(ht->buckets);
    ht->buckets = NULL;
    ht->capacity = 0;
    ht->dtor = 0;
    ht->hash = 0;
    ht->size = 0;
}

Pointer ht_set(HashTable *ht, char *key, Pointer data){
    if(ht == NULL || key == NULL || data == NULL){return NULL;}
    if(!ht->capacity){return NULL;}
    size_t hash_index = ht->hash(key) % ht->capacity;

    Pointer out = NULL;
    
    
    if(ht_contains(ht, key, &out)){
        pair *p_ = out;
        Pointer data_ = p_->data;
        p_->data = data;
        return data_;
    }
    else{
        pair *p = malloc(sizeof(pair));
        if(p == NULL){printf("Не удалось выделить память");return NULL;}

        bool succes = to_pair(p, key, data);

        if (succes == false){
            printf("Не получилось создать ячейку");
            free(p);
            return NULL;
        }   
        slist_append(&ht->buckets[hash_index], (Pointer)p);
        ht->size++;
        return NULL;
    }
}

bool ht_contains(HashTable *ht, char *key, Pointer *out){
    if(ht == NULL || key == NULL){return false;}
    if(!ht->capacity){return false;}

    size_t hash_index = ht->hash(key) % ht->capacity;

    Slist *list = &ht->buckets[hash_index];

    if (slist_find_custom(list, compare_key, key, out)){
        return true;
    }
    return false;
}

Pointer ht_get(HashTable *ht, char *key){
    if(ht == NULL || key == NULL || ht->capacity == 0){return NULL;}
    Slist *list;
    list = &ht->buckets[ht->hash(key)% ht->capacity];
    Pointer out;

    int tmp = slist_find_custom(list, compare_key, key, &out);
    if (tmp > 0){
        pair *p = out;
        return p->data;
    }
    return NULL;

}

void ht_delete(HashTable *ht, char *key){
    if (ht == NULL || key == NULL || ht->capacity == 0){return;}
    Pointer out = NULL;
    if (ht_contains(ht, key, &out)){
        slist_remove_first(&ht->buckets[ht->hash(key)% ht->capacity], out);
        delete_user_data(out, ht);
        ht->size--;
    }
}

static void traverse_adapter(Pointer p_, void *arg){
    if (p_){
        if (arg){
            pair *p = p_;
            void (*f)(char *, Pointer) = *(void (**)(char *, Pointer))arg;
            f(p->key, p->data);
        }
    }
}

void ht_traverse(HashTable *ht, void (*f)(char *key, Pointer data)){
    if (ht == NULL || ht->capacity == 0 || f == NULL){return;}

    for (size_t i = 0; i < ht->capacity ; i++){
        Slist *list = &ht->buckets[i];
        slist_foreach(list, traverse_adapter, &f);
    }
}

void ht_resize(HashTable *ht, size_t new_capacity){
    if(ht == NULL || new_capacity == 0){return;}   
    
    if (ht->capacity == new_capacity){return;}

    Slist *new_buckets = malloc(sizeof(Slist) * new_capacity);

    if(new_buckets == NULL){printf("Ошибка выделения памяти"); return;}

    for (size_t i = 0; i < new_capacity ; i++){
        slist_create(&new_buckets[i]);
    }

    for (size_t i = 0; i < ht->capacity ; i++){
        while (ht->buckets[i].head){
            //теперь нужно перераспределить всех нодов по новым корзинкам
            Pointer data = slist_remove(&ht->buckets[i], 0);
            pair *p = data;
            // ремов убивает ноды, но у нас еще p, p->key и юзердата (она не трогается)
            //Теперь нужно вставить новую пару в новую корзинку, что мы точно знаем - ключи не повторяются
            size_t hash_index = ht->hash(p->key) % new_capacity;
            slist_prepend(&new_buckets[hash_index], data);
            //мы не очищаем ничего, тк просто перекладываем из одного листа эти сущности в другой
        }
    }
    // единственное, что нужно очистить, это указатель на бакетc
    Pointer tmp = ht->buckets;
    ht->buckets = new_buckets;
    free(tmp);
    ht->capacity = new_capacity;
}