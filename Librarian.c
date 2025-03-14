#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void operation_date() {
    int day, month, year;

    printf("\nDear Librarian,\n");

    while (1) {
        printf("Please enter operation date (dd/mm/yyyy): ");

        if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
            printf("Invalid input. Please use the format dd/mm/yyyy.\n");
            while (getchar() != '\n');
            continue;
        }

        if (month < 1 || month > 12) {
            printf("Invalid month. Please ensure the month is between 1 and 12.\n");
            continue;
        }

        if (day < 1 || day > 31) {
            printf("Invalid day. Please ensure the day is between 1 and 31.\n");
            continue;
        }
        break;
    }

    LibrarianMenu(day, month, year);
}

//Librarian Menu
void LibrarianMenu(int day, int month, int year)//done
{
    printf("\nToday Date: %d/%d/%d\n",day,month,year);
    char selection;
    printf("TIRAMISU LIBRARIAN MENU\n");
    printf("1. Book Inventory Management\n");
    printf("2. Membership Management\n");
    printf("3. Borrowing & Returns\n");
    printf("4. Report Generation\n");
    printf("5. Exit\n");
    while (1)
    {
        printf("Enter Function above(1-5):");
        scanf(" %c",&selection);
        if (selection == '1'){
            printf("-------------------------------------\n");
            BookInventoryManagement(day, month, year);
            break;
        }
        else if (selection == '2'){
            printf("-------------------------------------\n");
            MembershipManagement(day, month, year);
            break;
        }
        else if (selection == '3'){
            printf("-------------------------------------\n");
            BorrowingAndReturns(day, month, year);
            break;
        }
        else if (selection == '4' )
        {
            printf("-------------------------------------\n");
            ReportGeneration(day, month, year);
            break;
        }
        else if (selection == '5' )
        {
            printf("-------------------------------------\n");
            Main_Menu();
            break;
        }
        else
        {
            printf("Invalid Input, Kindly Try Again !\n");
        }
    }

}

//Book Inventory Management
void BookInventoryManagement(int day, int month, int year)//done
{
    char selection;
    printf("\nBOOK INVENTORY MANAGEMENT MENU\n");
    printf("1. View Books\n");
    printf("2. Add Books\n");
    printf("3. Update Books Info\n");
    printf("4. Remove Books\n");
    printf("5. Back to Librarian Menu\n");
    while (1)
    {
        printf("Enter Function Above (1-5):");
        scanf(" %c",&selection);
        if (selection == '1')
        {
            printf("\n");
            viewbooks(day, month, year);
            break;
        }
        else if (selection == '2')
        {
            printf("\n");
            addbooks(day, month, year);
            break;
        }
        else if (selection == '3')
        {
            printf("\n");
            updatebooks(day, month, year);
            break;
        }
        else if (selection == '4')
        {
            printf("\n");
            removebooks(day, month, year);
            break;
        }
        else if (selection == '5'){
            printf("\n");
            LibrarianMenu(day, month, year);
            break;
        }
        else{
            printf("Invalid Selection, Please Try Again.\n");
        }
    }

}

