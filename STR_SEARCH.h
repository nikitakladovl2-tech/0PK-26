#ifndef STR_SEARCH_H
#define STR_SEARCH_H


#include <stddef.h>
void prefix_f(char pattern[], int pi[]);
size_t kmp_search(char text[], char pattern[], int results[]);

#endif