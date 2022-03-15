#include "utils.h"

size_t timer_from(int from) {
    size_t counter = 0;
    for (int i = from; i >= 0; --i) {
        ++counter;
        if (i > 0) {
        printf("%d ", i);
        } else {
            printf("%d\n", i);
        }
    }
    return counter;
}

int custom_pow(int base, int power) {
    int base_first = base;
    if (power == 0) {
        return 1;
    }
    for (int i = 1; i < power; ++i) {
        base *= base_first;
    }
    return base;
}
