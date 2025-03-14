#include <stdio.h>
#include <stdlib.h>
#include "library.h"

#define MAX_LEN 100
#define MAX_BOOKS 200
#define MAX_BORROW_HISTORY 50
#define MAX_MEMBERS 100

// book details
void bookdetails(struct Book book)
{
    printf("\n--- Book Details ---\n");
    printf("Code: %s\n", book.book_code);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Year: %d\n", book.year);
    printf("Genre: %s\n", book.genre);
    printf("Publisher: %s\n", book.publisher);
    printf("Format: %s\n", book.format);
    printf("Available: %d\n", book.available);
    printf("Borrowed: %d\n", book.borrowed);
    printf("Summary: %s\n", book.summary);
}


//Staff Menu
void StaffMenu()//
{
    char selection;
    printf("\n--- LIBRARY STAFF MENU ---\n");
    printf("1. Member Assistance\n");
    printf("2. Shelf Management\n");
    printf("3. Digital Resource Assistance\n");
    printf("4. Back to MAIN MENU\n");
    while (1)
    {
        printf("Enter Function above(1-4): ");
        scanf("%d", &selection);

        if(selection == 1)
        {
            printf("\n-------------------------------------\n");
            BookServices();
            break;
        }

        else if(selection == 2)
        {
            printf("\n-------------------------------------\n");
            management();
            break;
        }

        else if(selection == 3)
        {
            printf("\n-------------------------------------\n");
            digitalresource();
            break;
        }

        else if(selection == 4)
        {
            printf("Thank you for using!");
            printf("Back to MAIN MANU....\n");
            Main_Menu();
            break;
        }

        else
        {
            printf("Invalid choice. Please try again.\n\n");
        }
    }
}


//Member Assistance
void BookServices()//
{
    char selection;
    printf("\n--- SERVICE MENU ---\n");
    printf("1. Search For Books\n");
    printf("2. Reserve Books\n");
    printf("3. Library Service\n");
    printf("4. Back To LIBRARY STAFF MENU\n");

    while (1)
    {
        printf("Enter Function above(1-4): ");
        scanf("%d", &selection);
        if(selection == 1)
        {
            printf("\n-------------------------------------\n");
            BookSearch();
            break;
        }
        else if(selection == 2)
        {
            printf("\n-------------------------------------\n");
            Reserve_Book();
            break;
        }
        else if(selection == 3)
        {
            printf("\n-------------------------------------\n");
            LibraryService();
            break;
        }
        else if(selection == 4)
        {
            printf("Successfully Cancel!\n\n");
            StaffMenu();
            break;
        }

        else
        {
            printf("Invalid choice. Please Try again.\n\n");
        }
    }
}


