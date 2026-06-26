#include <stdio.h>   
#include <string.h>  
#include "contact.h" 

#define FILE_NAME "contacts.csv" // CSV file to store contacts

// color codes for terminal output
#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"

// Function to validate name, phone number, and email
int validateContact(char name[], char phone[], char email[])
{
    // Validate name (only alphabets, spaces dot allowed)
    for (int i = 0; name[i]; i++)
        if (!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z') || name[i] == ' ') || name[i] == '.')
            return 0;

    // Validate phone number length
    if (strlen(phone) != 10)
        return 0;

    // Validate phone number digits
    for (int i = 0; phone[i]; i++)
        if (phone[i] < '0' || phone[i] > '9')
            return 0;

    // Validate email format
    int at = 0, dot = 0;
    for (int i = 0; email[i]; i++)
    {
        if (email[i] == '@')
            at = 1; // Check for '@'
        if (email[i] == '.')
            dot = 1; // Check for '.'
    }

    return at && dot; // Valid if both '@' and '.' exist
}

// to print contact table header
void printTableHeader()
{
    printf(CYAN "\n---------------------------------------------------------------\n" RESET);
    printf(CYAN "S.No  Name               Phone        Email\n" RESET);
    printf(CYAN "---------------------------------------------------------------\n" RESET);
}

// Load contacts from CSV file into AddressBook
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fp = fopen(FILE_NAME, "r"); // Open file in read mode
    if (!fp)
        return; // Exit if file not found

    char line[200];
    fgets(line, sizeof(line), fp); // Skip header line

    // Read contacts until EOF or max limit
    while (addressBook->contactCount < MAX_CONTACTS && fscanf(fp, "%[^,],%[^,],%[^\n]\n",addressBook->contacts[addressBook->contactCount].name,addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[addressBook->contactCount].email) != EOF)
    {
        addressBook->contactCount++; // Increment contact count
    }

    fclose(fp); // Close file
}

// Save all contacts to CSV file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fp = fopen(FILE_NAME, "w"); // Open file in write mode
    if (!fp)
        return;

    fprintf(fp, "Name,Phone,Email\n"); // Write CSV header

    // Write each contact to file
    for (int i = 0; i < addressBook->contactCount; i++)
        fprintf(fp, "%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

    fclose(fp); // Close file
}

// Initialize AddressBook
void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;     // Reset count
    loadContactsFromFile(addressBook); // Load existing contacts
}

// Sort contacts alphabetically by name
void sortContactsByName(AddressBook *addressBook)
{
    Contact temp;

    // Bubble sort logic
    for (int i = 0; i < addressBook->contactCount - 1; i++)
        for (int j = i + 1; j < addressBook->contactCount; j++)
            if (strcmp(addressBook->contacts[i].name,addressBook->contacts[j].name) > 0)
            {
                temp = addressBook->contacts[i];
                addressBook->contacts[i] = addressBook->contacts[j];
                addressBook->contacts[j] = temp;
            }
}

