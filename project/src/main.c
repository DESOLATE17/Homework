#include "Data.h"
#include "read_data.h"
#include "write_data.h"
#include "test.h"
#define filename_for_transfer "transaction.dat"
#define filename_for_client_inf "record.dat"
#define filename_for_updated_inf "blackrecord.dat"

int main(void) {
    int choice = 0;
    Data client;
    Data transfer;
    FILE *client_inf;
    FILE *transaction_inf;
    FILE *updated_file;
    printf("%s%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n",
    "4 test program\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                client_inf = fopen(filename_for_client_inf, "w+");
                if (client_inf == NULL) {
                    puts("No access");
                } else {
                    print_client_data_fields();
                    while (read_client_inf_from_console(&client) == 8) {
                        write_client_inf_to_file(client_inf, &client);
                        print_client_data_fields();
                    }
                    fclose(client_inf);
                }
                break;
            case 2:
                transaction_inf = fopen(filename_for_transfer, "r+");
                if (transaction_inf == NULL) {
                    puts("No access");
                } else {
                    print_transfer_data_fields();
                    while (read_transfer_inf_from_console(&transfer) == 2) {
                        write_transaction_inf_to_file(transaction_inf, &transfer);
                        print_transfer_data_fields();
                    }
                    fclose(transaction_inf);
                }
                break;
            case 3:
                client_inf = fopen(filename_for_client_inf, "r");
                transaction_inf = fopen(filename_for_transfer, "r");
                updated_file = fopen(filename_for_updated_inf, "w");

                if (client_inf == NULL || transaction_inf == NULL || updated_file == NULL) {
                    puts("exit");
                } else {
                    while (read_client_inf_from_file(client_inf, &client) != EOF) {
                        while (read_transaction_inf_from_file(transaction_inf, &transfer) != EOF) {
                            if (client.Number == transfer.Number && transfer.cash_payments != 0) {
                            client.credit_limit += transfer.cash_payments;
                            }
                        }
                        write_client_inf_to_file(updated_file, &client);
                        rewind(transaction_inf);
                    }
                    fclose(client_inf);
                    fclose(transaction_inf);
                    fclose(updated_file);
                }
                break;
            case 4:
                test_write_to_file();
                break;
            default:
                puts("error");
                break;
        }
        printf("%s%s", "please enter action\n1 enter data client\n2 enter data transaction\n3 update base\n",
        "4 test program\n");
    }
    return 0;
}
