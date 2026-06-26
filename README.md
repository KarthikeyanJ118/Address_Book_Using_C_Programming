# 📒 Address Book in C

## 📌 Overview

This project is a **console-based Address Book application** written in C that allows users to manage contacts efficiently. It supports full **CRUD operations (Create, Read, Update, Delete)** along with **data persistence using file handling**.

The application uses **structures, pointers, strings, and file I/O concepts** to store and manage contact details such as **Name, Phone Number, and Email ID**.

---

## 🚀 Features

* ➕ Create new contacts with validation
* 🔍 Search contacts by:

  * Name
  * Phone Number
  * Email ID
* ✏️ Edit existing contact details
* ❌ Delete contacts
* 📋 Display all contacts in sorted order
* 💾 Automatic data saving to file (`contacts.csv`)
* 🔄 Load saved contacts on startup
* ✅ Input validation for:

  * Name (alphabets, spaces, dot)
  * Phone (10-digit unique number)
  * Email (valid format & unique)

---

## 🛠️ Technologies Used

* **Language:** C
* **Concepts:**

  * Structures
  * Pointers
  * Strings
  * File Handling (CSV)
  * Modular Programming

---

## 📂 Project Structure

```
├── main.c          # Entry point with menu-driven program
├── contact.c       # Core logic implementation
├── contact.h       # Structure definitions and function declarations
├── contacts.csv    # File for storing contact data
```

---

## ⚙️ How It Works

1. On startup, the program loads existing contacts from `contacts.csv`.
2. User interacts via a menu-driven interface.
3. Operations like create, search, edit, delete are performed in memory.
4. Data is saved back to the file before exiting.

---

## 🧪 Sample Menu

```
Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save and Exit
```

---

## ▶️ How to Compile and Run

### Compile:

```bash
gcc main.c contact.c -o address_book
```

### Run:

```bash
./address_book
```

---

## 📊 Data Storage Format

Contacts are stored in a CSV file:

```
#3
John Doe,9876543210,john@gmail.com
Jane Smith,9123456780,jane@gmail.com
```

---

## 🔒 Validations Implemented

* **Name:** Only alphabets, spaces, and dots allowed
* **Phone:** Exactly 10 digits & must be unique
* **Email:** Proper format with one '@' and valid domain

---

## 📈 Future Improvements

* Add GUI (using GTK or Qt)
* Support for larger datasets using dynamic memory
* Search with partial matching
* Import/Export contacts
* Password protection

---

## 👨‍💻 Author

**Mohammed Shaqeeb**

---

## 📜 License

This project is open-source and free to use for learning purposes.