// Create a new contact
void createContact(AddressBook *addressBook)
{
    char name[50], phone[15], email[50], choice;

    do
    {
        // Get contact details from user
        printf(BLUE "\nEnter Name  : " RESET);
        scanf(" %[^\n]", name);
        printf(BLUE "Enter Phone : " RESET);
        scanf(" %s", phone);
        printf(BLUE "Enter Email : " RESET);
        scanf(" %s", email);

        // Validate user input
        if (!validateContact(name, phone, email))
        {
            printf(RED "\nInvalid details! Try again.\n" RESET);
            continue;
        }

        // Store contact details
        strcpy(addressBook->contacts[addressBook->contactCount].name, name);
        strcpy(addressBook->contacts[addressBook->contactCount].phone, phone);
        strcpy(addressBook->contacts[addressBook->contactCount].email, email);

        addressBook->contactCount++;     // Increment contact count
        saveContactsToFile(addressBook); // Save to file

        printf(GREEN "\nContact added successfully!\n" RESET);
        printf(YELLOW "\nAdd another contact? (y/n): " RESET);
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
}

// Display all contacts
void listContacts(AddressBook *addressBook)
{
    if (addressBook->contactCount == 0)
    {
        printf(RED "\nNo contacts available!\n" RESET);
        return;
    }

    sortContactsByName(addressBook); // Sort contacts
    printTableHeader();              // Print table header

    // Print each contact
    for (int i = 0; i < addressBook->contactCount; i++)
        printf("%-5d %-18s %-12s %s\n",i + 1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

    printf(CYAN "---------------------------------------------------------------\n" RESET);
}

// Search contact by name, phone, or email
void searchContact(AddressBook *addressBook)
{
    int option;                  // Stores search option
    char query[50];              // Stores search input
    int indexList[MAX_CONTACTS]; // Stores matching contact indexes
    int count = 0, choice;       // Match count and user selection

    // Display search menu
    printf(BLUE "\nSearch Contact By:\n" RESET);
    printf("1. Name\n");
    printf("2. Phone\n");
    printf("3. Email\n");
    printf(BLUE "\nEnter your choice: " RESET);
    scanf("%d", &option); // Read user option

    // Get search input based on option
    if (option == 1)
    {
        printf(BLUE "\nEnter name to search: " RESET);
        scanf(" %[^\n]", query); // Read name with spaces
    }
    else if (option == 2)
    {
        printf(BLUE "\nEnter phone to search: " RESET);
        scanf(" %s", query); // Read phone number
    }
    else if (option == 3)
    {
        printf(BLUE "\nEnter email to search: " RESET);
        scanf(" %s", query); // Read email
    }
    else
    {
        printf(RED "\nInvalid option!\n" RESET); // Handle invalid option
        return;
    }

    // Search through contacts
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        // Case-insensitive name comparison
        if (option == 1 && strcasecmp(addressBook->contacts[i].name, query) == 0)
        {
            indexList[count++] = i; 
        }
        // Phone number comparison
        else if (option == 2 && strcmp(addressBook->contacts[i].phone, query) == 0)
        {// Store matching index
            indexList[count++] = i;
        }
        // Partial email match
        else if (option == 3 && strstr(addressBook->contacts[i].email, query) != NULL)
        {
            indexList[count++] = i;
        }
    }

    // If no contacts matched
    if (count == 0)
    {
        printf(RED "\nNo contact found!\n" RESET);
        return;
    }

    // If multiple contacts are found
    if (count > 1)
    {
        printf(YELLOW "\nMultiple contacts found:\n" RESET);
        printTableHeader(); // Print table header

        // Display matching contacts
        for (int i = 0; i < count; i++)
        {
            int idx = indexList[i]; // Actual index in address book
            printf("%-5d %-18s %-12s %s\n",i + 1,addressBook->contacts[idx].name,addressBook->contacts[idx].phone,addressBook->contacts[idx].email);
        }

        // Ask user to select one contact
        printf(BLUE "\nEnter S.No to view: " RESET);
        scanf("%d", &choice);

        // Validate selection
        if (choice < 1 || choice > count)
        {
            printf(RED "\nInvalid S.No!\n" RESET);
            return;
        }
    }
    else
    {
        choice = 1; // Only one contact found
    }

    // Get the selected contact index
    int realIndex = indexList[choice - 1];

    // Display selected contact details
    printf(GREEN "\nContact Details:\n" RESET);
    printf("Name  : %s\n", addressBook->contacts[realIndex].name);
    printf("Phone : %s\n", addressBook->contacts[realIndex].phone);
    printf("Email : %s\n", addressBook->contacts[realIndex].email);
}

// Edit an existing contact
void editContact(AddressBook *addressBook)
{
    char name[50], newName[50], phone[15], email[50];
    int indexList[MAX_CONTACTS], count = 0;

    printf(BLUE "\nEnter name to edit: " RESET);
    scanf(" %[^\n]", name);

    // Find matching contacts
    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].name, name) == 0)
            indexList[count++] = i;

    if (count == 0)
    {
        printf(RED "\nContact not found!\n" RESET);
        return;
    }

    int realIndex = indexList[0];

    // Get new details
    printf(BLUE "Enter new Name : " RESET);
    scanf(" %[^\n]", newName);
    printf(BLUE "Enter new Number : " RESET);
    scanf(" %s", phone);
    printf(BLUE "Enter new Mail : " RESET);
    scanf(" %s", email);

    if (!validateContact(newName, phone, email))
    {
        printf(RED "\nInvalid data!\n" RESET);
        return;
    }

    // Update contact
    strcpy(addressBook->contacts[realIndex].name, newName);
    strcpy(addressBook->contacts[realIndex].phone, phone);
    strcpy(addressBook->contacts[realIndex].email, email);

    saveContactsToFile(addressBook);
    printf(GREEN "\nContact updated successfully!\n" RESET);
}

// Delete a contact
void deleteContact(AddressBook *addressBook)
{
    char name[50];
    int indexList[MAX_CONTACTS], count = 0;

    printf(BLUE "Enter name to delete: " RESET);
    scanf(" %[^\n]", name);

    // Find contact
    for (int i = 0; i < addressBook->contactCount; i++)
        if (strcmp(addressBook->contacts[i].name, name) == 0)
            indexList[count++] = i;

    if (count == 0)
    {
        printf(RED "\nContact not found!\n" RESET);
        return;
    }

    int realIndex = indexList[0];

    // Shift contacts to delete entry
    for (int i = realIndex; i < addressBook->contactCount - 1; i++)
        addressBook->contacts[i] = addressBook->contacts[i + 1];

    addressBook->contactCount--;     // Decrease count
    saveContactsToFile(addressBook); // Save changes

    printf(GREEN "\nContact deleted successfully!\n" RESET);
}