void BookSearch()
{
    struct Book books[MAX_BOOKS];
    FILE *booksfile;
    int book_count = 0;
    char keyword[MAX_LEN];

    booksfile = fopen("books.txt", "r");
    if (booksfile == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(booksfile, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                  books[book_count].book_code, books[book_count].title, books[book_count].author,
                  &books[book_count].year, books[book_count].genre, books[book_count].publisher,
                  books[book_count].format, &books[book_count].available,
                  &books[book_count].borrowed, books[book_count].summary) != EOF)
    {
        book_count++;
        if (book_count >= MAX_BOOKS)
            break;
    }

    fclose(booksfile);

    while (1)
    {
        while (getchar() != '\n' && getchar() != EOF);

        printf("\nEnter the book name or part of the title: ");
        fgets(keyword, MAX_LEN, stdin);
        keyword[strcspn(keyword, "\n")] = 0;

        if (strlen(keyword) == 0)
        {
            printf("Please enter a valid book name or keyword.\n");
            continue;
        }

        struct Book matches[MAX_BOOKS];
        int match_count = 0;

        for (int i = 0; i < book_count; i++)
        {
            if (strstr(books[i].title, keyword) != NULL)
            {
                matches[match_count++] = books[i];
            }
        }

        if (match_count == 0)
        {
            printf("No books found with the keyword '%s'.\n\n", keyword);
            continue;
        }
        else if (match_count == 1)
        {
            char confirm;
            while (1)
            {
                printf("\nFound one book: %s.\nIs this the book you want? (y/n): ", matches[0].title);
                scanf(" %c", &confirm);
                getchar();

                if (confirm == 'y' || confirm == 'Y')
                {
                    bookdetails(matches[0]);

                    while (1)
                    {
                        printf("\nDo you want to exit to SERVICE MENU? (y/n): ");
                        scanf(" %c", &confirm);
                        getchar();

                        if (confirm == 'y' || confirm == 'Y')
                        {
                            BookServices();
                            return;
                        }
                        else if (confirm == 'n' || confirm == 'N')
                        {
                            break;
                        }
                        else
                        {
                            printf("Invalid input. Please enter 'y' or 'n'.\n");
                        }
                    }
                }
                else if (confirm == 'n' || confirm == 'N')
                {
                    break;
                }
                else
                {
                    printf("Invalid input. Please enter 'y' or 'n'.\n");
                }
            }
        }
        else
        {
            printf("\nFound %d books with the keyword '%s':\n", match_count, keyword);

            for (int i = 0; i < match_count; i++)
            {
                printf("%d. %s\n", i + 1, matches[i].title);
            }

            int choice;
            while (1)
            {
                printf("\nEnter the number of the book you want to select: ");
                if (scanf("%d", &choice) != 1 || choice < 1 || choice > match_count)
                {
                    printf("Invalid selection. Please try again.\n");
                    while (getchar() != '\n');
                }
                else
                {
                    char confirm;
                    while (1)
                    {
                        printf("\nYou chose: %s.\nIs this the book you want? (y/n): ", matches[choice - 1].title);
                        scanf(" %c", &confirm);
                        getchar();

                        if (confirm == 'y' || confirm == 'Y')
                        {
                            bookdetails(matches[choice - 1]);

                            while (1)
                            {
                                printf("\nDo you want to exit to SERVICE MENU? (y/n): ");
                                scanf(" %c", &confirm);
                                getchar();

                                if (confirm == 'y' || confirm == 'Y')
                                {
                                    BookServices();
                                    return;
                                }
                                else if (confirm == 'n' || confirm == 'N')
                                {
                                    BookSearch();
                                }
                                else
                                {
                                    printf("Invalid input. Please enter 'y' or 'n'.\n");
                                }
                            }
                        }
                        else if (confirm == 'n' || confirm == 'N')
                        {
                            break;
                        }
                        else
                        {
                            printf("Invalid input. Please enter 'y' or 'n'.\n");
                        }
                    }
                }
            }
        }
    }
}


