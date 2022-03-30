#include "Data.h"
#define FORMAT_OF_TRANSFER_INF_FIELDS 12.2
#define WIDTH_OF_NAME_FIELDS 11
#define WIDTH_OF_NUMBER_FIELD 12
#define WIDTH_OF_ADDRESS_FIELD 16
#define WIDTH_OF_TELNUM_FIELD 20
#define STR(X) STR2(X)
#define STR2(X) STR3(X)
#define STR3(x) #x

void write_client_inf(FILE *client_inf, Data *Client) {
    printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
           "1 Number account: ",
           "2 Client name: ",
           "3 Surname: ",
           "4 Client address: ",
           "5 Client phone number: ",
           "6 Client indebtedness: ",
           "7 Client credit limit: ",
           "8 Client cash payments: ");
    while (scanf(
            " %d%"STR(MAX_NAME_LEN)"s%"STR(MAX_NAME_LEN)"s%"STR(MAX_ADDRESS_LEN)"s%"STR(
                    MAX_TEL_NUM_LEN)"s%lf%lf%lf",
            &Client->Number, Client->Name, Client->Surname, Client->address, Client->TelNumber, &Client->indebtedness,
            &Client->credit_limit, &Client->cash_payments) == 8) {
        fprintf(client_inf,
                "%-"STR(WIDTH_OF_NUMBER_FIELD)"d%-"STR(WIDTH_OF_NAME_FIELDS)"s%-"STR(WIDTH_OF_NAME_FIELDS)"s%-"STR(
                        WIDTH_OF_ADDRESS_FIELD)"s%"STR(WIDTH_OF_TELNUM_FIELD)"s%"STR(
                        FORMAT_OF_TRANSFER_INF_FIELDS)"f%"STR(FORMAT_OF_TRANSFER_INF_FIELDS)"f%"STR(
                        FORMAT_OF_TRANSFER_INF_FIELDS)"f\n", Client->Number, Client->Name,
                Client->Surname,
                Client->address, Client->TelNumber, Client->indebtedness, Client->credit_limit, Client->cash_payments);
        printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
               "1 Account number: ",
               "2 Client name: ",
               "3 Surname: ",
               "4 Client address: ",
               "5 Client phone number: ",
               "6 Client indebtedness: ",
               "7 Client credit limit: ",
               "8 Client cash payments: ");
    }
}

void write_transaction_inf(FILE *transaction_inf, Data *transfer) {
    printf("%s\n%s\n",
           "1 Account number: ",
           "2 Client cash payments: ");
    while (scanf("%d %lf", &transfer->Number, &transfer->cash_payments) != 2) {
        fprintf(transaction_inf, "%-3d%-6.2f\n", transfer->Number, transfer->cash_payments);
        printf("%s\n%s\n",
               "1 Account number:",
               "2 Client cash payments: ");
    }
}

void update_base(FILE *client_inf, FILE *transaction_inf, FILE *updated_file, Data *client_data, Data *transfer) {
    while (fscanf(client_inf, "%d%"STR(MAX_NAME_LEN)"s%"STR(MAX_NAME_LEN)"s%"STR(MAX_ADDRESS_LEN)"s%"STR(
                          MAX_TEL_NUM_LEN)"s%lf%lf%lf", &client_data->Number, client_data->Name, client_data->Surname,
                  client_data->address, client_data->TelNumber, &client_data->indebtedness, &client_data->credit_limit,
                  &client_data->cash_payments) != EOF) {
        while (fscanf(transaction_inf, "%d %lf", &transfer->Number, &transfer->cash_payments) != EOF) {
            if (client_data->Number == transfer->Number && transfer->cash_payments != 0) {
                client_data->credit_limit += transfer->cash_payments;
            }
        }
        fprintf(updated_file, "%-"STR(WIDTH_OF_NUMBER_FIELD)"d%-"STR(WIDTH_OF_NAME_FIELDS)"s%-"STR(WIDTH_OF_NAME_FIELDS)"s%-"STR(
                        WIDTH_OF_ADDRESS_FIELD)"s%"STR(WIDTH_OF_TELNUM_FIELD)"s%"STR(
                                     FORMAT_OF_TRANSFER_INF_FIELDS)"f%"STR(FORMAT_OF_TRANSFER_INF_FIELDS)"f%"STR(
                                     FORMAT_OF_TRANSFER_INF_FIELDS)"f\n", client_data->Number, client_data->Name,
                client_data->Surname, client_data->address, client_data->TelNumber, client_data->indebtedness,
                client_data->credit_limit, client_data->cash_payments);
        rewind(transaction_inf);
    }
}
