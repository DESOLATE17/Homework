#ifndef PROJECT_INCLUDE_DATA_H_
#define PROJECT_INCLUDE_DATA_H_
#include <stdio.h>
#define MAX_NAME_LEN 19
#define MAX_ADDRESS_LEN 29
#define MAX_TEL_NUM_LEN 14

struct masterRecord
{
    int Number;
    char Name[MAX_NAME_LEN + 1];
    char Surname[MAX_NAME_LEN + 1];
    char address[MAX_ADDRESS_LEN + 1];
    char TelNumber[MAX_TEL_NUM_LEN + 1];
    double indebtedness;
    double credit_limit;
    double cash_payments;
};
typedef struct masterRecord Data;

void write_client_inf(FILE *client_inf, Data *Client);
void write_transaction_inf(FILE *transaction_inf, Data *transfer);
void update_base(FILE *client_inf, FILE *transaction_inf, FILE *updated_file, Data *client_data, Data *transfer);

#endif //PROJECT_INCLUDE_DATA_H_