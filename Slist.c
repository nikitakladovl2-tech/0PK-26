#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Slist.h"



void slist_create(Slist *a){
    if (a == NULL){
        return;
    }
    a->head = NULL;
}

void slist_prepend(Slist *a, Pointer data){
    if (a == NULL){
            return;
    }
    Node *node = malloc(sizeof(Node));

    if (node == NULL){
        printf("Ошибка выделения памяти");
        return;
    }
    node->data = data;
    node->next = a->head;
    a->head = node;
}

size_t slist_length(Slist *a){
    if (a == NULL){
            return 0;
    }
    Node *node = a->head;
    size_t length = 0;
    while (node){
        length++;
        node = node->next;
    }

    return length;
}

Pointer slist_get(Slist *list, int index){
    if (list == NULL){
            return NULL;
    }

    if (index < 0){
            return NULL;
    }

    Node *node = list->head;

    if (node == NULL){return NULL;}

    int current_index = 0;
    if (index  == current_index){
        return node->data;
    }

    while (node->next != NULL && index > current_index){


        node = node->next;
        current_index++;

        if (index == current_index){
        return node->data;
    }
    }
    return NULL;
}

Pointer slist_get_last(Slist *list){
    if (list == NULL){
            return NULL;
    }

    Node *node = list->head;

    if (node == NULL){return NULL;}
    while (node->next != NULL){
        node = node->next;
    }
    return node->data;
}

void slist_append(Slist *list, Pointer data){
    if (!list){
            return;
    }

    Node *node = list->head;

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL){
        printf("Ошибка выделения памяти");
        return;
    }

    if (!node){
        new_node->data = data;
        new_node->next = NULL;
        list->head = new_node;
        return;}

    while (node->next){
        node = node->next;
    }

    node->next = new_node;
    new_node->data = data;
    new_node->next = NULL;
}

Pointer slist_remove(Slist *list, int index){
    if (!list){return NULL;}
    if (index < 0){return NULL;}

    Node *node = list->head;

    if (!node){return NULL;}

    int current_index = 0;
    if (index  == current_index){
        Node *next_node;
        next_node = node->next;
        list->head = next_node;
        Pointer data = node->data;
        free(node);
        return data;
    }

    while (node->next != NULL && index > current_index){

        if (index - 1 == current_index){
            if (node->next == NULL){
                return NULL;
            }
            Pointer data = node->next->data;
            Node *next_next = node->next->next;
            free(node->next);
            node->next = next_next;
            return data;
        }
        node = node->next;
        current_index++;

    }

    return NULL;
}

int slist_find(Slist *list, Pointer data){
    if (list == NULL){
        return -1;
    }   

    Node *node = list->head;

    if (node == NULL){return -1;}

    int current_index = 0;

    while (node->next){
        if(node->data == data){
            return current_index;
        }
        node = node->next;
        current_index++;
    }
    
    printf("Не найдено в списке");
    return -1;
}

Pointer slist_remove_first(Slist *list, Pointer data){
    if (list == NULL){
        return NULL;
    }   

    Node *node = list->head;

    if (node == NULL){return NULL;}
    if (node->data == data){
        list->head = node->next;
        free(node);
        return data;
    }

  
    while (node->next){
        if(node->next->data == data){
            Node *next_node;
            next_node = node->next->next;
            free(node->next);
            node->next = next_node;
            return data;
        }
        node = node->next;
    }
    return NULL;
}

void slist_destroy(Slist *list){
    if (list == NULL){
        return;
    }   
    Node *node = list->head;

    if (node == NULL){return;}

    Node *tmp_node;

    while(node->next != NULL){
        tmp_node = node;
        node = node->next;
        free(tmp_node);
    }
    free(node);
    list->head = NULL;
    }

