#ifndef SORT_H
#define SORT_H

#include "internet_protocol.h"

void insertion_sort(internet_protocol* array[], int size, int (*compare)(const internet_protocol*, const internet_protocol*));
void quick_sort(internet_protocol* array[], int low, int high, int (*compare)(const internet_protocol*, const internet_protocol*));
int compare_by_usage_time(const internet_protocol* a, const internet_protocol* b);
int compare_by_program_and_data(const internet_protocol* a, const internet_protocol* b);

#endif // SORT_H
