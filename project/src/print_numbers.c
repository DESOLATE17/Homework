#include "print_numbers.h"

void print_numbers(int number) {
    if (number == 1) {
        printf("%d", number);
    } else {
        if (number > 0) {
        print_numbers(number - 1);
        } else {
            print_numbers(number + 1);
        }
        printf(" %d", number);
    }
}
