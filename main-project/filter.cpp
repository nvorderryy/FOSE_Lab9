#include "filter.h"
#include <cstring>
#include <iostream>

internet_protocol** filter(internet_protocol* array[], int size, bool (*check)(internet_protocol* element), int& result_size)
{
    internet_protocol** result = new internet_protocol * [size];
    result_size = 0;
    for (int i = 0; i < size; i++)
    {
        if (check(array[i]))
        {
            result[result_size++] = array[i];
        }
    }
    return result;
}

bool check_protocol_by_program(internet_protocol* element)
{
    return strstr(element->path, "Skype") != nullptr;
}

bool check_protocol_by_time(internet_protocol* element)
{
    return (element->start.hours > 8) ||
        (element->start.hours == 8 && element->start.minutes > 0) ||
        (element->start.hours == 8 && element->start.minutes == 0 && element->start.seconds > 0);
}
