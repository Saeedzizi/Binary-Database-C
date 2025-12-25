#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Data Structure Definition
typedef struct {
    int id;
    char name[50];
    char phone[20];
} Contact;

// Function to add a new contact
void add_contact() {
    FILE *file = fopen("database.bin", "ab");
    if (file == NULL) {
        printf("Error: Could not open database file!\n");
        return;
    }

    Contact c;
    printf("\n--- Add New Contact ---\n");
    printf("Enter ID: ");
    scanf("%d", &c.id);
    printf("Enter Name: ");
    scanf(" %[^\n]s", c.name); // Reads name with spaces
    printf("Enter Phone Number: ");
    scanf("%s", c.phone);

    fwrite(&c, sizeof(Contact), 1, file);
    fclose(file);
    printf("\nSuccess: Contact saved to binary database.\n");
}

// Function to display all contacts
void list_contacts() {
    FILE *file = fopen("database.bin", "rb");
    if (file == NULL) {
        printf("\nWarning: Database is empty or not found.\n");
        return;
    }

    Contact c;
    printf("\n--- Database Contact List ---\n");
    printf("%-5s | %-20s | %-15s\n", "ID", "Name", "Phone");
    printf("------------------------------------------\n");

    while (fread(&c, sizeof(Contact), 1, file)) {
        printf("%-5d | %-20s | %-15s\n", c.id, c.name, c.phone);
    }
    fclose(file);
}

// Function to search for a contact by name
void search_contact() {
    char target[50];
    printf("\nEnter name to search: ");
    scanf(" %[^\n]s", target);

    FILE *file = fopen("database.bin", "rb");
    if (file == NULL) return;

    Contact c;
    int found = 0;
    while (fread(&c, sizeof(Contact), 1, file)) {
        if (strcmp(c.name, target) == 0) {
            printf("\nResult Found!\nID: %d\nName: %s\nPhone: %s\n", c.id, c.name, c.phone);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nError: Contact '%s' not found.\n", target);
    fclose(file);
}

int main() {
    int choice;
    while (1) {
        printf("\n=== Saeed's Database Management System ===\n");
        printf("1. Add Contact\n");
        printf("2. List All Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Exit\n");
        printf("Select an option: ");
        
        if (scanf("%d", &choice) != 1) break;

        switch (choice) {
            case 1: add_contact(); break;
            case 2: list_contacts(); break;
            case 3: search_contact(); break;
            case 4: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}