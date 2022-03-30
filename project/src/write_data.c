#include "write_data.h"
#define FORMAT_OF_TRANSFER_INF_FIELDS 12.2
#define NAME_FIELDS_WIDTH 11
#define NUMBER_FIELD_WIDTH 12
#define ADDRESS_FIELD_WIDTH 16
#define TELNUM_FIELD_WIDTH 20
#define TRANSFER_NUMBER_SIZE 3
#define TRANSFER_CASH_PAYMENT_SIZE 6.2
#define STR(X) STR2(X)
#define STR2(X) STR3(X)
#define STR3(x) #x

void print_transfer_data_fields() {
    printf("%s\n%s\n",
           "1 Account number: ",
           "2 Client cash payments: ");
}

void print_client_data_fields() {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
        "1 Number account: ",
        "2 Client name: ",
        "3 Surname: ",
        "4 Client address: ",
        "5 Client phone number: ",
        "6 Client indebtedness: ",
        "7 Client credit limit: ",
        "8 Client cash payments: ");
}

void write_client_inf_to_file(FILE *client_inf, Data *client) {
    fprintf(client_inf,
        "%-"STR(NUMBER_FIELD_WIDTH)"d%-"STR(NAME_FIELDS_WIDTH)"s%-"STR(NAME_FIELDS_WIDTH)
        "s%-"STR(ADDRESS_FIELD_WIDTH)"s%"STR(TELNUM_FIELD_WIDTH)"s%"STR(
        FORMAT_OF_TRANSFER_INF_FIELDS)"f%"STR(FORMAT_OF_TRANSFER_INF_FIELDS)"f%"STR(
        FORMAT_OF_TRANSFER_INF_FIELDS)"f\n", client->Number, client->Name, client->Surname,
        client->Address, client->TelNumber, client->indebtedness, client->credit_limit,
        client->cash_payments);
}

void write_transaction_inf_to_file(FILE *transaction_inf, Data *transfer) {
    fprintf(transaction_inf, "%-"STR(
    TRANSFER_NUMBER_SIZE)"d%-"STR(
    TRANSFER_CASH_PAYMENT_SIZE)"f\n", transfer->Number, transfer->cash_payments);
}