void calculateReturnDate(int borrow_day, int borrow_month, int *return_day, int *return_month)
{
    *return_day = borrow_day + 14;
    *return_month = borrow_month;

    if (*return_day > 31)
    {
        *return_day -= 31;
        (*return_month)++;
    }

    if ((*return_month == 4 || *return_month == 6 || *return_month == 9 || *return_month == 11) && *return_day > 30)
    {
        *return_day -= 30;
        (*return_month)++;
    }

    if (*return_month > 12)
    {
        *return_month -= 12;
    }
}


 void Reserve_Book()
{
    FILE *booksFile, *borrowingFile, *membersFile;
    struct Book book;
    char book_code[100];
    char line[100];
    struct Book books[100];
    int bookCount = 0;
    int member_id = -1;
    char member_name[50];

    booksFile = fopen("books.txt", "r");
    if (booksFile == NULL)
    {
        printf("Error opening books file.\n");
        return;
    }

    while(fscanf(booksFile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                 books[bookCount].book_code,books[bookCount].title,books[bookCount].author,
                 &books[bookCount].year,books[bookCount].genre,books[bookCount].publisher,
                 books[bookCount].format,&books[bookCount].available,&books[bookCount].borrowed,
                 books[bookCount].summary) != EOF){
            bookCount++;
                 }
    fclose(booksFile);

    while (1)
    {
        printf("\nEnter the book code: ");
        scanf("%s", book_code);

        int bookFound = 0;
        for (int i = 0; i < bookCount; i++)
        {
            if (strcmp(books[i].book_code, book_code) == 0)
            {
                bookFound = 1;
                printf("\n---------- BOOK DETAILS ----------\n\n");
                printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n",
                       "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
                printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

                printf("%-7s %-30s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n\n",
                       books[i].book_code, books[i].title, books[i].author,
                       books[i].year, books[i].genre, books[i].publisher,
                       books[i].format, books[i].available, books[i].borrowed);


                borrowingFile = fopen("borrowing and return.txt", "r");
                if (borrowingFile == NULL)
                {
                    printf("Error opening borrowing history file.\n");
                    return;
                }

                int historyFound = 0;
                printf("\n---------- BORROWING HISTORY ----------\n\n");
                printf("%-10s %-20s %-10s %-10s  %-15s %-15s %-15s %-15s %-15s\n",
                       "Member ID", "Member Name", "Book Code", "Status", "Borrow Day", "Borrow Month",
                       "Estimate Day", "Estimate Month", "Return Day");
                printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

                while (fgets(line, sizeof(line), borrowingFile))
                {
                    struct Borrow_Return borrow;
                    sscanf(line, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d, %d, %f\n",
                           &borrow.member_id, borrow.member_name, borrow.book_code, borrow.status,
                           &borrow.borrow_day, &borrow.borrow_month,
                           &borrow.estimate_day, &borrow.estimate_month,
                           &borrow.return_day, &borrow.return_month, &borrow.fine);

                    if (strcmp(borrow.book_code, books[i].book_code) == 0)
                    {
                        historyFound = 1;
                        printf("%-10d %-20s %-10s %-10s  %-15d %-15d %-15d %-15d %-15d\n",
                               borrow.member_id, borrow.member_name, borrow.book_code, borrow.status,
                               borrow.borrow_day, borrow.borrow_month,
                               borrow.estimate_day, borrow.estimate_month,
                               borrow.return_day);
                    }
                }

                if (!historyFound)
                {
                    printf("No borrowing history available for this book.\n");
                }
                fclose(borrowingFile);

                if (books[i].available > 0)
                {
                    char confirm;
                    while (1)
                    {
                        printf("\nDo you want to reserve this book? (y/n): ");
                        scanf(" %c", &confirm);

                        if (confirm == 'y' || confirm == 'Y')
                        {
                            books[i].available--;
                            books[i].borrowed++;

                            int borrow_day, borrow_month;
                            while (1)
                            {
                                printf("\nEnter reserve day (1-31): ");
                                scanf("%d", &borrow_day);
                                printf("Enter reserve month (1-12): ");
                                scanf("%d", &borrow_month);

                                if (borrow_month < 1 || borrow_month > 12)
                                {
                                    printf("Invalid month. Please enter a month between 1 and 12.\n");
                                    continue;
                                }

                                int max_days = 31;
                                if (borrow_month == 2 || borrow_month == 4 || borrow_month == 6 || borrow_month == 9 || borrow_month == 11)
                                {
                                    max_days = 30;
                                }

                                if (borrow_day < 1 || borrow_day > max_days)
                                {
                                    printf("Invalid day for the entered month. Please try again.\n");
                                    continue;
                                }
                                break;
                            }

                            int return_day, return_month;
                            calculateReturnDate(borrow_day, borrow_month, &return_day, &return_month);

                            borrowingFile = fopen("borrowing and return.txt", "a");
                            if (borrowingFile == NULL)
                            {
                                printf("Error opening borrowing history file for writing.\n");
                                return;
                            }

                            if (member_id == -1)
                            {
                                while (1)
                                {
                                    membersFile = fopen("members.txt", "r");
                                    if (membersFile == NULL)
                                    {
                                        printf("Error opening members file.\n");
                                        fclose(borrowingFile);
                                        return;
                                    }

                                    printf("\nAvailable Members:\n");

                                    while (fgets(line, sizeof(line), membersFile))
                                    {
                                        struct Member member;
                                        sscanf(line, "%d, %[^,], %d, %[^,], %[^\n]", &member.member_id, member.name, &member.age, member.email, member.password);
                                        printf("Member ID: %d, Name: %s\n", member.member_id, member.name);
                                    }
                                    fclose(membersFile);

                                    printf("\nEnter your member ID: ");
                                    scanf("%d", &member_id);

                                    membersFile = fopen("members.txt", "r");
                                    int memberFound = 0;

                                    while (fgets(line, sizeof(line), membersFile))
                                    {
                                        struct Member member;
                                        sscanf(line, "%d, %[^,], %d, %[^,], %[^\n]", &member.member_id, member.name, &member.age, member.email, member.password);
                                        if (member.member_id == member_id)
                                        {
                                            memberFound = 1;
                                            strcpy(member_name, member.name);
                                            break;
                                        }
                                    }
                                    fclose(membersFile);

                                    if (memberFound)
                                    {
                                        break;
                                    }

                                    else
                                    {
                                        printf("Invalid Member ID. Please try again.\n");
                                    }
                                }
                            }

                            fprintf(borrowingFile, "%d, %s, %s, reserved, %d, %d, %d, %d, %d, %d, %.2f\n",
                                    member_id, member_name, books[i].book_code,
                                    borrow_day, borrow_month, return_day, return_month,
                                    0, 0, 0.00);
                            fclose(borrowingFile);

                            booksFile = fopen("books.txt", "w");
                            if (booksFile == NULL)
                            {
                                printf("Error opening books file.\n");
                                return;
                            }

                            for (int j = 0; j < bookCount; j++)
                            {
                                fprintf(booksFile, "%s, %s, %s, %d, %s, %s, %s, %d, %d, %s\n",
                                        books[j].book_code, books[j].title, books[j].author, books[j].year,
                                        books[j].genre, books[j].publisher, books[j].format,
                                        books[j].available, books[j].borrowed, books[j].summary);
                            }
                            fclose(booksFile);

                            printf("Book reserved successfully.\n");

                            char exit_confirm;

                            while (1)
                            {
                                printf("Do you want to exit to the SERVICE MENU? (y/n): ");
                                scanf(" %c", &exit_confirm);

                                if (exit_confirm == 'y' || exit_confirm == 'Y')
                                {
                                    BookServices();
                                    return;
                                }

                                else if (exit_confirm == 'n' || exit_confirm == 'N')
                                {
                                    Reserve_Book();
                                    break;
                                }

                                else
                                {
                                    printf("Invalid input. Please enter 'y' or 'n'.\n");
                                }
                            }
                            break;
                        }

                        else if (confirm == 'n' || confirm == 'N')
                        {
                            printf("Book reservation canceled.\n");
                            break;
                        }

                        else
                        {
                            printf("Invalid input. Please enter 'y' or 'n'.\n");
                        }
                    }
                }

                else
                {
                    printf("The book is not available for borrowing.\n");
                    break;
                }
                break;
            }
        }

        if (!bookFound)
        {
            printf("Book not found. Please try again.\n");
        }
    }
}



