#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include "bubble_sort.h"



int float_compare(const void* a, const void* b){
    float x =  *(const float *)a;
    float y =  *(const float *)b;
    if (x > y){
        return 1;
    }
    if (x < y){
        return -1;
    }
    return 0;   
}

int int_compare(const void* a, const void* b){
    int x =  *(const int *)a;
    int y =  *(const int *)b;
    if (x > y){
        return 1;
    }
    if (x < y){
        return -1;
    }
    return 0;   
}

int strlen_compare(const void* a, const void* b){
    const char *x = *(const char **)a;
    const char *y = *(const char **)b;
    if (strlen(x) > strlen(y)){
        return 1;
    }
    if (strlen(x) < strlen(y)){
        return -1;
    }
    return 0;   
}

int char_compare(const void* a, const void* b){
    const char x = *(const char *)a;
    const char y = *(const char *)b;
    if (x > y){
        return 1;
    }
    if (x < y){
        return -1;
    }
    return 0;   
}



void tests_int(void){
    {int arr[1] = {0};
    bubble_sort(arr, 1, sizeof(int), int_compare);
    assert(arr[0] == 0);
}
    {int arr[] = {7, 1, 2, 8};
    bubble_sort(arr, 4, sizeof(int), int_compare);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 7);
    assert(arr[3] == 8);
}
    {int arr[] = {1, 2, 7, 8};
    bubble_sort(arr, 4, sizeof(int), int_compare);
    assert(arr[0] == 1);
    assert(arr[1] == 2);
    assert(arr[2] == 7);
    assert(arr[3] == 8);
}

    {int arr[] = {4, 4, 4, 4};
    bubble_sort(arr, 4, sizeof(int), int_compare);
    assert(arr[0] == 4);
    assert(arr[1] == 4);
    assert(arr[2] == 4);
    assert(arr[3] == 4);
}

    {int arr[] = {5, 4, 3, 2};
    bubble_sort(arr, 4, sizeof(int), int_compare);
    assert(arr[0] == 2);
    assert(arr[1] == 3);
    assert(arr[2] == 4);
    assert(arr[3] == 5);
}

    {int arr[] = {1, 3, 1, 3};
    bubble_sort(arr, 4, sizeof(int), int_compare);
    assert(arr[0] == 1);
    assert(arr[1] == 1);
    assert(arr[2] == 3);
    assert(arr[3] == 3);
}
    printf("INT TESTS PASSED\n");
    return;
}



void tests_float(void){
    float epsilon = 0.0001;
    {float arr[1] = {0};
    bubble_sort(arr, 1, sizeof(float), float_compare);
    assert(fabsf(arr[0]) < epsilon);
}
    {float arr[4] = {0, 1.0, 2.0, 3.0};
    bubble_sort(arr, 4, sizeof(float), float_compare);
    assert(fabsf(arr[0]) < epsilon);
    assert(fabsf(arr[1] - 1) < epsilon);
    assert(fabsf(arr[2] - 2) < epsilon);
    assert(fabsf(arr[3] - 3) < epsilon);

}
    {float arr[4] = {3.0, 2.0, 1.0 , 4.0};
    bubble_sort(arr, 4, sizeof(float), float_compare);
    assert(fabsf(arr[0] - 1) < epsilon);
    assert(fabsf(arr[1] - 2) < epsilon);
    assert(fabsf(arr[2] - 3) < epsilon);
    assert(fabsf(arr[3] - 4) < epsilon);

}

    {float arr[4] = {4.0, 4.0, 4.0, 4.0};
    bubble_sort(arr, 4, sizeof(float), float_compare);
    assert(fabsf(arr[0] - 4) < epsilon);
    assert(fabsf(arr[1] - 4) < epsilon);
    assert(fabsf(arr[2] - 4) < epsilon);
    assert(fabsf(arr[3] - 4) < epsilon);

}

    {float arr[4] = {3.0, 2.0, 1.0, 0.0};
    bubble_sort(arr, 4, sizeof(float), float_compare);
    assert(fabsf(arr[0]) < epsilon);
    assert(fabsf(arr[1] - 1) < epsilon);
    assert(fabsf(arr[2] - 2) < epsilon);
    assert(fabsf(arr[3] - 3) < epsilon);

}

    {float arr[4] = {1.0, 3.0, 1.0, 3.0};
    bubble_sort(arr, 4, sizeof(float), float_compare);
    assert(fabsf(arr[0] - 1) < epsilon);
    assert(fabsf(arr[1] - 1) < epsilon);
    assert(fabsf(arr[2] - 3) < epsilon);
    assert(fabsf(arr[3] - 3) < epsilon);

}
    printf("FLOAT TESTS PASSED\n");
    return;
}

