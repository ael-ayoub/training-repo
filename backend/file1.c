#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[32];
    double balance;
} Account;

Account *create_account(int id, const char *name, double balance) {
    Account *acc = malloc(sizeof(Account));
    if (!acc) return NULL;
    acc->id = id;
    snprintf(acc->name, sizeof(acc->name), "%s", name);
    acc->balance = balance;
    return acc;
}

int deposit(Account *acc, double amount) {
    if (!acc || amount <= 0) return -1;
    acc->balance += amount;
    return 0;
}

int withdraw(Account *acc, double amount) {
    if (!acc || amount <= 0 || amount > acc->balance) return -1;
    acc->balance -= amount;
    return 0;
}

int main(void) {
    Account *acc = create_account(1, "Ayoub", 250.0);
    if (!acc) {
        fprintf(stderr, "allocation failed\n");
        return EXIT_FAILURE;
    }

    deposit(acc, 100.0);
    if (withdraw(acc, 50.0) != 0) {
        fprintf(stderr, "withdraw failed\n");
    }

    printf("Account #%d (%s): $%.2f\n", acc->id, acc->name, acc->balance);

    free(acc);
    return EXIT_SUCCESS;
}