void LibraryService()
{
    int selection;

    while (1)
    {
        printf("\n--- LIBRARY SERVICE MENU ---\n");
        printf("1. Book Borrowing Services\n");
        printf("2. Study Rooms Services\n");
        printf("3. Reference Services\n");
        printf("4. Computer and Internet Access Services\n");
        printf("5. Community Programs Services\n");
        printf("6. Access to Special Collections Services\n");
        printf("7. Back To SERVICE MENU\n");

        printf("Enter Function above (1-7): ");
        scanf("%d", &selection);
        getchar();

        if (selection == 1)
        {
            printf("\n--- BOOK BORROWING SERVICES ---\n");
            ServiceDetails("Book Borrowing");
        }
        else if (selection == 2)
        {
            printf("\n--- STUDY ROOMS SERVICES ---\n");
            ServiceDetails("Study Rooms");
        }
        else if (selection == 3)
        {
            printf("\n--- REFERENCE SERVICES ---\n");
            ServiceDetails("Reference Services");
        }
        else if (selection == 4)
        {
            printf("\n--- COMPUTER AND INTERNET ACCESS SERVICES ---\n");
            ServiceDetails("Computer and Internet Access");
        }
        else if (selection == 5)
        {
            printf("\n--- COMMUNITY PROGRAMS SERVICES ---\n");
            ServiceDetails("Community Programs");
        }
        else if (selection == 6)
        {
            printf("\n--- ACCESS TO SPECIAL COLLECTIONS SERVICES ---\n");
            ServiceDetails("Access to Special Collections");
        }
        else if (selection == 7)
        {
            printf("Returning to SERVICE MENU...\n");
             BookServices();
            return;
        }
        else
        {
            printf("Invalid choice. Please enter a number between 1 and 7.\n");
        }
    }
}


