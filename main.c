/* DOCUMENTATION:
   NAME      : KARTHIKEYAN J
   REG_NO    : 25031_122
   START_DATE: 10-12-2025
   END_DATE  : 14-12-2025
   DESC      : Address Book application with CRUD operations,file backup, and data reload using structures, strings, file I/O, and pointers
*/

#include <stdio.h>   
#include "contact.h" 

// color codes for terminal output
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"
#define RESET "\033[0m"

int main()
{
    int choice;              
    AddressBook addressBook; // AddressBook structure instance

    initialize(&addressBook); // Initialize address book and load data from file

    do
    {
        // Display menu
        printf(BLUE "\nAddress Book Menu:\n\n" RESET);
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
        printf("6. Save and Exit\n");
        printf(BLUE "\nEnter your choice : " RESET);

        scanf("%d", &choice); // Read user choice

        switch (choice)
        {
        case 1:
            createContact(&addressBook); // Add a new contact
            break;

        case 2:
            searchContact(&addressBook); // Search an existing contact
            break;

        case 3:
            editContact(&addressBook); // Edit contact details
            break;

        case 4:
            deleteContact(&addressBook); // Delete a contact
            break;

        case 5:
            listContacts(&addressBook); // Display all contacts
            break;

        case 6:
            saveContactsToFile(&addressBook); // Save contacts before exit
            printf(GREEN "\nContacts saved. Exiting...\n\n" RESET);
            break;

        default:
            printf(RED "Invalid choice!\n" RESET); // Handle invalid input
        }

    } while (choice != 6); // Repeat until user chooses Exit

    return 0; // Program termination
}