void tests_str(void){
    
    {const char *arr[] = {"fa"};

    bubble_sort(arr, 1, sizeof(const char *), strlen_compare);
    assert(strcmp(arr[0], "fa") == 0);
}

    {const char *arr[4] = {"a", "ab", "abc", "abcd"};
    bubble_sort(arr, 4, sizeof(const char *), strlen_compare);
    assert(strcmp(arr[0], "a") == 0);
    assert(strcmp(arr[1], "ab") == 0);
    assert(strcmp(arr[2], "abc") == 0);
    assert(strcmp(arr[3], "abcd") == 0);

}
    {const char *arr[4] = {"abcd", "abc", "ab", "a"};
    bubble_sort(arr, 4, sizeof(const char *), strlen_compare);
    assert(strcmp(arr[0], "a") == 0);
    assert(strcmp(arr[1], "ab") == 0);
    assert(strcmp(arr[2], "abc") == 0);
    assert(strcmp(arr[3], "abcd") == 0);

}

    {const char *arr[4] = {"a", "a", "a", "a"};
    bubble_sort(arr, 4, sizeof(const char *), strlen_compare);
    assert(strcmp(arr[0], "a") == 0);
    assert(strcmp(arr[1], "a") == 0);
    assert(strcmp(arr[2], "a") == 0);
    assert(strcmp(arr[3], "a") == 0);

}

    {const char *arr[4] = {"a", "ab", "a", "ab"};
    bubble_sort(arr, 4, sizeof(const char *), strlen_compare);
    assert(strcmp(arr[0], "a") == 0);
    assert(strcmp(arr[1], "a") == 0);
    assert(strcmp(arr[2], "ab") == 0);
    assert(strcmp(arr[3], "ab") == 0);

}

    {const char *arr[4] = {"abcd", "ab", "ab", "a"};
    bubble_sort(arr, 4, sizeof(const char *), strlen_compare);
    assert(strcmp(arr[0], "a") == 0);
    assert(strcmp(arr[1], "ab") == 0);
    assert(strcmp(arr[2], "ab") == 0);
    assert(strcmp(arr[3], "abcd") == 0);

}
    printf("STR TESTS PASSED\n");
    return;
    
}

void tests_char(void){
    
    {
    char q = 'q';
    char arr[] = {q};

    bubble_sort(arr, 1, sizeof(char), char_compare);
    assert(arr[0] == q);
}

    {
    char a = 'a', b = 'b', c = 'c', d = 'd';
    char arr[] = {d, b, c, a};
    
    bubble_sort(arr, 4, sizeof(char), char_compare);
    assert(arr[0] == a);
    assert(arr[1] == b);
    assert(arr[2] == c);
    assert(arr[3] == d);

}

    {
    char a = 'a', b = 'b', c = 'c', d = 'd';
    char arr[] = {d, b, d, b};
    
    bubble_sort(arr, 4, sizeof(char), char_compare);
    assert(arr[0] == b);
    assert(arr[1] == b);
    assert(arr[2] == d);
    assert(arr[3] == d);

}


    {
    char a = 'a', b = 'b', c = 'c', d = 'd';
    char arr[] = {a, a, a, a};
    
    bubble_sort(arr, 4, sizeof(char), char_compare);
    assert(arr[0] == a);
    assert(arr[1] == a);
    assert(arr[2] == a);
    assert(arr[3] == a);

}


    {
    char a = 'a', b = 'b', c = 'c', d = 'd';
    char arr[] = {a, b, c, d};
    
    bubble_sort(arr, 4, sizeof(char), char_compare);
    assert(arr[0] == a);
    assert(arr[1] == b);
    assert(arr[2] == c);
    assert(arr[3] == d);

}   
    printf("CHAR TESTS PASSED\n");
    return;
}


int main(){
    tests_int();
    tests_float();
    tests_str();
    tests_char();
    return 0;
}

