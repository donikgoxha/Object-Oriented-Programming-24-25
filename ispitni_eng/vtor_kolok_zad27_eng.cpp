#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TRANSACTIONS 500

// Structure to represent a transaction
struct Transaction {
    int day;
    int month;
    int year;
    int amount;
    char currency[4]; // 3 characters for currency + 1 for '\0'
};

// Function to check if a date is in the desired range (from 01/01/2013 to 31/12/2015)
int isInDateRange(int day, int month, int year) {
    // Check if the year is between 2013 and 2015
    if (year < 2013 || year > 2015) return 0;

    // If the year is 2013, the month must be >= 1, and day >= 1
    if (year == 2013 && (month < 1 || (month == 1 && day < 1))) return 0;

    // If the year is 2015, the month must be <= 12, and day <= 31
    if (year == 2015 && (month > 12 || (month == 12 && day > 31))) return 0;

    // For 2014, all months and days are valid.
    return 1;
}

int main() {
    int N; // Number of transactions
    struct Transaction transactions[MAX_TRANSACTIONS];

    // Read the number of transactions
    scanf("%d", &N);

    // Read each transaction
    for (int i = 0; i < N; i++) {
        // Read the date, amount, and currency for each transaction
        scanf("%d/%d/%d %d %s", &transactions[i].day, &transactions[i].month,
              &transactions[i].year, &transactions[i].amount, transactions[i].currency);
    }

    int totalAmount = 0;
    int transactionCount = 1; // To keep track of the transaction number

    // Print the transactions that match the criteria
    for (int i = 0; i < N; i++) {
        // Check if the transaction has currency "MKD", amount > 1000 and is within the date range
        if (strcmp(transactions[i].currency, "MKD") == 0 &&
            transactions[i].amount > 1000 &&
            isInDateRange(transactions[i].day, transactions[i].month, transactions[i].year)) {
            // Print the transaction in the specified format with its number
            printf("%d. %02d/%02d/%04d %d %s\n", transactionCount, transactions[i].day, transactions[i].month,
                   transactions[i].year, transactions[i].amount, transactions[i].currency);

            // Add the amount to the total sum
            totalAmount += transactions[i].amount;

            // Increment the transaction count
            transactionCount++;
        }
    }

    // Print the total amount
    printf("Total: %d MKD\n", totalAmount);

    return 0;
}