void ServiceDetails(const char *serviceName)
{
    FILE *file;
    char line[256];
    int found = 0;

    file = fopen("service.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, serviceName) != NULL)
        {
            found = 1;
            printf("%s", line);
            continue;
        }

        if (found && (strstr(line, "Book Borrowing") != NULL ||
                      strstr(line, "Study Rooms") != NULL ||
                      strstr(line, "Reference Services") != NULL ||
                      strstr(line, "Computer and Internet Access") != NULL ||
                      strstr(line, "Community Programs") != NULL ||
                      strstr(line, "Access to Special Collections") != NULL))
        {
            break;
        }

        if (found)
        {
            printf("%s", line);
        }
    }

    if (!found)
    {
        printf("No information found for %s.\n", serviceName);
    }

    fclose(file);
}




//Shelf Management
void management()//
{
    char selection;
    printf("\n--- SHELF MANAGEMENT MENU ---\n");
    printf("1. Search For Categories\n");
    printf("2. Update Categorization And Placement\n");
    printf("3. Back To LIBRARY STAFF MENU\n");

    while (1)
    {
        printf("Enter Function above(1-3): ");
        scanf("%d", &selection);
        if(selection == 1)
        {
            printf("\n-------------------------------------\n");
            categories();
            break;
        }

        else if(selection == 2)
        {
            printf("\n-------------------------------------\n");
            updateCP();
            break;
        }

        else if(selection == 3)
        {
            printf("Successfully Cancel!\n\n");
            StaffMenu();
            break;
        }

        else
        {
            printf("Invalid choice. Please Try again.\n\n");
        }
    }
}


void categories()
{
    struct Book book[100];
    int book_count = 0;
    char selected_genre[20];
    int choice;
    char selection;

    FILE *booksfile;
    booksfile = fopen("books.txt", "r");
    if (booksfile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(booksfile, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                  book[book_count].book_code,
                  book[book_count].title,
                  book[book_count].author,
                  &book[book_count].year,
                  book[book_count].genre,
                  book[book_count].publisher,
                  book[book_count].format,
                  &book[book_count].available,
                  &book[book_count].borrowed,
                  book[book_count].summary) != EOF)
    {
        book_count++;
    }
    fclose(booksfile);

    while (1)
    {
        printf("\n--- DIVE INTO GENRE EXPLORATION ---\n");
        printf("What\'s Your Preferred Genre?\n");
        printf("1. Fantasy\n");
        printf("2. Romance\n");
        printf("3. Fiction\n");
        printf("4. Horror\n");
        printf("5. Journal\n");
        printf("6. View All\n");
        printf("7. Exit\n");

        printf("Enter your choice (1-8): ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            strcpy(selected_genre, "Fantasy");
        }

        else if (choice == 2)
        {
            strcpy(selected_genre, "Romance");
        }

        else if (choice == 3)
        {
            strcpy(selected_genre, "Fiction");
        }

        else if (choice == 4)
        {
            strcpy(selected_genre, "Horror");
        }

        else if (choice == 5)
        {
            strcpy(selected_genre, "Journal");
        }

        else if (choice == 6)
        {
            printf("\n--- ALL BOOKS ---");
            for (int i = 0; i < book_count; i++)
            {
                bookdetails(book[i]);
            }

            if (selection == 'E' || selection == 'e')
            {
            management();
            break;
            }

            else
            {
                continue;
            }
        }

        else if (choice == 7)
        {
            management();
            break;
        }

        else
        {
            printf("Invalid value! Please re-enter.\n");
            continue;
        }

        printf("\n--- BOOKS IN THE %s ---\n", selected_genre);

        for (int i = 0; i < book_count; i++)
        {
            if (strcmp(book[i].genre, selected_genre) == 0)
            {
                bookdetails(book[i]);
            }
        }
    }
}


