#include "datatype.h"
#include "funtion.h"
int numberUser;
struct User user[100];
void loadFileUser(){
	FILE *file;
	file=fopen("user.bin", "rb");
	if(file==NULL){
		printf("Khong mo duoc file.\n");
		return;
	}
	numberUser=fread(&user,sizeof(struct User),100,file);
	fclose(file);
}

int checkDuplicate(struct User user1) {
    for (int i = 0; i < numberUser; i++) {
        if (strcmp(user[i].id, user1.id) == 0) {
            return 1;
        }
        if (strcmp(user[i].phone, user1.phone) == 0) {
            return 1;
        }
        
        if (strcmp(user[i].email, user1.email) == 0) {
            return 1;
        }
    }
    return 0;
}
int checkPhone(struct User user1){
	for(int i=0; i<strlen(user1.phone); i++){
    	if(user1.phone[i] < '0' || user1.phone[i] > '9'){
    		return 1;
		}
	}
	return 0;
}

int checkLength(char *input, int maxLength) {
    if (strlen(input) == 0) {
        return 1;
    }
    if (strlen(input) > maxLength) {
        return 2;
    }
    return 0;
}

int checkDate(int d, int m, int y){
	if (d > 0 && d <= 31 && m > 0 && m <= 12 && y > 1000 && y <= 2024) {
        if ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30) {
            return 1;
        } 
		else if (m == 2) {
            if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) {
                if (d > 29) {
                    return 1;
                } else {
                    return 0;
                }
            } else {
                if (d > 28) {
                    return 1;
                } else {
                    return 0;
                }
            }
        } else {
            return 0;;
        }
    } else {
        return 1;
    }
}

void addUser() {
    if (numberUser > 100) {
        printf("Danh sach day\n");
        return;
    }

    struct User user1;

    //id
    do{
    	do {
    		printf("\n*** Them nguoi dung moi ***\n\n");
	        printf("\nNhap ID (toi da 9 ky tu): ");
	        fgets(user1.id, sizeof(user1.id), stdin);
	        user1.id[strcspn(user1.id, "\n")] = 0;
	        if(checkLength(user1.id, 9)==1){
	        	printf("Thong tin khong duoc trong!\n");
			}
			if(checkLength(user1.id, 9)==2){
				printf("Thong tin vuot qua do dai toi da!\n");
			}
	    } while (checkLength(user1.id, 9)!=0);
	    if(checkDuplicate(user1)==1){
			printf("ID da ton tai!\n");
		}
	}while (checkDuplicate(user1)!=0);
    

    //ten
    do {
        printf("\nNhap ho va ten (toi da 49 ky tu): ");
        fgets(user1.name, sizeof(user1.name), stdin);
        user1.name[strcspn(user1.name, "\n")] = 0;
        for (int i = 0; i < strlen(user1.name); i++) {
            user1.name[i] = tolower(user1.name[i]);
        }
        if(checkLength(user1.name, 49)==1){
	        	printf("Thong tin khong duoc trong!\n");
			}
			if(checkLength(user1.name, 49)==2){
				printf("Thong tin vuot qua do dai toi da!\n");
			}
    } while (checkLength(user1.name, 49)!=0);

    // date
    do{
	    printf("\nNhap ngay thang nam sinh (dd mm yyyy): ");
	    scanf("%d %d %d", &user1.dateOfBirth.day, &user1.dateOfBirth.month, &user1.dateOfBirth.year);
	    getchar();
	    if(checkDate(user1.dateOfBirth.day, user1.dateOfBirth.month, user1.dateOfBirth.year)==1){
	    	printf("Ngay thang nam khong hop le!\n");
		}
	}while(checkDate(user1.dateOfBirth.day, user1.dateOfBirth.month, user1.dateOfBirth.year)!=0);
    

    // gtinh
    printf("Nhap gioi tinh (0: Nu, 1: Nam): ");
    scanf("%d", &user1.gender);
    getchar();
    
    // khoa
    user1.status=0;

    // sdt
    do{
    	do{
    		do {
		        printf("\nNhap so dien thoai (toi da 14 ky tu): ");
		        fgets(user1.phone, sizeof(user1.phone), stdin);
		        user1.phone[strcspn(user1.phone, "\n")] = 0;
		        if(checkLength(user1.phone, 14)==1){
		        	printf("Thong tin khong duoc trong!\n");
				}
				if(checkLength(user1.phone, 14)==2){
					printf("Thong tin vuot qua do dai toi da!\n");
				}
		    } while (checkLength(user1.phone, 14)!=0);
		    if(checkPhone(user1)==1){
		    	printf("Chi nhap so\n");
			}
		}while(checkPhone(user1)!=0);
		if(checkDuplicate(user1)==1){
			printf("So dien thoai da ton tai!\n");
		}
	}while(checkDuplicate(user1)!=0);
    
    //pass
    strcpy(user1.password, user1.phone);

    // email
    do{
    	do {
	        printf("\nNhap Email (toi da 49 ky tu): ");
	        fgets(user1.email, sizeof(user1.email), stdin);
	        user1.email[strcspn(user1.email, "\n")] = 0;
	        if (strstr(user1.email, "@gmail.com") == NULL) {
            	strcat(user1.email, "@gmail.com");
			}
	        if(checkLength(user1.email, 49)==1){
	        	printf("Thong tin khong duoc trong!\n");
			}
			if(checkLength(user1.email, 49)==2){
				printf("Thong tin vuot qua do dai toi da!\n");
			}
	    } while (checkLength(user1.email, 49)!=0);
	    if(checkDuplicate(user1)==1){
			printf("Email da ton tai!\n");
		}
	}while (checkDuplicate(user1)!=0);

    // save
    user[numberUser] = user1;
    numberUser++;
    printf("Them nguoi dung thanh cong\n");
    saveFileUser();
}

