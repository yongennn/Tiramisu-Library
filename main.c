#include <stdio.h>
#include <stdlib.h>
#include "library.h"


void login(){
    FILE *membersfile = fopen("members.txt","r+");
    struct Member members [100];
    int member_count = 0;
    char username[50], password[50];
    char librarian_username[] = "tiramisulibrarian";
    char librarian_password[] = "tiramisu_1234";
    char staff_username[] = "tiramisustaff";
    char staff_password[] = "staff_890";

    while(fscanf(membersfile, "%d, %[^,], %d, %[^,], %s\n",&members[member_count].member_id,members[member_count].name,&members[member_count].age,
                 members[member_count].email,members[member_count].password) != EOF) {
        member_count++;
    }
    int selection;
    printf("\n=======LOGIN TO TIRAMISU LIBRARY=======\n");
    printf("\n1. Members login");
    printf("\n2. Staff Login");
    while(1){
        printf("\nEnter your role (1-2):");
        getchar();
        scanf(" %d", &selection);
        if (selection == 2){
            printf("-------------------------------------");
            printf("\nSTAFF LOGIN\n");
            while (1) {
                printf("\nUSERNAME: ");
                scanf(" %s", username);
                printf("PASSWORD: ");
                scanf(" %s", password);

                if (strcmp(username, librarian_username) == 0 && strcmp(password, librarian_password) == 0) {
                    printf("Librarian login successful.\n");
                    operation_date();
                    break;
                }
                else if (strcmp(username, staff_username) == 0 && strcmp(password, staff_password) == 0) {
                    printf("Staff login successful.\n");
                    StaffMenu();
                    break;
                }
                else {
                    printf("Invalid username or password. Please try again.\n");
                }
            }
            break;
        }
        else if (selection == 1){
            members_main();
            break;
        }
        else{
            printf("Invalid Selection, Please select again...");
        }
    }
}
