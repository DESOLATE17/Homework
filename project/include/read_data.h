#ifndef PROJECT_INCLUDE_READ_DATA_H_
#define PROJECT_INCLUDE_READ_DATA_H_
#include "Data.h"
#include <stdio.h>

int read_client_inf_from_console(Data *client);
int read_client_inf_from_file(FILE *client_inf, Data *client);
int read_transfer_inf_from_console(Data *transfer);
int read_transaction_inf_from_file(FILE *transaction_inf, Data *transfer);

#endif  // PROJECT_INCLUDE_READ_DATA_H_