void saveFileUser(){
	FILE *file = fopen("user.bin", "wb");
	fwrite(user,sizeof(struct User),numberUser,file);
	fclose(file);
}

void displayUser() {
	if(numberUser==0){
		printf("Danh sach nguoi dung trong\n");
		return;
	}
	
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
    printf("| STT   | ID    | Ten              | Ngay sinh  | Gioi tinh | So dien thoai | Email                    | Trang thai |\n");
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
	for(int i=0; i<numberUser; i++){
		 printf("| %-5d | %-5s | %-16s | %02d/%02d/%04d | %-9s | %-13s | %-24s | %-10s |\n",
               i+1,user[i].id, user[i].name,
               user[i].dateOfBirth.day, user[i].dateOfBirth.month, user[i].dateOfBirth.year,
               user[i].gender ? "Nam" : "Nu",
               user[i].phone, user[i].email,
			   user[i].status ? "Lock" : "Open");
	}
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
}

// tim ten
void searchByName(char *sName, int len){
	FILE *file=fopen("user.bin", "rb");
	if (file == NULL) {
        printf("Khong the mo file!\n");
        return;
    }
    numberUser=fread(&user,sizeof(struct User),100,file);
    int count=0;
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
    printf("| STT   | ID    | Ten              | Ngay sinh  | Gioi tinh | So dien thoai | Email                    | Trang thai |\n");
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
	for(int j=0; j<len; j++){
		sName[j]=tolower(sName[j]);
	}
	for(int i=0; i<numberUser; i++){
		if(strstr(user[i].name,sName)!=NULL){
			count=1;
			printf("| %-5d | %-5s | %-16s | %02d/%02d/%04d | %-9s | %-13s | %-24s | %-10s |\n",
               i+1,user[i].id, user[i].name,
               user[i].dateOfBirth.day, user[i].dateOfBirth.month, user[i].dateOfBirth.year,
               user[i].gender ? "Nam" : "Nu",
               user[i].phone, user[i].email,
			   user[i].status ? "Lock" : "Open");
		}
	}
	if(count==0){
		printf("|                                    Khong tim thay nguoi dung voi ten da nhap.                                     |\n");
	}
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
	fclose(file);
}

