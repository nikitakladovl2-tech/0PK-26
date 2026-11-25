#include <stdio.h>
#include <stdlib.h>
#include "Slist.h"
#include <assert.h>
#include <string.h>
#include "Hash-table.h"

static int destructor_count = 0;


void add_value(char *key, Pointer data){
    (void)key;
    (*(int *)data)++;
}

unsigned constant_hash(char *key){
    (void)key;
    return 0;
}


void test_destructor(Pointer data){
    destructor_count++;
    free(data);
}


void test_init(void){
    HashTable ht;

    ht_init(&ht, 10, NULL, NULL);

    assert(ht.capacity == 10);
    assert(ht.size == 0);
    assert(ht.buckets != NULL);
    assert(ht.hash != NULL);
    assert(ht.dtor == NULL);

    for(size_t i = 0; i < ht.capacity; i++){
        assert(ht.buckets[i].head == NULL);
    }

    ht_destroy(&ht);

    printf("test_init: PASSED\n");
}


void test_destroy(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10, b = 20;

    ht_set(&ht, "first", &a);
    ht_set(&ht, "second", &b);

    ht_destroy(&ht);

    assert(ht.capacity == 0);
    assert(ht.size == 0);
    assert(ht.buckets == NULL);
    assert(ht.hash == NULL);
    assert(ht.dtor == NULL);


    printf("test_destroy: PASSED\n");
}


void test_set(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10, b = 20, c = 30;

    assert(ht_set(&ht, "first", &a) == NULL);
    assert(ht_set(&ht, "second", &b) == NULL);
    assert(ht_set(&ht, "third", &c) == NULL);

    assert(ht.size == 3);

    assert(ht_get(&ht, "first") == &a);
    assert(ht_get(&ht, "second") == &b);
    assert(ht_get(&ht, "third") == &c);

    ht_destroy(&ht);

    printf("test_set: PASSED\n");
}


void test_set_replace(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10, b = 20;

    ht_set(&ht, "number", &a);

    Pointer old_data = ht_set(&ht, "number", &b);

    assert(old_data == &a);
    assert(ht_get(&ht, "number") == &b);
    assert(ht.size == 1);

    ht_destroy(&ht);

    printf("test_set_replace: PASSED\n");
}


void test_contains(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10;
    ht_set(&ht, "number", &a);

    Pointer out = NULL;

    assert(ht_contains(&ht, "number", &out));
    assert(out != NULL);

    pair *p = out;

    assert(strcmp(p->key, "number") == 0);
    assert(p->data == &a);

    assert(!ht_contains(&ht, "unknown", &out));
    assert(out == NULL);

    ht_destroy(&ht);

    printf("test_contains: PASSED\n");
}

void test_get(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10, b = 20;

    ht_set(&ht, "first", &a);
    ht_set(&ht, "second", &b);

    assert(ht_get(&ht, "first") == &a);
    assert(ht_get(&ht, "second") == &b);

    assert(*(int *)ht_get(&ht, "first") == 10);
    assert(*(int *)ht_get(&ht, "second") == 20);

    ht_destroy(&ht);

    printf("test_get: PASSED\n");
}


void test_get_not_found(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    assert(ht_get(&ht, "unknown") == NULL);

    int a = 10;
    ht_set(&ht, "number", &a);

    assert(ht_get(&ht, "unknown") == NULL);

    ht_destroy(&ht);

    printf("test_get_not_found: PASSED\n");
}

void test_delete(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10, b = 20, c = 30;

    ht_set(&ht, "first", &a);
    ht_set(&ht, "second", &b);
    ht_set(&ht, "third", &c);

    ht_delete(&ht, "second");

    assert(ht.size == 2);
    assert(ht_get(&ht, "second") == NULL);

    assert(ht_get(&ht, "first") == &a);
    assert(ht_get(&ht, "third") == &c);

    ht_delete(&ht, "first");
    ht_delete(&ht, "third");

    assert(ht.size == 0);

    ht_destroy(&ht);

    printf("test_delete: PASSED\n");
}


void test_delete_not_found(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10;

    ht_set(&ht, "number", &a);

    ht_delete(&ht, "unknown");

    assert(ht.size == 1);
    assert(ht_get(&ht, "number") == &a);

    ht_destroy(&ht);

    printf("test_delete_not_found: PASSED\n");
}


