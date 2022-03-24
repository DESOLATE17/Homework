#include "utils.h"
#include <stdio.h>

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i > 0; --i) {
        ++counter;
        printf("%d ", i);
    }
    if (from < 0) {
        return counter;
    }
    puts("0");
    return counter + 1;
}

int custom_pow(int base, int power) {
    if (power == 0) {
        return 1;
    }
    int base_first = base;
    for (int i = 1; i < power; ++i) {
        base *= base_first;
    }
    return base;
}
