#ifndef PROJECT_INCLUDE_DATA_H_
#define PROJECT_INCLUDE_DATA_H_
#define MAX_NAME_LEN 19
#define MAX_ADDRESS_LEN 29
#define MAX_TEL_NUM_LEN 14

struct client_payment_info {
    int Number;
    char Name[MAX_NAME_LEN + 1];
    char Surname[MAX_NAME_LEN + 1];
    char Address[MAX_ADDRESS_LEN + 1];
    char TelNumber[MAX_TEL_NUM_LEN + 1];
    double indebtedness;
    double credit_limit;
    double cash_payments;
};
typedef struct client_payment_info Data;

#endif  //  PROJECT_INCLUDE_DATA_H_
