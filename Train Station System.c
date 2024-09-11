#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#pragma warning(disable:4996)
#define MAX_POSITIONS 6

//staff struc
struct Staff {
    char name[50];
    float salary;
    int age;
    char position[30];
    char staffID[7];
    char password[20];
};

//member struc
typedef struct {
	char password[16];
	char iC[15], contactNo[15];
	char memberId[30], name[30], gender[1], bookingId[10];
}Member;


//schedule struc
typedef struct {
	char trainID[20];
	char departureStation[50];
	char arrivalStation[50];
	char departureTime[10];
	char arrivalTime[10];
	int availableSeats;
}TrainSchedule;


//ticket booking struc
struct Payment {
    char paymentType[20];
    float amount;
};

struct TicketBooking {
    char bookID[10];
    char memberID[10];
    char trainID[10];
    char bookDate[11];
    char departureDate[11];
    char seatNum[5];
    char coach;
    int quantity;
    struct Payment paymentInfo;
    char ticketStatus[20];
};



//staff module func
void addStaff();
void viewStaff();
void modifyStaff();
void deleteStaff();
void adminLogin();
void staffLogin();
void staffModule();

//member module func
void addMember();
void searchMember();
void modifyMember();
void displayMember();
void deleteMember();
void reportMember();
void memberModule();

//train schedule func
void displayMenu();
void addscheRecord(FILE* fp);
void searchscheRecord(FILE* fp);
void modifyscheRecord(FILE* fp);
void displayscheAllRecord(FILE* fp);
void deletescheRecord(FILE* fp);
void reportAvailableSeats(FILE* fp);

//ticket bookin func
void addBookingRecord();
void searchRecordBooking();
void modifyBookingRecord();
void deleteBookingRecord();
void displayBookingRecord();
void generateBookingReport();
void ticketBookModule();



void addStaff() {
    struct Staff newStaff;
    char answer;

    FILE* file;
    file = fopen("staff.bin", "ab");
    if (!file) {
        printf("File open error!\n");
        exit(-1);
    }

    do {
        printf("\n-----------------------------------\n");
        printf("Enter Staff ID : ");
        rewind(stdin);
        fgets(newStaff.staffID, sizeof(newStaff.staffID), stdin);

        printf("-----------------------------------\n");
        printf("Enter Staff Name : ");
        rewind(stdin);
        gets(newStaff.name);

        printf("-----------------------------------\n");
        printf("Enter Staff Age : ");
        scanf("%d", &newStaff.age);

        printf("-----------------------------------\n");
        printf("Enter Staff Position : ");
        rewind(stdin);
        gets(newStaff.position);
        printf("-----------------------------------\n");
        printf("Create Staff Password: ");
        rewind(stdin);
        fgets(newStaff.password, sizeof(newStaff.password), stdin);
        strtok(newStaff.password, "\n");

        if (strcmp(newStaff.position, "manager") == 0) {
            newStaff.salary = 5671.0;
        }
        else if (strcmp(newStaff.position, "maintenance crew") == 0) {
            newStaff.salary = 5156.0;
        }
        else if (strcmp(newStaff.position, "train conductor") == 0) {
            newStaff.salary = 4956.0;
        }
        else if (strcmp(newStaff.position, "security officer") == 0) {
            newStaff.salary = 2825.0;
        }
        else if (strcmp(newStaff.position, "ticket inspector") == 0) {
            newStaff.salary = 2119.0;
        }
        else if (strcmp(newStaff.position, "cleaner") == 0) {
            newStaff.salary = 1819.0;
        }
        else {
            newStaff.salary = 0;
        }

        fwrite(&newStaff, sizeof(struct Staff), 1, file);

        printf("\nStaff added successfully~\n");

        printf("\nAny more Staff (Y/N) ? ");
        rewind(stdin);
        scanf("%c", &answer);


    } while (toupper(answer) == 'Y');

    fclose(file);
}

void viewStaff() {
    FILE* file = fopen("staff.bin", "rb");
    if (file == NULL) {
        printf("File open error!\n");
        exit(-1);
    }

    printf("============  ==================  =======   ==================   ===========\n");
    printf(" Staff ID            Name           Age          Position           Salary \n");
    printf("============  ==================  =======   ==================   ===========\n");

    struct Staff staff;
    while (fread(&staff, sizeof(struct Staff), 1, file) == 1) {
        printf("%-13s %-18s %-8d %-20s %.2lf\n", staff.staffID, staff.name, staff.age, staff.position, staff.salary);
    }

    fclose(file);
}

void modifyStaff() {
    char ans, cont, staffID[7], newPassword[20];
    int i = 0, pCount, found, updAge;
    struct Staff S[20];

    FILE* file;
    file = fopen("staff.bin", "rb+");
    if (!file) {
        printf("File open error!\n");
        exit(-1);
    }


    while (fread(&S[i], sizeof(struct Staff), 1, file) == 1)
        i++;
    pCount = i;
    rewind(file);

    do {
        printf("Enter Staff ID to be modified : ");
        scanf("%s", staffID);
        found = 0;

        for (i = 0; i < pCount; i++) {
            if (strcmp(staffID, S[i].staffID) == 0) {
                found = 1;
                printf("============  ==================  ======  ==================   ==========   =============\n");
                printf("\nStaff ID          Name            Age        Position          Salary         Password \n");
                printf("============  ==================  ======  ==================   ==========   =============\n");
                printf("%-13s %-18s %-8d %-20s %-8.2lf %-10s\n", S[i].staffID, S[i].name, S[i].age, S[i].position, S[i].salary, S[i].password);
                printf("\nUpdated age : ");
                rewind(stdin);
                scanf("%d", &updAge);

                printf("\nUpdated staff position : ");
                rewind(stdin);
                fgets(S[i].position, sizeof(S[i].position), stdin);
                strtok(S[i].position, "\n");

                printf("\nUpdated staff password (press enter to keep the same): ");
                fgets(newPassword, sizeof(newPassword), stdin);
                strtok(newPassword, "\n");

                if (strlen(newPassword) > 1) {
                    strcpy(S[i].password, newPassword);
                }

                printf("Confirm to Modify (Y=yes) ? ");
                rewind(stdin);
                scanf(" %c", &ans);

                if (strcmp(S[i].position, "manager") == 0) {
                    S[i].salary = 5671.0;
                }
                else if (strcmp(S[i].position, "maintenance crew") == 0) {
                    S[i].salary = 5156.0;
                }
                else if (strcmp(S[i].position, "train conductor") == 0) {
                    S[i].salary = 4956.0;
                }
                else if (strcmp(S[i].position, "security officer") == 0) {
                    S[i].salary = 2825.0;
                }
                else if (strcmp(S[i].position, "ticket inspector") == 0) {
                    S[i].salary = 2119.0;
                }
                else if (strcmp(S[i].position, "cleaner") == 0) {
                    S[i].salary = 1819.0;
                }
                else {
                    S[i].salary = 0;
                }

                if (toupper(ans) == 'Y') {
                    S[i].age = updAge;
                }

                printf("\nUpdated record : \n");

                printf("============  ==================  ======    ==================   ==========\n");
                printf(" Staff ID           Name            Age           Position          Salary \n");
                printf("============  ==================  ======    ==================   ==========\n");
                printf("%-13s %-18s %-8d %-20s %.2lf\n", S[i].staffID, S[i].name, S[i].age, S[i].position, S[i].salary);
            }
        }
        if (!found)
            printf("\nNo staff found with ID %s\n", staffID);
        printf("\nDo you want to modify another record? (Y=yes): ");
        scanf(" %c", &cont);

    } while (toupper(cont) == 'Y');


    rewind(file);
    fwrite(S, sizeof(struct Staff), pCount, file);

    fclose(file);
}

