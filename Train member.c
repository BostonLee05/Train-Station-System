//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <math.h>
//#include <ctype.h>
//#pragma warning(disable:4996)
//
//typedef struct {
//	char password[16];
//	char iC[12], contactNo[10];
//	char memberId[30], name[30], gender[1], bookingId[10];
//}Member;
//
//void addMember(); 
//void searchMember();
//void modifyMember();
//void displayMember();
//void deleteMember(); 
//void reportMember(); 
//void member();
//
//
//
//
//
////add member
//void addMember()
//{
//	system("cls");
//
//	Member mem;
//	char choice, confirmPassword[16];
//	int count = 0;
//
//
//	FILE* fptr;
//
//	fptr = fopen("member.bin", "ab+");
//
//	if (!fptr)
//	{
//		printf("File Open Error!!");
//		exit(-1);
//	}
//
//	fseek(fptr, 0, SEEK_END);
//	long fileSize = ftell(fptr);
//
//	if (fileSize != 0) 
//	{
//		fseek(fptr, -(long)sizeof(Member), SEEK_CUR);
//		fread(&mem, sizeof(Member), 1, fptr);
//
//		sscanf(mem.memberId, "M%04dd", &count);
//		count++;
//	}
//	else {
//		count = 1;
//	}
//
//	do {
//		printf("\n\nEnter 'exit' to return main menu anytime. ");
//		printf("\n===============================\n");
//		printf("\tADD MEMBER\n");
//		printf("===============================\n");
//
//		sprintf(mem.memberId, "M%04d", count);
//
//		do {
//			printf("Please enter your name : ");
//			rewind(stdin);
//			gets(mem.name);
//			if (strcmp(mem.name, "exit") == 0) 
//			{
//				fclose(fptr);
//				return;
//			}
//		} while (mem.name[0] == '\0');
//
//		do {
//			printf("Please enter your IC number (Without '-' ) : ");
//			rewind(stdin);
//			gets(mem.iC);
//			if (strcmp(mem.iC, "exit") == 0) 
//			{
//				fclose(fptr);
//				return;
//			}
//			if (mem.iC[0] == '\0')
//			{
//				printf("IC number cannot be empty!\n");
//				continue; 
//			}
//			/*if (strlen(mem.iC) != 12)
//			{
//				printf("IC number should be 12 digits long!\n");
//				continue;
//			}*/
//		} while (1);
//
//		do {
//			printf("Please enter your contact number : ");
//			rewind(stdin);
//			gets(mem.contactNo);
//			if (strcmp(mem.contactNo, "exit") == 0) 
//			{
//				fclose(fptr);
//				return;
//			}
//			if (mem.contactNo[0] == '\0')
//			{
//				printf("Contact number cannot be empty!\n");
//				continue;
//			}
//			/*if (strlen(mem.contactNo) != 10)
//			{
//				printf("Contact number should be 10 digits long!\n");
//				continue;
//			}*/
//		} while (1);
//
//		do {
//			printf("Please enter your gender (M = Male / F = Female): ");
//			rewind(stdin);
//			gets(mem.gender);
//			if (toupper(mem.gender[0]) != 'M' && toupper(mem.gender[0]) != 'F')
//			{
//				printf("Invalid gender! Please enter again. \n");
//			}
//			if (strcmp(mem.gender, "exit") == 0) 
//			{
//				fclose(fptr);
//				return;
//			}
//		} while (toupper(mem.gender[0]) != 'M' && toupper(mem.gender[0]) != 'F');
//
//		do {
//			printf("\nPassword : ");
//			scanf("%s", mem.password);
//			if (strcmp(mem.password, "exit") == 0) 
//			{
//				fclose(fptr);
//				return;
//			}
//			if (strlen(mem.password) < 8 || (strlen(mem.password) > 16))
//			{
//				printf("Please enter the password between 8 to 16 digits.");
//				continue;
//			}
//			printf("Confirm Password : ");
//			scanf("%s", confirmPassword);
//			if (strcmp(mem.password, confirmPassword) != 0)
//			{
//			printf("Please enter your password correctly!\n");
//			}
//		} while (strcmp(mem.password, confirmPassword) != 0);
//
//		fwrite(&mem, sizeof(Member), 1, fptr);
//
//		printf("Added successfully!\n");
//
//		printf("Add another member? (Y = Yes / N = No) : ");
//		rewind(stdin);
//		scanf("%c", &choice);
//		count++;
//	} while (toupper(choice) == 'Y');
//	fclose(fptr);
//}
////add member end
//
//
////search member
//void searchMember()
//{
//	Member mem;
//	int count = 0, i, no = 1;
//	char searchID[30];
//
//	FILE* fptr;
//
//	fptr = fopen("member.bin", "rb");
//
//	if (!fptr)
//	{
//		printf("File Open Error!!");
//		exit(-1);
//	}
//
//	printf("\n\nEnter 'exit' to return main menu anytime. ");
//	printf("\n=============================================================================================================================\n");
//	printf("\t\t\t\t\t\t\tSEARCH MEMBER\n");
//	printf("=============================================================================================================================\n");
//	printf("Enter member detail (ID, Name or IC Number) : ");
//	scanf("%s", &searchID);
//
//	if (strcmp(searchID, "exit") == 0) {
//		fclose(fptr);
//		return;
//	}
//
//	printf("\n\n=============================================================================================================================\n");
//	printf("\t\t\t\t\t\t\tMEMBER DETAILS\n");
//	printf("=============================================================================================================================\n");
//	printf("No.    %-10s \t\t%-20s \t%-13s \t\t\t%-11s \t\t%-5s\n", "User ID", "User Name", "IC Number", "Contact Number", "Gender");
//	printf("===   %-10s \t%-20s \t%-13s \t%-11s \t%-5s\n", "==================", "==================", "=========================", "====================", "==========");
//
//	while (fread(&mem, sizeof(Member), 1, fptr))
//	{
//		if (strcmp(searchID, mem.memberId) == 0 || strcmp(searchID, mem.name) == 0 || strcmp(searchID, mem.iC) == 0)
//		{
//			printf("\n%d.     %-10s \t\t %-20s \t %-13s \t\t\t %-11s \t\t %-5s\n", no, mem.memberId, mem.name, mem.iC, mem.contactNo, mem.gender);
//			count++;
//			no++;
//		}
//	}
//
//	if (count == 0)
//	{
//		printf("No member found.\n");
//	}
//	else
//	{
//		printf("\n\t\t\t< %d member(s) found.>\n\n", count);
//	}
//
//	fclose(fptr);
//}
////search member end
//
//
////modify 
//void modifyMember()
//{
//	Member mem[20];
//	char id[20], cont[1], newName[20], newIc[12], newContact[10], newGender[5], password[16], confirm, newPassword[16], confirmPassword[16];
//	int i = 0, error = 0, no = 1, found, memberCount, choice;
//
//
//	FILE* fptr;
//	fptr = fopen("member.bin", "rb");
//
//	while (fread(&mem[i], sizeof(Member), 1, fptr) == 1)
//		i++;
//	memberCount = i;
//	fclose(fptr);
//
//	printf("Please enter the member ID you want to modify : ");
//	rewind(stdin);
//	scanf("%s", id);
//	if (strcmp(id, "exit") == 0)
//	{
//		fclose(fptr);
//		return;
//	}
//	found = 0;
//	for (i = 0; i < memberCount; i++)
//	{
//		if (strcmp(id, mem[i].memberId) == 0)
//		{
//			found = 1;
//			break;
//		}
//	}
//
//	if (!found)
//	{
//		printf("\nMember ID '%s' does not exist.\n", id);
//		fclose(fptr);
//		return;
//	}
//
//
//	do {
//		printf("\nPlease enter your password : ");
//		rewind(stdin);
//		gets(password);
//		found = 0;
//
//		for (i = 0; i < memberCount; i++)
//		{
//			if (strcmp(id, mem[i].memberId) == 0 && strcmp(password, mem[i].password) == 0)
//			{
//				found = 1;
//				break;
//			}
//		}
//		if (!found)
//		{
//			printf("Invalid password. Please enter again. \n");
//		}
//	} while (!found);
//
//
//		do
//		{
//			found = 0;
//		for (i = 0; i < memberCount; i++)
//		{
//			if (strcmp(id, mem[i].memberId) == 0 && strcmp(password, mem[i].password) == 0)
//			{
//				found = 1;
//				printf("\n\n=============================================================================================================================\n");
//				printf("\t\t\t\t\t\t\tMEMBER DETAILS\n");
//				printf("=============================================================================================================================\n");
//				printf("No.    %-10s \t\t%-20s \t%-13s \t\t\t%-11s \t\t%-5s\n", "User ID", "User Name", "IC Number", "Contact Number", "Gender");
//				printf("-----------------------------------------------------------------------------------------------------------------------------\n");
//				printf("\n%d.     %-10s \t\t %-20s \t %-13s \t\t\t %-11s \t\t %-5s\n", no, mem[i].memberId, mem[i].name, mem[i].iC, mem[i].contactNo, mem[i].gender);
//				no++;
//
//				printf("\n===============================\n");
//				printf("\tEDIT DETAILS\n");
//				printf("===============================\n");
//				printf("| 1. | Edit Name\n");
//				printf("| 2. | Edit IC Number\n");
//				printf("| 3. | Edit Contact Number\n");
//				printf("| 4. | Edit Gender\n");
//				printf("| 0. | Exit\n");
//				printf("===============================\n");
//				printf("Choose the detail you want to edit : ");
//				if (scanf("%d", &choice) != 1 || choice < 0 || choice > 4)
//				{
//					while (getchar() != '\n');
//					printf("\n\nInvalid Input! Please Enter Again. ");
//					continue;
//				}
//
//				switch (choice)
//				{
//				case 1: do {
//					printf("Please enter your new name: ");
//					rewind(stdin);
//					gets(newName);
//					strcpy(mem[i].name, newName);
//					if (strcmp(newName, "exit") == 0)
//					{
//						fclose(fptr);
//						system("cls");
//						return;
//					}
//				} while (mem[i].name[0] == '\0');				
//					break;
//				case 2: printf("Please enter your new IC Number: ");
//					rewind(stdin);
//					gets(newIc);
//					strcpy(mem[i].iC, newIc);;
//					break;
//				case 3: printf("Please enter your new Contact Number: ");
//					rewind(stdin);
//					gets(newContact);
//					strcpy(mem[i].contactNo, newContact);;
//					break;
//				case 4: do {
//					printf("Please enter your new Gender (M = Male / F = Female): ");
//					rewind(stdin);
//					gets(newGender);
//					if (toupper(newGender[0]) != 'M' && toupper(newGender[0]) != 'F')
//					{
//						printf("Invalid gender! Please enter again. \n");
//					}
//				} while (toupper(newGender[0]) != 'M' && toupper(newGender[0]) != 'F');
//					strcpy(mem[i].gender, newGender);
//					break;
//				case 0:;
//					break;
//				default:
//					printf("Invalid choice. Please enter again. \n");
//					break;
//				}
//			}
//		}
//		if (!found)
//			printf("\nMember ID '%s' not found. ", id);
//		printf("\nAny more record to modify (Y=Yes)? ");
//		rewind(stdin);
//		scanf("%c", &cont);
//
//	}while (toupper(cont) == 'Y');
//	fptr = fopen("member.bin", "wb");
//	rewind(fptr);
//	fwrite(mem, sizeof(Member), memberCount, fptr);
//	fclose(fptr);
//
//}
////modify end
//
////display member
//void displayMember()
//{
//	Member mem;
//	int count = 0, no = 1;
//
//	FILE* fptr;
//
//	fptr = fopen("member.bin", "rb");
//
//	if (!fptr)
//	{
//		printf("File Open Error!!");
//		exit(-1);
//	}
//
//	printf("=============================================================================================================================\n");
//	printf("\t\t\t\t\t\t\tMEMBER DETAILS\n");
//	printf("=============================================================================================================================\n");
//	printf("No.    %-10s \t\t%-20s \t%-13s \t\t\t%-11s \t\t%-5s\n", "User ID", "User Name", "IC Number", "Contact Number", "Gender");
//	printf("===   %-10s \t%-20s \t%-13s \t%-11s \t%-5s\n", "==================", "==================", "=========================", "====================", "==========");
//
//
//	while (fread(&mem, sizeof(Member), 1, fptr))
//	{
//		printf("\n%d.     %-10s \t\t %-20s \t %-13s \t\t\t %-11s \t\t %-5s\n", no, mem.memberId, mem.name, mem.iC, mem.contactNo, mem.gender);
//		count++;
//		no++;
//	}
//
//	printf("\n\n\t\t\t\t\t\t< %d member(s) listed >\n", count);
//
//	fclose(fptr);
//
//}
////display member end
//
////delete
//void deleteMember()
//{
//	Member mem;
//	int found = 0;
//	char id[20];
//
//	FILE* fptr, * tempFile;
//
//	fptr = fopen("member.bin", "rb+");
//	tempFile = fopen("temp.bin", "wb");
//
//	if (!fptr || !tempFile)
//	{
//		printf("File Open Error!!");
//		exit(-1);
//	}
//
//	printf("Please enter member Id to delete : ");
//	scanf("%s", id);
//
//	while (fread(&mem, sizeof(Member), 1, fptr))
//	{
//		if (strcmp(id, mem.memberId) != 0)
//		{
//			fwrite(&mem, sizeof(Member), 1, tempFile);
//		}
//		else
//		{
//			found = 1;
//		}
//	}
//	fclose(fptr);
//	fclose(tempFile);
//
//	if (!found)
//	{
//		printf("Member ID %s not found. ", id);
//	}
//	else
//	{
//		remove("member.bin");
//		rename("temp.bin", "member.bin");
//		printf("Member with ID %s has been deleted. ", id);
//	}
//}
////delete member end
//
////report
//void reportMember()
//{
//	Member mem;
//	int total = 0, male = 0, female = 0;
//
//	FILE* fptr;
//
//	fptr = fopen("member.bin", "rb");
//
//	if (!fptr) {
//		printf("File Open Error!!");
//		exit(-1);
//	}
//
//	while (fread(&mem, sizeof(Member), 1, fptr))
//	{
//		total++;
//		if (toupper(mem.gender[0]) == 'M')
//		{
//			male++;
//		}
//		else if (toupper(mem.gender[0]) == 'F')
//		{
//			female++;
//		}
//	}
//	fclose(fptr);
//
//	printf("\n\n==================================================\n");
//	printf("\t\tMEMBERSHIP STATISTICS\n");
//	printf("==================================================\n");
//	printf("Total Members: %d\n", total);
//	printf("Male Members: %d\n", male);
//	printf("Female Members: %d\n", female);
//}
////report end
//
////whole member module
//void member()
//{
//	int choice;
//	
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
//		printf("| 5. | Delete Member\n");
//		printf("-----------------------------\n");
//		printf("| 6. | Report\n");
//		printf("-----------------------------\n");
//		printf("| 0. | Exit\n");
//		printf("-----------------------------\n");
//		printf("Enter Your Choice (1 / 2 / 3 / 4 / 0) >> ");
//
//		if (scanf("%d", &choice) != 1 || choice < 0 || choice > 6) {
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
//		case 3:searchMember();
//			break;
//		case 4:modifyMember();
//			break;
//		case 5:deleteMember();
//			break;
//		case 6: reportMember();
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
//
//
//
////Main Menu
//void mainMenu()
//{
//	
//	int choice;
//
//
//	do {
//		printf("\n\n#######  ######      #      #####  #    #     #######  #####   #####  #   #  #####  #######  #####  #    #   #####      #######   #     #  #######  #######  #####  #     #\n");
//		printf("   #     #    #     # #       #    ##   #        #       #    #       #  #   #         #       #    ##   #  #          #           #   #  #            #     #      ##   ##\n");
//		printf("   #     #####     #   #      #    # #  #        #       #    #       # #    ###       #       #    # #  #  #  ###      #######     # #    #######     #     ###    # # # #\n");
//		printf("   #     #   #    #######     #    #  # #        #       #    #       #  #   #         #       #    #  # #  #    #             #     #            #    #     #      #  #  #\n");
//		printf("   #     #    #  #       #  #####  #   ##        #     #####   #####  #   #  #####     #     #####  #   ##   ####       #######      #     #######     #     #####  #     #\n");
//		printf("\n\n=============================\n");
//		printf("\t    MENU\n");
//		printf("=============================\n");
//		printf("| 1. | Staff Information\n");
//		printf("-----------------------------\n");
//		printf("| 2. | Member Information\n");
//		printf("-----------------------------\n");
//		printf("| 3. | Train Sheduling Module\n");
//		printf("-----------------------------\n");
//		printf("| 4. | Ticket Booking\n");
//		printf("-----------------------------\n");
//		printf("| 0. | Exit\n");
//		printf("-----------------------------\n");
//		printf("Enter Your Choice (1 / 2 / 3 / 4 / 0) >> ");
//
//
//		if (scanf("%d", &choice) != 1 || choice < 0 || choice > 4) {
//			while (getchar() != '\n');
//			printf("\n\nInvalid Input! Please Enter Again. ");
//			continue;
//		}
//		system("cls");
//		switch (choice)
//		{
//		case 1:;
//			break;
//		case 2: member();
//			break;
//		case 3:;
//			break;
//		case 4:;
//			break;
//		case 0:
//			printf("Exiting The program. Goodbye!\n\n");
//			break;
//		default:
//			printf("Invalid Input! Please Enter Again. \n");
//			break;
//		}
//	} while (choice != 0);
//	return 0;
//}
////main menu end
//
//
////main program
//void main()
//{
//	//addMember();
//	//displayMember();
//	//searchMember();
//	//modifyMember();
//	//deleteMember();
//	//reportMember();
//	mainMenu();
//
//	return 0;
//}
////main program end 