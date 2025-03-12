#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LEN 100

// Book structure
typedef struct {
    char title[MAX_TITLE_LEN];
    int available;
    int borrowed;
} Book;

// Hash table
Book hash_table[MAX_BOOKS];

// Hash function
unsigned int hash(char *title) {
    int i;
	unsigned int hash_val = 0;
    for (i = 0; title[i] != '\0'; i++) {
        hash_val += title[i];
    }
    return hash_val % MAX_BOOKS;
}

// Insert a book
void insert_book(char *title, int available) {
    unsigned int index = hash(title);
    int i = index;
    while (hash_table[i].title[0] != '\0') {
        if (strcmp(hash_table[i].title, title) == 0) {
            printf("Book already exists in the library.\n");
            printf("Enter the number of new copies to add: ");
            int new_copies;
            scanf("%d", &new_copies);
            hash_table[i].available += new_copies;
            printf("New copies added. Total available copies of '%s': %d\n", title, hash_table[i].available);
            return;
        }
        i = (i + 1) % MAX_BOOKS;
        if (i == index) {
            printf("Hash table is full.\n");
            return;
        }
    }
    strcpy(hash_table[i].title, title);
    hash_table[i].available = available;
    hash_table[i].borrowed = 0;
    printf("Book '%s' added to the library.\n", title);
}

// Search for a book
int search_book(char *title) {
    unsigned int index = hash(title);
    int i = index;
    while (hash_table[i].title[0] != '\0') {
        if (strcmp(hash_table[i].title, title) == 0) {
            return i;
        }
        i = (i + 1) % MAX_BOOKS;
        if (i == index) {
            break;
        }
    }
    printf("Book '%s' not found in the library.\n", title);
    return -1;
}

// Borrow a book
void borrow_book(char *title) {
    int index = search_book(title);
    if (index != -1) {
        if (hash_table[index].available > 0) {
            hash_table[index].available--;
            hash_table[index].borrowed++;
            printf("Book '%s' borrowed successfully.\n", title);
        } else {
            printf("Book '%s' is not available for borrowing.\n", title);
        }
    }
}

// Return a book
void return_book(char *title) {
    int index = search_book(title);
    if (index != -1) {
        if (hash_table[index].borrowed > 0) {
            hash_table[index].available++;
            hash_table[index].borrowed--;
            printf("Book '%s' returned successfully.\n", title);
        } else {
            printf("No copies of '%s' were borrowed.\n", title);
        }
    }
}

// Delete a book
void delete_book(char *title) {
    int index = search_book(title);
    if (index != -1) {
        if (hash_table[index].borrowed == 0) {
            memset(&hash_table[index], 0, sizeof(Book));
            printf("Book '%s' deleted from the library.\n", title);
        } else {
            printf("Can't delete '%s' because it has been borrowed.\n", title);
        }
    }
}

// Display all available books
void display_books() {
    int i;
	printf("Available books in the library:\n");
    for (i = 0; i < MAX_BOOKS; i++) {
        if (hash_table[i].title[0] != '\0' && hash_table[i].available > 0) {
            printf("Title: %s, Available copies: %d\n", hash_table[i].title, hash_table[i].available);
        }
    }
}

// Display borrowed books
void display_borrowed_books() {
    printf("\nBorrowed Books\n");
    printf("===============\n");
    int i, found = 0;
    for (i = 0; i < MAX_BOOKS; i++) {
        if (hash_table[i].title[0] != '\0' && hash_table[i].borrowed > 0) {
            printf("Title: %s, Copies borrowed: %d\n", hash_table[i].title, hash_table[i].borrowed);
            found = 1;
        }
    }
    if (!found) {
        printf("No books have been borrowed.\n");
    }
}


int main() {
    // Initialize hash table
    memset(hash_table, 0, sizeof(hash_table));

    // Menu
    int choice;
    char title[MAX_TITLE_LEN];
    int available;

    do {
        printf("\n");
        printf("=============================================================\n");
        printf("                   Library Management System                 \n");
        printf("=============================================================\n");
        printf("  1. Add Book\n");
        printf("  2. Borrow Book\n");
        printf("  3. Return Book\n");
        printf("  4. Delete Book\n");
        printf("  5. Display Available Books\n");
        printf("  6. Display Borrowed Books\n");
        printf("  7. Exit\n");
        printf("=============================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("\nAdd Book\n");
                printf("=========\n");
                printf("Enter book title: ");
                scanf(" %[^\n]s", title);
                printf("Enter number of available copies: ");
                scanf("%d", &available);
                insert_book(title, available);
                break;
            case 2:
                printf("\nBorrow Book\n");
                printf("============\n");
                printf("Enter book title to borrow: ");
                scanf(" %[^\n]s", title);
                borrow_book(title);
                break;
            case 3:
                printf("\nReturn Book\n");
                printf("============\n");
                printf("Enter book title to return: ");
                scanf(" %[^\n]s", title);
                return_book(title);
                break;
            case 4:
                printf("\nDelete Book\n");
                printf("============\n");
                printf("Enter book title to delete: ");
                scanf(" %[^\n]s", title);
                delete_book(title);
                break;
            case 5:
                printf("\nAvailable Books\n");
                printf("================\n");
                display_books();
                break;
            case 6:
                display_borrowed_books();
                break;
            case 7:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 7);

    return 0;
}

