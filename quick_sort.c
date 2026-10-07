#include "quick_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void quick_sort(void* p_array, size_t i, size_t size , int (*p_compare_f)(const void *a, const void *b)){
    if (p_array == NULL || size == 0 || i <= 1 || p_compare_f == NULL) {
        return;
    }

    typedef struct {
        int left;
        int right;
    } Range;

    Range stack[i];
    size_t top = 0;

    char *base = p_array;

    void *tmp = malloc(size);

    if (tmp == NULL){
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    // start sort
    stack[top++] = (Range){0, i - 1};

    while (top > 0){

        Range current = stack[--top];

        char *right = base + size * current.right;

        int index_pivot = current.right;
        char *border = base + size * current.left;

        // у нас есть указатели на левую и правую ячеку 
        for (int j = current.left; j < current.right; j++){
            char *cur = base + size * j;
            if (p_compare_f(cur, right) <= 0){
                memcpy(tmp, cur, size);
                memcpy(cur, border, size);
                memcpy(border, tmp, size);
                border = border + size;
            }
        }

        memcpy(tmp, right, size);
        memcpy(right, border, size);
        memcpy(border, tmp, size);
        
        index_pivot = (border - base)/size;

        if (current.left < index_pivot - 1){
            stack[top++] = (Range){current.left, index_pivot - 1};
        }
        if (current.right > index_pivot + 1){
            stack[top++] = (Range){index_pivot + 1, current.right};
        }
    }

    // end sort
    free(tmp);
    return;
}














