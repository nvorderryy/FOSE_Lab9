#ifndef INTERNET_PROTOCOL_H
#define INTERNET_PROTOCOL_H

#include "constants.h"

struct time1 {
    int hours;
    int minutes;
    int seconds;
};

struct weight {
    int kbytes;
};

struct internet_protocol {
    time1 start;
    time1 finish;
    weight receive;
    weight send;
    char path[MAX_STRING_SIZE];
};

#endif