void test_collision(void){
    HashTable ht;

    ht_init(&ht, 10, constant_hash, NULL);

    int a = 10, b = 20, c = 30;

    ht_set(&ht, "first", &a);
    ht_set(&ht, "second", &b);
    ht_set(&ht, "third", &c);

    assert(ht.size == 3);

    // Все элементы находятся в одной корзине.
    assert(slist_length(&ht.buckets[0]) == 3);

    assert(ht_get(&ht, "first") == &a);
    assert(ht_get(&ht, "second") == &b);
    assert(ht_get(&ht, "third") == &c);

    ht_delete(&ht, "second");

    assert(ht.size == 2);
    assert(slist_length(&ht.buckets[0]) == 2);

    assert(ht_get(&ht, "second") == NULL);
    assert(ht_get(&ht, "first") == &a);
    assert(ht_get(&ht, "third") == &c);

    ht_destroy(&ht);

    printf("test_collision: PASSED\n");
}


void test_traverse(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    int a = 10, b = 20, c = 30;

    ht_set(&ht, "first", &a);
    ht_set(&ht, "second", &b);
    ht_set(&ht, "third", &c);

    ht_traverse(&ht, add_value);

    assert(a == 11);
    assert(b == 21);
    assert(c == 31);

    assert(ht.size == 3);

    ht_destroy(&ht);

    printf("test_traverse: PASSED\n");
}


void test_traverse_empty(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    ht_traverse(&ht, add_value);

    assert(ht.size == 0);

    ht_destroy(&ht);

    printf("test_traverse_empty: PASSED\n");
}


void test_resize_more(void){
    HashTable ht;
    ht_init(&ht, 2, NULL, NULL);

    int a = 10, b = 20, c = 30;

    ht_set(&ht, "first", &a);
    ht_set(&ht, "second", &b);
    ht_set(&ht, "third", &c);

    ht_resize(&ht, 100);

    assert(ht.capacity == 100);
    assert(ht.size == 3);

    assert(ht_get(&ht, "first") == &a);
    assert(ht_get(&ht, "second") == &b);
    assert(ht_get(&ht, "third") == &c);

    ht_destroy(&ht);

    printf("test_resize_increase: PASSED\n");
}


void test_resize_min(void){
    HashTable ht;
    ht_init(&ht, 100, NULL, NULL);

    int a = 10, b = 20, c = 30;

    ht_set(&ht, "first", &a);
    ht_set(&ht, "second", &b);
    ht_set(&ht, "third", &c);

    ht_resize(&ht, 1);

    assert(ht.capacity == 1);
    assert(ht.size == 3);

    assert(slist_length(&ht.buckets[0]) == 3);

    assert(ht_get(&ht, "first") == &a);
    assert(ht_get(&ht, "second") == &b);
    assert(ht_get(&ht, "third") == &c);

    ht_destroy(&ht);

    printf("test_resize_decrease: PASSED\n");
}


void test_resize_empty(void){
    HashTable ht;
    ht_init(&ht, 10, NULL, NULL);

    ht_resize(&ht, 100);

    assert(ht.capacity == 100);
    assert(ht.size == 0);

    for(size_t i = 0; i < ht.capacity; i++){
        assert(ht.buckets[i].head == NULL);
    }

    ht_destroy(&ht);

    printf("test_resize_empty: PASSED\n");
}


void test_resize_destructor(void){
    HashTable ht;
    destructor_count = 0;

    ht_init(&ht, 10, NULL, test_destructor);

    int *a = malloc(sizeof(int));
    assert(a != NULL);

    *a = 100;

    ht_set(&ht, "number", a);

    ht_resize(&ht, 100);

    assert(destructor_count == 0);

    assert(ht_get(&ht, "number") == a);
    assert(*(int *)ht_get(&ht, "number") == 100);

    ht_destroy(&ht);

    assert(destructor_count == 1);

    printf("test_resize_destructor: PASSED\n");
}

void test_destructor_replace(void){
    HashTable ht;
    destructor_count = 0;

    ht_init(&ht, 10, NULL, test_destructor);

    int *a = malloc(sizeof(int));
    int *b = malloc(sizeof(int));

    assert(a != NULL);
    assert(b != NULL);

    *a = 10;
    *b = 20;

    ht_set(&ht, "number", a);
    ht_set(&ht, "number", b);

    assert(destructor_count == 0);
    assert(ht.size == 1);
    assert(ht_get(&ht, "number") == b);

    ht_destroy(&ht);

    assert(destructor_count == 1);

    printf("test_destructor_replace: PASSED\n");
}

int main(void){
    test_init(); 
    test_destroy();
    test_set();
    test_set_replace();
    test_contains();
    test_get();
    test_get_not_found();
    test_delete();
    test_delete_not_found();
    test_collision();
    test_traverse();
    test_traverse_empty();
    test_resize_more();
    test_resize_min();
    test_resize_empty();
    test_resize_destructor();
    test_destructor_replace();
    printf("\nALL 16 TESTS PASSED!\n");

    return 0;
}















