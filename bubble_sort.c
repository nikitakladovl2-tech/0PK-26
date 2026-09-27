 #include "bubble_sort.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(void* p_array, int i, size_t size , int (*p_compare_f)(const void *a, const void *b)){
    if (i <= 1){
        return;
    }
    char *cur = p_array;
    int transport = 1;
    void *tmp = malloc(size);
    if (tmp == NULL){
        printf("Ошибка выделения памяти!\n");
        exit(1);
    }
    for (;transport != 0;){
        transport = 0;
        for (int j = 0; j < i - 1; j++){
            if (p_compare_f(cur, cur + size) > 0){  
                memcpy(tmp, cur, size);
                memcpy(cur, cur + size, size);
                memcpy(cur + size, tmp, size);
                transport++;    
            }
            cur = cur + size;
        }
        cur = p_array;
        
    }
    free(tmp);
    return;
}














