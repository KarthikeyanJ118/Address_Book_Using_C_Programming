#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100 // Maximum number of contacts allowed

// Structure to store contact details
typedef struct
{
    char name[50];  // Contact name
    char phone[15]; // Contact phone number
    char email[50]; // Contact email address
} Contact;

// Structure to manage the address book
typedef struct
{
    Contact contacts[MAX_CONTACTS]; // Array of contacts
    int contactCount;               // Current number of contacts
} AddressBook;

// Function declarations 

// Initialize address book and load data from file
void initialize(AddressBook *addressBook);

// Create and add a new contact
void createContact(AddressBook *addressBook);

// Search for a contact by name, phone, or email
void searchContact(AddressBook *addressBook);

// Edit an existing contact
void editContact(AddressBook *addressBook);

// Delete a contact from address book
void deleteContact(AddressBook *addressBook);

// Display all contacts
void listContacts(AddressBook *addressBook);

// Save contacts to file
void saveContactsToFile(AddressBook *addressBook);

// Load contacts from file
void loadContactsFromFile(AddressBook *addressBook);

#endif // End of CONTACT_H