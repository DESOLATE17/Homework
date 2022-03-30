#include "Data.h"
#define filename_for_transfer "transaction.dat"
#define filename_for_client_inf "client.dat"
#define filename_for_updated_inf "updated.dat"

int main(void)
{
    int choice = 0;
    Data client_data;
    Data transfer;
    FILE *client_inf;
    FILE *transaction_inf;
    FILE *updated_file;
    printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    while (scanf("%d", &choice) != -1) {
        switch (choice) {
            case 1:
                client_inf = fopen(filename_for_client_inf, "w+");
                if (client_inf == NULL) {
                    puts("No access");
                }
                else {
                    write_client_inf(client_inf, &client_data);
                    fclose(client_inf);
                }
                break;
            case 2:
                transaction_inf = fopen(filename_for_transfer, "r+");
                if (transaction_inf == NULL) {
                    puts("No access");
                }
                else {
                    write_transaction_inf(transaction_inf, &transfer);
                    fclose(transaction_inf);
                }
                break;
            case 3:
                client_inf = fopen(filename_for_client_inf, "r");
                transaction_inf = fopen(filename_for_transfer, "r");
                updated_file = fopen(filename_for_updated_inf, "w");

                if (client_inf == NULL || transaction_inf == NULL || updated_file == NULL) {
                    puts("exit");
                }

                else {
                    update_base(client_inf, transaction_inf, updated_file, &client_data, &transfer);
                    fclose(client_inf);
                    fclose(transaction_inf);
                    fclose(updated_file);
                }
                break;
            default:
                puts("error");
                break;
        }
        printf("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
    }
    return 0;
}
