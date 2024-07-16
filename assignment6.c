/*************************************/
    /* Name: Oomat Latipov */
    /* NetID: U13921223 */
    /* Program Description: This program */
    /* can manage checking and savings accounts. */
/*************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Maximum number of accounts that can be created
#define MAX_ACCOUNTS 100

typedef struct {
    int account_number; // 4-digit account number
    char account_type; // 'c' for checking, 's' for savings
    char account_holder_name[100]; // Name of the account holder
    char open_date[11]; // Date when the account was opened (YYYY-MM-DD)
    double balance; // Balance of the account
} Account;

// Array and number to store account information, and the number of acoounts
Account accounts[MAX_ACCOUNTS];
int account_count = 0;

// Function to print the main menu
void print_main_menu() {
    printf("******* Main menu *******\n");
    printf("c(reate an account)\n");
    printf("d(eposit money)\n");
    printf("w(ithdraw money)\n");
    printf("s(sort and print accounts)\n");
    printf("q(uit program)\n");
    printf("*************************\n");
    printf("Enter operation code (c, d, w, s, q): ");
}

// Function to validate the account number (must be between 1000 and 9999)
int validate_account_number(int account_number) {
    return account_number >= 1000 && account_number <= 9999;
}

// Function to validate the account type ('c' or 's')
int validate_account_type(char account_type) {
    return account_type == 'c' || account_type == 's';
}

// Function to validate the date format (must be YYYY-MM-DD)
int validate_date_format(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;

    int year, month, day;
    if (sscanf(date, "%d-%d-%d", &year, &month, &day) != 3) return 0;
    if (year == 0 || month == 0 || day == 0) return 0;
    if (year < 1900 || year > 2100) return 0;
    if (month < 1 || month > 12) return 0;
    if (day < 1 || day > 31) return 0;
    return 1;
}

// Function to create a new account
void create_account() {
    if (account_count >= MAX_ACCOUNTS) { // Check if account limit is reached
        printf("Account limit reached.\n");
        return;
    }

    Account new_account;
    int valid = 0;

    // Validate account number
    while (!valid) { 
        printf("Enter account number (4 digits): ");
        scanf("%d", &new_account.account_number);
        if (!validate_account_number(new_account.account_number)) {
            printf("Enter a number between 1000 and 9999.\n");
        } else {
            valid = 1;
        }
    }

    valid = 0;
    while (!valid) {
        printf("Enter account type: c(hecking), s(avings)\n");
        printf("c or s: ");
        scanf(" %c", &new_account.account_type);

        // Convert to lowercase
        new_account.account_type = tolower(new_account.account_type);
        if (!validate_account_type(new_account.account_type)) {
            printf("Wrong account type. Enter c or s.\n");
        } else {
            valid = 1;
        }
    }

    // Get account holder's name
    printf("Enter account holder's name: ");
    scanf(" %[^\n]", new_account.account_holder_name);

    valid = 0;

    // Validate open date
    while (!valid) {
        printf("Enter open date (YYYY-MM-DD): ");
        scanf("%s", new_account.open_date);
        if (!validate_date_format(new_account.open_date)) {
            printf("%s Wrong date format.\n", new_account.open_date);
        } else {
            valid = 1;
        }
    }

    valid = 0;

    // Validate initial balance (must be positive)
    while (!valid) {
        printf("Enter balance (number only): $ ");
        scanf("%lf", &new_account.balance);
        if (new_account.balance < 0) {
            printf("Balance must be a positive number.\n");
        } else {
            valid = 1;
        }
    }

    // Add the new account to the accounts array and increment the account count
    accounts[account_count++] = new_account;
    printf("Account %d is created.\n\n", new_account.account_number);
}

// Function to deposit money into an account
void deposit_money() {
    int account_number;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &account_number);

    // Find the account by account number
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].account_number == account_number) {

            // Validate deposit amount (must be positive)
            do {
                printf("Enter amount (> 0, number only): $ ");
                scanf("%lf", &amount);
                if (amount <= 0) {
                    printf("Amount must be greater than 0.\n");
                }
            } while (amount <= 0);

            // Update account balance
            accounts[i].balance += amount;
            printf("Remaining balance: $ %.2f\n\n", accounts[i].balance);
            return;
        }
    }
    printf("Account not found.\n");
}

// Function to withdraw money from an account
void withdraw_money() {
    int account_number;
    double amount;
    printf("Enter account number: ");
    scanf("%d", &account_number);

    // Find the account by account number
    for (int i = 0; i < account_count; i++) {
        if (accounts[i].account_number == account_number) {
            
            // Validate withdrawal amount (must be positive)
            do {
                printf("Enter amount (> 0, number only): $ ");
                scanf("%lf", &amount);
                if (amount <= 0) {
                    printf("Amount must be greater than 0.\n");
                }
            } while (amount <= 0);

            // Check if there are sufficient funds
            if (accounts[i].balance >= amount) {
                // Update account balance
                accounts[i].balance -= amount;
                printf("Remaining balance: $ %.2f\n\n", accounts[i].balance);
            } else {
                printf("Insufficient balance.\n\n");
            }
            return;
        }
    }
    printf("Account not found.\n");
}

// Comparison function for sorting by account number
int compare_by_account_number(const void *a, const void *b) {
    return ((Account *)a)->account_number - ((Account *)b)->account_number;
}

// Comparison function for sorting by holder name
int compare_by_holder_name(const void *a, const void *b) {
    const Account *account_a = (const Account *)a;
    const Account *account_b = (const Account *)b;

    const char *name_a = account_a->account_holder_name;
    const char *name_b = account_b->account_holder_name;

    // Compare characters one by one
    while (*name_a && *name_b) {
        char char_a = tolower(*name_a); // Convert to lowercase for comparison
        char char_b = tolower(*name_b);

        if (char_a != char_b) {
            return char_a - char_b; // Return difference if characters differ
        }

        // If characters are the same case-insensitively, compare case-sensitively
        if (*name_a != *name_b) {
            return *name_a - *name_b;
        }

        name_a++;
        name_b++;
    }

    // If one string is a prefix of the other, the shorter string is considered smaller
    return *name_a - *name_b;
}

// Comparison function for sorting by open date
int compare_by_open_date(const void *a, const void *b) {
    return strcmp(((Account *)a)->open_date, ((Account *)b)->open_date);
}

// Comparison function for sorting by balance
int compare_by_balance(const void *a, const void *b) {
    double balance_diff = ((Account *)a)->balance - ((Account *)b)->balance;
    if (balance_diff > 0) return 1;
    if (balance_diff < 0) return -1;
    return 0;
}

// Function to sort and print accounts based on a selected field
void sort_and_print_accounts() {
    char field;
    printf("Enter the sorting field: a(ccount number), h(older name), o(pen date), b(alance)\n");
    printf("a, h, o or b: ");
    scanf(" %c", &field);

    field = tolower(field); // Convert to lowercase

    // Sort accounts based on the selected field
    switch (field) {
        case 'a':
            qsort(accounts, account_count, sizeof(Account), compare_by_account_number);
            break;
        case 'h':
            qsort(accounts, account_count, sizeof(Account), compare_by_holder_name);
            break;
        case 'o':
            qsort(accounts, account_count, sizeof(Account), compare_by_open_date);
            break;
        case 'b':
            qsort(accounts, account_count, sizeof(Account), compare_by_balance);
            break;
        default:
            printf("Invalid sorting field.\n");
            return;
    }

    // Print sorted accounts
    printf("#### Type Holder name                    Open date          Balance\n");
    printf("------------------------------------------------------------------------\n");
    for (int i = 0; i < account_count; i++) {
        printf("%4d   %-6c %-30s %-15s %10.2f\n",
            accounts[i].account_number,
            toupper(accounts[i].account_type),
            accounts[i].account_holder_name,
            accounts[i].open_date,
            accounts[i].balance);
    }
    printf("------------------------------------------------------------------------\n\n");
}

int main() {
    char operation;
    while (1) {
        print_main_menu();
        scanf(" %c", &operation);
        switch (operation) {
            case 'c':
                create_account();
                break;
            case 'd':
                deposit_money();
                break;
            case 'w':
                withdraw_money();
                break;
            case 's':
                sort_and_print_accounts();
                break;
            case 'q':
                return 0;
            default:
                printf("Invalid operation code.\n");
        }
    }
    return 0;
}
