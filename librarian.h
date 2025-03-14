#ifndef library_h   // Include guard to prevent multiple inclusions
#define library_h

#define MAX_LEN 100
#define MAX_BOOKS 100
#define MAX_BORROW_HISTORY 50
#define MAX_MEMBERS 100
#define MAX_GENRES 10

struct Member{
    int member_id;
    char name[50];
    int  age;
    char email[50];
    char password[50];
};

struct Memberships{
    int  member_id;
    char name[50];
    int register_date;
    int register_month;
    int register_year;
    int expired_date;
    int expired_month;
    int expired_year;
};

struct Book{
    char book_code[10];
    char title[100];
    char author[50];
    int year;
    char genre[50];
    char publisher[50];
    char format[10];
    int available;
    int borrowed;
    char summary[100];
};

struct Borrow_Return{
    int member_id;
    char member_name[50];
    char book_code[10];
    char status[20];
    int  borrow_day;
    int  borrow_month;
    int  estimate_day;
    int  estimate_month;
    int  return_day;
    int  return_month;
    float fine;
};

struct Event{
    char title[100];
    char date[30];
    char venue[100];
    char type[50];
};

struct LibraryService{
    char service_title[100];
    char service_description[200];
};

struct MemberBenefit{
    char benefit_title[100];
    char benefit_description[200];
};

struct Memberfine //done//
{
    int memberID;
    char member_name[50];
    float fine;
    char status[10];
};

//define
void login();

void operation_date();void LibrarianMenu(); void BookInventoryManagement(); void viewbooks();
void addbooks(); void updatebooks(); void removebooks(); void MembershipManagement();
void RegisterMember(); void updatemembership(); void membershipcancellation();
void viewmembers(); void borrow_system(); void BorrowingAndReturns();
void ReportGeneration(); void returned();

void Main_Menu();void Explore_Books();void printBooksDetails(struct Book book);
void Book_Categories(); void Available_Resource(); void BookSearch();
void View_Event();void Service_Menu();void Library_Service();

void BookServices();void BookSearch();
void calculateReturnDate(int borrow_day, int borrow_month, int *return_day, int *return_month);
void ReserveBook(); void LibraryService(); void ServiceDetails(const char *serviceName);void management();
void categories(); void updateCP(); void digitalresource();void Member_Benefit();

void updatepassword(int memberID, const char *newpassword);void mainmenu(int memberID);void searching(int memberID);
void calculateReturnDate(int borrow_day, int borrow_month, int *return_day, int *return_month);
void ReserveBook(memberID);void accountmanagement(int memberID); void borrowhistory(int memberID);
void showmembership(int memberID); void payfine(int memberID);void digitalresource(int memberID);
void recommendation(int memberID); void members_main();


#endif
