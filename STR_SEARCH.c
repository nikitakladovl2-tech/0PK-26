#include "STR_SEARCH.h"
#include <stdio.h>
#include <string.h>



void prefix_f(char pattern[], int pi[]){
    size_t len_pattern = strlen(pattern);

    pi[0] = 0;
    for (size_t i = 1; i < len_pattern ; i++){
        int j = pi[i -1];

        while (j > 0 && pattern[i] != pattern[j]){
            j = pi[j-1];
        }
        if(pattern[i] == pattern[j]){
            j++;
        }
        pi[i] = j;
    }
}


size_t kmp_search(char text[], char pattern[], int results[]){
    size_t len_text = strlen(text);
    size_t len_pattern = strlen(pattern);

    if (len_pattern == 0 || len_text == 0){
        for (int i = 0; i < len_text; i++){
            results[i] = i;
        }
        return len_text;
    }
    if (len_pattern > len_text){
        return 0;
    }

    int pi[len_pattern];
    prefix_f(pattern, pi);


    int pos_in_res = 0;

    int j = 0;

    for (size_t i = 0; i < len_text; i++){
        while (j > 0 && text[i] != pattern[j]){
            j = pi[j - 1];
        }
        if (text[i] == pattern[j]){
            j++;
        }
        if (j == len_pattern){
            int start = i - len_pattern + 1;
            results[pos_in_res] = start;
            pos_in_res++;
            j = pi[j-1];
        }
    }
    return pos_in_res;
}

