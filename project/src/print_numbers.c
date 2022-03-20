#include "print_numbers.h"
#include <stdio.h>

void print_numbers(int number) {
    if (number == 1) {
        printf("1");
    } else {
        if (number > 0) {
        print_numbers(number - 1);
        } else {
            print_numbers(number + 1);
        }
        printf(" %d", number);
    }
}