void deleteStaff() {
    char staffID[6], confirm;
    int i = 0, pCount, found = 0;
    struct Staff S[20];

    FILE* file;
    file = fopen("staff.bin", "rb");
    if (!file) {
        printf("File open error!\n");
        exit(-1);
    }


    while (fread(&S[i], sizeof(struct Staff), 1, file) == 1)
        i++;
    pCount = i;
    fclose(file);

    printf("\nEnter Staff ID of the staff to be deleted: ");
    scanf("%s", staffID);

    for (i = 0; i < pCount; i++) {
        if (strcmp(staffID, S[i].staffID) == 0) {
            found = 1;
            printf("\n============  ==================  ======   ==================   ==========\n");
            printf("\n Staff ID          Name            Age         Position           Salary \n");
            printf("============  ==================  ======   ==================   ==========\n");
            printf("%-13s %-18s %-8d %-20s %.2lf\n", S[i].staffID, S[i].name, S[i].age, S[i].position, S[i].salary);

            printf("\nAre you sure you want to delete this staff? (Y/N): ");
            scanf(" %c", &confirm);

            if (toupper(confirm) == 'Y') {
                for (int j = i; j < pCount - 1; j++)
                    S[j] = S[j + 1];
                pCount--;

                file = fopen("staff.bin", "wb");
                if (!file) {
                    printf("Error opening file for writing.\n");
                    return;
                }
                fwrite(S, sizeof(struct Staff), pCount, file);
                fclose(file);

                printf("\nStaff with ID %s has been deleted successfully.\n", staffID);
            }
            else {
                printf("\nDeletion cancelled.\n");
            }
            break;
        }
    }
    if (!found) {
        printf("\nNo staff found with ID %s.\n", staffID);
    }
}

