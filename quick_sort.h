#ifndef QUICK_SORT_H
#define QUICK_SORT_H

#include <stddef.h>

void quick_sort(void* p_array, size_t i, size_t size , int (*p_compare_f)(const void *a, const void *b));

#endif





