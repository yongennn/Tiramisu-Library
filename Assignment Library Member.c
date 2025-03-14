#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "library.h"

#define default_pw "default123"
#define MEMBER_FILE "members.txt"
#define MEMBERSHIP_FILE "memberships.txt"
#define HISTORY_FILE "borrowing and return.txt"
#define BOOK_FILE "books.txt"

void updatepassword(int memberID, const char *newpassword) //done//
{
    struct Member members[100];
    FILE *file = fopen(MEMBER_FILE, "r+");
      if (MEMBER_FILE == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int memberCount = 0;
    int found = 0;

    while (fscanf(file, "%d, %49[^,], %d, %49[^,], %49s",
                  &members[memberCount].member_id, members[memberCount].name,
                  &members[memberCount].age, members[memberCount].email,
                  members[memberCount].password) == 5) {
        memberCount++;
    }

    for (int i = 0; i < memberCount; i++) {
        if (members[i].member_id == memberID) {
            strcpy(members[i].password, newpassword);
            found = 1;
            break;
        }
    }

    if (found) {
        rewind(file);
        for (int i = 0; i < memberCount; i++) {
            fprintf(file, "%d, %s, %d, %s, %s\n",
                    members[i].member_id, members[i].name,
                    members[i].age, members[i].email,
                    members[i].password);
        }
        ftruncate(fileno(file), ftell(file));
        printf("Password Updated Successfully For Member ID :%d!\n", memberID);
    } else {
        printf("Member ID not found!\n");
    }

    fclose(file);
}

void mainmenu(int memberID)//done//
{
    int choice;
    printf("\n\n----------MAIN MENU----------\n\n");
    printf("Logged in as Member ID: **%d**\n\n",memberID);
    printf("1)Searching & Reservation\n");
    printf("2)Account Management\n");
    printf("3)Digital Resource\n");
    printf("4)Recommendation\n");
    printf("5)Exit\n\n");
    printf("Please Enter Your Choice:");
    scanf("%d",&choice);

  switch (choice) {
        case 1:
            printf("--------SEARCHING & RESERVATION--------\n\n");
            searchingandreservation(memberID);
            break;
        case 2:
            printf("--------ACCOUNT MANAGEMENT--------\n\n");
            accountmanagement(memberID);
            break;
        case 3:
            printf("--------DIGITAL RESOURCE--------\n\n");
            digital_resource(memberID);
            break;
        case 4:
            printf("---------RECOMMENDATION---------\n\n");
            recommendation(memberID);
            break;
        case 5:
            printf("Exiting................\n");
            Main_Menu();
            break;
        default:
            printf("Invalid Input, Kindly Try Again !\n");
            mainmenu(memberID);
            break;
    }
}

void searchingandreservation(int memberID) //done//
{
    int choice;
    printf("1) Searching\n");
    printf("2) Reservation\n");
    printf("3) Main Menu\n");
    printf("Please Enter Your Choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        searching(memberID);
    } else if (choice == 2) {
        ReserveBook(memberID);
    } else if (choice == 3) {
        printf("Back to Main Menu.....\n\n");
        mainmenu(memberID);
    } else {
        printf("Invalid input. Please try again.\n\n\n");
        searchingandreservation(memberID);
    }
}

void searching(int memberID)//done//
{
    struct Book books[MAX_BOOKS];
    FILE *booksfile;
    int book_count = 0;
    char keyword[MAX_LEN];

    booksfile = fopen("books.txt", "r");
    if (booksfile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fscanf(booksfile, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                  books[book_count].book_code, books[book_count].title, books[book_count].author,
                  &books[book_count].year, books[book_count].genre, books[book_count].publisher,
                  books[book_count].format, &books[book_count].available,
                  &books[book_count].borrowed, books[book_count].summary) != EOF) {
        book_count++;
        if (book_count >= MAX_BOOKS) break;
    }

    fclose(booksfile);

    while (1) {

        while (getchar() != '\n' && getchar() != EOF);

        printf("\nEnter the book name or part of the title:");
        fgets(keyword, MAX_LEN, stdin);
        keyword[strcspn(keyword,"\n")] = 0;

        if (strlen(keyword) == 0) {
            printf("Please enter a valid book name or keyword.\n");
            continue;
        }

        struct Book matches[MAX_BOOKS];
        int match_count = 0;

        for (int i = 0; i < book_count; i++) {
            if (strstr(books[i].title, keyword) != NULL) {
                matches[match_count++] = books[i];
            }
        }

        if (match_count == 0) {
            printf("No books found with the keyword '%s'.\n\n", keyword);
            continue;
        } else if (match_count == 1) {
            char confirm;
            while (1) {
                printf("\nFound one book: %s.\nMore Detail? (y/n): ", matches[0].title);
                scanf(" %c", &confirm);
                getchar();

                if (confirm == 'y' || confirm == 'Y') {
                    printf("\n---------- BOOK DETAILS ----------\n");
                    printf("Code: %s\nTitle: %s\nAuthor: %s\nYear: %d\nGenre: %s\nPublisher: %s\nFormat: %s\nAvailable: %d\nBorrowed: %d\nSummary: %s\n",
                           matches[0].book_code, matches[0].title, matches[0].author,
                           matches[0].year, matches[0].genre, matches[0].publisher,
                           matches[0].format, matches[0].available, matches[0].borrowed, matches[0].summary);

                    while (1) {
                        printf("\nBack to Main Menu? (y/n): ");
                        scanf(" %c", &confirm);
                        getchar();

                        if (confirm == 'y' || confirm == 'Y') {
                            printf("Returning to main menu with memberID: %d\n", memberID);
                            mainmenu(memberID);
                            return;
                        } else if (confirm == 'n' || confirm == 'N') {
                            members_main();
                            break;
                        } else {
                            printf("Invalid input. Please enter 'y' or 'n'.\n");
                        }
                    }
                } else if (confirm == 'n' || confirm == 'N') {
                    members_main();
                    break;
                } else {
                    printf("Invalid input. Please enter 'y' or 'n'.\n");
                }
            }
        } else {
            printf("\nFound %d books with the keyword '%s':\n", match_count, keyword);

            for (int i = 0; i < match_count; i++) {
                printf("%d. %s\n", i + 1, matches[i].title);
            }

            int choice;
            while (1) {
                printf("\nEnter The Book's Number to get more Detail:");
                if (scanf("%d", &choice) != 1 || choice < 1 || choice > match_count) {
                    printf("Invalid selection. Please try again.\n");
                    while (getchar() != '\n');
                } else {
                    char confirm;
                    while (1) {
                        printf("\nYou chose: %s.\nIs this the book you want? (y/n): ", matches[choice - 1].title);
                        scanf(" %c", &confirm);
                        getchar();

                        if (confirm == 'y' || confirm == 'Y')
                            {
                            printf("\n---------- BOOK DETAILS ----------\n");
                            printf("Code: %s\nTitle: %s\nAuthor: %s\nYear: %d\nGenre: %s\nPublisher: %s\nFormat: %s\nAvailable: %d\nBorrowed: %d\nSummary: %s\n",
                                   matches[choice - 1].book_code, matches[choice - 1].title, matches[choice - 1].author,
                                   matches[choice - 1].year, matches[choice - 1].genre, matches[choice - 1].publisher,
                                   matches[choice - 1].format, matches[choice - 1].available, matches[choice - 1].borrowed, matches[choice - 1].summary);

                            while (1) {
                                printf("\nBack to Main Menu? (y/n): ");
                                scanf(" %c", &confirm);
                                getchar();

                                if (confirm == 'y' || confirm == 'Y') {
                                    printf("Returning to main menu with memberID: %d\n", memberID);
                                    mainmenu(memberID);
                                    return;
                                } else if (confirm == 'n' || confirm == 'N') {
                                    searching(memberID);
                                } else {
                                    printf("Invalid input. Please enter 'y' or 'n'.\n");
                                }
                            }
                        } else if (confirm == 'n' || confirm == 'N') {
                            break;
                        } else {
                            printf("Invalid input. Please enter 'y' or 'n'.\n");
                        }
                    }
                }
            }
        }
    }
}

void calculate_returndate(int borrow_day, int borrow_month, int *return_day, int *return_month)
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

void ReserveBook(memberID)//done//
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

                                if (borrow_day < 1 || borrow_day > 31&&borrow_month < 1 || borrow_month > 12)
                                {
                                    printf("Invalid date. Please enter a proper date.\n");
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
                            calculate_returndate(borrow_day, borrow_month, &return_day, &return_month);

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
                                printf("Do you want to exit to the Main Menu? (y/n): ");
                                scanf(" %c", &exit_confirm);

                                if (exit_confirm == 'y' || exit_confirm == 'Y')
                                {
                                    mainmenu(memberID);
                                    return;
                                }

                                else if (exit_confirm == 'n' || exit_confirm == 'N')
                                {
                                    ReserveBook();
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
                            printf("Book reservation canceled.\n\n\n");
                            searchingandreservation(memberID);
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

void accountmanagement(int memberID)// done//
{
    int choice;

    printf("1)Borrow History\n");
    printf("2)Membership\n");
    printf("3)Pay overdue fine\n");
    printf("4)Main Menu\n\n");
    printf("Please Enter Your Choice:");
    scanf("%d",&choice);

    while (1) {
        if (choice == 1) {
            printf("\n");
            borrowhistory(memberID);
            break;
        } else if (choice == 2) {
            printf("\n");
            showmembership(memberID);
            break;
        } else if (choice == 3) {
            printf("\n");
            payfine(memberID);
            break;
        } else if (choice == 4) {
            printf("Back to Main Menu.....\n");
            mainmenu(memberID);
            break;
        } else {
            printf("Invalid Input, Please Try Again.\n");
            printf("Please Enter Your Choice: ");
            scanf("%d", &choice);
        }
    }
}
void borrowhistory(int memberID)//done//
{
    struct Borrow_Return records[100];
    FILE *file = fopen(HISTORY_FILE, "r");
      if (HISTORY_FILE == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int count = 0;
    while (fscanf(file, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d, %d, %f\n",
                  &records[count].member_id,
                  records[count].member_name,
                  records[count].book_code,
                  records[count].status,
                  &records[count].borrow_day,
                  &records[count].borrow_month,
                  &records[count].return_day,
                  &records[count].return_month,
                  &records[count].estimate_day,
                  &records[count].estimate_month,
                  &records[count].fine) == 11) {
        count++;
    }

    printf("Borrowing History for Member ID %d:\n", memberID);
    printf("---------------------------------------------------------------------------------------------------\n");
    printf("Member ID | Member Name   | Book Code | Status   | Borrow Date  | Return Date  | Due Date  | Fine  \n");
    printf("---------------------------------------------------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < count; i++) {
        if (records[i].member_id == memberID) {
            printf("%-10d | %-14s | %-9s | %-8s | %02d/%02d      | %02d/%02d      | %02d/%02d      | %.2f\n",
                records[i].member_id,
                records[i].member_name,
                records[i].book_code,
                records[i].status,
                records[i].borrow_day, records[i].borrow_month,
                records[i].return_day, records[i].return_month,
                records[i].estimate_day, records[i].estimate_month,
                records[i].fine);
            found = 1;
        }
    }

    if (!found) {
        printf("No records found for Member ID %d.\n", memberID);
    }

    printf("---------------------------------------------------------------------------------------------------\n");
    fclose(file);
    char option;
        while(1){
        printf("Back to Main Menu ?(y/n):");
        scanf(" %c", &option);
        if (option == 'N' || option == 'n'){
            printf("\n");
            borrowhistory(memberID);
            break;
        }
        else if (option == 'y' || option == 'Y'){
            printf("\n");
            mainmenu(memberID);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

void showmembership(int memberID)//done//
{
    struct Memberships memberships[MAX_MEMBERS];
    int membershipCount = 0;

    FILE *file = fopen(MEMBERSHIP_FILE, "r");
    if (file == NULL) {
        printf("Error opening membership file.\n");
        return;
    }

    while (fscanf(file, "%d, %49[^,], %d, %d, %d, %d, %d, %d\n",
                  &memberships[membershipCount].member_id,
                  memberships[membershipCount].name,
                  &memberships[membershipCount].register_date,
                  &memberships[membershipCount].register_month,
                  &memberships[membershipCount].register_year,
                  &memberships[membershipCount].expired_date,
                  &memberships[membershipCount].expired_month,
                  &memberships[membershipCount].expired_year) == 8) {
        membershipCount++;
        if (membershipCount >= MAX_MEMBERS) {
            break;
        }
    }
    fclose(file);

    printf("Membership Details for Member ID %d:\n", memberID);
    printf("\n\n-----------------------------------------------------------\n");
    printf("Member ID | Member Name   | Start Date    | Expiration Date\n");
    printf("-----------------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < membershipCount; i++) {
        if (memberships[i].member_id == memberID) {
            printf("%-10d | %-14s | %02d-%02d-%d | %02d-%02d-%d\n",
                   memberships[i].member_id,
                   memberships[i].name,
                   memberships[i].register_date, memberships[i].register_month, memberships[i].register_year,
                   memberships[i].expired_date, memberships[i].expired_month, memberships[i].expired_year);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No membership details found for Member ID %d.\n", memberID);
    }

    printf("-----------------------------------------------------------\n\n");

    getchar();

    printf("Please press'ENTER' to back to Main Menu:");
    getchar();
    printf("\nBack to Main Menu........\n");
    mainmenu(memberID);
}

void payfine(int memberID) {
    struct Memberfine members[MAX_MEMBERS];
    int memberCount = 0;
    FILE *file = fopen("memberfine.txt", "r");

    if (file == NULL) {
        printf("Error opening member balance file!\n");
        return;
    }

    while (fscanf(file, "%d, %[^,], %f, %s",
                  &members[memberCount].memberID,
                  members[memberCount].member_name,
                  &members[memberCount].fine,
                  members[memberCount].status) != EOF) {
        memberCount++;
    }
    fclose(file);

    struct Memberfine *member = NULL;
    for (int i = 0; i < memberCount; i++) {
        if (members[i].memberID == memberID) {
            member = &members[i];
            break;
        }
    }

    if (member == NULL) {
        printf("No Overdue Record found!\n\n");
        getchar();

        printf("Please press'ENTER' to back to Main Menu:");
        getchar();
        printf("\nBack to Main Menu........\n");
        mainmenu(memberID);
        return;
    }

    printf("\n\nCurrent Fine Information for Member ID %d:\n\n", member->memberID);
    printf("--------------------------------------------------------------------------\n");
    printf("  Member ID  |   Member Name      |    Fine   |   Status \n");
    printf("--------------------------------------------------------------------------\n");
    printf("    %-10d |  %-16s |      $%.2f     |      %s    \n",
           member->memberID, member->member_name, member->fine, member->status);
    printf("--------------------------------------------------------------------------\n");

    if (strcmp(member->status, "Paid") == 0) {
    printf("This member has already paid all fines.\n");
    printf("Back to Main Menu........\n");
    mainmenu(memberID);
    return;
    }

    float paymentAmount;
    printf("Enter the amount you wish to pay: $");
    scanf("%f", &paymentAmount);

    if (paymentAmount <= 0) {
        printf("Invalid amount.\n\n\n");
        payfine(memberID);
        return;
    }

    if (paymentAmount > member->fine) {
        printf("Payment amount exceeds the fine.\n\n");
        printf("Please enter a valid amount.\n");
        payfine(memberID);
        return;
    }

    member->fine -= paymentAmount;

    if (member->fine < 0) {
        member->fine = 0;
    }

    if (member->fine == 0) {
        strcpy(member->status, "Paid");
    }

    file = fopen("memberfine.txt", "w");
    if (file == NULL) {
        printf("Error opening member fine file for writing!\n");
        return;
    }

    for (int i = 0; i < memberCount; i++) {
        fprintf(file, "%d, %s, %.2f, %s\n", members[i].memberID, members[i].member_name, members[i].fine, members[i].status);
    }
    fclose(file);

    printf("Payment successful!\n\n");

    char option;
    while (1) {
        printf("Back to Main Menu? (y/n): ");
        scanf(" %c", &option);
        if (option == 'N' || option == 'n') {
            payfine(memberID);
            break;
        } else if (option == 'y' || option == 'Y') {
            printf("\nBack to Main Menu........\n");
            mainmenu(memberID);
            break;
        } else {
            printf("Invalid option. Try again.\n");
        }
    }
}

void digital_resource(int memberID)//done
{
    int choice;
    char line[256];
    struct Book book[100];
    int book_count = 0;
    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
            printf("Error opening file.\n");
            return;}

    printf("1. Journal\n");
    printf("2. E-Book\n");
    printf("3. Audio Book\n");
    printf("4. Main Menu\n\n");

    while (1) {
        printf("Which Digital Resource Are You Looking for? ");
        scanf(" %d", &choice);
        printf("\n");

        if (!file) {
            printf("Error opening file.\n");
            return;
        }

        if (choice == 1) {
            printf("--------------------------------------------------- JOURNALS ------------------------------------------------------------------------\n\n");
            printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n", "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, "Journal")) {
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
        } else if (choice == 2) {
            printf("--------------------------------------------------- E-BOOKS ------------------------------------------------------------------------\n\n");
            printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n", "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, "E-Book")) {
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
        } else if (choice == 3) {
            printf("------------------------------------------------ AUDIO BOOKS ------------------------------------------------------------------------\n\n");
            printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n", "Code", "Title", "Author", "Year", "Genre", "Publisher", "Format", "Available", "Borrowed");
            printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

            while (fgets(line, sizeof(line), file)) {
                if (strstr(line, "AudioBook")) {
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
        } else if (choice == 4) {
            printf("\nBack to Main Menu........\n\n");
            fclose(file);
            mainmenu(memberID);
            return;
        } else {
            printf("Invalid Selection, Please Try Again.\n");
        }
    }

        fclose(file);
        char option;
        while(1){
        printf("Back to Main Menu ?(y/n):");
        scanf(" %c", &option);
        if (option == 'N' || option =='n'){
            printf("\n");
            printf("\nBack to Digital Resource Menu........\n");
            digital_resource(memberID);
            break;
        }
        else if (option == 'Y' || option =='y'){
            printf("\nBack to Main Menu........\n");
            mainmenu(memberID);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

void recommendation(int memberID) //done//
{
    struct Book books[MAX_BOOKS];
    int bookCount = 0;

    char userBorrowingHistory[MAX_BORROW_HISTORY][MAX_GENRES];
    int historyCount = 0;

    FILE *historyFile = fopen("borrowing and return.txt", "r");
    if (historyFile == NULL) {
        printf("Error opening borrowing history file.\n");
        return;
    }

    while (fscanf(historyFile, "%s", userBorrowingHistory[historyCount]) == 1 && historyCount < MAX_BORROW_HISTORY) {
        historyCount++;
    }
    fclose(historyFile);

    FILE *file = fopen("books.txt", "r");
    if (file == NULL) {
        printf("Error opening books file.\n");
        return;
    }

    while (fscanf(file, "%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                  books[bookCount].book_code,
                  books[bookCount].title,
                  books[bookCount].author,
                  &books[bookCount].year,
                  books[bookCount].genre,
                  books[bookCount].publisher,
                  books[bookCount].format,
                  &books[bookCount].available,
                  &books[bookCount].borrowed,
                  books[bookCount].summary) == 10) {
        bookCount++;
    }

    fclose(file);

    printf("Recommendations for Member ID %d:\n", memberID);
    printf("-----------------------------------------------------------\n");


    int mostBorrowedIndex = -1;
    for (int i = 0; i < bookCount; i++) {
        if (mostBorrowedIndex == -1 || books[i].borrowed > books[mostBorrowedIndex].borrowed) {
            mostBorrowedIndex = i;
        }
    }

    if (mostBorrowedIndex != -1) {
        printf("1. Most Borrowed Book: %s by %s (Borrowed %d times)\n\n",
               books[mostBorrowedIndex].title,
               books[mostBorrowedIndex].author,
               books[mostBorrowedIndex].borrowed);
    }

    srand(time(NULL));
    int randomIndex = rand() % bookCount;
    printf("\n2. Random Recommendation: %s by %s\n\n",
           books[randomIndex].title,
           books[randomIndex].author);

char choice;
printf("\nWould you like to see details of the recommended books? (y/n): ");
scanf(" %c", &choice);

if (choice == 'y') {
    if (mostBorrowedIndex != -1) {
        printf("\nDetails of Most Borrowed Book:\n");
        printf("Book Code: %s\n", books[mostBorrowedIndex].book_code);
        printf("Title: %s\n", books[mostBorrowedIndex].title);
        printf("Author: %s\n", books[mostBorrowedIndex].author);
        printf("Year: %d\n", books[mostBorrowedIndex].year);
        printf("Genre: %s\n", books[mostBorrowedIndex].genre);
        printf("Publisher: %s\n", books[mostBorrowedIndex].publisher);
        printf("Format: %s\n", books[mostBorrowedIndex].format);
        printf("Available: %d\n", books[mostBorrowedIndex].available);
        printf("Borrowed: %d\n", books[mostBorrowedIndex].borrowed);
        printf("Summary: %s\n", books[mostBorrowedIndex].summary);
    }

    printf("\nDetails of Random Recommendation:\n");
    printf("Book Code: %s\n", books[randomIndex].book_code);
    printf("Title: %s\n", books[randomIndex].title);
    printf("Author: %s\n", books[randomIndex].author);
    printf("Year: %d\n", books[randomIndex].year);
    printf("Genre: %s\n", books[randomIndex].genre);
    printf("Publisher: %s\n", books[randomIndex].publisher);
    printf("Format: %s\n", books[randomIndex].format);
    printf("Available: %d\n", books[randomIndex].available);
    printf("Borrowed: %d\n", books[randomIndex].borrowed);
    printf("Summary: %s\n", books[randomIndex].summary);
}

char confirm;
while (1) {
    printf("\nBack to Main Menu? (y/n): ");
    scanf(" %c", &confirm);

    if (confirm == 'y' || confirm == 'Y') {
        printf("Back to Main Menu........");
        mainmenu(memberID);
        return;
    } else if (confirm == 'n' || confirm == 'N') {
        recommendation(memberID);
        break;
    } else {
        printf("Invalid input. Please enter 'y' or 'n'.\n");
    }
}

printf("-----------------------------------------------------------\n");
}

void members_main()//done//
{
    int choice;
    char password[20];
    char newpassword[20];
    int memberID;

    printf("-------------MEMBER LOGIN MENU----------------\n\n");
    printf("Welcome To XXX Library! Login With Your:\n\n");
    printf("1. Default password (For First Time Login)\n");
    printf("2. Custom password\n\n");
    printf("Please Enter Your Choice: ");
    scanf("%d", &choice);
    printf("\n");

    if (choice == 1) {
        printf("--------DEFAULT PASSWORD--------\n\n");
        printf("Member ID: ");
        scanf("%d", &memberID);
        printf("Default Password: ");
        scanf("%s", password);

        struct Member member;
        FILE *fptr = fopen(MEMBER_FILE, "r");
        if (fptr != NULL) {
            int found = 0;
            while (fscanf(fptr, "%d,%49[^,],%d,%49[^,],%49s",
                          &member.member_id, member.name,
                          &member.age, member.email, member.password) == 5) {
                if (member.member_id == memberID && strcmp(password, default_pw) == 0) {
                    printf("Login successfully!Set your Custom Password Now:\n\n");
                    printf("Enter new password: ");
                    scanf("%s", newpassword);
                    updatepassword(memberID, newpassword);
                    found = 1;
                    break;
                }
            }
            fclose(fptr);
            if (!found) {
                printf("Incorrect member ID or password. Login failed.\n");
                login();
            }
        } else {
            printf("Error opening member file.\n");
        }
    } else if (choice == 2) {
        printf("--------CUSTOM PASSWORD--------\n\n");
        printf("Member ID: ");
        scanf("%d", &memberID);
        printf("Custom Password: ");
        scanf("%s", password);

        FILE *fptr = fopen(MEMBER_FILE, "r");
        if (fptr != NULL) {
            struct Member member;
            int found = 0;

            while (fscanf(fptr, "%d,%49[^,],%d,%49[^,],%49s",
                          &member.member_id, member.name,
                          &member.age, member.email, member.password) == 5) {
                if (member.member_id == memberID && strcmp(password, member.password) == 0) {
                    printf("Login successfully!\n\n");
                    found = 1;
                    mainmenu(memberID);
                    break;
                }
            }
            fclose(fptr);
            if (!found) {
                printf("Incorrect member ID or password. Login failed.\n");
                login();
            }
        } else {
            printf("Error opening member file.\n");
        }
    } else {
        printf("Invalid choice. Please try again.\n");
        Main_Menu();
    }

    return 0;
}
