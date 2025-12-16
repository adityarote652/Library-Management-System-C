/*
 * Project Name: Library Management System
 * Author: Aditya Rote
 * Description: A console-based application to manage book records, issue/return stock, and track transaction logs.
 * Language: C (Standard)
 * Date: December 2025
 */

#include <stdio.h>
#include <string.h>

// Structure to store details of a single book
struct Book 
{
    int id;              // ID for the book
    char title[50];      // Name of the book
    char author[50];     // Name of the author
    int quantity;        // Number of copies available
};

// Structure to keep track of issued books
struct IssueRecord 
{
    int bookID;
    char booktitle[50];
    char studentname[50];
    char studentID[50];
    char issuedate[15];
    char returndate[15];
};

//Datasets
struct Book library[100];
struct IssueRecord issueList[100];

int count = 0;          // Total number of book in library
int issueCount = 0;     // Total number of issued books

// Functions
void addbook();
void viewbooks();
void issuebook();
void returnbook();
void viewissuedbooks();
void searchbook();

int main()
{
    int choice;

    // Infinite loop to keep the menu open
    while(1) 
    {
        printf("\n=== KBT COE Library System ===\n");
        printf("1. Add Book: \n");
        printf("2. View All Books: \n");
        printf("3. Issue Book: \n");
        printf("4. Return Book: \n");
        printf("5. View Issued Log: \n");
        printf("6. Search Book: \n");
        printf("7. Exit \n");

        printf("Enter choice: ");
        
        // Input validation: checks if user entered a number
        if (scanf("%d", &choice) != 1) 
        {
            printf("Invalid input! Please enter a number.\n");
            while(getchar() != '\n');
            continue;
        }
        
        // Switch cases
        switch(choice) 
        {
            case 1: 
            addbook(); 
            break;

            case 2: 
            viewbooks(); 
            break;

            case 3: 
            issuebook(); 
            break;

            case 4: 
            returnbook(); 
            break;

            case 5: 
            viewissuedbooks(); 
            break;

            case 6: 
            searchbook(); 
            break;

            case 7:
            printf("Exiting...!");
            return 0;       // Exits the program

            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}

// Functions to add new book to the library
void addbook() 
{
    printf("\n--- Add New Book ---\n");
    //declare a unique id to every new book 
    library[count].id = count + 1;
    
    printf("Enter Title: ");
    scanf(" %[^\n]", library[count].title);
    // "%[^\n]" reads a string with spaces until enter is pressed
    printf("Enter Author: ");
    scanf(" %[^\n]", library[count].author);
    printf("Enter Quantity: ");
    scanf("%d", &library[count].quantity);
    
    printf("Book Added! \nID is: %d\n", library[count].id);
    count++;     //Increment total book count
}

// Function to display all books
void viewbooks() 
{
    printf("\n--- Library Stock ---\n");
    // %-5s means left-align string in 5 spaces
    printf("%-5s %-20s %-20s %-5s\n", "ID", "Title", "Author", "Qty");
    printf("--------------------------------------------------------\n");

    for(int i = 0; i < count; i++) 
    {
        printf("%-5d %-20s %-20s %-5d\n", 
            library[i].id, 
            library[i].title, 
            library[i].author, 
            library[i].quantity
        );
    }
}

// Function to handle issuing a book to a student
void issuebook() 
{
    int searchID;
    int found = 0;
    
    printf("\n--- Issue Book Transaction ---\n");
    printf("Enter Book ID to issue: ");
    scanf("%d", &searchID);
    
    // Search for the book ID in the library array
    for(int i = 0; i < count; i++) {
        if(library[i].id == searchID) 
        {
            found = 1;
            
            // Check if stock is available
            if(library[i].quantity > 0) 
            {
                library[i].quantity--; // Reduce stock by 1
                
                issueList[issueCount].bookID = searchID;
                strcpy(issueList[issueCount].booktitle, library[i].title);
                
                printf("Enter Student Name: ");
                scanf(" %[^\n]", issueList[issueCount].studentname);
                
                printf("Enter Student College ID: ");
                scanf(" %[^\n]", issueList[issueCount].studentID);

                printf("Enter Date of Issue (DD/MM/YYYY): ");
                scanf(" %[^\n]", issueList[issueCount].issuedate); 
                
                printf("Enter Expected Return Date (DD/MM/YYYY): ");
                scanf(" %[^\n]", issueList[issueCount].returndate);
                
                printf("Success! Book Issued.\n");
                issueCount++; 
            } 
            else 
            {
                printf("Stock Empty! Cannot issue.\n");
            }
            break;     // Stop searching once book is found
        }
    }
    if(!found) printf("Book ID not found.\n");
}

// Function for return a book
void returnbook() 
{
    int searchID; 
    int found = 0;
    printf("\n--- Return Book ---\n");
    printf("Enter Book ID to return: ");
    scanf("%d", &searchID);

    // Search for the book
    for(int i = 0; i < count; i++) 
    {
        if(library[i].id == searchID) 
        {
            library[i].quantity++;         // Increase stock by 1
            printf("Book Returned Successfully! Stock updated.\n");
            found = 1;
            break;
        }
    }
    if(!found) printf("Book ID not found in system.\n");
}

// Function to view the log of all issued books
void viewissuedbooks() 
{
    printf("\n--- Issued Books Register ---\n");
    if(issueCount == 0) 
    {
        printf("No records found.\n");
        return;
    }
    
    printf("%-15s %-15s %-12s %-12s\n", "Student", "Book", "Issue Date", "Return Date");
    printf("-------------------------------------------------------------\n");
    
    for(int i = 0; i < issueCount; i++) 
    {
        printf("%-15s %-15s %-12s %-12s\n", 
            issueList[i].studentname, 
            issueList[i].booktitle,
            issueList[i].issuedate,
            issueList[i].returndate
        );
    }
}

// Function to search for a book by ID
void searchbook() 
{
    int id;
    printf("Enter ID: ");
    scanf("%d", &id);

    // loop to find the id of the book
    for(int i=0; i<count; i++) 
    {
        if(library[i].id == id)
        {
            printf("\nFound :\n");
            printf("Title : %s \nAuthor : %s \nQuantity : %d\n",
                 library[i].title, 
                 library[i].author, 
                 library[i].quantity
                );
            return;       // Exit function after finding the book
        }
    }
    printf("Not found..!\n");   //if book is not found
}