void updateCP()
{
    struct Book book[100];
    FILE *booksfile;
    char code[10], new_code[10], confirm, exit_choice;
    int book_count = 0, found = 0;

    booksfile = fopen("books.txt", "r+");
    if (booksfile == NULL)
    {
        printf("Error: Could not open file\n");
        return;
    }

    while (fscanf(booksfile, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                  book[book_count].book_code, book[book_count].title, book[book_count].author,
                  &book[book_count].year, book[book_count].genre, book[book_count].publisher,
                  book[book_count].format, &book[book_count].available, &book[book_count].borrowed,
                  book[book_count].summary) != EOF)
    {
        book_count++;
    }

    do
    {
        found = 0;

        printf("\nEnter Book ID to update: ");
        scanf("%s", code);

        for (int i = 0; i < book_count; i++)
        {
            if (strcmp(book[i].book_code, code) == 0)
            {
                found = 1;

                printf("\nBook found:\n");
                printf("%-7s %-30s %-20s %-10s %-10s %-20s %-10s %-10s %-10s\n",
                       "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
                printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
                printf("%-7s %-30s %-20s %-10d %-10s %-20s %-10s %-10d %-10d\n\n",
                       book[i].book_code, book[i].title, book[i].author,
                       book[i].year, book[i].genre, book[i].publisher,
                       book[i].format, book[i].available, book[i].borrowed);

                printf("Is this the book you want to update? (y/n): ");
                while ((getchar()) != '\n');
                scanf("%c", &confirm);

                if (confirm == 'y')
                {
                    int code_exists, valid_format;

                    do
                    {
                        code_exists = 0;
                        valid_format = 1;

                        printf("\nEnter new Book Code: ");
                        scanf("%s", new_code);

                        for (int j = 0; j < book_count; j++)
                        {
                            if (strcmp(new_code, book[j].book_code) == 0)
                            {
                                code_exists = 1;
                                printf("Error: The code '%s' is already in use. Please try a different code.\n", new_code);
                                break;
                            }
                        }

                        if (new_code[0] == 'F')
                        {
                            strcpy(book[i].genre, "Fantasy");
                        }

                        else if (new_code[0] == 'R')
                        {
                            strcpy(book[i].genre, "Romance");
                        }

                        else if (new_code[0] == 'S' && new_code[1] == 'F')
                        {
                            strcpy(book[i].genre, "Fiction");
                        }

                        else if (new_code[0] == 'H')
                        {
                            strcpy(book[i].genre, "Horror");
                        }

                        else if (new_code[0] == 'C' && new_code[1] == 'F')
                        {
                            strcpy(book[i].genre, "Fiction");
                        }

                        else if (strncmp(new_code, "JRN", 3) == 0)
                        {
                            strcpy(book[i].genre, "Journal");
                        }

                        else
                        {
                            printf("Invalid book code format!\n");
                            valid_format = 0;
                        }
                    }
                    while (code_exists || !valid_format);

                    strcpy(book[i].book_code, new_code);
                    printf("Book Code and Genre updated successfully!\n");
                }

                else
                {
                    printf("No changes were made.\n");
                }
                break;
            }
        }

        if (found == 0)
        {
            printf("Book not found! Please try again.\n");
        }

    } while (found == 0);


    rewind(booksfile);

    for (int i = 0; i < book_count; i++)
    {
        fprintf(booksfile, "%s, %s, %s, %d, %s, %s, %s, %d, %d, %s\n",
                book[i].book_code, book[i].title, book[i].author, book[i].year, book[i].genre,
                book[i].publisher, book[i].format, book[i].available, book[i].borrowed,
                book[i].summary);
    }

    fclose(booksfile);

    printf("\nDo you want to exit to SHELF MANAGEMENT MENU? (y/n): ");
    while ((getchar()) != '\n');
    scanf("%c", &exit_choice);

    if (exit_choice == 'n')
    {
        updateCP();
    }

    else
    {
        management();
    }
}


//Digital Resource Assistance
void digitalresource()
{
    int choice;
    char line[256];
    struct Book book[100];
    int book_count = 0;
    FILE *file = fopen("books.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    printf("\n--- DIGITAL RESOURCE MENU ---\n");
    printf("1. Journal\n");
    printf("2. E-Book\n");
    printf("3. Audio Book\n");
    printf("4. Back to LIBRARY STAFF MENU\n\n");

    while (1)
    {
        printf("Which Digital Resource Are You Looking for? ");
        scanf(" %d", &choice);
        printf("\n");

        if (!file)
        {
            printf("Error opening file.\n");
            return;
        }

        if (choice == 1)
        {
            printf("---------- JOURNALS ----------\n\n");
            printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n", "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), file))
            {
                if (strstr(line, "Journal"))
                {
                    sscanf(line, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]",
                        book[book_count].book_code, book[book_count].title, book[book_count].author,
                        &book[book_count].year, book[book_count].genre, book[book_count].publisher,
                        book[book_count].format, &book[book_count].available, &book[book_count].borrowed,
                        book[book_count].summary);
                    printf("%-7s %-30s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n\n",
                        book[book_count].book_code, book[book_count].title, book[book_count].author,
                        book[book_count].year, book[book_count].genre, book[book_count].publisher,
                        book[book_count].format, book[book_count].available, book[book_count].borrowed);
                    book_count++;
                }
            }
            break;
        }

        else if (choice == 2)
        {
            printf("---------- E-BOOKS ----------\n\n");
            printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n", "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), file))
            {
                if (strstr(line, "E-Book"))
                {
                    sscanf(line, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]",
                        book[book_count].book_code, book[book_count].title, book[book_count].author,
                        &book[book_count].year, book[book_count].genre, book[book_count].publisher,
                        book[book_count].format, &book[book_count].available, &book[book_count].borrowed,
                        book[book_count].summary);
                    printf("%-7s %-30s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n\n\n",
                        book[book_count].book_code, book[book_count].title, book[book_count].author,
                        book[book_count].year, book[book_count].genre, book[book_count].publisher,
                        book[book_count].format, book[book_count].available, book[book_count].borrowed);
                    book_count++;
                }
            }
            break;
        }

        else if (choice == 3)
        {
            printf("---------- AUDIO BOOKS ----------\n\n");
            printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n", "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), file))
            {
                if (strstr(line, "AudioBook"))
                {
                    sscanf(line, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]",
                        book[book_count].book_code, book[book_count].title, book[book_count].author,
                        &book[book_count].year, book[book_count].genre, book[book_count].publisher,
                        book[book_count].format, &book[book_count].available, &book[book_count].borrowed,
                        book[book_count].summary);
                    printf("%-7s %-30s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n\n\n",
                        book[book_count].book_code, book[book_count].title, book[book_count].author,
                        book[book_count].year, book[book_count].genre, book[book_count].publisher,
                        book[book_count].format, book[book_count].available, book[book_count].borrowed);
                    book_count++;
                }
            }
            break;
        }

        else if (choice == 4)
        {
            printf("........Back to LIBRARY STAFF MENU........\n\n");
            fclose(file);
            StaffMenu();
            return;
        }

        else
        {
            printf("Invalid Selection, Please Try Again.\n");
        }
    }

        fclose(file);
        char option;
        while(1)
        {
        printf("Back to LIBRARY STAFF MENU ?(y/n):");
        scanf(" %c", &option);

        if (option == 'n')
        {
            printf("\n");
            digitalresource();
            break;
        }

        else if (option == 'y')
        {
            printf("\n");
            StaffMenu();
            break;
        }

        else
        {
            printf("Invalid option. Try again.\n");
        }
    }
}
