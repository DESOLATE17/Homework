#include <stdio.h>
#include <stdlib.h>
#include "cparser.h"

int main(int argc, const char **argv) {
    if (argc != 2) {
        return -1;
    }
    const char *path_to_eml = argv[1];
   
    FILE * file = fopen(path_to_eml, "rb");
    long n;
    char *letter;
    char temp;

    if (file == NULL) {
        puts("Error openning file");
    } else {
        fseek(file, 0L, SEEK_END);
        n = ftell(file);
        fclose(file);
        letter = malloc(n);
        if (letter == NULL) {
            puts ("error");
        } else {
            file = fopen(path_to_eml, "r");
            if (file == NULL) {
                puts("can't open file");
                free (letter);
            } else {
                n = 0;
                while ((temp = getc(file)) != EOF)
                    letter[n++] = temp;
            }
        }
        parse(letter);
    }

    return 0;
}