//tim id
void searchById(char *sId, int len){
	FILE *file=fopen("user.bin", "rb");
	if (file == NULL) {
        printf("Khong the mo file!\n");
        return;
    }
    numberUser=fread(&user,sizeof(struct User),100,file);
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
    printf("| STT   | ID    | Ten              | Ngay sinh  | Gioi tinh | So dien thoai | Email                    | Trang thai |\n");
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
	
	for(int i=0; i<numberUser; i++){
		if(strcmp(user[i].id,sId)==0){
			printf("| %-5d | %-5s | %-16s | %02d/%02d/%04d | %-9s | %-13s | %-24s | %-10s |\n",
               i+1,user[i].id, user[i].name,
               user[i].dateOfBirth.day, user[i].dateOfBirth.month, user[i].dateOfBirth.year,
               user[i].gender ? "Nam" : "Nu",
               user[i].phone, user[i].email,
			   user[i].status ? "Lock" : "Open");
			printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
			fclose(file);
			return;
		}
	}
	printf("|                                    Khong tim thay nguoi dung voi Id da nhap.                                      |\n");
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
	fclose(file);
}

//khoa
void lock() {
    char sId[10];
    printf("\n*** Khoa/Mo Khoa Nguoi Dung ***\n\n");
    printf("Nhap ID: ");
    fgets(sId, 10, stdin);
    sId[strcspn(sId, "\n")] = 0;

    int choose;
    for (int i = 0; i < numberUser; i++) {
        if (strcmp(user[i].id, sId) == 0) {
            printf("Tai khoan nguoi dung '%s' hien dang %s\n", user[i].id, user[i].status ? "Khoa" : "Mo khoa");
			
            if (user[i].status == false) {
                printf("Xac nhan khoa?\n [0] No\t [1] Yes\n Lua chon: ");
                scanf("%d", &choose);
                getchar();
                if (choose == 1) {
                    user[i].status = true;
                    printf("Khoa thanh cong!\n");
                    saveFileUser();
                    return;
                }else if(choose == 0) {
                	return;
				}else{
					printf("Khong hop le!\n");
					return;
				}
            }
            else if (user[i].status == true) {
                printf("Xac nhan mo khoa?\n [0] No\t [1] Yes\n Lua chon: ");
                scanf("%d", &choose);
                getchar();
                if (choose == 1) {
                    user[i].status = false;
                    printf("Mo khoa thanh cong!\n");
                    saveFileUser();
                    return;
                }else if(choose == 0) {
                	return;
				}else{
					printf("Khong hop le!\n");
					return;
				}
            }
        }
    }
    printf("Khong tim thay nguoi dung voi ID da nhap!\n");
}

