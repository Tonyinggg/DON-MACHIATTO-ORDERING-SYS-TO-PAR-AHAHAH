#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MEDIUM_PRICE 29.0
#define LARGE_PRICE 39.0
#define SUGAR_PRICE 10.0
#define ICE_PRICE 10.0

float calculate_total(float price, int quantity, float sugar_cost, float ice_cost) {
    return (price + sugar_cost + ice_cost) * quantity;
}


#define MAX_USERS 10

#define MAX_USERNAME_LENGTH 20
#define MAX_PASSWORD_LENGTH 20


typedef struct {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
} User;


User users[MAX_USERS];

int num_users = 0;


void register_user();
bool login();
void logout();

int main() {
    while (true) {
        int choice;
        char size;
        int quantity;
        char ice[4];
        char sugar[4];
        float total_cost;
        float price;
        float sugar_cost = 0.0;
        float ice_cost = 0.0;
        bool logged_in = false;

        printf("\n1. Register\n2. Login\n3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                register_user();
                break;
            case 2:
                logged_in = login();
                if (logged_in) {
                    printf("Login successful!\n");
                    
                } else {
                    printf("Login failed. Invalid username or password.\n");
                }
                break;
            case 3:
                printf("Exiting program.\n");
                return 0;
            default:
                printf("Invalid choice.\n");
        }

        if (logged_in) {
            while (true) {
                printf("\nPlease choose a coffee (1 - Dark Chocolate, 2 - Matcha, 3 - Strawberry): ");
                scanf("%d", &choice);

                if (choice < 1 || choice > 3) {
                    printf("Invalid choice. Please choose 1, 2, or 3.\n");
                    continue;
                }

                char *flavor;
                switch (choice) {
                    case 1:
                        flavor = "Dark Chocolate";
                        break;
                    case 2:
                        flavor = "Matcha";
                        break;
                    case 3:
                        flavor = "Strawberry";
                        break;
                }

                printf("Please choose a size (M for Medium, L for Large): ");
                scanf(" %c", &size);
                size = toupper(size);

                if (!(size == 'M' || size == 'L')) {
                    printf("Invalid size. Please choose M for Medium or L for Large.\n");
                    continue;
                }

                if (size == 'M') {
                    price = MEDIUM_PRICE;
                } else {
                    price = LARGE_PRICE;
                }

                printf("How many would you like to order?: ");
                scanf("%d", &quantity);

                printf("Would you like to add ice? (yes/no): ");
                scanf("%s", ice);
                if (!(strcmp(ice, "yes") == 0 || strcmp(ice, "no") == 0)) {
                    printf("Invalid input. Please enter yes or no.\n");
                    continue;
                }
                if (strcmp(ice, "yes") == 0) {
                    ice_cost = ICE_PRICE;
                }

                printf("Would you like to add sugar? (yes/no): ");
                scanf("%s", sugar);
                if (!(strcmp(sugar, "yes") == 0 || strcmp(sugar, "no") == 0)) {
                    printf("Invalid input. Please enter yes or no.\n");
                    continue;
                }
                if (strcmp(sugar, "yes") == 0) {
                    sugar_cost = SUGAR_PRICE;
                }

                total_cost = calculate_total(price, quantity, sugar_cost, ice_cost);

                printf("\nYou have ordered %d %c %s Iced Coffee(s) with %s ice and %s sugar.\n", quantity, size, flavor, ice, sugar);
                printf("Total Cost: php%.2f\n", total_cost);

                char another_order[4];
                printf("\nWould you like to place another order? (yes/no): ");
                scanf("%s", another_order);
                if (strcmp(another_order, "no") == 0) {
                    printf("Thank you for using our system. Have a great day!\n");
                    break;
                }
            }
            logout(); 
        }
    }

    return 0;
}

void register_user() {
    if (num_users >= MAX_USERS) {
        printf("Cannot register more users. Maximum limit reached.\n");
        return;
    }

    printf("Enter username: ");
    scanf("%s", users[num_users].username);
    printf("Enter password: ");
    scanf("%s", users[num_users].password);

    printf("User registered successfully.\n");
    num_users++;
}

bool login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    for (int i = 0; i < num_users; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

void logout() {
    printf("Logged out successfully.\n");
}
