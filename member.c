//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#pragma warning(disable:4996)
//
//typedef struct {
//	char password[16];
//	char iC[12];
//	char contactNo[10];
//	char memberId[20], name[30], gender[1], bookingId;
//}Member;
//
//
//void addMember();
//void displayMember();
//void searchMember();
//void editMember();
//void reportMember();
//void deleteMember();
//void memberModule();
//
////add member
//void addMember()
//{
//	//declaration
//	Member mem;
//	char choice, confirmPassword[16];
//	//declaration end
//
//
//	//open file
//	FILE* fptr;
//
//	fptr = fopen("member.bin", "ab");
//	//file open end
//
//
//	//check file open
//	if (!fptr)
//	{
//		printf("File Open Error!!");
//		exit(-1);
//	}
//	//check file open end
//
//
//	//input
//	do {
//		printf("\n\nEnter 'exit' to return main menu anytime. ");
//		printf("\n===============================\n");
//		printf("\tADD MEMBER\n");
//		printf("===============================\n");
//		
//		do {
//			printf("Please enter your member ID : ");
//			rewind(stdin);
//			gets(mem.memberId);
//			if (strcmp(mem.memberId, "exit") == 0)
//			{
//				fclose(fptr);
//				return 0;
//			}
//		} while (mem.memberId[0] == '\0');
//
//		do {
//			printf("Please enter your name : ");
//			rewind(stdin);
//			gets(mem.name);
//			if (strcmp(mem.name, "exit") == 0)
//			{
//				fclose(fptr);
//				return 0;
//			}
//		} while (mem.name[0] == '\0');
//
//		do {
//			printf("Please enter your IC number : ");
//			rewind(stdin);
//			gets(mem.iC);
//			if (strcmp(mem.iC, "exit") == 0)
//			{
//				fclose(fptr);
//				return 0;
//			}
//		} while (strlen(mem.iC) == '\0');
//
//		do {
//			printf("Please enter your contact number : ");
//			rewind(stdin);
//			gets(mem.contactNo);
//			if (strcmp(mem.contactNo, "exit") == 0)
//			{
//				fclose(fptr);
//				return 0;
//			}
//		} while (strlen(mem.contactNo) == '\0');
//
//		do {
//			printf("Please enter your gender (M = Male / F = Female) : ");
//			rewind(stdin);
//			gets(mem.gender);
//			if (toupper(mem.gender[0]) != 'M' && toupper(mem.gender[0]) != 'F')
//			{
//				printf("Invalid gender! Please enter again. \n");
//			}
//			if (strcmp(mem.gender, "exit") == 0)
//			{
//				fclose(fptr);
//				return 0;
//			}
//		} while (toupper(mem.gender[0]) != 'M' && toupper(mem.gender[0]) != 'F');
//
//		do {
//			printf("Please enter password : ");
//			rewind(stdin);
//			gets(mem.password);
//			if (strcmp(mem.password, "exit") == 0)
//			{
//				fclose(fptr);
//				return 0;
//			}
//			if (strlen(mem.password) < 8 || (strlen(mem.password) > 16))
//			{
//				printf("Please enter the password between 8 to 16 digits.");
//				continue;
//			}
//			printf("Please confirm your password : ");
//			rewind(stdin);
//			gets(confirmPassword);
//			if (strcmp(mem.password, confirmPassword) != 0)
//			{
//				printf("Please enter your password correctly!\n");
//			}
//		} while (strcmp(mem.password, confirmPassword) != 0);
//
//		fwrite(&mem, sizeof(Member), 1, fptr);
//
//		printf("Aded successfully!\n");
//
//		printf("Add another member ? (Y = Yes / N = No) : ");
//		rewind(stdin);
//		scanf("%c", &choice);
//
//	} while (toupper(choice) == 'Y');
//	//input end
//
//	//close file
//	fclose(fptr);
//	//close file end
//}
////add member end
//
//
//
//
////display member
//void displayMember()
//{
//	//declaration
//	Member mem;
//	int count = 0;
//	//declaration end
//
//
//	//open file
//	FILE* fptr;
//
//	fptr = fopen("member.bin", "rb");
//	//file open end
//
//	//check file open
//	if (!fptr)
//	{
//		printf("File Open Error!!");
//		exit(-1);
//	}
//	//check file open end
//
//	while (fread(&mem, sizeof(Member), 1, fptr))
//	{
//		printf("%s %s %s %s %s %s\n", mem.memberId, mem.name, mem.iC, mem.contactNo, mem.iC, mem.gender);
//		count++;
//	}
//	printf("%d member(s) listed. \n", count);
//
//	fclose(fptr);
//}
//
//
//
//
//
//
//
//
////member module
//void memberModule()
//{
//	int choice;
//
//	do {
//		printf("\n\n=============================\n");
//		printf("\t    MEMBER\n");
//		printf("=============================\n");
//		printf("| 1. | Add Member\n");
//		printf("-----------------------------\n");
//		printf("| 2. | Display Member\n");
//		printf("-----------------------------\n");
//		printf("| 3. | Search Member\n");
//		printf("-----------------------------\n");
//		printf("| 4. | Edit Member\n");
//		printf("-----------------------------\n");
//		printf("| 0. | Exit\n");
//		printf("-----------------------------\n");
//		printf("Enter Your Choice (1 / 2 / 3 / 4 / 0) >> ");
//
//		if (scanf("%d", &choice) != 1 || choice < 0 || choice > 4) {
//			while (getchar() != '\n');
//			printf("\n\nInvalid Input! Please Enter Again. ");
//			continue;
//		}
//
//		system("cls");
//		switch (choice)
//		{
//		case 1:addMember();
//			break;
//		case 2: displayMember();
//			break;
//		case 3:;
//			break;
//		case 4:;
//			break;
//		case 0:;
//			break;
//		default:
//			printf("Invalid Input! Please Enter Again. \n");
//			break;
//		}
//
//	} while (choice != 0);
//
//}
////member module end
//
//void main()
//{
//	memberModule();
//
//
//	return 0;
//}