#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef void *Pointer;

typedef struct tDeque{

    size_t size;
    size_t capacity;
    Pointer *data;

    size_t delta; // сдвиг на начало массива
    
} Deque;

void deque_create(Deque *d){
    (*d).data = malloc(10*sizeof(void*));

    if ((*d).data == NULL){
        printf("Ошибка выделения памяти");
    }
    (*d).size = 0;
    (*d).capacity = 10;
    (*d).delta = 0;

}

bool add_capacity(Deque *d){
    size_t delta = (*d).delta;
    size_t size = (*d).size;

    if (((*d).capacity)-((*d).size) < 1){


        if ((*d).delta == 0){
            void *tmp = realloc((*d).data, (*d).capacity*10*sizeof(void*));
            if (tmp == NULL){
                printf("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ для увеличения дека");
                return false;
            } 
            (*d).capacity = (*d).capacity*10;
     
            (*d).data = tmp;

            return true;
        }
        else{
            void **tmp = malloc((*d).capacity*10*sizeof(void*));
            if (tmp == NULL){
                printf("ОШИБКА ВЫДЕЛЕНИЯ ПАМЯТИ для увеличения дека");
                return false;
            }

            size_t j = 0;
            for (size_t i = 0; i < size; i++){
                if (i + delta < (*d).capacity){
                    tmp[i] = (*d).data[i + delta];

                }
                else if (i + delta >= (*d).capacity){
                    tmp[i] = (*d).data[j++];
                }    
            }
            free((*d).data);
            (*d).data = tmp;
            (*d).delta = 0;
            (*d).capacity = (*d).capacity*10;
        }
    }
     return true; }

void deque_destroy(Deque *d){

    if ((*d).data != NULL){
        free((*d).data);
    }
    (*d).size = 0;
    (*d).capacity = 0;
    (*d).delta = 0;

}

size_t deque_size(Deque *d){
    return (*d).size;
}

void deque_push_back(Deque *d, void *elem){
    bool succes = true;

    if (((*d).capacity)-((*d).size) < 1){
        succes = add_capacity(d);
    }
    if (succes != true){
        printf("Не удалось расширить дек");
        return;
    }
    ((*d).data)[((*d).size + (*d).delta)%(*d).capacity] = elem; 
    (*d).size++;
    }

void deque_push_front(Deque *d, void *elem){

    bool succes = true;

    if (((*d).capacity)-((*d).size) < 1){
        succes = add_capacity(d);
    }

    if (succes == true){
            // сдвигаем начало на 1 влево и вставляем в него элемен
            if ((*d).delta > 0){
                (*d).data[--(*d).delta] = elem;
                (*d).size++;
            }
            else if ((*d).delta == 0){
               (*d).delta = (*d).capacity - 1;
               (*d).data[(*d).delta] = elem;
                (*d).size++;
            }
    } 
    else {
        printf("Не удалось расширить дек");
    }         
}

Pointer deque_pop_back(Deque *d){
     if ((*d).size == 0) {
        return NULL; 
    }
    Pointer res = ((*d).data)[((*d).delta + (*d).size - 1)%(*d).capacity];
    (*d).size--;
    return res;
}

Pointer deque_pop_front(Deque *d){
        if ((*d).size == 0) {
        return NULL; 
    }
    Pointer res = ((*d).data)[(*d).delta];
    
    (*d).delta = ((*d).delta + 1) % (*d).capacity;
    (*d).size--;
    return res;
}

Pointer deque_peek_back(Deque *d){
    if ((*d).size == 0) {
        return NULL; 
    }
    Pointer res = ((*d).data)[((*d).delta + (*d).size - 1)%(*d).capacity];
    return res;
}

Pointer deque_peek_front(Deque *d){
            if ((*d).size == 0) {
        return NULL; 
    }
    Pointer res = ((*d).data)[(*d).delta];
    return res;
}

void test_add_capacity(){
    Deque d;
    deque_create(&d);
    assert(d.capacity == 10);
    for (size_t i = 0; i < 102; i++){
        void *j = &i;
        deque_push_front(&d, j);
    }
    assert(d.capacity == 1000);
    printf("test_add_capacity PASSED\n");
}

void test_deque_peek_back(){
    Deque d;
    deque_create(&d);

    int a = 1;
    char b = 'c';

    void *t1 = &a;
    void *t2 = &b;

    deque_push_front(&d, t2);
    deque_push_front(&d, t1);

    assert(*(char*)deque_peek_back(&d) == 'c');

    printf("deque_push_back PASSED\n");


}

void test_deque_size(){


        Deque d;
    deque_create(&d);

    int a = 1;
    char b = 'c';

    void *t1 = &a;
    void *t2 = &b;

    deque_push_front(&d, t2);
    deque_push_front(&d, t1);

    assert(deque_size(&d)== 2);
    printf("deque_deque_size PASSED\n");

}

void test_deque_pop_back(){

    Deque d;
    deque_create(&d);

    int a = 1;
    char b = 'c';

    void *t1 = &a;
    void *t2 = &b;

    deque_push_front(&d, t2);
    deque_push_front(&d, t1);

    assert(*(char*)deque_pop_back(&d) == 'c');
    assert(deque_size(&d) == 1);
    printf("deque_pop_back PASSED\n");
}

void test_deque_pop_front(){
    
    Deque d;
    deque_create(&d);

    int a = 1;
    char b = 'c';

    void *t1 = &a;
    void *t2 = &b;

    deque_push_front(&d, t2);
    deque_push_front(&d, t1);

    assert(*(char*)deque_pop_front(&d) == 1);
    assert(deque_size(&d) == 1);
    printf("deque_pop_front PASSED\n");
}

void test_deque_peek_front(){
    
    Deque d;
    deque_create(&d);

    int a = 1;
    char b = 'c';

    void *t1 = &a;
    void *t2 = &b;

    deque_push_front(&d, t2);
    deque_push_front(&d, t1);

    assert(*(char*)deque_peek_front(&d) == 1);
    assert(deque_size(&d) == 2);
    printf("deque_peek_front PASSED\n");
}

int main(void){  
    test_add_capacity();
    test_deque_peek_back();
    test_deque_size();
    test_deque_pop_back();
    test_deque_pop_front();
    test_deque_peek_front();
    test_deque_peek_back();
    return 0;
}