//sx xuoi
void down(){
	for (int i = 0; i < numberUser - 1; i++) {
        for (int j = i + 1; j < numberUser; j++) {
            char *nameA = strrchr(user[i].name, ' ');//lay dia chi kt ' '
            char *nameB = strrchr(user[j].name, ' ');
            //lay ky tu dau tien cua ten 
            nameA = (nameA != NULL) ? nameA + 1 : user[i].name;
            nameB = (nameB != NULL) ? nameB + 1 : user[j].name;

            if (strcmp(nameA, nameB) > 0) {
                struct User temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }
    printf("Danh sach da sap xep tu tren xuong (A-Z)!\n");
    displayUser();
}

//sx nguoc
void up(){
	for (int i = 0; i < numberUser - 1; i++) {
        for (int j = i + 1; j < numberUser; j++) {
            char *nameA = strrchr(user[i].name, ' ');
            char *nameB = strrchr(user[j].name, ' ');

            nameA = (nameA != NULL) ? nameA + 1 : user[i].name;
            nameB = (nameB != NULL) ? nameB + 1 : user[j].name;

            if (strcmp(nameA, nameB) < 0) {
                struct User temp = user[i];
                user[i] = user[j];
                user[j] = temp;
            }
        }
    }
    printf("Danh sach da sap xep tu duoi len (Z-A)!\n");
    displayUser();
}



void signUpAdmin() {
    FILE *file = fopen("admin.bin", "wb");
    if (file == NULL) {
        printf("Loi mo file.\n");
        return;
    }

    struct Admin admin1;

    do {
        printf("\nTao Email (toi da 49 ky tu): ");
        fgets(admin1.email, sizeof(admin1.email), stdin);
        admin1.email[strcspn(admin1.email, "\n")] = 0;
        
        if (strstr(admin1.email, "@gmail.com") == NULL) {
            strcat(admin1.email, "@gmail.com");
        }

        if (checkLength(admin1.email, 49) == 1) {
            printf("Email khong duoc trong!\n");
        } else if (checkLength(admin1.email, 49) == 2) {
            printf("Email vuot qua do dai toi da!\n");
        }
    } while (checkLength(admin1.email, 49) != 0);

    do {
        printf("\nTao Mat khau (toi da 49 ky tu): ");
        fgets(admin1.password, sizeof(admin1.password), stdin);
        admin1.password[strcspn(admin1.password, "\n")] = 0;

        if (checkLength(admin1.password, 49) == 1) {
            printf("Mat khau khong duoc trong!\n");
        } else if (checkLength(admin1.password, 49) == 2) {
            printf("Mat khau vuot qua do dai toi da!\n");
        }
    } while (checkLength(admin1.password, 49) != 0);

    fwrite(&admin1, sizeof(struct Admin), 1, file);
    fclose(file);

    printf("\nDang ky thanh cong!\n");
}

void loadFileAdmin(int *flag) {
    FILE *file;
    struct Admin admin;
    char inputEmail[50], inputPassword[50];
    int choose;

    file = fopen("admin.bin", "rb");
    if (file == NULL) {
        printf("Ban chua co tai khoan. Xac nhan dang ky?\n [0] No\t [1] Yes: ");
        scanf("%d", &choose);
        getchar();
        if (choose == 1) {
            signUpAdmin();
            *flag=1;
        } else if (choose == 0) {
            *flag=2;
        } else {
            printf("Lua chon khong hop le!\n");
            *flag=1;
        }
        return;
    }

    fread(&admin, sizeof(struct Admin), 1, file);
    fclose(file);

	printf("\n*** Dang nhap Admin ***\n\n");
    while (1) {
        
        printf("Nhap Email(-@gmail.com): ");
        fgets(inputEmail, sizeof(inputEmail), stdin);
        inputEmail[strcspn(inputEmail, "\n")] = 0;

        printf("Nhap Mat khau: ");
        fgets(inputPassword, sizeof(inputPassword), stdin);
        inputPassword[strcspn(inputPassword, "\n")] = 0;

        if (strcmp(inputEmail, admin.email) == 0 && strcmp(inputPassword, admin.password) == 0) {
            printf("\nDang nhap thanh cong!\n");
            *flag=0;
            break;
        } else {
            printf("\nEmail hoac mat khau sai. Vui long nhap lai!\n");
        }
    }
}

//dang nhap user
int indexChange;
void loginUser(int *flag) {
    char inputID[10], inputPassword[15];
    int found = 0;

    printf("\n*** Dang nhap nguoi dung ***\n\n");
    printf("Nhap ID: ");
    fgets(inputID, sizeof(inputID), stdin);
    inputID[strcspn(inputID, "\n")] = 0;

    for (int i = 0; i < numberUser; i++) {
        if (strcmp(user[i].id, inputID) == 0) {
            found = 1;

            if (user[i].status==1) {
                printf("Tai khoan cua ban da bi khoa.\n");
                *flag=2;
                return;
            }

            printf("Nhap mat khau (Mat khau khoi tao la So dien thoai): ");
            fgets(inputPassword, sizeof(inputPassword), stdin);
            inputPassword[strcspn(inputPassword, "\n")] = 0;

            if (strcmp(user[i].password, inputPassword) == 0) {
                printf("Dang nhap thanh cong!\nXin chao %s.\n", user[i].name);
                indexChange=i;
                *flag=0;
            } else {
                printf("Mat khau khong dung. Vui long thu lai.\n");
                *flag=1;
            }
            return;
        }
    }

    if (found==0) {
        printf("Khong tim thay tai khoan voi ID da nhap.\n");
    }
    *flag=1;
}


//doi mk ad
void changeAdminPassword() {
    struct Admin admin;
    FILE *file = fopen("admin.bin", "rb");
    if (file == NULL) {
        printf("Khong tim thay tai khoan admin. Vui long tao tai khoan truoc!\n");
        return;
    }

    fread(&admin, sizeof(struct Admin), 1, file);
    fclose(file);

    char oldPassword[50];
    char newPassword[50];
    char confirmPassword[50];

    printf("\n*** Doi Mat Khau Admin ***\n\n");

    do {
        printf("Nhap mat khau cu: ");
        fgets(oldPassword, sizeof(oldPassword), stdin);
        oldPassword[strcspn(oldPassword, "\n")] = 0;

        if (strcmp(admin.password, oldPassword) != 0) {
            printf("Mat khau cu khong dung. Vui long thu lai.\n");
        }
    } while (strcmp(admin.password, oldPassword) != 0);

    do {
        printf("Nhap mat khau moi: ");
        fgets(newPassword, sizeof(newPassword), stdin);
        newPassword[strcspn(newPassword, "\n")] = 0;

        printf("Xac nhan mat khau moi: ");
        fgets(confirmPassword, sizeof(confirmPassword), stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = 0;

        if (strcmp(newPassword, confirmPassword) != 0) {
            printf("Mat khau xac nhan khong khop. Vui long thu lai.\n");
        } else if (strlen(newPassword) == 0) {
            printf("Mat khau moi khong duoc de trong. Vui long thu lai.\n");
        } else if (strlen(newPassword) > 49) {
            printf("Mat khau moi qua dai (toi da 49 ky tu). Vui long thu lai.\n");
        }
    } while (strcmp(newPassword, confirmPassword) != 0 || strlen(newPassword) == 0 || strlen(newPassword) > 49);

    strcpy(admin.password, newPassword);

    file = fopen("admin.bin", "wb");
    if (file != NULL) {
        fwrite(&admin, sizeof(struct Admin), 1, file);
        fclose(file);
        printf("Doi mat khau thanh cong!\n");
    } else {
        printf("Loi khi ghi file. Vui long thu lai!\n");
    }
}

//sua thong tin user
void editUser() {
    char inputID[10];
    int found = 0;

    printf("\n*** Chinh Sua Thong Tin Nguoi Dung ***\n");
    printf("Nhap ID nguoi dung muon chinh sua: ");
    fgets(inputID, sizeof(inputID), stdin);
    inputID[strcspn(inputID, "\n")] = 0;

    for (int i = 0; i < numberUser; i++) {
        if (strcmp(user[i].id, inputID) == 0) {
            found = 1;

            printf("\nThong tin hien tai cua nguoi dung '%s':\n", user[i].id);
            printf("Ho va ten: %s\n", user[i].name);
            printf("Ngay sinh: %02d/%02d/%04d\n", user[i].dateOfBirth.day, user[i].dateOfBirth.month, user[i].dateOfBirth.year);
            printf("Gioi tinh: %s\n", user[i].gender ? "Nam" : "Nu");
            printf("So dien thoai: %s\n", user[i].phone);
            printf("Email: %s\n", user[i].email);
            printf("Trang thai: %s\n", user[i].status ? "Mo khoa" : "Khoa");

            printf("\nNhap thong tin moi (bo trong neu khong muon thay doi):\n");

            printf("Ho va ten moi: ");
            fgets(user[i].name, sizeof(user[i].name), stdin);
            user[i].name[strcspn(user[i].name, "\n")] = 0;

            printf("Nhap ngay thang nam sinh (dd mm yyyy) moi (0 0 0 neu khong doi): ");
            int day, month, year;
            scanf("%d %d %d", &day, &month, &year);
            getchar();
            if (day != 0 || month != 0 || year != 0) {
                user[i].dateOfBirth.day = day;
                user[i].dateOfBirth.month = month;
                user[i].dateOfBirth.year = year;
            }

            printf("Nhap gioi tinh moi (0: Nu, 1: Nam, -1 neu khong doi): ");
            int gender;
            scanf("%d", &gender);
            getchar();
            if (gender == 0 || gender == 1) {
                user[i].gender = gender;
            }

            printf("Nhap so dien thoai moi: ");
            fgets(user[i].phone, sizeof(user[i].phone), stdin);
            user[i].phone[strcspn(user[i].phone, "\n")] = 0;

            printf("Nhap email moi: ");
            fgets(user[i].email, sizeof(user[i].email), stdin);
            user[i].email[strcspn(user[i].email, "\n")] = 0;
            if (strstr(user[i].email, "@gmail.com") == NULL) {
            	strcat(user[i].email, "@gmail.com");
			}
			
            saveFileUser();
            printf("\nChinh sua thong tin thanh cong!\n");
            return;
        }
    }

    if (found==0) {
        printf("Khong tim thay nguoi dung voi ID '%s'.\n", inputID);
    }
}




void changeUserPassword() {
    
    FILE *file = fopen("user.bin", "rb");
    if (file == NULL) {
        printf("Khong tim thay tai khoan nguoi dung. Vui long tao tai khoan truoc!\n");
        return;
    }

    fread(&user, sizeof(struct User), 1, file);
    fclose(file);

    char oldPassword[50];
    char newPassword[50];
    char confirmPassword[50];

    printf("\n*** Doi Mat Khau Nguoi Dung ***\n\n");

    do {
        printf("Nhap mat khau cu: ");
        fgets(oldPassword, sizeof(oldPassword), stdin);
        oldPassword[strcspn(oldPassword, "\n")] = 0;

        if (strcmp(user[indexChange].password, oldPassword) != 0) {
            printf("Mat khau cu khong dung. Vui long thu lai.\n");
        }
    } while (strcmp(user[indexChange].password, oldPassword) != 0);

    do {
        printf("Nhap mat khau moi: ");
        fgets(newPassword, sizeof(newPassword), stdin);
        newPassword[strcspn(newPassword, "\n")] = 0;

        printf("Xac nhan mat khau moi: ");
        fgets(confirmPassword, sizeof(confirmPassword), stdin);
        confirmPassword[strcspn(confirmPassword, "\n")] = 0;

        if (strcmp(newPassword, confirmPassword) != 0) {
            printf("Mat khau xac nhan khong khop. Vui long thu lai.\n");
        } else if (strlen(newPassword) == 0) {
            printf("Mat khau moi khong duoc de trong. Vui long thu lai.\n");
        } else if (strlen(newPassword) > 49) {
            printf("Mat khau moi qua dai (toi da 49 ky tu). Vui long thu lai.\n");
        }
    } while (strcmp(newPassword, confirmPassword) != 0 || strlen(newPassword) == 0 || strlen(newPassword) > 49);

    strcpy(user[indexChange].password, newPassword);

    file = fopen("user.bin", "wb");
    if (file != NULL) {
        fwrite(&user, sizeof(struct User), 1, file);
        fclose(file);
        printf("Doi mat khau thanh cong!\n");
    } else {
        printf("Loi khi ghi file. Vui long thu lai!\n");
    }
}

void displayAnUser() {
	
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
    printf("| STT   | ID    | Ten              | Ngay sinh  | Gioi tinh | So dien thoai | Email                    | Trang thai |\n");
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
	printf("| %-5d | %-5s | %-16s | %02d/%02d/%04d | %-9s | %-13s | %-24s | %-10s |\n",
	       indexChange+1,user[indexChange].id, user[indexChange].name,
	       user[indexChange].dateOfBirth.day, user[indexChange].dateOfBirth.month, user[indexChange].dateOfBirth.year,
	       user[indexChange].gender ? "Nam" : "Nu",
	       user[indexChange].phone, user[indexChange].email,
		   user[indexChange].status ? "Lock" : "Open");
    printf("+-------+--------------------------+------------+-----------+---------------+--------------------------+------------+\n");
}

