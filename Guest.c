#include <stdio.h>
#include <stdlib.h>
#include "library.h"

void Main_Menu(){
    int choice;
    char selection;

    printf("\n======WELCOME TO TIRAMISU LIBRARY======\n");
    printf("1. BROWSE THE LIBRARY\n");
    printf("2. DISCOVER EXCITING EVENTS AND WORKSHOPS AHEAD\n");
    printf("3. EXPERIENCE PREMIUM LIBRARY SERVICES & MEMBER REWARDS\n");
    printf("4. LOGIN\n");
    printf("5. BECOME OUR MEMBER NOW!\n");
    printf("6. EXIT\n");

    while (1)
    {
        printf("Enter your choice (1-6): ");
        scanf(" %d", &choice);

        if (choice == 1){
            printf("\n-------------------------------------\n");
            Explore_Books();
            break;
        }
        else if (choice == 2){
            printf("\n-------------------------------------\n");
            View_Event();
            break;
        }
        else if (choice == 3){
            printf("\n-------------------------------------\n");
            Service_Menu();
            break;
        }
        else if (choice == 4){
            printf("\n-------------------------------------\n");
            login();
            break;
        }
        else if (choice == 5) {
            printf("\n-------------------------------------\n");
            printf("\nBECOME OUR LIBRARY MEMBER TO ENJOY PREMIUM SERVICES!\n");
            printf("Ways to Become Our Member\n");
            printf("1. Sign up Register Form at the Tiramisu Library Counter\n");
            printf("2. Choose your preferred packets (3 Months Packet, 6 Months Packet, 12 Months Packet)\n");
            printf("3. Pay the Payment and Done your Registration\n");
            while(1){
                printf("Press E/e to return to MAIN MENU:");
                scanf(" %c", &selection);
                if (selection == 'E' || selection == 'e') {
                    printf("\n-------------------------------------\n");
                    Main_Menu();
                    break;
                }
                else {
                    printf("\nInvalid input! Please Re-enter\n");
                    continue;
                }
            }
        }
        else if (choice == 6){
            printf("\nThank you for visiting! We hope to see you again soon.\n");
            break;
        }
        else{
            printf("Invalid value! Please re-enter\n");
            printf("\n-------------------------------------\n");
        }
    }
}

void Explore_Books(){
    int choice;

    while (1){
        printf("\n=====FIND YOUR PERFECT READ=====\n");
        printf("1. CATEGORIES\n");
        printf("2. AVAILABLE RESOURCES\n");
        printf("3. BOOK SEARCH\n");
        printf("4. EXIT TO LIBRARY MAIN MENU\n");

        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        if (choice == 1){
            printf("\n-------------------------------------\n");
            Book_Categories();
            break;
        }
        else if (choice == 2){
            printf("\n-------------------------------------\n");
            Available_Resource();
            break;
        }
        else if (choice == 3){
            printf("\n-------------------------------------\n");
            BookSearchBar();
            break;
        }
        else if (choice == 4){
            printf("\n-------------------------------------\n");
            Main_Menu();
            break;
        }
        else{
            printf("Invalid value! Please re-enter\n");
            printf("\n-------------------------------------\n");
        }
    }
}

void printBooksDetails(struct Book book){
    printf("\nCode: %s\n", book.book_code);
    printf("Title: %s\n", book.title);
    printf("Author: %s\n", book.author);
    printf("Year: %d\n", book.year);
    printf("Genre: %s\n", book.genre);
    printf("Publisher: %s\n", book.publisher);
    printf("Format: %s\n", book.format);
    printf("Summary: %s\n", book.summary);
    printf("--------------------------------------------------------------------------------------------------------------------\n");
}

