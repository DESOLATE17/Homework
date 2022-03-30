#include "write_data.h"
#include "read_data.h"

void test_write_to_file() {
    const char *filename = "test.dat";
    Data expected_data = {1, "Max", "Ivanov", "Russia, Moscow", "89060000001", 10000, 150000, 505.5};

    FILE *test_file = fopen(filename, "w+");
    if (test_file == NULL) {
        perror("Error opening file");
        return;
    }
    write_client_inf_to_file(test_file, &expected_data);

    Data got_data;
    read_client_inf_from_file(test_file, &got_data);

    if (expected_data.Number != got_data.Number) {
        perror("Error: expected equality");
    }

    fclose(test_file);
}
