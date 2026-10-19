#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "STR_SEARCH.h"


void test_null_pattern(){
    int all_index[] = {0, 1, 2};
    char text[] = "123";
    int list_index[3];
    kmp_search(text, "", list_index);

    for (int i = 0; i < 3; i++){
        assert(all_index[i] == list_index[i]);  
    }
    printf("null_pattern test passed\n");
    return;
}

void test_correct_pattern(){
{
    char text[] = "213";
    int list_index[3];
    kmp_search(text, "1", list_index);
    assert(1 == list_index[0]);
}

{   size_t count;

    char text[] = "stringin";
    int list_index[2];
    count = kmp_search(text, "in", list_index);

    assert(count == 2);
    assert(list_index[0] == 3);
    assert(list_index[1] == 6);
}

{   size_t count;
    
    char text[] = "";
    int list_index[2];
    count = kmp_search(text, "in", list_index);

    assert(count == 0);

}


    printf("correct_pattern test passed\n"); 
    return;
}


void test_text_shorter_than_pattern(){
   size_t count;
    
    char text[] = "12";
    int list_index[2];
    count = kmp_search(text, "in5", list_index);
    assert(count == 0);
    printf("text_shorter_than_pattern test passed\n"); 
    return;
}



int main(void){ 
    test_text_shorter_than_pattern();
    test_null_pattern();
    test_correct_pattern();
    return 0;
}