void viewbooks(int day, int month, int year)//done
{
    struct Book book[100];
    FILE *booksfile;
    booksfile = fopen("books.txt","r");
    if (booksfile == NULL){
        printf("Error opening file !\n");
    }

    printf("VIEW BOOKS\n\n");
    int book_count = 0;

    printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n","Code","Title","Author","Year","Genre","Publisher","Format","Available","Borrowed");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");

    while(fscanf(booksfile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                 book[book_count].book_code,book[book_count].title,book[book_count].author,
                 &book[book_count].year,book[book_count].genre,book[book_count].publisher,book[book_count].format,
                 &book[book_count].available,&book[book_count].borrowed,book[book_count].summary) != EOF){
            book_count++;
                 }
    for(int i = 0 ;i < book_count;i++){
        printf("%-7s %-30s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n",book[i].book_code, book[i].title, book[i].author,
               book[i].year, book[i].genre,book[i].publisher,
               book[i].format,book[i].available,book[i].borrowed);
    }

    fclose(booksfile);
    printf("\n");
    char option;
    while(1){
        printf("Back to Book Inventory Menu ?(y/n):");
        scanf("%s", &option);
        if (option == 'y' || option == 'Y'){
            printf("\n");
            BookInventoryManagement(day, month, year);
            break;
        }
        else if (option == 'n' || option == 'N'){
            viewbooks(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }

}

void addbooks(int day, int month, int year) //done
{
    struct Book book [100];
    char add_option;
    int book_count = 0, found = 0;
    FILE *booksfile = fopen("books.txt","r");
    if (booksfile == NULL){
        printf("Error opening file !\n");
    }

    while(fscanf(booksfile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                 book[book_count].book_code,book[book_count].title,book[book_count].author,
                 &book[book_count].year,book[book_count].genre,book[book_count].publisher,book[book_count].format,
                 &book[book_count].available,&book[book_count].borrowed,book[book_count].summary) != EOF){
            book_count++;
    }
    fclose(booksfile);

    struct Book new_book;
    printf("ADD BOOKS SYSTEM\n");
    printf("b: Back to Book Inventory Management.\n");
    printf("Book Code:");
    scanf(" %[^\n]",new_book.book_code);
    for(int i = 0 ;i < book_count;i++){
        if (strcmp(new_book.book_code,"b") == 0){
            printf("...back to Book Inventory Management\n\n");
            BookInventoryManagement(day,month,year);
        }
        else if (strcmp(new_book.book_code,book[i].book_code)== 0){
            found = 1;
            printf("Book Code existed.");
            break;
        }
    }
    if(!found){
        printf("Book Title: ");
        scanf(" %[^\n]",new_book.title);

        printf("Author:");
        scanf(" %[^\n]",new_book.author);
        while (1){
            printf("Year:");
            if(scanf(" %d", &new_book.year) != 1){
                printf("Please enter number only.\n");
                while(getchar()!='\n');
            }
            else{
                break;
            }
        }

        printf("Genre:");
        scanf(" %[^\n]",new_book.genre);

        printf("Publisher:");
        scanf(" %[^\n]",new_book.publisher);

        printf("Format (E-book/PaperBook/Journal/Audio):");
        scanf(" %[^\n]",new_book.format);

        while (1){
            printf("Quantity:");
            if(scanf(" %d", &new_book.available) != 1){
                printf("Please enter number only.\n");
                while(getchar()!='\n');
            }
            else{
                break;
            }
        }
        printf("Summary:");
        scanf(" %[^\n]",new_book.summary);

        booksfile = fopen("books.txt", "a+");  // Append mode
        if (booksfile == NULL) {
        printf("Error opening file!\n");
        }

        fprintf(booksfile,"%s, %s, %s, %d, %s, %s, %s, %d, 0, %s\n",new_book.book_code, new_book.title, new_book.author,new_book.year,
            new_book.genre, new_book.publisher,new_book.format,new_book.available, new_book.summary);
        fclose(booksfile);
        printf("Book added successfully.\n");
    }

    while(1){
        printf("Add another new Books ?(y/n):");
        scanf("%s", &add_option);
        if (add_option == 'y'){
            addbooks(day, month, year);
            break;
        }
        else if (add_option == 'n'){
            printf("Back to Book Inventory Management Menu.\n\n");
            BookInventoryManagement(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Please try again.\n");
        }
    }

}

void updatebooks(int day, int month, int year)//done
{
    struct Book book[100];
    FILE *booksfile;
    booksfile = fopen("books.txt","r+");
    char code[10],choice,option;
    int book_count = 0, found = 0,new_year;

    while(fscanf(booksfile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                 book[book_count].book_code,book[book_count].title,book[book_count].author,
                 &book[book_count].year,book[book_count].genre,book[book_count].publisher,
                 book[book_count].format,&book[book_count].available,
                 &book[book_count].borrowed,book[book_count].summary) != EOF){
            book_count++;
                 }

    printf("UPDATE BOOKS INFO\n");

    printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n","Code","Title","Author","Year","Genre","Publisher","Format","Available","Borrowed");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    for(int i = 0 ;i < book_count;i++){
        printf("%-7s %-30s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n",book[i].book_code, book[i].title, book[i].author,book[i].year,
               book[i].genre,book[i].publisher,book[i].format,book[i].available,book[i].borrowed);
    }
    printf("b: Back to Book Inventory Management Menu");
    printf("\nEnter Book ID:");
    scanf(" %s",code);
    if (strcmp(code,"b") == 0){
            printf("...back to Book Inventory Management\n\n");
            BookInventoryManagement(day,month,year);
    }
    char new_book_code[10];
    printf("\n%-7s %-20s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n","Code","Title","Author","Year","Genre","Publisher","Format","Available","Borrowed");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    for(int i = 0; i < book_count; i++){
        if (strcmp(book[i].book_code, code) == 0){
            found = 1;
            printf("%-7s %-20s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n",book[i].book_code, book[i].title,
                   book[i].author,book[i].year, book[i].genre,book[i].publisher,book[i].format,book[i].available,book[i].borrowed);
            printf("\n1. Book Code\t2. Title\t3. Author\t4. Year \t5. Genre\n6. Publisher\t7. Format\t8. Available\t9. Borrowed\t10. Summary\n\n");
            while(1){
                printf("Enter number attribute to update (1-10):");
                scanf("%d",&choice);
                if (choice == 1){
                    printf("Enter new Book Code:");
                    scanf(" %[^\n]" ,book[i].book_code);
                    break;
                }
                else if (choice == 2){
                    printf("Enter New Title:");
                    scanf(" %[^\n]", book[i].title);
                    break;
                }
                else if (choice == 3){
                    printf("Enter new Author Name: ");
                    scanf(" %[^\n]", book[i].author);
                    break;
                }
                else if (choice == 4){
                    printf("Enter New year:");
                    scanf("%d", &book[i].year);
                    break;
                }
                else if (choice == 5){
                    printf("Enter new Genre:");
                    scanf(" %[^\n]",book[i].genre);
                    break;
                }
                else if (choice == 6){
                    printf("Enter new Publisher:");
                    scanf(" %[^\n]",book[i].publisher);
                    break;
                }
                else if (choice == 7){
                    printf("Enter new Format:");
                    scanf(" %[^\n]", book[i].format);
                    break;
                }
                else if (choice == 8){
                    printf("Enter new Available Number:");
                    scanf("%d" ,&book[i].available);
                    break;
                }
                else if (choice == 9){
                    printf("Enter new Borrowed Number:");
                    scanf("%d" ,&book[i].borrowed);
                    break;
                }
                else if (choice == 10){
                    printf("Summary: %s\n",book[i].summary);
                    printf("Enter new Summary:");
                    scanf(" %[^\n]",book[i].summary);
                    break;
                }
                else{
                    printf("Invalid option.\n");
                }
                break;
            }
            break;
        }
    }
    if (found == 0){
        printf("Book not found!\n");
    }
    else {
        booksfile = fopen("books.txt", "w");
        for (int i = 0; i < book_count; i++) {
            fprintf(booksfile,"%s, %s, %s, %d, %s, %s, %s, %d, %d, %s\n",
            book[i].book_code, book[i].title, book[i].author, book[i].year, book[i].genre,
            book[i].publisher, book[i].format,book[i].available, book[i].borrowed, book[i].summary);
        }
        printf("Book updated successfully!\n");
    }

    fclose(booksfile);
    while(1){
        printf("Update another books info ?(y/n):");
        scanf(" %s", &option);
        if (option == 'n'){
            printf("\n");
            BookInventoryManagement(day, month, year);
            break;
        }
        else if (option == 'y'){
            printf("\n");
            updatebooks(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

void removebooks(int day, int month, int year)
{
    struct Book book[100];
    FILE *bookfile = fopen("books.txt","r");
    int book_count = 0;

    while(fscanf(bookfile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                 book[book_count].book_code,book[book_count].title,book[book_count].author,
                 &book[book_count].year,book[book_count].genre,book[book_count].publisher,
                 book[book_count].format,&book[book_count].available,&book[book_count].borrowed,
                 book[book_count].summary) != EOF){
            book_count++;
                 }

    printf("REMOVE BOOKS\n");
    printf("%-7s %-30s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n","Code","Title","Author","Year","Genre","Publisher","Format","Available","Borrowed");
    printf("-------------------------------------------------------------------------------------------------------------------------------------\n");
    for(int i = 0 ;i < book_count;i++){
        printf("%-7s %-30s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n",book[i].book_code, book[i].title, book[i].author,book[i].year, book[i].genre,
               book[i].publisher,book[i].format,book[i].available,book[i].borrowed);
    }
    char code[10];
    printf("\nb:Back to Book Inventory Management Menu");
    printf("\nEnter Delete Book Code:");
    scanf("%s",&code);
    if (strcmp(code,"b")==0){
        printf("Back to Book Inventory Management Menu.....\n");
        BookInventoryManagement(day,month,year);
    }
    printf("\n%-7s %-20s %-20s %-7s %-10s %-20s %-11s %-10s %-2s\n","Code","Title","Author","Year","Genre","Publisher","Format","Available","Borrowed");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    char confirm_delete;
    int found = 0;
    for(int i = 0; i < book_count; i++){
        if (strcmp(book[i].book_code, code) == 0){
            found = 1;
            printf("%-7s %-20s %-20s %-7d %-10s %-20s %-11s %-10d %-2d\n",book[i].book_code, book[i].title,
                   book[i].author,book[i].year, book[i].genre,book[i].publisher,book[i].format,book[i].available,book[i].borrowed);
            printf("\nBook %s (%s) founded.",book[i].book_code,book[i].title);
            printf("Confirm to delete ?(y/n):");
            getchar();
            scanf("%c",&confirm_delete);
            if(confirm_delete == 'y'){
                bookfile = fopen("books.txt", "w");
                if (bookfile == NULL) {
                    printf("Error opening file for writing.\n");
                }
                for (int j = 0; j < book_count; j++){
                    if (strcmp(book[j].book_code,code) == 0){
                        continue;
                    }
                    fprintf(bookfile,"%s, %s, %s, %d, %s, %s, %s, %d, %d, %s\n",
                            book[j].book_code, book[j].title, book[j].author,book[j].year,
                            book[j].genre,book[j].publisher,book[j].format,book[j].available,book[j].borrowed,book[j].summary);
                }
                fclose(bookfile);
                printf("Book %s deleted successful.",code);
            }
            else{
                printf("Deletion Canceled.");
            }
            break;
        }
    }
    if(!found){
        printf("Book Not found.");
    }
    char option;
    while(1){
        printf("\nDelete another Book ?(y/n):");
        scanf(" %c", &option);
        if (option == 'n'){
            printf("\n");
            BookInventoryManagement(day, month, year);
            break;
        }
        else if (option == 'y'){
            printf("\n");
            removebooks(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

//Membership Management
void MembershipManagement(int day, int month, int year)//done
{
    char selection;
    printf("\nMEMBERSHIP MANAGEMENT MENU\n");
    printf("1. View Members\n");
    printf("2. Register New Members\n");
    printf("3. Update Members Information\n");
    printf("4. Memberships Cancellations\n");
    printf("5. Memberships Renewal\n");
    printf("6. Back to Librarian Menu\n");
    while (1)
    {
        printf("Enter Function Above (1-6):");
        scanf(" %c",&selection);
        if(selection == '1'){
            printf("\n");
            viewmembers(day,month,year);
            break;
        }
        else if (selection == '2')
        {
            printf("\n");
            RegisterMember(day,month,year);
            break;
        }
        else if (selection == '3')
        {
            printf("\n");
            updatemembership(day,month,year);
            break;
        }
        else if (selection == '4')
        {
            printf("\n");
            membershipcancellation(day,month,year);
            break;
        }
        else if (selection == '5')
        {
            printf("\n");
            membershipsrenewal(day,month,year);
            break;
        }
        else if (selection == '6')
        {
            printf("\n");
            LibrarianMenu(day,month,year);
            break;
        }
        else
        {
            printf("Invalid Selection, Please Try Again.\n");
        }
    }
}

void RegisterMember(int day, int month, int year) //done
{

    struct Member members;
    struct Memberships memberships;
    char add_option;
    FILE *membersfile = fopen("members.txt", "r");
    if (membersfile == NULL){
        printf("Error opening file !\n");
    }

    int lastid;
    while(fscanf(membersfile, "%d, %[^,], %d, %[^,], %s\n",&lastid,members.name,&members.age,members.email,members.password) != EOF) {
    }
    fclose(membersfile);
    members.member_id = lastid + 1;

    membersfile = fopen("members.txt","a");
    if (membersfile == NULL){
        printf("Error opening file !\n");
    }
    printf("REGISTER NEW MEMBERSHIP\n");
    printf("b: back to membership management menu\n");
    printf("Enter your name: ");
    scanf(" %[^\n],", members.name);
    if (strcmp(members.name,"b")==0){
        printf("back to membership management menu....\n\n");
        MembershipManagement(day,month,year);
    }
    while(1){
        printf("Enter your age: ");
        if (scanf(" %d", &members.age) != 1){
            printf("Please enter a number only.\n");
            while(getchar() != '\n');
        }
        else{
            break;
        }
    }

    printf("Enter your email: ");
    scanf("%s", members.email);

    int expired_day = day;
    int expired_month = month;
    int expired_year = year;
    int plan;

    printf("Memberships Plan:\n");
    printf("1. 3 Month Plan\n");
    printf("2. 6 Month Plan\n");
    printf("3. 1 Year Plan\n");
    printf("Enter Member Plan (1-3):");
    scanf("%d",&plan);
    if (plan == 1) {
        expired_month = month + 3;
        printf("3 Month Plan Selected\n");
    }
    else if (plan == 2) {
        expired_month = month + 6;
        printf("6 Month Plan Selected\n");
    }
    else if (plan == 3) {
        expired_year = year + 1;
        printf("1 Year Plan Selected\n");
    }

    if (expired_month > 12) {
        expired_month -= 12;
        expired_year += 1;
    }

    fprintf(membersfile,"%d, %s, %d, %s, default123\n", members.member_id,members.name, members.age, members.email);
    fclose(membersfile);

    FILE* membershipsfile = fopen("memberships.txt","a");
    if (membershipsfile == NULL) {
        printf("Error opening memberships file!\n");
        fclose(membersfile);
    }
    fprintf(membershipsfile, "%d, %s, %d, %d, %d, %d, %d, %d\n",
            members.member_id, members.name, day, month, year, expired_day, expired_month, expired_year);
    fclose(membershipsfile);

    printf("New member registered Successfully !\n");

    while(1){
        printf("Add another new member ?(y/n):");
        scanf("%s", &add_option);
        if (add_option == 'y'){
            break;
        }
        else if (add_option == 'n'){
            printf("Back to Membership Management Menu.\n\n");
            MembershipManagement(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Please try again.\n");
        }
    }
}

void updatemembership(int day, int month, int year) //done
{
    FILE *membersfile = fopen("members.txt","r+");
    struct Member members [100];
    int member_count = 0, choice, new_age;
    int member_id;
    char option;
    int found = 0;

    if (membersfile == NULL){
        printf("Error opening file !\n");
    }

    while(fscanf(membersfile, "%d, %[^,], %d, %[^,], %s\n",&members[member_count].member_id,members[member_count].name,&members[member_count].age,
                 members[member_count].email,members[member_count].password) != EOF) {
        member_count++;
    }
    printf("UPDATE MEMBERS INFO\n\n");
    printf("Current Member:\n\n");
    printf("%-10s %-20s %-7s %-20s %-7s\n","Member ID","Name","Age","Email");
    printf("-------------------------------------------------------------------\n");

    for (int i = 0; i < member_count; i++){
        printf("M0%-8d %-20s %-6d %-21s\n",members[i].member_id,members[i].name,members[i].age,members[i].email);
    }
    printf("0: back to membership management menu\n");
    printf("Enter Member ID: M0");
    scanf("%d",&member_id);
    if (member_id == 0){
        printf("back to membership management menu....\n\n");
        MembershipManagement(day,month,year);
    }

    for(int i = 0; i < member_count; i++){
        if (members[i].member_id == member_id){
            found = 1; // member found
            printf("1. Name: %s\n",members[i].name);
            printf("2. Age: %d\n",members[i].age);
            printf("3. Email: %s\n",members[i].email);

            while(1){

                printf("Enter attribute number (1-3):");
                scanf("%d",&choice);

                if (choice == 1){
                    printf("Enter new name:");
                    scanf(" %[^\n]",members[i].name);
                    break;
                }
                else if (choice == 2){
                    printf("Enter new age:");
                    scanf("%d", &members[i].age);
                    break;
                }
                else if (choice == 3){
                    printf("Enter new Email:");
                    scanf("%s", members[i].email);
                    break;
                }
                else{
                    printf("Invalid option. Please Enter Again.\n");
                }
            }
            break;
        }
    }
    if (found) {
        membersfile = fopen("members.txt","w");
        for (int i = 0; i < member_count; i++) {
            fprintf(membersfile, "%d, %s, %d, %s, %s\n", members[i].member_id,members[i].name ,members[i].age, members[i].email, members[i].password);
        }

        printf("Membership updated successfully!\n");
    }
    else {
        printf("Member not found!\n");
    }

    fclose(membersfile);
    while(1){
        printf("Update another members info ?(y/n):");
        scanf("%s", &option);
        if (option == 'n'){
            printf("\n");
            MembershipManagement(day, month, year);
            break;
        }
        else if (option == 'y'){
            printf("\n");
            updatemembership(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

void membershipcancellation(int day, int month, int year) //done
{
    struct Member members[100];
    FILE *membersfile = fopen("members.txt","r+");
    struct Memberships memberships [100];
    FILE* membershipsfile = fopen("memberships.txt","r");
    int member_count = 0;
    int members_count = 0;
    if (membersfile == NULL){
        printf("Error opening file.\n");
    }

    while(fscanf(membersfile, "%d, %[^,], %d, %[^,], %s\n",&members[member_count].member_id,members[member_count].name,&members[member_count].age,members[member_count].email,members[member_count].password) != EOF) {
        member_count++;
    }
    while (fscanf(membershipsfile, "%d, %[^,], %d, %d, %d, %d, %d, %d\n",
                  &memberships[members_count].member_id,
                  memberships[members_count].name,
                  &memberships[members_count].register_date,
                  &memberships[members_count].register_month,
                  &memberships[members_count].register_year,
                  &memberships[members_count].expired_date,
                  &memberships[members_count].expired_month,
                  &memberships[members_count].expired_year) != EOF) {
        members_count++;
    }
    printf("MEMBERSHIP CANCELLATION\n\n");
    printf("%-15s %-20s %-7s %-20s\n","Member ID","Name","Age","Email");
    printf("----------------------------------------------------------------------\n");

    for (int i = 0; i < member_count; i++){
        printf("M0%-13d %-20s %-6d %-21s\n",members[i].member_id,members[i].name,members[i].age,members[i].email);
    }
    int delete_id;
    char confirm_delete;
    printf("0: back to membership management menu\n");
    printf("Member ID: M0"); //search for member id
    scanf("%d",&delete_id);
    if (delete_id == 0){
        printf("back to membership management menu....\n\n");
        MembershipManagement(day,month,year);
    }
    int member_found = 0;
    for (int i = 0; i < member_count; i++){
        if (delete_id == members[i].member_id){
            member_found = 1;
            printf("Member M0%d (%s) founded. Confirm delete ?(y/n):",members[i].member_id,members[i].name);
            getchar();
            scanf("%c", &confirm_delete);
            if(confirm_delete == 'y'|| confirm_delete == 'Y'){
                membersfile = fopen("members.txt", "w");
                membershipsfile = fopen("memberships.txt","w");
                if (membersfile == NULL || membershipsfile == NULL) {
                    printf("Error opening file for writing.\n");
                }
                for (int j = 0; j < member_count; j++){
                    if (members[j].member_id == delete_id){
                        continue;
                    }
                    fprintf(membersfile, "%d, %s, %d, %s, %s\n", members[j].member_id, members[j].name, members[j].age, members[j].email, members[j].password);
                }
                for (int z = 0; z < members_count; z++){
                        if (memberships[z].member_id == delete_id){
                            continue;
                        }
                        fprintf(membershipsfile,"%d, %s, %d, %d, %d, %d, %d, %d\n", memberships[z].member_id,
                                memberships[z].name,memberships[z].register_date,
                                memberships[z].register_month,memberships[z].register_year,
                                memberships[z].expired_date, memberships[z].expired_month, memberships[z].expired_year);
                }
                fclose(membersfile);
                fclose(membershipsfile);
                printf("Member M0%d deleted successful.",delete_id);
            }
            else{
            printf("Deletion Canceled.");
            }
            break;
        }
    }
    if(!member_found){
        printf("Member not found.");
    }
    char option;
    while(1){
        printf("\nDelete another members info ?(y/n):");
        scanf(" %c", &option);
        if (option == 'n'){
            printf("\n");
            MembershipManagement(day, month, year);
            break;
        }
        else if (option == 'y'){
            printf("\n");
            membershipcancellation(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }

}

void membershipsrenewal(int day, int month, int year){
    struct Memberships memberships [100];
    FILE* membershipsfile = fopen("memberships.txt","r");
    int members_count = 0;
    if (membershipsfile == NULL){
        printf("Error opening file !\n");
    }
    while (fscanf(membershipsfile, "%d, %[^,], %d, %d, %d, %d, %d, %d\n",
                  &memberships[members_count].member_id,
                  memberships[members_count].name,
                  &memberships[members_count].register_date,
                  &memberships[members_count].register_month,
                  &memberships[members_count].register_year,
                  &memberships[members_count].expired_date,
                  &memberships[members_count].expired_month,
                  &memberships[members_count].expired_year) != EOF) {
        members_count++;
    }
    printf("MEMBERSHIPS RENEWAL\n");
    printf("Memberships needed to be renew:\n");
    printf("%-10s %-20s %-16s %-12s \n","Member ID","Name","Register Date","Expired Date");
    printf("-------------------------------------------------------------------\n");
    int expired = 0;
    for(int i = 0; i < members_count; i++){
        if ((year > memberships[i].expired_year) || (year == memberships[i].expired_year && month > memberships[i].expired_month) ||
           (year == memberships[i].expired_year && month == memberships[i].expired_month && day > memberships[i].expired_date)) {
               expired = 1;
               printf("M0%-8d %-20s %02d/%02d/%-10d %02d/%02d/%-10d\n",memberships[i].member_id,memberships[i].name,memberships[i].register_date,
               memberships[i].register_month,memberships[i].register_year,memberships[i].expired_date,memberships[i].expired_month,memberships[i].expired_year);
        }
    }
    if(!expired){
        printf("No expired Memberships.");
    }
    else{
        int memberid, found = 0;
        int plan;
        printf("0: back to membership management menu\n");
        printf("Enter Member ID: M0");
        scanf("%d",&memberid);
        if (memberid == 0){
        printf("back to membership management menu....\n\n");
        MembershipManagement(day,month,year);
        }
        printf("%-10s %-20s %-16s %-12s \n","Member ID","Name","Register Date","Expired Date");
        printf("-------------------------------------------------------------------\n");
        for(int i = 0; i < members_count; i++){
            if(memberid == memberships[i].member_id){
                found = 1;
                printf("M0%-8d %-20s %02d/%02d/%-10d %02d/%02d/%-10d\n",memberships[i].member_id,memberships[i].name,memberships[i].register_date,
                memberships[i].register_month,memberships[i].register_year,memberships[i].expired_date,memberships[i].expired_month,
                memberships[i].expired_year);
                printf("Renewal Plan:\n");
                printf("1. 3 Month Plan\n");
                printf("2. 6 Month Plan\n");
                printf("3. 1 Year Plan\n");
                memberships[i].expired_date = day;
                memberships[i].expired_month = month;
                memberships[i].expired_year = year;
                while (1){
                    printf("Enter Renewal Plan (1-3):");
                    scanf("%d",&plan);
                    if (plan == 1){
                        memberships[i].expired_month += 3;
                        if (memberships[i].expired_month > 12) {
                            memberships[i].expired_month -= 12;
                            memberships[i].expired_year += 1;
                        }
                        break;
                    }
                    else if (plan == 2) {
                        memberships[i].expired_month += 6;
                        if (memberships[i].expired_month > 12) {
                            memberships[i].expired_month -= 12;
                            memberships[i].expired_year += 1;
                        }
                        break;
                    }
                    else if (plan == 3) {
                        memberships[i].expired_year += 1;
                        break;
                    }
                    else{
                        printf("Invalid Plan Option. Please Try Again.");
                    }
                }
                printf("Membership renewed successfully! New expiration date: %02d/%02d/%d\n",memberships[i].expired_date, memberships[i].expired_month, memberships[i].expired_year);
                break;
            }
        }
        if (!found) {
            printf("Member with ID M0%d not found.\n", memberid);
        }
    }
    membershipsfile = fopen("memberships.txt","w");
    for (int j = 0; j < members_count; j++){
        fprintf(membershipsfile,"%d, %s, %d, %d, %d, %d, %d, %d\n", memberships[j].member_id,memberships[j].name,memberships[j].register_date,
                memberships[j].register_month,memberships[j].register_year,memberships[j].expired_date, memberships[j].expired_month, memberships[j].expired_year);
    }
    fclose(membershipsfile);
    char option;
    while(1){
        printf("Renew Another Memberships ?(y/n):");
        scanf("%s", &option);
        if (option == 'y'){
            printf("\n");
            membershipsrenewal(day,month,year);
            break;
        }
        else if (option == 'n'){
            printf("\n");
            MembershipManagement(day,month,year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

void viewmembers(int day, int month, int year) //done
{
    FILE *membersfile = fopen("members.txt","r+");
    struct Member members [100];
    int member_count = 0, i, choice, new_age;
    char option;
    int found = 0;
    printf("VIEW MEMBERSHIP\n\n");

    if (membersfile == NULL){
        printf("Error opening file !\n");
    }

    while(fscanf(membersfile, "%d,%[^,],%d,%[^,],%s\n",
                 &members[member_count].member_id,
                 members[member_count].name,
                 &members[member_count].age,
                 members[member_count].email,
                 members[member_count].password) != EOF) {
        member_count++;
    }
    printf("%-15s %-20s %-7s %-20s\n","Member ID","Name","Age","Email");
    printf("----------------------------------------------------------------------\n");
    for (i = 0; i < member_count; i++){
        printf("M0%-13d %-20s %-6d %-21s\n",members[i].member_id,members[i].name,members[i].age,members[i].email);
    }
    fclose(membersfile);
    printf("\n");
    while(1){
        printf("Back to Members Management Menu ?(y/n):");
        scanf("%s", &option);
        if (option == 'y' || option == 'Y'){
            printf("\n");
            MembershipManagement(day, month, year);
            break;
        }
        else if (option == 'n'||option == 'N'){
            printf("\n");
            viewmembers(day, month, year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

//Borrow and Returns //done
void BorrowingAndReturns(int day,int month,int year)
{
    char selection;
    printf("BORROWING AND RETURNS\n");
    printf("1. Books Borrowing\n");
    printf("2. Book Returns\n");
    printf("3. Librarian Menu\n");
    while (1)
    {
        printf("Enter Function above(1-3):");
        scanf(" %c",&selection);
        if (selection == '1')
        {
            printf("-------------------------------------\n");
            borrow_system(day,month,year);
            break;
        }
        else if (selection == '2')
        {
            printf("-------------------------------------\n");
            returned(day,month,year);
            break;
        }
        else if (selection == '3')
        {
            printf("-------------------------------------\n");
            LibrarianMenu(day,month,year);
            break;
        }
        else
        {
            printf("Invalid Input, Kindly Try Again !\n");
        }
    }
}

void borrow_system(int day, int month, int year) //done
{
    struct Borrow_Return borrow[100];
    struct Member members[100];
    struct Book book[100];
    int borrow_count = 0, member_count = 0,book_count = 0;
    char option;
    FILE *borrowfile = fopen("borrowing and return.txt","r");
    FILE *membersfile = fopen("members.txt","r");
    FILE *booksfile = fopen("books.txt","r+");

    if (borrowfile == NULL || membersfile == NULL || booksfile == NULL){
        printf("Error opening file!\n");
    }

    while(fscanf(booksfile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",book[book_count].book_code,book[book_count].title,book[book_count].author,
                 &book[book_count].year,book[book_count].genre,book[book_count].publisher,book[book_count].format,&book[book_count].available,
                 &book[book_count].borrowed,book[book_count].summary) != EOF){
            book_count++;
                 }

    while(fscanf(borrowfile, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d, %d, %f\n",
                 &borrow[borrow_count].member_id,borrow[borrow_count].member_name,borrow[borrow_count].book_code,borrow[borrow_count].status,
                 &borrow[borrow_count].borrow_day,&borrow[borrow_count].borrow_month,&borrow[borrow_count].estimate_day,&borrow[borrow_count].estimate_month,
                 &borrow[borrow_count].return_day,&borrow[borrow_count].return_month,&borrow[borrow_count].fine) != EOF) {
        borrow_count++;
    }

    while(fscanf(membersfile, "%d, %[^,], %d, %[^,], %s\n",
                 &members[member_count].member_id,members[member_count].name,&members[member_count].age,members[member_count].email,
                 members[member_count].password) != EOF) {
        member_count++;
    }

    printf("BORROW SYSTEM\n\n");
    printf("%-10s %-17s %-10s %-15s %-15s %-15s %-15s %-10s\n","MemberID","MemberName","BookCode","Status","Borrow","Est Return","Return" ,"Fine");
    printf("---------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < borrow_count; i++){
        printf("M0%-8d %-17s %-10s %-15s %02d/%02d \t\t%02d/%02d \t\t%02d/%02d \t\t%-10.2f\n",
            borrow[i].member_id, borrow[i].member_name,borrow[i].book_code, borrow[i].status,borrow[i].borrow_day,
            borrow[i].borrow_month,borrow[i].estimate_day,borrow[i].estimate_month,borrow[i].return_day,
            borrow[i].return_month,borrow[i].fine);
    }
    fclose(borrowfile);

    int memberid;
    printf("Press '0' back to borrowing and return menu.");
    printf("\nMember ID: M0"); // Search for member id
    scanf("%d", &memberid);
    int member_found = 0;
    if (memberid == 0){
        printf("Back to Borrowing And Returns Menu ......\n\n");
        BorrowingAndReturns(day,month,year);
    }
    for (int i = 0; i < member_count; i++) {
        if (memberid == members[i].member_id) {
            member_found = 1;
            printf("Member Name: %s\n", members[i].name);
            printf("Book Code: ");
            char bookcode[20];
            scanf(" %s", bookcode);
            int book_found = 0;

            printf("Searching for book code: %s\n", bookcode);
            for (int j = 0; j < book_count; j++) {
                if (strcmp(book[j].book_code, bookcode) == 0) {
                    printf("Book Name: %s\n", book[j].title);
                    book_found = 1;
                    int reservation_updated = 0;
                    //members made reservation before borrow books
                    for (int z = 0; z < borrow_count; z++) {
                        if (memberid == borrow[z].member_id && strcmp(borrow[z].status, "reserved") == 0 && strcmp(borrow[z].book_code, bookcode) == 0) {
                            for (int k = z; k < borrow_count - 1; k++) {
                                borrow[k] = borrow[k + 1];
                            }
                            borrow_count--; // Reduce the borrow record count
                            reservation_updated = 1;
                            printf("Reserved book %s has been changed to borrowed.\n", bookcode);
                            break;
                        }
                    }
                    //members not make reservation
                    if(!reservation_updated && book[j].available > 0){
                        book[j].available -= 1;
                        book[j].borrowed += 1;
                        printf("Book borrowed successfully!\n");
                        fclose(booksfile);
                    }
                    else if (!reservation_updated && book[j].available == 0){
                        printf("Sorry, this book is currently unavailable.\n");
                        break;
                    }
                    //append record
                    booksfile = fopen("books.txt", "w"); // Reopen file for writing
                    if (booksfile == NULL) {
                        printf("Error opening books file for writing!\n");
                    }
                    for (int k = 0; k < book_count; k++) {
                        fprintf(booksfile, "%s, %s, %s, %d, %s, %s, %s, %d, %d, %s\n",
                        book[k].book_code, book[k].title, book[k].author, book[k].year, book[k].genre,
                        book[k].publisher, book[k].format, book[k].available, book[k].borrowed, book[k].summary);
                    }
                    fclose(booksfile);

                    borrowfile = fopen("borrowing and return.txt", "w");
                    if (borrowfile == NULL) {
                        printf("Error opening file for appending!\n");
                    }

                    for (int k = 0; k < borrow_count; k++) {
                    fprintf(borrowfile, "%d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %.2f\n",
                        borrow[k].member_id, borrow[k].member_name, borrow[k].book_code, borrow[k].status,
                        borrow[k].borrow_day, borrow[k].borrow_month, borrow[k].estimate_day, borrow[k].estimate_month,
                        borrow[k].return_day, borrow[k].return_month, borrow[k].fine);
                    }

                    int borrow_day = day, borrow_month = month;
                    int estimate_day = borrow_day + 14;
                    int estimate_month = borrow_month;

                    if ((estimate_month == 1 || estimate_month == 3 || estimate_month == 5 || estimate_month == 7 || estimate_month == 8 || estimate_month == 10 || estimate_month == 12) && estimate_day > 31)
                    {
                        estimate_month += 1;
                        estimate_day -= 31;
                    }
                    else if ((estimate_month == 4 || estimate_month == 6 || estimate_month == 9 || estimate_month == 11) && estimate_day > 30) {
                        estimate_month += 1;
                        estimate_day -= 30;
                    }
                    else if (estimate_month == 2 && estimate_day > 28) {
                        estimate_month += 1;
                        estimate_day -= 28;
                    }

                    if (estimate_month > 12) {
                        estimate_month = 1; // Move to January of the next year
                    }
                    printf("Member Return Book Date: %02d/%02d\n", estimate_day, estimate_month);
                    fprintf(borrowfile, "%d, %s, %s, borrowed, %d, %d, %d, %d, 0, 0, 0.00\n",
                            memberid, members[i].name, bookcode, borrow_day, borrow_month, estimate_day, estimate_month);
                    fclose(borrowfile);
                    printf("Book Borrowed Successfully.\n");
                    break;
                }
            }
            if (!book_found) {
                printf("Book with code %s not found or unavailable.\n", bookcode);
            }
            break;
        }
    }
    if (!member_found) {
        printf("Member not found.\n");
    }
    while(1){
        printf("Borrow another book ?(y/n):");
        scanf("%s", &option);
        if (option == 'y' || option == 'Y'){
            printf("\n");
            borrow_system(day,month,year);
            break;
        }
        else if (option == 'n'|| option == 'N'){
            printf("\n");
            BorrowingAndReturns(day,month,year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
    fclose(membersfile);
}

void returned(int day, int month, int year) //done
{
    struct Borrow_Return borrow[100];
    struct Book book[100];
    int borrow_count = 0,book_count = 0;
    char option;
    FILE *borrowfile = fopen("borrowing and return.txt","r+");
    FILE *bookfile = fopen("books.txt","r+");
    FILE *finefile = fopen("memberfine.txt","a");

    if (borrowfile == NULL || bookfile == NULL) {
        printf("Error opening file!\n");
    }

    while(fscanf(borrowfile, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d, %d, %f\n",
                 &borrow[borrow_count].member_id,borrow[borrow_count].member_name,borrow[borrow_count].book_code,
                 borrow[borrow_count].status,&borrow[borrow_count].borrow_day,&borrow[borrow_count].borrow_month,&borrow[borrow_count].estimate_day,
                 &borrow[borrow_count].estimate_month,&borrow[borrow_count].return_day,&borrow[borrow_count].return_month,&borrow[borrow_count].fine) != EOF) {
        borrow_count++;
    }

    while(fscanf(bookfile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",
                 book[book_count].book_code,
                 book[book_count].title,book[book_count].author,
                 &book[book_count].year,book[book_count].genre,
                 book[book_count].publisher,book[book_count].format,&book[book_count].available,&book[book_count].borrowed,book[book_count].summary) != EOF){
        book_count++;
    }

    printf("RETURN SYSTEM\n\n");
    printf("%-10s %-17s %-10s %-15s %-15s %-15s %-15s %-10s\n","MemberID","MemberName","BookCode","Status","Borrow","Est Return","Return" ,"Fine");
    printf("---------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < borrow_count; i++){
         if (strcmp(borrow[i].status, "borrowed") == 0){
            printf("M0%-8d %-17s %-10s %-15s %02d/%02d \t\t%02d/%02d \t\t%02d/%02d \t\t%-10.2f\n",
            borrow[i].member_id, borrow[i].member_name,borrow[i].book_code, borrow[i].status,borrow[i].borrow_day,
            borrow[i].borrow_month,borrow[i].estimate_day,borrow[i].estimate_month,borrow[i].return_day,
            borrow[i].return_month,borrow[i].fine);
        }
    }
    int member_id;
    printf("Press '0' back to borrowing and return menu.");
    printf("\nEnter Member ID: M0");
    scanf("%d",&member_id);
    if (member_id == 0){
        printf("Back to Borrowing And Returns Menu ......\n\n");
        BorrowingAndReturns(day,month,year);
    }
    int member_found = 0;
    char book_code[20];

    printf("%-10s %-17s %-10s %-15s %-15s %-15s %-15s %-10s\n","MemberID","MemberName","BookCode","Status","Borrow","Est Return","Return" ,"Fine");
    printf("---------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < borrow_count; i++){
        if (borrow[i].member_id == member_id && strcmp(borrow[i].status, "borrowed") == 0){
            member_found = 1;
            printf("M0%-8d %-17s %-10s %-15s %02d/%02d \t\t%02d/%02d \t\t%02d/%02d \t\t%-10.2f\n",
            borrow[i].member_id, borrow[i].member_name,borrow[i].book_code, borrow[i].status,borrow[i].borrow_day,
            borrow[i].borrow_month,borrow[i].estimate_day,borrow[i].estimate_month,borrow[i].return_day,
            borrow[i].return_month,borrow[i].fine);
        }
    }

    if (!member_found) {
        printf("Member ID M0%d not found!\n", member_id);
        fclose(borrowfile);
    }
    else{
        while (1) {
            printf("\nEnter the Book Code to return (or type 'done' to finish): ");
            scanf("%s", book_code);

            if (strcmp(book_code, "done") == 0) {
                break;
            }
            int book_found = 0;
            for (int i = 0; i < borrow_count; i++) {
                if (borrow[i].member_id == member_id && strcmp(borrow[i].book_code, book_code) == 0 && strcmp(borrow[i].status, "borrowed")==0) {
                    book_found = 1;
                    strcpy(borrow[i].status, "returned");

                    borrow[i].return_day = day;
                    borrow[i].return_month = month;

                    int overdue_days = (borrow[i].return_day - borrow[i].estimate_day) + (borrow[i].return_month - borrow[i].estimate_month) * 30;

                    borrow[i].fine = overdue_days > 0 ? overdue_days * 1 : 0.00;

                    if (borrow[i].fine > 0) {
                        printf("Member will be fined by RM%.2f\n", borrow[i].fine);
                        fprintf(finefile, "%d, %s, %.2f, Unpaid\n", borrow[i].member_id, borrow[i].member_name, borrow[i].fine);
                    }

                    for (int j = 0; j < book_count; j++) {
                        if (strcmp(book[j].book_code, book_code) == 0) {
                            book[j].available += 1;
                            book[j].borrowed -= 1;
                            break;
                        }
                    }
                    printf("Book %s has been successfully returned.\n", book_code);
                    break;
                }
            }
            if (!book_found) {
                printf("Book code %s not found for member M0%d.\n", book_code, member_id);
                break;
            }
        }
        bookfile = fopen("books.txt", "w");
        for (int j = 0; j < book_count; j++) {
            fprintf(bookfile, "%s, %s, %s, %d, %s, %s, %s, %d, %d, %s\n", book[j].book_code, book[j].title, book[j].author,
                book[j].year, book[j].genre, book[j].publisher, book[j].format, book[j].available, book[j].borrowed, book[j].summary);
        }
        fclose(bookfile);

        borrowfile = fopen("borrowing and return.txt", "w");
        for (int j = 0; j < borrow_count; j++) {
            fprintf(borrowfile, "%d, %s, %s, %s, %d, %d, %d, %d, %d, %d, %.2f\n", borrow[j].member_id, borrow[j].member_name,
                borrow[j].book_code, borrow[j].status, borrow[j].borrow_day, borrow[j].borrow_month, borrow[j].estimate_day,
                borrow[j].estimate_month, borrow[j].return_day, borrow[j].return_month, borrow[j].fine);
        }
        fclose(borrowfile);
        fclose(finefile);
    }

    while(1){
        printf("Return another book ?(y/n):");
        scanf("%s", &option);
        if (option == 'y'){
            printf("\n");
            returned(day,month,year);
            break;
        }
        else if (option == 'n'){
            printf("\n");
            BorrowingAndReturns(day,month,year);
            break;
        }
        else{
            printf("Invalid option. Try again.\n");
        }
    }
}

//Report Generation
void ReportGeneration(int day, int month, int year)
{
    struct Borrow_Return borrowandreturn[100];
    struct Book book[100];
    FILE *borrowandreturnfile = fopen("borrowing and return.txt","r");
    FILE *booksfile = fopen("books.txt","r");
    int book_count = 0, borrow_return_count = 0;

    if(borrowandreturnfile == NULL || booksfile == NULL){
        printf("Error opening file !\n");
    }

    while(fscanf(borrowandreturnfile, "%d, %[^,], %[^,], %[^,], %d, %d, %d, %d, %d, %d, %f\n",
                 &borrowandreturn[borrow_return_count].member_id,borrowandreturn[borrow_return_count].member_name,borrowandreturn[borrow_return_count].book_code,borrowandreturn[borrow_return_count].status,
                 &borrowandreturn[borrow_return_count].borrow_day,&borrowandreturn[borrow_return_count].borrow_month,&borrowandreturn[borrow_return_count].estimate_day,&borrowandreturn[borrow_return_count].estimate_month,
                 &borrowandreturn[borrow_return_count].return_day,&borrowandreturn[borrow_return_count].return_month,&borrowandreturn[borrow_return_count].fine) != EOF) {
        borrow_return_count++;
    }

    while(fscanf(booksfile,"%[^,], %[^,], %[^,], %d, %[^,], %[^,], %[^,], %d, %d, %[^\n]\n",book[book_count].book_code,book[book_count].title,book[book_count].author,
                 &book[book_count].year,book[book_count].genre,book[book_count].publisher,book[book_count].format,&book[book_count].available,
                 &book[book_count].borrowed,book[book_count].summary) != EOF){
            book_count++;
                 }
    fclose(borrowandreturnfile);
    fclose(booksfile);

    printf("REPORT & GENERATION\n\n");
    int book_on_borrowed = 0;
    for(int i = 0; i < book_count; i++){
        book_on_borrowed += book[i].borrowed;
    }
    printf("Book On Borrowed: %4d\n",book_on_borrowed);

    int book_in_house = 0;
    for(int i = 0; i < book_count; i++){
        book_in_house += book[i].available;
    }
    printf("Book In House: %7d\n",book_in_house);

    int most_borrowed_num = 0;
    char most_borrowed_book[100];
    char most_borrowed_book_code[10];
    for (int i = 0; i < book_count; i++) {
        if (book[i].borrowed > most_borrowed_num) {
            most_borrowed_num = book[i].borrowed;
            strcpy(most_borrowed_book_code,book[i].book_code);
            strcpy(most_borrowed_book, book[i].title);
        }
    }
    printf("Most Borrowed book:(%s) %s\n",most_borrowed_book_code,most_borrowed_book);

    printf("Overdue Item:\n");
    printf("Cutoff Date:%02d/%02d/%04d", day, month, year);
    printf("\n%-10s %-17s %-10s %-15s %-15s %-15s %-15s %-10s\n","MemberID","MemberName","BookCode","Status","Borrow","Est Return");
    printf("---------------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < borrow_return_count; i++) {
        if (strcmp(borrowandreturn[i].status, "borrowed") == 0){
            if ((month > borrowandreturn[i].estimate_month) ||  (month == borrowandreturn[i].estimate_month && day > borrowandreturn[i].estimate_day)) {
                printf("M0%-8d %-17s %-10s %-15s %02d/%-13d %02d/%-13d\n",
                borrowandreturn[i].member_id, borrowandreturn[i].member_name,borrowandreturn[i].book_code, borrowandreturn[i].status,borrowandreturn[i].borrow_day,
                borrowandreturn[i].borrow_month,borrowandreturn[i].estimate_day,borrowandreturn[i].estimate_month);
            }
        }
    }

    char option;
    while(1){
        printf("\n\nBack to Librarian Menu ?(y/n):");
        scanf("%s", &option);
        if (option == 'y'){
            printf("\n");
            LibrarianMenu(day,month,year);
            break;
        }
        else if (option == 'n'){
            printf("\n");
            ReportGeneration(day,month,year);
            break;
        }
        else{
            printf("Invalid option. Try again.");
        }
    }
}
