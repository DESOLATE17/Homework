#ifndef PROJECT_INCLUDE_WRITE_DATA_H_
#define PROJECT_INCLUDE_WRITE_DATA_H_
#include "Data.h"
#include <stdio.h>

void print_transfer_data_fields();
void print_client_data_fields();
void write_client_inf_to_file(FILE *client_inf, Data *client);
void write_transaction_inf_to_file(FILE *transaction_inf, Data *transfer);

#endif  // PROJECT_INCLUDE_WRITE_DATA_H_
