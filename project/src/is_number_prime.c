#include "prime_function.h"

int is_number_prime(int number) {
    if (number <= 1) {
        return 0;
    }
    int i = 2;
    while (i*i <= abs(number)) {
        if (number % i == 0) {
            return 0;
        }
        ++i;
    }
    return 1;
}