void adminLogin() {
    char adminID[10];
    char adminName[50];
    int choice;

    printf("=================================\n");
    printf("  Enter Your Admin ID and Name  \n");
    printf("----------------------------------\n");
    printf("Admin ID : ");
    scanf("%s", adminID);
    printf("Name : ");
    scanf("%s", adminName);

    if (strcmp(adminID, "AD123") == 0 && strcmp(adminName, "admin123") == 0) {
        printf("\nAdmin login successful~\n");
    }
    else {
        printf("\nLogin unsuccessful\n");
        return adminLogin();
    }

    do {
        printf("\n----------------------------\n");
        printf("|\tWelcome Admin !  \t|\n");
        printf("----------------------------\n");
        printf("What do you want to do ? \n");
        printf("1. Add Staff\n");
        printf("2. Delete Staff\n");
        printf("3. Modify Staff\n");
        printf("4. View Staff Members\n");
        printf("0. Exit\n");
        printf("Enter your choice > ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addStaff();
            break;
        case 2:
            deleteStaff();
            break;
        case 3:
            modifyStaff();
            break;
        case 4:
            viewStaff();
            break;
        case 0:
            system("cls");
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 0);
}

void staffLogin() {
    char staffID[6];
    char password[20];
    struct Staff staff;
    char choice;

    printf("\n================================\n");
    printf("Enter Your Staff ID: ");
    scanf("%s", staffID);
    printf("Enter Your Password: ");
    scanf("%s", password);


    FILE* file;
    file = fopen("staff.bin", "rb");
    if (!file) {
        printf("File Open Error!!\n");
        exit(-1);
    }

    int found = 0;
    while (fread(&staff, sizeof(struct Staff), 1, file) == 1) {
        if (strcmp(staff.staffID, staffID) == 0 && strcmp(staff.password, password) == 0) {
            found = 1;
            printf("\t               Welcome %s staff !\n", staff.name);
            printf("============  ==================  ======   ==================   ==========\n");
            printf("\nStaff ID          Name            Age          Position           Salary \n");
            printf("============  ==================  ======   ==================   ==========\n");
            printf("%-13s %-18s %-8d %-20s %.2lf\n", staff.staffID, staff.name, staff.age, staff.position, staff.salary);

            break;
        }
    }

    if (!found) {
        printf("Staff with ID %s and provided password not found or password incorrect.\n", staffID);
    }

    fclose(file);

    printf("\nPress 1 to go back to main menu... ");
    scanf(" %c", &choice);
    if (choice == '1') {
        return;
    }
    else {
        while (getchar() != '\n');
        getchar();
    }
}

void staffModule()
{
    char choice;

   // do {

        printf("\nStaff Login\n");
        printf("================\n");
        printf("1. Admin\n");
        printf("2. Staff\n");
        printf("0. Exit\n");
        printf("Enter your choice > ");
        scanf(" %c", &choice);

        switch (toupper(choice)) {
        case '1':
            adminLogin();
            break;
        case '2':
            staffLogin();
            break;
        case '0': system("cls");;
            break;
        default:
            printf("\nInvalid choice\n");
        }

   // } while (choice != 0);

   return 0;
}

//staff end


void addMember()
{
    system("cls");

    Member mem;
    char choice, confirmPassword[16];
    int count = 0;


    FILE* fptr;

    fptr = fopen("member.bin", "ab+");

    if (!fptr)
    {
        printf("File Open Error!!");
        exit(-1);
    }

    fseek(fptr, 0, SEEK_END);
    long fileSize = ftell(fptr);

    if (fileSize != 0)
    {
        fseek(fptr, -(long)sizeof(Member), SEEK_CUR);
        fread(&mem, sizeof(Member), 1, fptr);

        sscanf(mem.memberId, "M%04d", &count);
        count++;
    }
    else {
        count = 1;
    }

    do {
        printf("\n\nEnter 'exit' to return main menu anytime. ");
        printf("\n===============================\n");
        printf("\tADD MEMBER\n");
        printf("===============================\n");

        sprintf(mem.memberId, "M%04d", count);

        do {
            printf("Please enter your name : ");
            rewind(stdin);
            gets(mem.name);
            if (strcmp(mem.name, "exit") == 0)
            {
                fclose(fptr);
                return;
            }
        } while (mem.name[0] == '\0');

        do{
            printf("Please enter your IC number (Without '-' ) : ");
            rewind(stdin);
            gets(mem.iC);
            if (strcmp(mem.iC, "exit") == 0)
            {
                fclose(fptr);
                return;
            }
        } while (mem.iC[0] == '\0' || strlen(mem.iC) != 12);

        do {
            printf("Please enter your contact number (Without '-' ) : ");
            rewind(stdin);
            gets(mem.contactNo);
            if (strcmp(mem.contactNo, "exit") == 0)
            {
                fclose(fptr);
                return;
            }
        } while (mem.contactNo[0] == '\0' || strlen(mem.contactNo) != 10);

        do {
            printf("Please enter your gender (M = Male / F = Female): ");
            rewind(stdin);
            gets(mem.gender);
            if (toupper(mem.gender[0]) != 'M' && toupper(mem.gender[0]) != 'F')
            {
                printf("Invalid gender! Please enter again. \n");
            }
            if (strcmp(mem.gender, "exit") == 0)
            {
                fclose(fptr);
                return;
            }
        } while (toupper(mem.gender[0]) != 'M' && toupper(mem.gender[0]) != 'F');

        do {
            printf("\nPassword : ");
            scanf("%s", mem.password);
            if (strcmp(mem.password, "exit") == 0)
            {
                fclose(fptr);
                return;
            }
            if (strlen(mem.password) < 8 || (strlen(mem.password) > 16))
            {
                printf("Please enter the password between 8 to 16 digits.");
                continue;
            }
            printf("Confirm Password : ");
            scanf("%s", confirmPassword);
            if (strcmp(mem.password, confirmPassword) != 0)
            {
                printf("Please enter your password correctly!\n");
            }
        } while (strcmp(mem.password, confirmPassword) != 0);

        fwrite(&mem, sizeof(Member), 1, fptr);

        printf("Added successfully!\n");

        printf("\nAdd another member? (Y = Yes / N = No) : ");
        rewind(stdin);
        scanf("%c", &choice);
        count++;
    } while (toupper(choice) == 'Y');
    fclose(fptr);
}

void searchMember()
{
    Member mem;
    int count = 0, i, no = 1;
    char searchID[30];

    FILE* fptr;

    fptr = fopen("member.bin", "rb");

    if (!fptr)
    {
        printf("File Open Error!!");
        exit(-1);
    }

    printf("\n\nEnter 'exit' to return main menu anytime. ");
    printf("\n=============================================================================================================================\n");
    printf("\t\t\t\t\t\t\tSEARCH MEMBER\n");
    printf("=============================================================================================================================\n");
    printf("Enter member detail (ID, Name or IC Number) : ");
    scanf("%s", &searchID);

    if (strcmp(searchID, "exit") == 0) {
        fclose(fptr);
        return;
    }

    printf("\n\n=============================================================================================================================\n");
    printf("\t\t\t\t\t\t\tMEMBER DETAILS\n");
    printf("=============================================================================================================================\n");
    printf("No.    %-10s \t\t%-20s \t%-13s \t\t\t%-11s \t\t%-5s\n", "User ID", "User Name", "IC Number", "Contact Number", "Gender");
    printf("===   %-10s \t%-20s \t%-13s \t%-11s \t%-5s\n", "==================", "==================", "=========================", "====================", "==========");

    while (fread(&mem, sizeof(Member), 1, fptr))
    {
        if (strcmp(searchID, mem.memberId) == 0 || strcmp(searchID, mem.name) == 0 || strcmp(searchID, mem.iC) == 0)
        {
            printf("\n%d.     %-10s \t\t %-20s \t %-13s \t\t\t %-11s \t\t %-5s\n", no, mem.memberId, mem.name, mem.iC, mem.contactNo, mem.gender);
            count++;
            no++;
        }
    }

    if (count == 0)
    {
        printf("No member found.\n");
    }
    else
    {
        printf("\n\t\t\t< %d member(s) found.>\n\n", count);
    }

    fclose(fptr);
}

void modifyMember()
{
    Member mem[20];
    char id[20], cont, newName[20], newIc[12], newContact[10], newGender[5], password[16], confirmPassword[16];
    int i = 0, error = 0, no = 1, found, memberCount, choice;


    FILE* fptr;
    fptr = fopen("member.bin", "rb");

    while (fread(&mem[i], sizeof(Member), 1, fptr) == 1)
        i++;
    memberCount = i;
    fclose(fptr);

    printf("Please enter the member ID you want to modify : ");
    rewind(stdin);
    scanf("%s", id);
    if (strcmp(id, "exit") == 0)
    {
        fclose(fptr);
        return;
    }
    found = 0;
    for (i = 0; i < memberCount; i++)
    {
        if (strcmp(id, mem[i].memberId) == 0)
        {
            found = 1;
            break;
        }
    }

    if (!found)
    {
        printf("\nMember ID '%s' does not exist.\n", id);
        fclose(fptr);
        return;
    }


    do {
        printf("\nPlease enter your password : ");
        rewind(stdin);
        gets(password);
        found = 0;

        for (i = 0; i < memberCount; i++)
        {
            if (strcmp(id, mem[i].memberId) == 0 && strcmp(password, mem[i].password) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("\nInvalid password or member ID. Please enter again. \n");
            error++;
        }
        if (error >= 3)
        {
            printf("\nToo many attempt. Exiting to menu. \n");
            fclose(fptr);
            return;
        }
    } while (!found);


    do
    {
        found = 0;
        for (i = 0; i < memberCount; i++)
        {
            if (strcmp(id, mem[i].memberId) == 0 && strcmp(password, mem[i].password) == 0)
            {
                found = 1;
                printf("\n\n=============================================================================================================================\n");
                printf("\t\t\t\t\t\t\tMEMBER DETAILS\n");
                printf("=============================================================================================================================\n");
                printf("No.    %-10s \t\t%-20s \t%-13s \t\t\t%-11s \t\t%-5s\n", "User ID", "User Name", "IC Number", "Contact Number", "Gender");
                printf("-----------------------------------------------------------------------------------------------------------------------------\n");
                printf("\n%d.     %-10s \t\t %-20s \t %-13s \t\t\t %-11s \t\t %-5s\n", no, mem[i].memberId, mem[i].name, mem[i].iC, mem[i].contactNo, mem[i].gender);
                

                printf("\n===============================\n");
                printf("\tEDIT DETAILS\n");
                printf("===============================\n");
                printf("| 1. | Edit Name\n");
                printf("| 2. | Edit IC Number\n");
                printf("| 3. | Edit Contact Number\n");
                printf("| 4. | Edit Gender\n");
                printf("| 0. | Exit\n");
                printf("===============================\n");
                printf("Choose the detail you want to edit : ");
                if (scanf("%d", &choice) != 1 || choice < 0 || choice > 4)
                {
                    while (getchar() != '\n');
                    printf("\n\nInvalid Input! Please Enter Again. ");
                    continue;
                }

                switch (choice)
                {
                case 1: do {
                    printf("Please enter your new name: ");
                    rewind(stdin);
                    gets(newName);
                    strcpy(mem[i].name, newName);
                    if (strcmp(newName, "exit") == 0)
                    {
                        fclose(fptr);
                        system("cls");
                        return;
                    }
                } while (mem[i].name[0] == '\0');
                break;
                case 2: printf("Please enter your new IC Number: ");
                    rewind(stdin);
                    gets(newIc);
                    strcpy(mem[i].iC, newIc);;
                    break;
                case 3: printf("Please enter your new Contact Number: ");
                    rewind(stdin);
                    gets(newContact);
                    strcpy(mem[i].contactNo, newContact);;
                    break;
                case 4: do {
                    printf("Please enter your new Gender (M = Male / F = Female): ");
                    rewind(stdin);
                    gets(newGender);
                    if (toupper(newGender[0]) != 'M' && toupper(newGender[0]) != 'F')
                    {
                        printf("Invalid gender! Please enter again. \n");
                    }
                } while (toupper(newGender[0]) != 'M' && toupper(newGender[0]) != 'F');
                strcpy(mem[i].gender, newGender);
                break;
                case 0:;
                    break;
                default:
                    printf("Invalid choice. Please enter again. \n");
                    break;
                }
            }
        }
        if (!found)
            printf("\nMember ID '%s' not found. ", id);
        printf("\nAny more record to modify ? (Y = Yes / N = No) : ");
        rewind(stdin);
        scanf("%c", &cont);
    } while (toupper(cont) == 'Y');
    fptr = fopen("member.bin", "wb");
    rewind(fptr);
    fwrite(mem, sizeof(Member), memberCount, fptr);
    fclose(fptr);

}

void displayMember()
{
    Member mem;
    int count = 0, no = 1;

    FILE* fptr;

    fptr = fopen("member.bin", "rb");

    if (!fptr)
    {
        printf("File Open Error!!");
        exit(-1);
    }

    printf("=============================================================================================================================\n");
    printf("\t\t\t\t\t\t\tMEMBER DETAILS\n");
    printf("=============================================================================================================================\n");
    printf("No.    %-10s \t\t%-20s \t%-13s \t\t\t%-11s \t\t%-5s\n", "User ID", "User Name", "IC Number", "Contact Number", "Gender");
    printf("===   %-10s \t%-20s \t%-13s \t%-11s \t%-5s\n", "==================", "==================", "=========================", "====================", "==========");


    while (fread(&mem, sizeof(Member), 1, fptr))
    {
        printf("\n%d.     %-10s \t\t %-20s \t %-13s \t\t\t %-11s \t\t %-5s\n", no, mem.memberId, mem.name, mem.iC, mem.contactNo, mem.gender);
        count++;
        no++;
    }

    printf("\n\n\t\t\t\t\t\t< %d member(s) listed >\n", count);

    fclose(fptr);

}

void deleteMember()
{
    Member mem;
    int found = 0, memberCount = 0, i = 0, error = 0;
    char id[20], cont[1], password[16];

    FILE* fptr, * tempFile;

    fptr = fopen("member.bin", "rb+");
    tempFile = fopen("temp.bin", "wb");

    if (!fptr || !tempFile)
    {
        printf("File Open Error!!");
        exit(-1);
    }

    while (fread(&mem, sizeof(Member), 1, fptr) == 1) {
        memberCount++;
    }

    printf("Please enter member Id to delete : ");
    scanf("%s", id);

    do {
        printf("\nPlease enter your password : ");
        rewind(stdin);
        gets(password);
        found = 0;

        rewind(fptr);

        for (i = 0; i < memberCount; i++)
        {
            fread(&mem, sizeof(Member), 1, fptr);
            if (strcmp(id, mem.memberId) == 0 && strcmp(password, mem.password) == 0)
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("Invalid password. Please enter again. \n");
            error++;
        }
        if (error >= 3)
        {
            printf("\nToo many attempt. Exiting to menu. \n");
            fclose(fptr);
            fclose(tempFile);
            return;
        }
    } while (!found);

    rewind(fptr);

    while (fread(&mem, sizeof(Member), 1, fptr))
    {
        if (strcmp(id, mem.memberId) != 0)
        {
            fwrite(&mem, sizeof(Member), 1, tempFile);
        }
        else
        {
            found = 1;
        }
    }
    fclose(fptr);
    fclose(tempFile);

    if (!found)
    {
        printf("Member ID %s not found. ", id);
    }
    else
    {
        remove("member.bin");
        rename("temp.bin", "member.bin");
        printf("Member with ID %s has been deleted. ", id);
    }
}

void reportMember()
{
    Member mem;
    int total = 0, male = 0, female = 0;

    FILE* fptr;

    fptr = fopen("member.bin", "rb");

    if (!fptr) {
        printf("File Open Error!!");
        exit(-1);
    }

    while (fread(&mem, sizeof(Member), 1, fptr))
    {
        total++;
        if (toupper(mem.gender[0]) == 'M')
        {
            male++;
        }
        else if (toupper(mem.gender[0]) == 'F')
        {
            female++;
        }
    }
    fclose(fptr);

    printf("\n\n==================================================\n");
    printf("\t\tMEMBERSHIP STATISTICS\n");
    printf("==================================================\n");
    printf("Total Members: %d\n", total);
    printf("Male Members: %d\n", male);
    printf("Female Members: %d\n", female);
}

void member()
{
    int choice;


    do {
        printf("\n\n=============================\n");
        printf("\t    MEMBER\n");
        printf("=============================\n");
        printf("| 1. | Add Member\n");
        printf("-----------------------------\n");
        printf("| 2. | Display Member\n");
        printf("-----------------------------\n");
        printf("| 3. | Search Member\n");
        printf("-----------------------------\n");
        printf("| 4. | Edit Member\n");
        printf("-----------------------------\n");
        printf("| 5. | Delete Member\n");
        printf("-----------------------------\n");
        printf("| 6. | Statistic Report\n");
        printf("-----------------------------\n");
        printf("| 0. | Exit\n");
        printf("-----------------------------\n");
        printf("Enter Your Choice (1 / 2 / 3 / 4 / 0) >> ");

        if (scanf("%d", &choice) != 1 || choice < 0 || choice > 6) {
            while (getchar() != '\n');
            printf("\n\nInvalid Input! Please Enter Again. ");
            continue;
        }

        system("cls");
        switch (choice)
        {
        case 1:addMember();
            break;
        case 2: displayMember();
            break;
        case 3:searchMember();
            break;
        case 4:modifyMember();
            break;
        case 5:deleteMember();
            break;
        case 6: reportMember();
            break;
        case 0:;
            break;
        default:
            printf("Invalid Input! Please Enter Again. \n");
            break;
        }

    } while (choice != 0);

}

//member end


void displayscheMenu() {

    printf("-----------------------------\n");
    printf("|  TRAIN SCHEDULING MODULE  |\n");
    printf("-----------------------------\n\n");

    printf("---------------------------------\n");
    printf("|1. Add Record                  |\n");
    printf("---------------------------------\n");
    printf("|2. Search Record               |\n");
    printf("---------------------------------\n");
    printf("|3. Modify Record               |\n");
    printf("---------------------------------\n");
    printf("|4. Display All Records         |\n");
    printf("---------------------------------\n");
    printf("|5. Delete Record               |\n");
    printf("---------------------------------\n");
    printf("|6. Report Available Seats      |\n");
    printf("---------------------------------\n");
    printf("|7. Exit                        |\n");
    printf("---------------------------------\n\n");

}

void addscheRecord(FILE* fp) {
    TrainSchedule train;
    char ans;

    fp = fopen("trains.txt", "a");
    if (!fp) {
        printf("File open error!!\n");
        exit(-1);
    }

    fseek(fp, 0, SEEK_SET);

    printf("-------------------\n");
    printf("|   Add Record    |\n");
    printf("-------------------\n\n");

    printf("Enter Train ID > ");
    scanf("%s", train.trainID);
    printf("-------------------------------\n");
    printf("Enter Departure Station > ");
    scanf("%s", train.departureStation);
    printf("-------------------------------\n");
    printf("Enter Arrival Station > ");
    scanf("%s", train.arrivalStation);
    printf("-------------------------------\n");
    printf("Enter Departure Time > ");
    scanf("%s", train.departureTime);
    printf("-------------------------------\n");
    printf("Enter Arrival Time > ");
    scanf("%s", train.arrivalTime);
    printf("-------------------------------\n");
    printf("Enter Available Seats > ");
    scanf("%d", &train.availableSeats);
    printf("-------------------------------\n");
    fprintf(fp, "%s %s %s %s %s %d\n", train.trainID, train.departureStation,
        train.arrivalStation, train.departureTime, train.arrivalTime,
        train.availableSeats);

    fclose(fp);
    printf("\nRecord added successfully...\n\n");


    printf("Do you want to go back to the menu (Y/N)? \n");
    printf("Y = Yes / N = No(Exit program) > ");
    scanf(" %c", &ans);

    system("cls");

    if (ans == 'Y' || ans == 'y') {
        return;
    }
    else {
        printf("Exiting program.\n");
        exit(-1);
    }

    system("pause");
}

void searchscheRecord(FILE* fp) {
    TrainSchedule train;
    char key[10];
    char ans;


    printf("-----------------------\n");
    printf("|    Search Record    |\n");
    printf("-----------------------\n\n");

    printf("Enter Train ID to search > ");
    scanf("%s", key);
    printf("-----------------------------------------");

    int found = 0;

    while (fscanf(fp, "%s %s %s %s %s %d", train.trainID, train.departureStation,
        train.arrivalStation, train.departureTime, train.arrivalTime,
        &train.availableSeats) != EOF) {
        if (strcmp(train.trainID, key) == 0) {
            printf("\n\nTrain ID: %s\nDeparture Station: %s\nArrival Station: %s\n"
                "Departure Time: %s\nArrival Time: %s\nAvailable Seats: %d\n\n",
                train.trainID, train.departureStation, train.arrivalStation,
                train.departureTime, train.arrivalTime, train.availableSeats);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("\n\nTrain ID not found....\n\n");
    }
    printf("-----------------------------------------\n\n");

    printf("Do you want to go back to the menu (Y/N)? \n");
    printf("Y = Yes / N = No(Exit program) > ");
    scanf(" %c", &ans);

    system("cls");

    if (ans == 'Y' || ans == 'y') {
        return;
    }
    else {
        printf("Exiting program.\n");
        exit(-1);
    }

    system("pause");
}

void modifyscheRecord(FILE* fp) {
    TrainSchedule train;
    char key[10];
    char ans;

    printf("-----------------------\n");
    printf("|    Modify Record    |\n");
    printf("-----------------------\n\n");

    printf("| Enter Train ID to modify > ");
    scanf("%s", key);
    printf("------------------------------------\n");

    long int currentPosition = ftell(fp);
    int found = 0;

    while (fscanf(fp, "%s %s %s %s %s %d", train.trainID, train.departureStation,
        train.arrivalStation, train.departureTime, train.arrivalTime,
        &train.availableSeats) != EOF) {

        if (strcmp(train.trainID, key) == 0) {
            printf("| Enter new Departure Station > ");
            scanf("%s", train.departureStation);
            printf("------------------------------------\n");

            printf("| Enter new Arrival Station > ");
            scanf("%s", train.arrivalStation);
            printf("------------------------------------\n");

            printf("| Enter new Departure Time > ");
            scanf("%s", train.departureTime);
            printf("------------------------------------\n");

            printf("| Enter new Arrival Time > ");
            scanf("%s", train.arrivalTime);
            printf("------------------------------------\n");

            printf("| Enter new Available Seats > ");
            scanf("%d", &train.availableSeats);
            printf("------------------------------------\n");

            fseek(fp, currentPosition, SEEK_SET);
            fprintf(fp, "%s %s %s %s %s %d\n", train.trainID, train.departureStation,
                train.arrivalStation, train.departureTime, train.arrivalTime,
                train.availableSeats);

            found = 1;
            break;
        }
        currentPosition = ftell(fp);
    }

    if (found) {
        printf("Record modified successfully...\n");
    }
    else {
        printf("Train ID not found...\n");
    }

    printf("-----------------------------------------\n\n");

    printf("Do you want to go back to the menu (Y/N)? \n");
    printf("Y = Yes / N = No(Exit program) > ");
    scanf(" %c", &ans);

    system("cls");

    if (ans == 'Y' || ans == 'y') {
        return;
    }
    else {
        printf("Exiting program.\n");
        exit(-1);
    }

    system("pause");
}

void displayscheAllRecord(FILE* fp) {
    TrainSchedule train;

    char ans;

    printf("--------------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-18s | %-15s | %-13s | %-6s |\n", "Train ID", "Departure Station", "Arrival Station", "Departure Time", "Arrival Time", "Available Seats");
    printf("--------------------------------------------------------------------------------------------------------------\n");

    while (fscanf(fp, "%s %s %s %s %s %d\n", train.trainID, train.departureStation,
        train.arrivalStation, train.departureTime, train.arrivalTime,
        &train.availableSeats) != EOF) {
        printf("| %-10s | %-20s | %-18s | %-15s | %-13s | %-6d          |\n", train.trainID, train.departureStation,
            train.arrivalStation, train.departureTime, train.arrivalTime,
            train.availableSeats);
    }

    printf("--------------------------------------------------------------------------------------------------------------\n");

    printf("Do you want to go back to the menu (Y/N)? \n");
    printf("Y = Yes / N = No(Exit program) > ");
    scanf(" %c", &ans);

    system("cls");

    if (ans == 'Y' || ans == 'y') {
        return;
    }
    else {
        printf("Exiting program.\n");
        exit(-1);
    }


   return(0);
}

void deletescheRecord(FILE* fp) {
    TrainSchedule train;
    char key[10];
    char ans;

    printf("-----------------------\n");
    printf("|    Delete Record    |\n");
    printf("-----------------------\n\n");

    printf("Enter Train ID to delete > ");
    scanf("%s", key);

    long int currentPosition = ftell(fp); // Get current file position
    FILE* temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        perror("Error creating temp file");
        exit(-1);
    }

    int found = 0;
    while (fscanf(fp, "%s %s %s %s %s %d", train.trainID, train.departureStation,
        train.arrivalStation, train.departureTime, train.arrivalTime,
        &train.availableSeats) != EOF) {
        if (strcmp(train.trainID, key) != 0) {
            fprintf(temp, "%s %s %s %s %s %d\n", train.trainID, train.departureStation,
                train.arrivalStation, train.departureTime, train.arrivalTime,
                train.availableSeats);
        }
        else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove("trains.txt");
    rename("temp.txt", "trains.txt");

    if (found) {
        printf("\n\nRecord deleted successfully...\n\n");
    }
    else {
        printf("\n\nTrain ID not found...\n");
    }

    printf("-----------------------------------------\n\n");
    printf("Do you want to go back to the menu (Y/N)? \n");
    printf("Y = Yes / N = No(Exit program) > ");
    scanf(" %c", &ans);

    system("cls");

    if (ans == 'Y' || ans == 'y') {
        return;
    }
    else {
        printf("Exiting program.\n");
        exit(-1);
    }


    return(0);
}

void reportAvailableSeats(FILE* fp) {
    TrainSchedule train;
    int totalSeats = 0, availableTrains = 0;
    char ans;

    printf("-------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-15s |\n", "Train ID", "Available Seats", "Total Seats");
    printf("-------------------------------------------------------\n");

    while (fscanf(fp, "%s %s %s %s %s %d", train.trainID, train.departureStation,
        train.arrivalStation, train.departureTime, train.arrivalTime,
        &train.availableSeats) != EOF) {
        totalSeats += train.availableSeats;
        availableTrains++;
        printf("| %-10s | %-20d | %-15d |\n", train.trainID, train.availableSeats, train.availableSeats);
    }

    printf("-------------------------------------------------------\n\n");
    printf("Total Available Seats across all trains > %d\n", totalSeats);
    printf("Number of Trains > %d\n", availableTrains);

    printf("-----------------------------------------\n\n");
    printf("Do you want to go back to the menu (Y/N)? \n");
    printf("Y = Yes / N = No(Exit program) > ");
    scanf(" %c", &ans);
    system("cls");


    if (ans == 'Y' || ans == 'y') {
        return;
    }
    else {
        printf("Exiting program.\n");
        exit(-1);
    }


    system("pause");
}

void shaduleModule()
{
    FILE* fp;
    int choice;

    while (1)
    {
        displayscheMenu();
        printf("Enter your choice > ");
        if (scanf("%d", &choice) != 1 || choice < 0 || choice > 7) {
            // Clear the input buffer
            while (getchar() != '\n');
            system("cls");
            printf("Invalid Input! Please Enter Again.\n");

        }

        switch (choice) {
        case 1: fp = fopen("tranis.txt", "a");
            if (!fp) {
                printf("File open error!!\n");
                exit(-1);
            }
            system("cls");
            addscheRecord(fp);
            fclose(fp);
            return(0);

        case 2: fp = fopen("trains.txt", "r");
            if (!fp) {
                printf("File open error!!\n");
                exit(-1);
            }
            system("cls");
            searchscheRecord(fp);
            fclose(fp);
            return(0);

        case 3: fp = fopen("trains.txt", "r+");
            if (!fp) {
                printf("File open error!!\n");
                exit(-1);
            }
            system("cls");
            modifyscheRecord(fp);
            fclose(fp);
            return(0);

        case 4: fp = fopen("trains.txt", "r");
            if (!fp) {
                printf("File open error!!\n");
                exit(-1);
            }
            system("cls");
            displayscheAllRecord(fp);
            fclose(fp);
            return(0);

        case 5: fp = fopen("trains.txt", "r+");
            if (!fp) {
                printf("File open error!!\n");
                exit(-1);
            }
            system("cls");
            deletescheRecord(fp);
            fclose(fp);
            return(0);

        case 6: fp = fopen("trains.txt", "r");
            if (!fp) {
                printf("File open error!!\n");
                exit(-1);
            }
            system("cls");
            reportAvailableSeats(fp);
            fclose(fp);
            return(0);

        case 7: system("cls");
            return 0;
        default:
            printf("Invalid choice. Please try again...\n");
            return(0);
        }
    }

    return 0;
}

//train shedule end


void addBookingRecord() {
    struct TicketBooking ticket;
    char choice;

    do {
        system("cls");
        printf("=========================================================================================================\n\n");
        printf("                                                                                                     \n");
        printf("  _ _ _     _                      _          _____         _   _            _____       _     _     \n");
        printf("| | | |___| |___ ___ _____ ___   | |_ ___   | __  |___ ___| |_|_|___ ___   |     |___ _| |_ _| |___  \n");
        printf("| | | | -_| |  _| . |     | -_|  |  _| . |  | __ -| . | . | '_| |   | . |  | | | | . | . | | | | -_| \n");
        printf("|_____|___|_|___|___|_|_|_|___|  |_| |___|  |_____|___|___|_,_|_|_|_|_  |  |_|_|_|___|___|___|_|___| \n");
        printf("                                                                    |___|                            \n");
        printf("=========================================================================================================\n\n");
        printf("\nPlease enter information below:\n");
        printf("================================\n");
        printf("\tEnter Booking Id : ");
        scanf("%s", ticket.bookID);
        printf("\tEnter Member Id: ");
        scanf("%s", ticket.memberID);
        printf("\tEnter Train Id: ");
        scanf("%s", ticket.trainID);
        printf("\tEnter Booking date (DD/MM/YYYY): ");
        scanf("%s", ticket.bookDate);
        printf("\tEnter departure date (DD/MM/YYYY): ");
        scanf("%s", ticket.departureDate);
        printf("\tEnter Seat Number: ");
        scanf("%s", ticket.seatNum);
        printf("\tEnter Coach: ");
        scanf(" %c", &ticket.coach);
        printf("\tEnter Quantity: ");
        scanf("%d", &ticket.quantity);
        printf("\tEnter Payment Type: ");
        scanf("%s", ticket.paymentInfo.paymentType);
        printf("\tEnter Amount: ");
        scanf("%f", &ticket.paymentInfo.amount);
        printf("\tEnter Ticket Status: ");
        scanf("%s", ticket.ticketStatus);

        FILE* fp = fopen("ticketrecord.txt", "a");
        if (fp == NULL) {
            printf("Error opening file for writing.\n");
            return;
        }

        fprintf(fp, "%s %s %s %s %s %s %c %d %s %.2f %s\n", ticket.bookID, ticket.memberID, ticket.trainID,
            ticket.bookDate, ticket.departureDate, ticket.seatNum,
            ticket.coach, ticket.quantity, ticket.paymentInfo.paymentType,
            ticket.paymentInfo.amount, ticket.ticketStatus);

        fclose(fp);

        printf("Record added successfully.\n");


        do {
            printf("Any Other Record (Y/N)? ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            if (choice != 'Y' && choice != 'N') {
                printf("Invalid option. Please enter Y or N.\n");
            }
        } while (choice != 'Y' && choice != 'N');

    } while (choice == 'Y');
}

void searchBookingRecord() {
    char bookID[10];
    char choice;

    do {
        system("cls");

        printf("=========================================================================================================\n\n");
        printf("                                                                                                     \n");
        printf("  _ _ _     _                      _          _____         _   _            _____       _     _     \n");
        printf("| | | |___| |___ ___ _____ ___   | |_ ___   | __  |___ ___| |_|_|___ ___   |     |___ _| |_ _| |___  \n");
        printf("| | | | -_| |  _| . |     | -_|  |  _| . |  | __ -| . | . | '_| |   | . |  | | | | . | . | | | | -_| \n");
        printf("|_____|___|_|___|___|_|_|_|___|  |_| |___|  |_____|___|___|_,_|_|_|_|_  |  |_|_|_|___|___|___|_|___| \n");
        printf("                                                                    |___|                            \n");
        printf("=========================================================================================================\n\n");
        printf("\nSearch Record\n");
        printf("\tEnter Booking Id to search: ");
        scanf("%s", bookID);

        struct TicketBooking ticket;

        FILE* fp = fopen("ticketrecord.txt", "r");
        if (fp == NULL) {
            printf("Error opening file for reading.\n");
            return;
        }

        int found = 0;
        while (fscanf(fp, "%s %s %s %s %s %s %c %d %s %f %s\n",
            ticket.bookID, ticket.memberID, ticket.trainID,
            ticket.bookDate, ticket.departureDate, ticket.seatNum,
            &ticket.coach, &ticket.quantity, ticket.paymentInfo.paymentType,
            &ticket.paymentInfo.amount, ticket.ticketStatus) != EOF) {
            if (strcmp(ticket.bookID, bookID) == 0) {
                printf("Record Found:\n");
                printf("=========================================\n");
                printf("Booking ID:       %s\n", ticket.bookID);
                printf("Member ID:        %s\n", ticket.memberID);
                printf("Train ID:         %s\n", ticket.trainID);
                printf("Booking Date:     %s\n", ticket.bookDate);
                printf("Departure Date:   %s\n", ticket.departureDate);
                printf("Seat Number:      %s\n", ticket.seatNum);
                printf("Coach:            %c\n", ticket.coach);
                printf("Quantity:         %d\n", ticket.quantity);
                printf("Payment Type:     %s\n", ticket.paymentInfo.paymentType);
                printf("Amount:           %.2f\n", ticket.paymentInfo.amount);
                printf("Ticket Status:    %s\n", ticket.ticketStatus);
                printf("=========================================\n");
                found = 1;
                break;
            }
        }
        if (!found)
            printf("Record not found.\n");
        fclose(fp);

        do {
            printf("Search Other Record (Y/N)? ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            if (choice != 'Y' && choice != 'N') {
                printf("Invalid option. Please enter Y or N.\n");
            }
        } while (choice != 'Y' && choice != 'N');

    } while (choice == 'Y');

    if (choice == 'N') {
        return;
    }
}

void modifyBookingRecord() {
    char bookingID[10];
    char choice;

    do {
        system("cls");

        printf("=========================================================================================================\n\n");
        printf("                                                                                                     \n");
        printf("  _ _ _     _                      _          _____         _   _            _____       _     _     \n");
        printf("| | | |___| |___ ___ _____ ___   | |_ ___   | __  |___ ___| |_|_|___ ___   |     |___ _| |_ _| |___  \n");
        printf("| | | | -_| |  _| . |     | -_|  |  _| . |  | __ -| . | . | '_| |   | . |  | | | | . | . | | | | -_| \n");
        printf("|_____|___|_|___|___|_|_|_|___|  |_| |___|  |_____|___|___|_,_|_|_|_|_  |  |_|_|_|___|___|___|_|___| \n");
        printf("                                                                    |___|                            \n");
        printf("=========================================================================================================\n\n");
        printf("Enter Booking ID to modify: ");
        scanf("%s", bookingID);

        struct TicketBooking ticket;
        FILE* fp = fopen("ticketrecord.txt", "r+");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return;
        }

        int found = 0;
        long int pos = 0;
        while (fscanf(fp, "%s %s %s %s %s %s %c %d %s %f %s\n",
            ticket.bookID, ticket.memberID, ticket.trainID,
            ticket.bookDate, ticket.departureDate, ticket.seatNum,
            &ticket.coach, &ticket.quantity, ticket.paymentInfo.paymentType,
            &ticket.paymentInfo.amount, ticket.ticketStatus) != EOF) {
            if (strcmp(ticket.bookID, bookingID) == 0) {
                printf("Enter new Booking Date (DD/MM/YYYY): ");
                scanf("%s", ticket.bookDate);
                printf("Enter new Departure Date (DD/MM/YYYY): ");
                scanf("%s", ticket.departureDate);
                printf("Enter new Seat Number: ");
                scanf("%s", ticket.seatNum);
                printf("Enter new Coach: ");
                scanf(" %c", &ticket.coach);
                printf("Enter new Quantity: ");
                scanf("%d", &ticket.quantity);
                printf("Enter new Payment Type: ");
                scanf("%s", ticket.paymentInfo.paymentType);
                printf("Enter new Amount: ");
                scanf("%f", &ticket.paymentInfo.amount);
                printf("Enter new Ticket Status: ");
                scanf("%s", ticket.ticketStatus);

                fseek(fp, pos, SEEK_SET);
                fprintf(fp, "%s %s %s %s %s %s %c %d %s %.2f %s\n",
                    ticket.bookID, ticket.memberID, ticket.trainID,
                    ticket.bookDate, ticket.departureDate, ticket.seatNum,
                    ticket.coach, ticket.quantity, ticket.paymentInfo.paymentType,
                    ticket.paymentInfo.amount, ticket.ticketStatus);
                printf("Record modified successfully.\n");
                found = 1;
                break;
            }
            pos = ftell(fp);
        }

        if (!found)
            printf("Record not found.\n");
        fclose(fp);


        do {
            printf("Modify Other Record (Y/N)? ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            if (choice != 'Y' && choice != 'N') {
                printf("Invalid option. Please enter Y or N.\n");
            }
        } while (choice != 'Y' && choice != 'N');

    } while (choice == 'Y');
}

void deleteBookingRecord() {
    char bookingID[10];
    char choice;

    do {
        system("cls");

        printf("Enter Booking ID to delete: ");
        scanf("%s", bookingID);

        struct TicketBooking ticket;
        FILE* fp = fopen("ticketrecord.txt", "r");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return;
        }
        FILE* temp = fopen("temp.txt", "w");
        if (temp == NULL) {
            printf("Error creating temporary file.\n");
            fclose(fp);
            return;
        }

        int found = 0;
        while (fscanf(fp, "%s %s %s %s %s %s %c %d %s %f %s\n",
            ticket.bookID, ticket.memberID, ticket.trainID,
            ticket.bookDate, ticket.departureDate, ticket.seatNum,
            &ticket.coach, &ticket.quantity, ticket.paymentInfo.paymentType,
            &ticket.paymentInfo.amount, ticket.ticketStatus) != EOF) {
            if (strcmp(ticket.bookID, bookingID) == 0) {
                printf("Record deleted successfully.\n");
                found = 1;
                continue;
            }
            fprintf(temp, "%s %s %s %s %s %s %c %d %s %.2f %s\n",
                ticket.bookID, ticket.memberID, ticket.trainID,
                ticket.bookDate, ticket.departureDate, ticket.seatNum,
                ticket.coach, ticket.quantity, ticket.paymentInfo.paymentType,
                ticket.paymentInfo.amount, ticket.ticketStatus);
        }
        fclose(fp);
        fclose(temp);
        remove("ticketrecord.txt");
        rename("temp.txt", "ticketrecord.txt");

        if (!found)
            printf("Record not found.\n");


        do {
            printf("Delete Other Record (Y/N)? ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            if (choice != 'Y' && choice != 'N') {
                printf("Invalid option. Please enter Y or N.\n");
            }
        } while (choice != 'Y' && choice != 'N');

    } while (choice == 'Y');
}

void displayBookingRecord() {
    char choice;

    do {
        system("cls");

        struct TicketBooking ticket;
        FILE* fp = fopen("ticketrecord.txt", "r");
        if (fp == NULL) {
            printf("Error opening file.\n");
            return;
        }

        printf("=========================================================================================================\n\n");
        printf("                                                                                                     \n");
        printf("  _ _ _     _                      _          _____         _   _            _____       _     _     \n");
        printf("| | | |___| |___ ___ _____ ___   | |_ ___   | __  |___ ___| |_|_|___ ___   |     |___ _| |_ _| |___  \n");
        printf("| | | | -_| |  _| . |     | -_|  |  _| . |  | __ -| . | . | '_| |   | . |  | | | | . | . | | | | -_| \n");
        printf("|_____|___|_|___|___|_|_|_|___|  |_| |___|  |_____|___|___|_,_|_|_|_|_  |  |_|_|_|___|___|___|_|___| \n");
        printf("                                                                    |___|                            \n");
        printf("=========================================================================================================\n\n");
        printf("All Records:\n");
        printf("=======================================================================================================================================================\n");
        printf("| %-10s | %-10s | %-10s | %-12s | %-15s | %-10s | %-6s | %-8s | %-15s | %-8s | %-12s |\n",
            "Booking ID", "Member ID", "Train ID", "Booking Date", "Departure Date", "Seat Num", "Coach", "Quantity", "Payment Type", "Amount", "Ticket Status");
        printf("=======================================================================================================================================================\n");
        while (fscanf(fp, "%s %s %s %s %s %s %c %d %s %f %s\n",
            ticket.bookID, ticket.memberID, ticket.trainID,
            ticket.bookDate, ticket.departureDate, ticket.seatNum,
            &ticket.coach, &ticket.quantity, ticket.paymentInfo.paymentType,
            &ticket.paymentInfo.amount, ticket.ticketStatus) != EOF) {
            printf("| %-10s | %-10s | %-10s | %-12s | %-15s | %-10s | %-6c | %-8d | %-15s | %-8.2f | %-12s |\n",
                ticket.bookID, ticket.memberID, ticket.trainID,
                ticket.bookDate, ticket.departureDate, ticket.seatNum,
                ticket.coach, ticket.quantity, ticket.paymentInfo.paymentType,
                ticket.paymentInfo.amount, ticket.ticketStatus);
        }
        printf("=======================================================================================================================================================\n");
        fclose(fp);


        do {
            printf("Display Other Records (Y/N)? ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            if (choice != 'Y' && choice != 'N') {
                printf("Invalid option. Please enter Y or N.\n");
            }
        } while (choice != 'Y' && choice != 'N');

    } while (choice == 'Y');
}

void generateBookingReport() {
    struct TicketBooking ticket;
    char choice;

    system("cls");

    FILE* fp = fopen("ticketrecord.txt", "r");
    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    int totalRecords = 0;
    float totalAmount = 0;

    printf("=========================================================================================================\n\n");
    printf("                                                                                                     \n");
    printf("  _ _ _     _                      _          _____         _   _            _____       _     _     \n");
    printf("| | | |___| |___ ___ _____ ___   | |_ ___   | __  |___ ___| |_|_|___ ___   |     |___ _| |_ _| |___  \n");
    printf("| | | | -_| |  _| . |     | -_|  |  _| . |  | __ -| . | . | '_| |   | . |  | | | | . | . | | | | -_| \n");
    printf("|_____|___|_|___|___|_|_|_|___|  |_| |___|  |_____|___|___|_,_|_|_|_|_  |  |_|_|_|___|___|___|_|___| \n");
    printf("                                                                    |___|                            \n");
    printf("=========================================================================================================\n\n\n\n");
    printf("=======================================================================================================================================================\n");
    printf("                                                            Ticket Booking Report\n");
    printf("=======================================================================================================================================================\n");


    printf("%-15s %-15s %-15s %-15s %-15s %-10s %-7s %-10s %-15s %-10s %-15s\n",
        "Booking ID", "Member ID", "Train ID", "Booking Date", "Departure Date",
        "Seat Num", "Coach", "Quantity", "Payment Type", "Amount", "Ticket Status");
    printf("=======================================================================================================================================================\n");

    while (fscanf(fp, "%s %s %s %s %s %s %c %d %s %f %s\n",
        ticket.bookID, ticket.memberID, ticket.trainID,
        ticket.bookDate, ticket.departureDate, ticket.seatNum,
        &ticket.coach, &ticket.quantity, ticket.paymentInfo.paymentType,
        &ticket.paymentInfo.amount, ticket.ticketStatus) != EOF) {
        printf("%-15s %-15s %-15s %-15s %-15s %-10s %-7c %-10d %-15s %-10.2f %-15s\n",
            ticket.bookID, ticket.memberID, ticket.trainID,
            ticket.bookDate, ticket.departureDate, ticket.seatNum,
            ticket.coach, ticket.quantity, ticket.paymentInfo.paymentType,
            ticket.paymentInfo.amount, ticket.ticketStatus);
        totalRecords++;
        totalAmount += ticket.paymentInfo.amount;
    }
    fclose(fp);

    printf("=======================================================================================================================================================\n");
    printf("Total Records: %d\n", totalRecords);
    printf("Total Amount: %.2f\n", totalAmount);
    printf("=======================================================================================================================================================\n");

    do {
        printf("Press 'b' to go back to the main menu: ");
        scanf(" %c", &choice);
        choice = toupper(choice);
        if (choice != 'B') {
            printf("Invalid input. Please press 'b' to go back to the main menu.\n");
        }
    } while (choice != 'B');
}

void ticketBookModule()
{
    char choice;

    do {
        system("cls");
        printf("=========================================================================================================\n\n");
        printf("                                                                                                     \n");
        printf("  _ _ _     _                      _          _____         _   _            _____       _     _     \n");
        printf("| | | |___| |___ ___ _____ ___   | |_ ___   | __  |___ ___| |_|_|___ ___   |     |___ _| |_ _| |___  \n");
        printf("| | | | -_| |  _| . |     | -_|  |  _| . |  | __ -| . | . | '_| |   | . |  | | | | . | . | | | | -_| \n");
        printf("|_____|___|_|___|___|_|_|_|___|  |_| |___|  |_____|___|___|_,_|_|_|_|_  |  |_|_|_|___|___|___|_|___| \n");
        printf("                                                                    |___|                            \n");
        printf("=========================================================================================================\n\n");
        printf("Please select one of the services\n");
        printf("================================\n");
        printf("\t1. Add Record\n\n");
        printf("\t2. Search Record\n\n");
        printf("\t3. Modify Record\n\n");
        printf("\t4. Delete Record\n\n");
        printf("\t5. Display Record\n\n");
        printf("\t6. Generate Report\n\n");
        printf("\t7. Exit\n");

        printf("\nEnter your choice : ");
        scanf(" %c", &choice);

        switch (choice) {
        case '1':
            addBookingRecord();
            break;
        case '2':
            searchBookingRecord();
            break;
        case '3':
            modifyBookingRecord();
            break;
        case '4':
            deleteBookingRecord();
            break;
        case '5':
            displayBookingRecord();
            break;
        case '6':
            generateBookingReport();
            break;
        case '7':
            system("cls");
            return 0;
        default:
            printf("\tInvalid choice. Please enter again.\n");
            break;
        }
    } while (choice != '7');

    return 0;
}

//ticket booking end


void main()
{

	int choice;


	do {
		printf("\n\n#######  ######      #      #####  #    #     #######  #####   #####  #   #  #####  #######  #####  #    #   #####      #######   #     #  #######  #######  #####  #     #\n");
		printf("   #     #    #     # #       #    ##   #        #       #    #       #  #   #         #       #    ##   #  #          #           #   #  #            #     #      ##   ##\n");
		printf("   #     #####     #   #      #    # #  #        #       #    #       # #    ###       #       #    # #  #  #  ###      #######     # #    #######     #     ###    # # # #\n");
		printf("   #     #   #    #######     #    #  # #        #       #    #       #  #   #         #       #    #  # #  #    #             #     #            #    #     #      #  #  #\n");
		printf("   #     #    #  #       #  #####  #   ##        #     #####   #####  #   #  #####     #     #####  #   ##   ####       #######      #     #######     #     #####  #     #\n");
		printf("\n\n=============================\n");
		printf("\t    MENU\n");
		printf("=============================\n");
		printf("| 1. | Staff Information\n");
		printf("-----------------------------\n");
		printf("| 2. | Member Information\n");
		printf("-----------------------------\n");
		printf("| 3. | Train Sheduling Module\n");
		printf("-----------------------------\n");
		printf("| 4. | Ticket Booking\n");
		printf("-----------------------------\n");
		printf("| 0. | Exit\n");
		printf("-----------------------------\n");
		printf("Enter Your Choice (1 / 2 / 3 / 4 / 0) >> ");


		if (scanf("%d", &choice) != 1 || choice < 0 || choice > 4) {
			while (getchar() != '\n');
			printf("\n\nInvalid Input! Please Enter Again. ");
			continue;
		}
		system("cls");
		switch (choice)
		{
		case 1:staffModule();
			break;
		case 2: member();
			break;
		case 3: shaduleModule();
			break;
		case 4: ticketBookModule();
			break;
		case 0:
			printf("Exiting The program. Goodbye!\n\n");
			break;
		default:
			printf("Invalid Input! Please Enter Again. \n");
			break;
		}
	} while (choice != 0);
	return 0;
}
