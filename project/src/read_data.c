#include "read_data.h"
#define STR(X) STR2(X)
#define STR2(X) STR3(X)
#define STR3(x) #x

int read_client_inf_from_console(Data *client) {
    return scanf(
            " %d%"STR(MAX_NAME_LEN)"s%"STR(MAX_NAME_LEN)"s%"STR(MAX_ADDRESS_LEN)"s%"STR(
            MAX_TEL_NUM_LEN)"s%lf%lf%lf",
            &client->Number, client->Name, client->Surname, client->Address, client->TelNumber,
             &client->indebtedness, &client->credit_limit, &client->cash_payments);
}

int read_transfer_inf_from_console(Data *transfer) {
    return scanf("%d %lf", &transfer->Number, &transfer->cash_payments);
}

int read_client_inf_from_file(FILE *client_inf, Data *client) {
    return fscanf(client_inf, "%d%"STR(MAX_NAME_LEN)"s%"STR(MAX_NAME_LEN)"s%"STR(MAX_ADDRESS_LEN)"s%"STR(
        MAX_TEL_NUM_LEN)"s%lf%lf%lf", &client->Number, client->Name, client->Surname,
        client->Address, client->TelNumber, &client->indebtedness, &client->credit_limit,
        &client->cash_payments);
}

int read_transaction_inf_from_file(FILE *transaction_inf, Data *transfer) {
    return fscanf(transaction_inf, "%d %lf", &transfer->Number, &transfer->cash_payments);
}