void Book_Categories() {
    struct Book book[100];
    int book_count = 0;
    char selected_genre[20];
    int choice;
    char selection;
    char input[100];

    FILE *booksfile;
    booksfile = fopen("books.txt", "r");
    if (booksfile == NULL){
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
                  book[book_count].summary) != EOF) {
        book_count++;
    }
    fclose(booksfile);

    while (1) {

        printf("\n=====DIVE INTO GENRE EXPLORATION====\n");
        printf("What\'s Your Preferred Genre?\n");
        printf("1. FANTASY\n");
        printf("2. ROMANCE\n");
        printf("3. FICTION\n");
        printf("4. HORROR\n");
        printf("5. JOURNAL\n");
        printf("6. VIEW ALL\n");
        printf("7. EXIT\n");

        printf("Enter your choice (1-7): ");
        scanf("%d", &choice);

        if (choice == 1) {
            strcpy(selected_genre, "Fantasy");
        }
        else if (choice == 2) {
            strcpy(selected_genre, "Romance");
        }
        else if (choice == 3) {
            strcpy(selected_genre, "Fiction");
        }
        else if (choice == 4) {
            strcpy(selected_genre, "Horror");
        }
        else if (choice == 5) {
            strcpy(selected_genre, "Journal");
        }
        else if (choice == 6){
            printf("\n=====ALL BOOKS=====");
            for (int i = 0; i < book_count; i++){
                printBooksDetails(book[i]);
            }

            printf("Press any key to return to GENRE SELECTION, or type 'E/e' to head back to the Main Menu: ");
            scanf(" %c", &selection);
            if (selection == 'E' || selection == 'e') {
                printf("\n-------------------------------------\n");
                Main_Menu();
                break;
            }
            else {
                continue;
            }
        }
        else if (choice == 7){
            printf("\n-------------------------------------\n");
            Explore_Books();
            break;
        }
        else {
            printf("Invalid value! Please re-enter.\n");
            printf("\n-------------------------------------\n");
            continue;
        }
        printf("\n=====BOOKS IN THE %s=====\n", selected_genre);
        for (int i = 0; i < book_count; i++) {
            if (strcmp(book[i].genre, selected_genre) == 0) {
                printBooksDetails(book[i]);
            }
        }
        printf("Press any key to return to GENRE SELECTION, or type 'E/e' to head back to the Main Menu: ");
        scanf(" %c", &selection);
        if (selection == 'E' || selection == 'e') {
            printf("\n-------------------------------------\n");
            Main_Menu();
            break;
        }
        else {
            continue;
        }
    }
}


void Available_Resource(){
    struct Book book[100];
    int book_count = 0;
    char book_format[20];
    char selection;
    int choice;

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
                  book[book_count].summary) != EOF) {
        book_count++;
    }
    fclose(booksfile);

    while (1) {
        printf("\n=====VIEW AVAILABLE RESOURCE====\n");
        printf("1. PAPERBOOK\n");
        printf("2. E-BOOK\n");
        printf("3. JOURNAL\n");
        printf("4. AUDIO BOOK\n");
        printf("5. VIEW ALL\n");
        printf("6. EXIT\n");

        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);

        if (choice == 1){
            strcpy(book_format,"PaperBook");
            printf("\n=====Available %s=====\n", book_format);
        }
        else if(choice == 2){
            strcpy(book_format,"E-Book");
            printf("\n=====Available %s=====\n", book_format);
            for (int i = 0; i < book_count; i++){
                if (strcmp(book[i].format, book_format) == 0){
                    printf(" Code: %s\n Title: %s\n Author: %s\n Year: %d\n Genre: %s\n Publisher: %s\n Format: %s\n Summary: %s\n",
                            book[i].book_code, book[i].title, book[i].author, book[i].year, book[i].genre, book[i].publisher, book[i].format, book[i].summary);
                    printf("--------------------------------------------------------------------------------------------------------------------\n");
                }
            }
        }
        else if(choice == 3){
            strcpy(book_format,"Journal");
            printf("\n=====Available %s=====\n", book_format);
        }
        else if(choice == 4){
            strcpy(book_format,"AudioBook");
            printf("\n=====Available %s=====\n", book_format);
        }
        else if(choice == 5){
            printf("\n\n====All Available Resources====\n");
            for (int i = 0; i < book_count; i++) {
                if (book[i].available >= 0) {
                    printBooksDetails(book[i]);
                }
            }
            printf("Press any key to return to AVAILABLE RESOURCE MENU, or type 'E/e' to head back to the LIBRARY MAIN MENU: ");
            scanf(" %c", &selection);
            if (selection == 'E' || selection == 'e'){
                printf("\n-------------------------------------\n");
                Main_Menu();
                break;
            }
            else{
                continue;
            }
        }
        else if (choice == 6){
            printf("\n-------------------------------------\n");
            Explore_Books();
            break;
        }
        else {
            printf("Invalid value! Please re-enter.\n");
            printf("\n-------------------------------------\n");
            continue;
        }

        for (int i = 0; i < book_count; i++){
            if (strcmp(book[i].format, book_format) == 0 && book[i].available > 0){
                printBooksDetails(book[i]);
            }
        }
        printf("Press any key to return to AVAILABLE RESOURCE MENU, or type 'E/e' to head back to the LIBRARY Main Menu: ");
        scanf(" %c", &selection);
        if (selection == 'E' || selection == 'e'){
            printf("\n-------------------------------------\n");
            Main_Menu();
            break;
        }
        else{
            continue;
        }
    }
}

