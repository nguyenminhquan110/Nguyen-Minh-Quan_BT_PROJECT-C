#include <stdio.h>
#include "datatype.h"
#include "funtion.h"

struct User user[100];
struct Admin admin;
int main() {
	loadFileUser();
	int choice, choice2, choice3, flag=0;
	char sName[50], sId[10];
	int len;
	do{
		printf("\n***Bank Managament System Using C***\n\n");
		printf("          VAI TRO CUA BAN\n");
		printf("       ====================\n");
		printf("       [1] Quan Ly\n");
		printf("       [2] Nguoi Dung\n");
		printf("       [3] Thoat He Thong\n");
		printf("       ====================\n");
		printf("       Lua Chon: ");
		scanf("%d", &choice);
		system("cls");
		getchar();
		switch(choice){
			
			case 1:
				do{
					loadFileAdmin(&flag);
				}while(flag==1);
				if(flag==2){
					break;
				}
				do{
					printf("\n         *** Quan Ly ***\n");
					printf("              MENU\n");
					printf("       ====================\n");
					printf("       [1] Them nguoi dung.\n");
					printf("       [2] Danh sach nguoi dung.\n");
					printf("       [3] Chi tiet nguoi dung.\n");
					printf("       [4] Khoa/Mo khoa nguoi dung.\n");
					printf("       [5] Chinh sua thong tin nguoi dung.\n");
					printf("       [6] Ve chung toi.\n");
					printf("       [7] Doi mat khau.\n");
					printf("       [0] Quay lai.\n");
					printf("       ====================\n");
					printf("       Lua chon: ");
					scanf("%d", &choice2);
					system("cls");
					getchar();
					
					switch(choice2){
						case 0:
							break;
						case 1:
							addUser();
							break;
						case 2:
							do{
								printf("\n*** Danh sach nguoi dung ***\n\n");
								printf("    ====================\n");
								printf("    [1] Sap xep xuoi theo ten.\n");
								printf("    [2] Sap xep nguoc theo ten.\n");
								printf("    [0] Quay lai.\n");
								printf("    ====================\n");
								printf("    Lua chon: ");
								scanf("%d", &choice3);
								system("cls");
								getchar();
								switch(choice3){
									case 1:
										down();
										break;
									case 2:
										up();
										break;
									default:
										printf("       Khong Hop Le!\n");
								}
							}while(choice3!=0);
							break;
						case 3:
							do{
								printf("\n*** Chi Tiet Nguoi Dung ***\n\n");
								printf("    ====================\n");
								printf("    [1] Tim kien theo ten.\n");
								printf("    [2] Tim kiem theo ID.\n");
								printf("    [0] Quay lai.\n");
								printf("    ====================\n");
								printf("    Lua chon: ");
								scanf("%d", &choice3);
								system("cls");
								getchar();
								switch(choice3){
									case 0:
										break;
									case 1:
										printf("Nhap Ten: ");
										fgets(sName,50,stdin);
										sName[strcspn(sName,"\n")]=0;
										len = strlen(sName);
										searchByName(sName,len);
										break;
									case 2:
										printf("Nhap ID: ");
										fgets(sId,10,stdin);
										sId[strcspn(sId,"\n")]=0;
										len = strlen(sId);
										searchById(sId,len);
										break;
									default:
										printf("       Khong Hop Le!\n");
								}
							}while(choice3!=0);
							break;
							
						case 4:
							lock();
							break;
						case 5:
							editUser();
							break;
						case 6:
							printf("The project of Ho Hieu Thanh.\n");
							break;
						case 7:
							changeAdminPassword();
							break;
					}
				}while(choice2!=0);
				break;
			case 2:
				do{
					loginUser(&flag);
				}while(flag==1);
				if(flag==2){
					break;
				}
				do{
					printf("\n*** Nguoi Dung ***\n");
					printf("       MENU\n");
					printf("  ===============\n");
					printf("  [1] Thong tin tai khoan.\n");
					printf("  [2] Doi mat khau.\n");
					printf("  [0] Quay lai.\n");
					printf("  ===============\n");
					printf("  Lua chon: ");
					scanf("%d", &choice2);
					system("cls");
					getchar();
					switch(choice2){
						case 0:
							break;
						case 1:
							displayAnUser();
							break;
						case 2:
							changeUserPassword();
							break;
						default:
							printf("  Khong Hop Le!\n");
					}
				}while(choice2!=0);
				break;
			case 3:
				printf("=========Cam On Va Hen Gap Lai===========");
				break;
			default:
				printf("       Khong Hop Le!\n");
		}
	}while(choice!=3);
	return 0;
}