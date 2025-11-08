#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to record expense details
struct Expense {
    char date[11]; // Format: DD-MM-YYYY
    float amount;
    char category[50];
    char description[100];
};

// Global variables
struct Expense expenses[100]; // Maximum of 100 expenses
int expenseCount = 0;

// Function to display all expenses
void displayExpenses() {
    if (expenseCount == 0) {
        printf("\nNo expenses to display!\n");
        return;
    }

    printf("\n--- Expense List ---\n");
    for (int i = 0; i < expenseCount; i++) {
        printf("%d. Date: %s, Amount: %.2f, Category: %s, Description: %s\n",
               i + 1, expenses[i].date, expenses[i].amount,
               expenses[i].category, expenses[i].description);
    }
}

// Main program
int main() {
    FILE *file;
    int choice;

    // Load expenses from file
    file = fopen("expenses.dat", "rb");
    if (file != NULL) {
        fread(&expenseCount, sizeof(int), 1, file);
        fread(expenses, sizeof(struct Expense), expenseCount, file);
        fclose(file);
    }

    while (1) {
        printf("\nPersonal Expense Tracker\n");
        printf("1. Add Expense\n");
        printf("2. Edit Expense\n");
        printf("3. Delete Expense\n");
        printf("4. Display All Expenses\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) { // Add Expense
            if (expenseCount >= 100) {
                printf("Expense list is full!\n");
                continue;
            }
            struct Expense newExpense;
            printf("Enter date (DD-MM-YYYY): ");
            scanf(" %[^\n]", newExpense.date);

            // Validate date format
            if (strlen(newExpense.date) != 10 || newExpense.date[2] != '-' || newExpense.date[5] != '-') {
                printf("Invalid date format. Please use DD-MM-YYYY.\n");
                continue;
            }

            printf("Enter amount: ");
            scanf("%f", &newExpense.amount);
            getchar(); // Consume newline character
            printf("Enter category: ");
            fgets(newExpense.category, sizeof(newExpense.category), stdin);
            newExpense.category[strcspn(newExpense.category, "\n")] = '\0'; // Remove newline

            printf("Enter description: ");
            fgets(newExpense.description, sizeof(newExpense.description), stdin);
            newExpense.description[strcspn(newExpense.description, "\n")] = '\0'; // Remove newline

            expenses[expenseCount++] = newExpense;
            printf("Expense added successfully!\n");

        } else if (choice == 2) { // Edit Expense
    int id;
    printf("Enter expense ID to edit (1 to %d): ", expenseCount);
    scanf("%d", &id);
    if (id < 1 || id > expenseCount) {
        printf("Invalid expense ID.\n");
        continue;
    }
    struct Expense *expense = &expenses[id - 1];

    printf("Editing Expense ID %d\n", id);
    printf("Current date: %s\n", expense->date);
    printf("Enter new date (DD-MM-YYYY) (or press enter to keep current): ");
    char newDate[11];
    getchar(); // Consume newline character left by scanf
    fgets(newDate, sizeof(newDate), stdin);
    if (strlen(newDate) > 1) {
        newDate[strcspn(newDate, "\n")] = 0; // Remove newline
        if (strlen(newDate) == 10 && newDate[2] == '-' && newDate[5] == '-') {
            strcpy(expense->date, newDate);
        } else {
            printf("Invalid date format. Keeping current date.\n");
        }
    }

    printf("Current amount: %.2f\n", expense->amount);
    getchar();
    printf("Enter new amount (or press enter to keep current): ");
    char newAmount[20];
    fgets(newAmount, sizeof(newAmount), stdin);
    if (strlen(newAmount) > 1) {
        newAmount[strcspn(newAmount, "\n")] = 0; // Remove newline
        expense->amount = atof(newAmount);
    }

    printf("Current category: %s\n", expense->category);
    printf("Enter new category (or press enter to keep current): ");
    fgets(newAmount, sizeof(newAmount), stdin);
    if (strlen(newAmount) > 1) {
        newAmount[strcspn(newAmount, "\n")] = 0; // Remove newline
        strcpy(expense->category, newAmount);
    }

    printf("Current description: %s\n", expense->description);
    printf("Enter new description (or press enter to keep current): ");
    fgets(newAmount, sizeof(newAmount), stdin);
    if (strlen(newAmount) > 1) {
        newAmount[strcspn(newAmount, "\n")] = 0; // Remove newline
        strcpy(expense->description, newAmount);
    }

    printf("Expense edited successfully!\n");
}

         else if (choice == 3) { // Delete Expense
            int id;
            printf("Enter expense ID to delete (1 to %d): ", expenseCount);
            scanf("%d", &id);
            if (id < 1 || id > expenseCount) {
                printf("Invalid expense ID.\n");
                continue;
            }

            // Shift the remaining expenses to delete the chosen expense
            for (int i = id - 1; i < expenseCount - 1; i++) {
                expenses[i] = expenses[i + 1];
            }

            expenseCount--;
            printf("Expense deleted successfully!\n");

        } else if (choice == 4) { // Display All Expenses
            displayExpenses(); // Function to display all expenses

        } else if (choice == 5) { // Exit
            // Save expenses to file before exiting
            file = fopen("expenses.dat", "wb");
            if (file != NULL) {
                fwrite(&expenseCount, sizeof(int), 1, file);
                fwrite(expenses, sizeof(struct Expense), expenseCount, file);
                fclose(file);
            }
            break;
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;

}