#ifndef BUBBLE_SORT_H
#define BUBBLE_SORT_H

#include <stddef.h>

void bubble_sort(void* p_array, int i, size_t size , int (*p_compare_f)(const void *a, const void *b));

#endif