void BookSearchBar()
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
                        printf("\nDo you want to exit to EXPLORE BOOK MENU? (y/n): ");
                        scanf(" %c", &confirm);
                        getchar();

                        if (confirm == 'y' || confirm == 'Y')
                        {
                            Explore_Books();
                            return;
                        }
                        else if (confirm == 'n' || confirm == 'N')
                        {
                            BookSearchBar();
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
                                printf("\nDo you want to exit to EXPLORE BOOK MENU? (y/n): ");
                                scanf(" %c", &confirm);
                                getchar();

                                if (confirm == 'y' || confirm == 'Y')
                                {
                                    Explore_Books();
                                    return;
                                }
                                else if (confirm == 'n' || confirm == 'N')
                                {
                                    BookSearchBar();
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
void View_Event(){
    int choice;
    char selection;
    struct Event events[100];
    int event_count = 0;
    char event_type[50];

    FILE *eventsfile;
    eventsfile = fopen("events.txt", "r");
    if (eventsfile == NULL) {
        printf("Error opening file!\n");
        return;
    }


    while (fscanf(eventsfile, "%[^,], %[^,], %[^,], %[^\n]\n",
                    events[event_count].title,
                    events[event_count].date,
                    events[event_count].venue,
                    events[event_count].type) != EOF) {
        event_count++;
    }
    fclose(eventsfile);

    if (event_count == 0) {
    printf("No events available.\n");
    return;
    }

    while(1){
        srand(time(NULL));

        int random_index = rand() % event_count;

        printf("\nDon\'t Miss Out! Discover the Future with Our Upcoming Events!\n");
        printf("Title: %s\n", events[random_index].title);
        printf("Date: %s\n", events[random_index].date);
        printf("Venue: %s\n", events[random_index].venue);

        printf("\n======EXPLORE UPCOMING EVENTS======");
        printf("\n1. WORKSHOP\n");
        printf("2. COMMUNITY PROGRAM\n");
        printf("3. EVENTS\n");
        printf("4. VIEW ALL\n");
        printf("5. EXIT TO LIBRARY MAIN MENU\n");

        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);

        if (choice == 1){
            strcpy(event_type, "Workshop");
        }
        else if (choice == 2){
            strcpy(event_type, "Community events");
        }
        else if (choice == 3){
            strcpy(event_type, "Events");
        }
        else if (choice == 4){
            strcpy(event_type, "All");
        }
        else if (choice == 5){
            printf("\n-------------------------------------\n");
            Main_Menu();
            break;
        }
        else{
            printf("Invalid Input, Please Re-enter\n");
            printf("\n-------------------------------------\n");
            continue;
        }

        printf("\n======EVENTS LISTS======\n");
        for (int i = 0; i < event_count; i++) {
            if (choice == 4 || strcmp(events[i].type, event_type) == 0) {
                printf("Title: %s\n", events[i].title);
                printf("Date: %s\n", events[i].date);
                printf("Venue: %s\n", events[i].venue);
                printf("Type: %s\n", events[i].type);
                printf("-----------------------------------------------------\n");
            }
        }
        printf("If you are interested, you can sign up at the library counter.");
        printf("Press any key to return to EVENTS SELECTION, or type 'E/e' to head back to the LIBRARY Main Menu: ");
        scanf(" %c", &selection);
        if (selection == 'E' || selection == 'e'){
            printf("\n-------------------------------------\n");
            Main_Menu();
            break;
        }
        else{
            continue;
        }
    }
}

void Service_Menu(){
    int choice;
    char selection;

    while (1) {
        printf("\n===== DISCOVER THE BENEFITS OF MEMBERSHIP AND WORLD-CLASS LIBRARY SERVICES =====\n");
        printf("1. LIBRARY SERVICES\n");
        printf("2. MEMBER BENEFITS\n");
        printf("3. EXIT TO LIBRARY MAIN MENU\n");
        printf("Enter Your Choice (1-3): ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("\n-------------------------------------\n");
            Library_Service();
            break;
        }
        else if (choice == 2) {
            printf("\n-------------------------------------\n");
            Member_Benefit();
            break;
        }
        else if (choice == 3){
            printf("\n-------------------------------------\n");
            Main_Menu();
            break;
        }
        else {
            printf("Invalid Input, Please Re-enter.\n");
            printf("\n-------------------------------------\n");
        }

    }
}

void Library_Service(){
    struct LibraryService services[100];
    int service_count = 0;
    char selection;

    FILE *servicefile = fopen("service.txt", "r");
    if (servicefile == NULL) {
        printf("Error opening file!\n");
        return;
    }


    while (fscanf(servicefile, "%[^,], %[^\n]\n", services[service_count].service_title, services[service_count].service_description) != EOF) {
        service_count++;
    }

    fclose(servicefile);

    if (service_count == 0) {
        printf("No service available.\n");
        return;
    }

    printf("\n===== VIEW LIBRARY SERVICES =====\n");
    for (int i = 0; i < service_count; i++) {
        printf("%d. %s : %s\n", i+1, services[i].service_title, services[i].service_description);
    }

    printf("\nPress any key to return to last page, or type 'E/e' to head back to the LIBRARY Main Menu: ");
    scanf(" %c", &selection);
    if (selection == 'E' || selection == 'e'){
        printf("\n-------------------------------------\n");
        Main_Menu();
    }
    else{
        printf("\n-------------------------------------\n");
        Service_Menu();
    }
}

void Member_Benefit(){
    struct MemberBenefit benefits[100];
    int benefit_count = 0;
    char selection, answer;

    FILE *benefitfile = fopen("benefit.txt", "r");
    if (benefitfile == NULL) {
        printf("Error opening file!\n");
        return;
    }


    while (fscanf(benefitfile, "%[^,], %[^\n]\n", benefits[benefit_count].benefit_title, benefits[benefit_count].benefit_description) != EOF) {
        benefit_count++;
    }

    fclose(benefitfile);

    if (benefit_count == 0) {
        printf("No service available.\n");
        return;
    }

    printf("\n===== VIEW MEMBER BENEFITS =====\n");
    for (int i = 0; i < benefit_count; i++) {
        printf("%d. %s : %s\n", i+1, benefits[i].benefit_title, benefits[i].benefit_description);
    }

    printf("\nType any key to return to SERVICE MENU (Type 'E' to go back to the MAIN MENU): ");
    scanf(" %c", &selection);
    if (selection == 'E' || selection == 'e') {
        printf("\n-------------------------------------\n");
        Main_Menu();
    }
    else {
        printf("\n-------------------------------------\n");
        Service_Menu();
    }
}

int main(){
    Main_Menu();
}
