#include "sort.h"
#include <algorithm>
#include <cstring>

using namespace std;

void insertion_sort(internet_protocol* array[], int size, int (*compare)(const internet_protocol*, const internet_protocol*))
{
    for (int i = 1; i < size; i++)
    {
        internet_protocol* key = array[i];
        int j = i - 1;
        while (j >= 0 && compare(array[j], key) > 0)
        {
            array[j + 1] = array[j];
            j--;
        }
        array[j + 1] = key;
    }
}

int partition(internet_protocol* array[], int low, int high, int (*compare)(const internet_protocol*, const internet_protocol*))
{
    internet_protocol* pivot = array[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (compare(array[j], pivot) < 0)
        {
            i++;
            swap(array[i], array[j]);
        }
    }
    swap(array[i + 1], array[high]);
    return i + 1;
}

void quick_sort(internet_protocol* array[], int low, int high, int (*compare)(const internet_protocol*, const internet_protocol*))
{
    if (low < high)
    {
        int pi = partition(array, low, high, compare);
        quick_sort(array, low, pi - 1, compare);
        quick_sort(array, pi + 1, high, compare);
    }
}

int compare_by_usage_time(const internet_protocol* a, const internet_protocol* b)
{
    int duration_a = (a->finish.hours * 3600 + a->finish.minutes * 60 + a->finish.seconds) -
        (a->start.hours * 3600 + a->start.minutes * 60 + a->start.seconds);
    int duration_b = (b->finish.hours * 3600 + b->finish.minutes * 60 + b->finish.seconds) -
        (b->start.hours * 3600 + b->start.minutes * 60 + b->start.seconds);
    return duration_b - duration_a;
}

int compare_by_program_and_data(const internet_protocol* a, const internet_protocol* b)
{
    int program_cmp = strcmp(a->path, b->path);
    if (program_cmp == 0)
    {
        int data_a = a->receive.kbytes + a->send.kbytes;
        int data_b = b->receive.kbytes + b->send.kbytes;
        return data_b - data_a;
    }
    return program_cmp;
}