void slist_copy(Slist *dst, Slist *src){
    if (src == NULL || dst == NULL){
        return;
    }  

    Node *src_node = src->head;

    if (dst == src){
        return;
    }
    slist_destroy(dst);

    if(src_node == NULL){return;}

    Node *dst_node = malloc(sizeof(Node));
    if (dst_node == NULL){
        printf("Ошибка выделения памяти");
        return;
    }

    dst->head = dst_node;
    dst_node->data = src_node->data;
    dst_node->next = NULL;
    while(src_node->next != NULL){
        src_node = src_node->next;
        Node *new_dst_node = malloc(sizeof(Node));
        if (new_dst_node == NULL){
        printf("Ошибка выделения памяти");
        return;
    }
        new_dst_node->data = src_node->data;
        new_dst_node->next = NULL;
        dst_node->next = new_dst_node;
        dst_node = dst_node->next;

    }
}

void slist_from_array(Slist *list, Pointer *arr, size_t n){
    if (list == NULL || arr == NULL){
        printf("Некорректный указатель на список");
        return;
    }   
    slist_destroy(list);

    if (n == 0){
        list->head = NULL;
        return;
    }


    Node *node = malloc(sizeof(Node));

    if (node == NULL){
        printf("Ошибка выделения памяти");
        return;
    }

    list->head = node;

    for (size_t i = 0; i < n; i++){

        Node *new_node = malloc(sizeof(Node));
        if (new_node == NULL){
                printf("Ошибка выделения памяти");
                slist_destroy(list);
                return;
            }

        node->data = arr[i];
        node->next = new_node;
        if (i == n - 1){
            node->next = NULL;
            free(new_node);
        }
        node = node->next;
    }
}

Pointer *slist_to_array(Slist *list, size_t *n){
    if (list == NULL || n == NULL){
        return NULL;
    }   

    *n = 0;

    Node *node = list->head;

    if (node == NULL){return NULL;}

    *n = slist_length(list);

    Pointer *arr = malloc(*n * sizeof(Pointer));

    if (arr == NULL) {
        printf("Ошибка выделения памяти");
        *n = 0;
        return NULL;
    }

    for (size_t i = 0; i < *n; i++) {
        arr[i] = node->data;
        node = node->next;
    }
    return arr;
}

void slist_concat(Slist *dst, Slist *src){
    if (src == NULL || dst == NULL){
        return;
    }  

    if (dst == src){
            return;
        }

    Node *src_node = src->head;
    
    if (src_node == NULL){
        return;
    }

    Node *dst_node = dst->head;

    if(dst_node == NULL){
        dst->head = src_node;
        src->head = NULL;
        return;
    }
    while(dst_node->next){
        dst_node = dst_node->next;
    }
    dst_node->next = src_node;
    src->head = NULL;
}

void slist_foreach(Slist *list, void (*func)(Pointer data, void *arg), void *arg){
    if (list == NULL || func == NULL){
        return;
    }  
    Node *node = list->head;
    if(node == NULL){return;}
    func(node->data, arg);
    while(node->next){
        node = node->next;
        func(node->data, arg);
    }
}

int slist_find_custom(Slist *list, int (*predicate)(Pointer data, Pointer arg), Pointer arg, Pointer *out){
    if (list == NULL || predicate == NULL || out == NULL){
        return 0;
    }   
    *out = NULL;
    Node *node = list->head;
    if(node == NULL){return 0;}

    if (predicate(node->data, arg)){*out = node->data; return 1;}
    while(node->next){
        node = node->next;
        if (predicate(node->data, arg)){*out = node->data; return 1;}
    }
    return 0;
}



















































// void slist_foreach_index(Slist *list, void (*func)(Pointer data, void *arg), void *arg, int index){
//     if (list == NULL || func == NULL){
//         return;
//     }  
//     Node *node = list->head;
//     if(node == NULL){return;}
//     int current_index = 0;

//     while(node){
//         if(index == current_index){
//         func(node->data, arg);
//         }
//         current_index++;
//         if (!node){break;}
//         node = node->next;
//     }
// }



