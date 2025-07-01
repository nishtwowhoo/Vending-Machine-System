#include <stdio.h>
#include <string.h>
#include <ctype.h>  // For tolower()

struct Product {
    char name[30];
    float price;
};

// Function prototypes
void displayMenu(struct Product products[], int size);
float calculateTotal(float prices[], int count);
void generateReceipt(struct Product products[], int selected[], int quantities[], int count, float total, float paid);
void promptForMoney(float total, float *paid);
int getProductChoice();
int getQuantity();
void selectItems(int selected[], int quantities[], float prices[], int *count, struct Product products[], int size);

int main() {
    // Initialize products
    struct Product products[] = {
        {"100 Plus", 2.00},
        {"Coca Cola", 2.50},
        {"Sprite", 2.30},
        {"Milo", 3.00},
        {"Red Bull", 4.50},
        {"Milk", 3.20},
        {"Chips More", 1.80},
        {"Oreos", 2.50},
        {"Mr. Potato", 3.00},
        {"Oatbar", 1.50},
        {"Maggi Cup Curry", 2.80}
    };

    // Shopping cart variables
    int selected[10];     // Stores product indices
    int quantities[10];   // Stores quantities
    float prices[10];     // Stores individual item prices
    int count = 0;        // Number of items selected
    float total = 0.0;    // Total cost
    float paid = 0.0;     // Amount paid by customer

    // Shopping process
    selectItems(selected, quantities, prices, &count, products, 11);
    total = calculateTotal(prices, count);
    promptForMoney(total, &paid);
    generateReceipt(products, selected, quantities, count, total, paid);

    return 0;
}

// Display all available products
void displayMenu(struct Product products[], int size) {
    printf("\nAvailable products:\n");
    for (int i = 0; i < size; i++) {
        printf("%2d. %-20s RM%5.2f\n", i + 1, products[i].name, products[i].price);
    }
    printf("\n");
}

// Calculate total cost
float calculateTotal(float prices[], int count) {
    float total = 0.0;
    for (int i = 0; i < count; i++) {
        total += prices[i];
    }
    return total;
}

// Handle payment process
void promptForMoney(float total, float *paid) {
    int result;
    do {
        printf("Total cost: RM%.2f. Please insert money: RM", total);
        result = scanf("%f", paid);
        
        // Clear input buffer if invalid input
        while (getchar() != '\n');
        
        if (result != 1) {
            printf("Invalid amount. Please enter a number.\n");
        }
        else if (*paid < total) {
            printf("Insufficient funds. Please insert more money.\n");
        }
    } while (result != 1 || *paid < total);
}

// Generate and print receipt
void generateReceipt(struct Product products[], int selected[], int quantities[], int count, float total, float paid) {
    float change = paid - total;
    
    printf("\n----- Receipt -----\n");
    printf("%-20s %5s %10s\n", "Product", "Qty", "Price (RM)");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < count; i++) {
        printf("%-20s %5d %10.2f\n", 
              products[selected[i]].name, 
              quantities[i], 
              products[selected[i]].price * quantities[i]);
    }

    printf("----------------------------------------\n");
    printf("%-20s %5s %10.2f\n", "Total", "", total);
    printf("%-20s %5s %10.2f\n", "Paid", "", paid);
    printf("%-20s %5s %10.2f\n", "Change", "", change);
    printf("------------------- Thank you! -----------\n");
}

// Item selection process
void selectItems(int selected[], int quantities[], float prices[], int *count, struct Product products[], int size) {
    int choice, quantity;
    char more;

    do {
        displayMenu(products, size);
        choice = getProductChoice();
        quantity = getQuantity();
        
        if (*count >= 10) {
            printf("Maximum items reached (10). Cannot add more.\n");
            break;
        }
        
        selected[*count] = choice - 1;
        quantities[*count] = quantity;
        prices[*count] = products[choice - 1].price * quantity;
        (*count)++;

        // Strict y/n validation
        int valid;
        do {
            printf("Would you like to select another item? (y/n): ");
            more = getchar();
            while (getchar() != '\n'); // Clear buffer
            more = tolower(more);
            valid = (more == 'y' || more == 'n');
            if (!valid) {
                printf("Error: Please enter only 'y' or 'n'.\n");
            }
        } while (!valid);

    } while (more == 'y' && *count < 10);
}

// Get valid product choice (1-11)
int getProductChoice() {
    int choice;
    int result;
    do {
        printf("Select a product by number (1-11): ");
        result = scanf("%d", &choice);
        
        // Clear input buffer if invalid input
        while (getchar() != '\n');
        
        if (result != 1 || choice < 1 || choice > 11) {
            printf("Invalid choice. Please enter a number between 1 and 11.\n");
        }
    } while (result != 1 || choice < 1 || choice > 11);
    return choice;
}

// Get valid quantity (>= 1)
int getQuantity() {
    int quantity;
    int result;
    do {
        printf("Enter the quantity (1 or more): ");
        result = scanf("%d", &quantity);
        
        // Clear input buffer if invalid input
        while (getchar() != '\n');
        
        if (result != 1 || quantity < 1) {
            printf("Quantity must be at least 1.\n");
        }
    } while (result != 1 || quantity < 1);
    return quantity;
}