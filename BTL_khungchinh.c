#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

#define YEAR 2018
#define MAX_NAME 40
#define MAX_DPMENT 30
#define MAX_DUTY 30
#define MAX_BIRTH 30
#define MAX_ADD 100
#define MAX_ELV 15
#define MAX_PHONE 11
#define MAX_MAIL 32
#define MAX_STAFF 1000

/**********************************************************************************************************************
 *                                  This program is used to manage a company's staff                                  *
 *                                             Copyright by Group 13                                                  *
 **********************************************************************************************************************/
 /*defination of staff's data contains Name, Department, Duty, Birthday, Address, Phone number, email, English degree*/
typedef struct stData
{
    int ID;
    char name[MAX_NAME];
    int sex;
    char dpment[MAX_DPMENT];
    char duty[MAX_DUTY];
    char birth[MAX_BIRTH];
    char add[MAX_ADD];
    char phNum[MAX_PHONE];
    char elv[MAX_ELV];
    char mail[MAX_MAIL];
    int stTime;
    int sal;
    struct stData *pNext;
} STAFF;

struct stData  *first = NULL, *last = NULL, *temp;

int gNumOfStaff = 0;
void dataEntry(STAFF* pStaff, int amount);
void instruction(void);
int checkChr(char str[]);
int checkPhoneNumb(char str[]);
int checkDate(char str[]);
int checkMail(char str[]);
int checkDegree(char str[], char str2[]);
int checkToFind(char str[], char str2[]);
int findSomeone();
int findStaff(STAFF* pStaff, int n);
int changeInformation(STAFF* pStaff, int n);
void deleteRecord();
void showAllList();
void mainMenu();
int main()
{
    STAFF* pStaff;
    char cpny[100];
    printf("Type your company's name: ");
    fflush(stdin);
    gets(cpny); 
    mainMenu();
    return 0;
}

void instruction(void)
{
    printf("\nEach staff's information contains:");
    printf("\n\t-ID");
    printf("\n\t-Name");
    printf("\n\t-Sex");
    printf("\n\t-Department");
    printf("\n\t-Duty");
    printf("\n\t-Date of birth");
    printf("\n\t-Address");
    printf("\n\t-Phone number");
    printf("\n\t-Email");
    printf("\n\t-English degree");
    printf("\n\t-Salary");
    printf("\n\nPlease type data in that order and base on these notice below:");
    printf("\nID is an integer number which is bigger than, smaller than 32000 and it isn't a coincidence to any other's one");
    printf("\nIn the fields: Name, Department, Duty");
    printf("\nThey are all strings of Latin letters and space, not contains numbers or special characters");
    printf("\nDepartment: Name of the Department which the staff is in");
    printf("\nDuty: The position of that staff in the Department");
    printf("\nSex: 1 equal to Male, 0 equal to Female");
    printf("\nDate of birth: dd/mm/yyyy. Eg: 26/04/1999, 04/12/1998, 22/07/1999");
    printf("\nAddress: Not exceed more than 200 characters");
    printf("\nPhone number: exceed 10 or 11 numbers, begin with 0. Eg: 01678216705, 096061596");
    printf("\nEmail: Accept Gmail, Yahoo and Hotmail, max and min value of the length are 32 and 16");
    printf("\nEnglish degree: Accept Vstep, Ielts, Toeic and Toefl. eg Toeic 450, Ielts 6.5");
    printf("\nSalary has to meet the regional minimum wage. (>= 176 USD per month)");
    printf("\nAll difference will be count as wrong!");
}

/*This function is used to check some fields that only include Latin letter such as Name, Duty,...*/
int checkChr(char str[])
{
    int i;
    for(i = 0; i < strlen(str); i++)
    {
        if(str[i] < 65 && str[i] != ' ' || (90 < str[i] && str[i] < 97) || str[i] > 122)
        {
            return 0;
        }
    }
    return 1;
}

/*This function is used to check if the phone number you type is right wrong in Vietnam's format*/
int checkPhoneNumb(char str[])
{
    int i;
    if(str[0] != '0')
    {
        return 0;
    }
    else if((str[1] == '1' && strlen(str) != 11) || (str[1] != '1' && strlen(str) != 10)) 
    {
        return 0;
    }
    else
    {
        for(i = 1; i < strlen(str); i++)
        {
            if((0 <= str[i] && str[i] <= 47) || 58 <= str[i])
            {
                return 0;
            }
        }
    }
    return 1;
}

/*This function is used to check if the date you type is right wrong format*/
int checkDate(char str[])
{
    int i;
    if(strlen(str) != 10)
    {
        return 0;
    }
    if((48 > str[2] && str[2] != '/') || str[2] > 57 || (48 < str[5] && str[5] != '/') || str[5] > 57)
    {
        return 0;
    }
    else
    {
        for(i = 0; i < 10; i++)
        {
            if((i != 2 && i != 5) && (47 >= str[i] || str[i] > 57))
            {
                return 0;
            }
        }
    }
    return 1;
}

/*This function is used to check if the email you type is right wrong format*/
int checkMail(char str[])
{
    int i, count = 0;
    if(16 > strlen(str) || strlen(str) > 32)
    {
        return 0;
    }
    if(str[strlen(str) - 4] != '.' || str[strlen(str) - 3] != 'c' || str[strlen(str) - 2] != 'o' ||
        str[strlen(str) - 1] != 'm')
    {
        return 0;
    }
    return 1;
}

int checkDegree(char str[], char str2[])
{
    int i;
    for(i = 0; i < 5; i++)
    {
        if(65 <=str[i] && str[i] <= 90)
        {
            if(str2[i] != str[i] && str2[i] != str[i] + 32)
            {
                return 0;
            }
            else if(97 <=str[i] && str[i] <= 122)
            {
                if(str2[i] != str[i] && str2[i] != str[i] - 32)
                {
                    return 0;
                }
            }
        }
    }
}


int checkToFind(char str[], char str2[])
{
    int i;
    if(strlen(str) != strlen(str2))
    {
        return 0;
    }
    else
    {
        for(i = 0; i < strlen(str); i++)
        {
            if(65 <=str[i] && str[i] <= 90)
            {
                if(str2[i] != str[i] && str2[i] != str[i] + 32)
                {
                    return 0;
                }
            }
            else if(97 <=str[i] && str[i] <= 122)
            {
                if(str2[i] != str[i] && str2[i] != str[i] - 32)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}

/*This function is used to view all staff's information*/
void showAllList()
{
    struct stData* p;
    int i = 1, back;
    system("cls");
    p = first;
    if(gNumOfStaff == 0)
    {
        printf("\nThere hasn't any record typed. You have to insert some record into the list.");
        getch();
        mainMenu();
    }
    else
    {
        while(p != NULL)
        {
            printf("\nStaff %d:", i);
            printf("\nID: %d", p->ID);
            printf("\nName: %s", p->name);
            printf("\nSex: ");
            if(p->sex == 1)
            {
                printf("Male");
            }
            else
            {
                printf("Female");
            }
            printf("\nDepartment: %s", p->dpment);
            printf("\nDuty: %s", p->duty);
            printf("\nDate of birth: %s", p->birth);
            printf("\nAddress: %s", p->add);
            printf("\nPhone number: %s", p->phNum);
            printf("\nEnglish level: %s", p->elv);
            printf("\nEmail: %s", p->mail);
            printf("\nStart working time: %d", p->stTime);
            printf("\nSalary: %d USD", p->sal);
            printf("\n\n");
            i++;
            p = p->pNext;
        }
    };
    printf("Type 1 if you want to show menu: ");
    scanf("%d", &back);
    if(back == 1)
    {
        mainMenu();
    }
}


/*Insert a record at the terminal*/
void insertRecord(struct stData* temp)
{
    int j, choice = 0, findOut = 1;
    char deg1[] = "Ielts", deg2[] = "Toeic", deg3[] = "Toefl", deg4[] = "Vstep";
    do
    {
        gNumOfStaff++;
        /*Supply a suitable memory space to store new's record information*/
        temp = (struct stData*)malloc(sizeof(STAFF));
        printf("\nType staff[%d]'s information:\n", gNumOfStaff);
        printf("\nID: ");
        scanf("%d", &temp->ID);
        /*Check the existence of the ID
        do
        {
            for(j = 0; j < gNumOfStaff - 1; j++)
            {
                if(temp->ID == pStaff[j]->ID)
                {
                    printf("\nThis ID is used for another staff\n");
                    printf("Type again: ");
                    printf("\nStaff[%d]'s information:", gNumOfStaff);
                    printf("\nID: ");
                    scanf("%d", &temp->ID);
                    findOut = 0;
                    break;  
                }
            }
        }
        while(findOut == 0);
        */
        printf("Name: ");
        fflush(stdin);
        gets(temp->name);
        while(!checkChr(temp->name))
        {
            printf("Invalid Name, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Name: ");
                fflush(stdin);
                gets(temp->name);
            }
            else if(choice == 0)
            {
                printf("Name: ");
                fflush(stdin);
                gets(temp->name);
            }
        }
        printf("Sex: ");
        scanf("%d", &temp->sex);
        while(temp->sex != 0 && temp->sex != 1)
        {
            printf("Invalid Sex, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Sex: ");
                scanf("%d", &temp->sex);
            }
            else if(choice == 0)
            {
                printf("Sex: ");
                scanf("%d", &temp->sex);
            }
        }
        printf("Department: ");
        fflush(stdin);
        gets(temp->dpment);
        while(!checkChr(temp->dpment))
        {
            printf("Invalid Department, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Department: ");
                fflush(stdin);
                gets(temp->dpment);
            }
            else if(choice == 0)
            {
                printf("Department: ");
                fflush(stdin);
                gets(temp->dpment);
            }
        }
        printf("Duty: ");
        fflush(stdin);
        gets(temp->duty);
        while(!checkChr(temp->duty))
        {
            printf("Invalid Duty, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Duty: ");
                fflush(stdin);
                gets(temp->duty);
            }
            else if(choice == 0)
            {
                printf("Duty: ");
                fflush(stdin);
                gets(temp->duty);
            }
        }
        printf("Date of birth: ");
        fflush(stdin);
        gets(temp->birth);
        while(!checkDate(temp->birth))
        {
            printf("Invalid Birthday, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Birthday: ");
                fflush(stdin);
                gets(temp->birth);
            }
            else if(choice == 0)
            {
                printf("Birthday: ");
                fflush(stdin);
                gets(temp->birth);
            }
        }
        printf("Address: ");
        fflush(stdin);
        gets(temp->add);
        printf("Phone number: ");
        fflush(stdin);
        gets(temp->phNum);
        while(!checkPhoneNumb(temp->phNum))
        {
            printf("Invalid Phone Number, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Phone: ");
                fflush(stdin);
                gets(temp->phNum);
            }
            else if(choice == 0)
            {
                printf("Phone: ");
                fflush(stdin);
                gets(temp->phNum);
            }
        }
        printf("Email: ");
        fflush(stdin);
        gets(temp->mail);
        while(!checkMail(temp->mail))
        {
            printf("Invalid name, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Email: ");
                fflush(stdin);
                gets(temp->mail);
            }
            else if(choice == 0)
            {
                printf("Email: ");
                fflush(stdin);
                gets(temp->mail);
            }
        }
        printf("English degree: ");
        fflush(stdin);
        gets(temp->elv);
        while(!checkDegree(temp->elv, deg1) && !checkDegree(temp->elv, deg2)
             && !checkDegree(temp->elv, deg3) && !checkDegree(temp->elv, deg4))
        {
            printf("Degree type denied, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("English degree: ");
                fflush(stdin);
                gets(temp->elv);
            }
            else if(choice == 0)
            {
                printf("English degree: ");
                fflush(stdin);
                gets(temp->elv);
            }

        }
        printf("Start working year: ");
        scanf("%d", &temp->stTime);
        while(YEAR - temp->stTime < 0)
        {
            printf("Now is 2018, type again!");
            printf("\nStart working year: ");
            scanf("%d", &temp->stTime);
        }
        printf("Salary: ");
        scanf("%d", &temp->sal);
        while(temp->sal < 176)
        {
            printf("Invalid Salary, type 1 to view instruction or type 0 to type again!");
            scanf("%d", &choice);
            if(choice == 1)
            {
                system("cls");
                instruction();
                printf("Type any key to continue typing\n");
                getch();
                system("cls");
                printf("Salary: ");
                scanf("%d", &temp->sal);
            }
            else if(choice == 0)
            {
                printf("Salary: ");
                fflush(stdin);
                scanf("%d", &temp->sal);
            }
        }
        /*Make temp locate at the end of the list*/
        temp->pNext = NULL;
        if(first == NULL)
        {
            first = temp;
        }
        else
        {
            last->pNext = temp;
        }
        last = temp;
        last->pNext = NULL;
        printf("\nType 1 to continue inserting other record or type 0 to come back the menu\n");
        scanf("%d", &choice);
    }
    while(choice == 1);
    mainMenu();
}


void deleteRecord()
{
    struct stData *search, *store, *mem;
    int find, i, findOut = 0, view;
    system("cls");
    printf("It's necessary to know exact the staff's ID, whose you want to remove from the list");
    printf("\nDo you want to have a look to the list once before find him or her?");
    printf("\nType 0 to skip or 1 to view: ");
    scanf("%d", view);
    if(view == 1)
    {
        system("cls");
        showAllList();
    }
    else
    {
        printf("\nEnter the necessary ID: ");
        scanf("%d", &find);
        search = first;
        if(search->ID == find)
        {
            store = first;
            first = first->pNext;
            free(store);
        }
        else
        {
            while(search != NULL)
            {
                store = search;
                if(search->ID == find)
                {
                    findOut = 1;
                    mem = search;
                    search = search->pNext;
                    store = search;
                    free(mem);
                    break;
                }
            }
        }
        if(findOut == 0)
        {
            printf("\nWe can't find any staff who has that ID");
            printf("\nDo you want to try other ID ?");
            printf("Type any key to get back menu");
     		getch();
        }    
        mainMenu();
    }
}

void mainMenu()
{
    int choice;
    system("cls");
    printf("\n+------+---------------+-----------+---+---+-----------+---------------+-----+------+");
    printf("\n+------+---------------+-----------[  MENU ]-----------+---------------+-----+------+");
    printf("\n+------+---------------+-----------+-------+-----------+---------------+-----+------+");
    printf("\n|------+---------------+--->>      1. Enter Data      <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      2. Show Data       <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      3. Find Staff      <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      4. Insert Record   <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      5. Delete Record   <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      6. Back To Menu    <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      7. Exit            <<---------------+-----+------|");
    printf("\n+------+---------------+-------------------------------+---------------+-----+------+");
    do
    {
        printf("\nYour choice is: ");
        scanf("%d", &choice);
        switch(choice)
        {
            /*
            case 1:
            {
                dataEntry();
                break;
            }
            */
            case 2:
            {
                showAllList();
                break;
            }
            case 3:
            {
                system("cls");
                findSomeone();
                break;
            }
            case 4:
            {
                system("cls");
                insertRecord(temp);
            }       
            case 5:
            {
                system("cls");
                deleteRecord();
                break;
            }
            case 6:
            {
                system("cls");
                mainMenu();
                break;
            }
            /*
            case 7:
            {
                free();
                exit(0);
                break;
            }
            */
            default:
            {
                system("cls");
                printf("\nWrong Selection!");
                printf("\nType any key to come back menu");
                getch();
                mainMenu();
                break;
            }
        }
    }
    while (1);
}

// Manh

int findSomeone()
{
    int temp;
    printf("Find someone by:\n");
    printf("1: ID\n2: Name\n3: English level\n4: Address");
    printf("Your choose: \n");
    scanf("%d", &temp);
    while(temp < 1 || temp > 4)
    {
        printf("Invalid, input again!\n");
        scanf("%d", & temp);
    }
}

//tìm nhân viên
int findStaff(STAFF* pStaff , int n)
{
    int ID, i, temp;
    int k = findSomeone();
    char nameCheck[100], dateOfBirth[100], englishLevel[100], address[100];
    switch (k)
    {
        case 1 :
        {
            printf("Input ID: \n");
            scanf("%d", &ID);
            for (i = 0; i < n; ++i)
            {
                if (ID == pStaff[i].ID)
                {
                    temp = 1;
                    break;
                }
            }

            if (temp == 1)
            {
                system("cls");
                printf("Staff's Information:\n");
                printf("ID: %d\n", pStaff[i].ID);
                printf("Name: %s\n", pStaff[i].name);
                printf("Department: %s\n", pStaff[i].dpment);
                printf("Sex: %s\n", pStaff[i].sex);
                printf("Date of birth: %s\n", pStaff[i].birth);
                printf("Address: %s\n", pStaff[i].add);
                printf("Phone number: %s\n", pStaff[i].phNum);
                printf("Work's time: %d years\n", pStaff[i].stTime);
                printf("Salary: %d USD\n", pStaff[i].sal);
                printf("English level: %s\n", pStaff[i].elv);
            }
            else
            {
                printf("ID you just inputed not exist!\n");
            }
            break;
        }
        case 2:
        {
            printf("Input name: \n");
            scanf("%s", nameCheck);
            for (i = 0; i < n; ++i)
            {
                system("cls");
                if (strcmp(nameCheck, pStaff[i].name) == 1)
                {
                    temp = 1;
                    printf("Staff's Information:\n");
                    printf("ID: %d\n", pStaff[i].ID);
                    printf("Name: %s\n", pStaff[i].name);
                    printf("Department: %s\n", pStaff[i].dpment);
                    printf("Sex: %s\n", pStaff[i].sex);
                    printf("Date of birth: %s\n", pStaff[i].birth);
                    printf("Address: %s\n", pStaff[i].add);
                    printf("Phone number: %s\n", pStaff[i].phNum);
                    printf("Work's time: %d years\n", pStaff[i].stTime);
                    printf("Salary: %d USD\n", pStaff[i].sal);
                    printf("English level: %s\n", pStaff[i].elv);
                }
            }

            if (temp != 1)
            {
                printf("Name you just inputed not exist!\n");
            }
            break;
        }
        case 4:
        {
            printf("Input English level: \n");
            scanf("%s", englishLevel);
            for (i = 0; i < n; ++i)
            {
                system("cls");
                if (strcmp(englishLevel, pStaff[i].elv) == 1)
                {
                    temp = 1;
                    printf("Staff's Information:\n");
                    printf("ID: %d\n", pStaff[i].ID);
                    printf("Name: %s\n", pStaff[i].name);
                    printf("Department: %s\n", pStaff[i].dpment);
                    printf("Sex: %s\n", pStaff[i].sex);
                    printf("Date of birth: %s\n", pStaff[i].birth);
                    printf("Address: %s\n", pStaff[i].add);
                    printf("Phone number: %s\n", pStaff[i].phNum);
                    printf("Work's time: %d years\n", pStaff[i].stTime);
                    printf("Salary: %d USD\n", pStaff[i].sal);
                    printf("English level: %s\n", pStaff[i].elv);
                }
            }

            if (temp != 1)
            {
                printf("Invalid\n");
            }
            break;
        }
        case 3:
        {
            printf("Input Address: \n");
            scanf("%s", address);
            for (i = 0; i < n; ++i)
            {
                system("cls");
                if (strcmp(address, pStaff[i].add) == 1)
                {
                    temp = 1;
                    printf("Staff's Information:\n");
                    printf("ID: %d\n", pStaff[i].ID);
                    printf("Name: %s\n", pStaff[i].name);
                    printf("Department: %s\n", pStaff[i].dpment);
                    printf("Sex: %s\n", pStaff[i].sex);
                    printf("Date of birth: %s\n", pStaff[i].birth);
                    printf("Address: %s\n", pStaff[i].add);
                    printf("Phone number: %s\n", pStaff[i].phNum);
                    printf("Work's time: %d years\n", pStaff[i].stTime);
                    printf("Salary: %d USD\n", pStaff[i].sal);
                    printf("English level: %s\n", pStaff[i].elv);
                }
            }

            if (temp != 1)
            {
                printf("Invalid\n");
            }
            break;
        }
    }
}

//chỉnh sửa thông tin nhân viên
int changeInformation(STAFF* pStaff, int n)
{
    //tạo các mảng lưu giá trị tạm thời của các biến cần thay đổi
    char tDepartment[100], tAdd[100];
    char tPhNum[100], tELv[100];
    int tSalary;
    //nhập ID nhân viên cần thay đổi
    //khởi tạo giá trị ID để so sánh
    int tID;
    //kiểm tra ID vừa nhập vào
    int i, check = 0, goOn, userChoose;
    //nếu ID tồn tại giá trị check = 1 bắt đầu thực hiện thau đổi thông tin
    //nếu ID đó không tồn tại bắt người dùng nhập lại cho đến khi đúng
    AS:while(check != 1)
    {
        printf("ID: \n");
        scanf("%d", &tID);
        for(i = 0; i < n; i++)
        {
            if (tID == pStaff[i].ID)
            {
                check = 1;
                break;
            }
        }
    }
    //bắt đầu việc thực hiên thay đổi thông tin
    TS:printf("You want to change: \n");
    printf("1: Department\n");
    printf("2: Address\n");
    printf("3: Phone number\n");
    printf("4: English level\n");
    printf("5: Salary\n");
    printf("6: Add staff\n");
    printf("7: Delete staff\n");
    printf("You chose:\n");

    scanf("%d", &userChoose);
    while(userChoose < 1 || userChoose > 7)
    {
        printf("Wrong funcion! input again!!\n");
        scanf("%d", &userChoose);
    }
    switch (userChoose)
    {
        case 1:
        {
            printf("Enter new department: \n");
            fflush(stdin);
            gets(tDepartment);
            strcpy(pStaff[i].dpment, tDepartment);
            printf("Change successfully!!!\n");
            printf("Do you want to go on change: \n");
            printf("1: Continue this staff\n");
            printf("2: Another staff\n");
            printf("3: No, finish change\n");
            scanf("%d", &goOn);
            if (goOn == 1)
            {
                goto TS;
            }
            else if (goOn == 2)
            {
                goto AS;
            }
            else
            {
                break;
            }
        }
        case 2:
        {
            printf("Enter new address: \n");
            fflush(stdin);
            gets(tAdd);
            strcpy(pStaff[i].add, tAdd);
            printf("Change successfully!!!\n");
            printf("Do you want to go on change: \n");
            printf("1: Continue this staff\n");
            printf("2: Another staff\n");
            printf("3: No, finish change\n");
            scanf("%d", &goOn);
            if (goOn == 1)
            {
                goto TS;
            }
            else if (goOn == 2)
            {
                goto AS;
            }
            else
            {
                break;
            }
        }
        case 3:
        {
            printf("Enter new phone number: \n");
            fflush(stdin);
            gets(tPhNum);
            strcpy(pStaff[i].phNum, tPhNum);
            printf("Change successfully!!!\n");
            printf("Do you want to go on change: \n");
            printf("1: Continue this staff\n");
            printf("2: Another staff\n");
            printf("3: No, finish change\n");
            scanf("%d", &goOn);
            if (goOn == 1)
            {
                goto TS;
            }
            else if (goOn == 2)
            {
                goto AS;
            }
            else
            {
                break;
            }
        }
        case 4:
        {
            printf("Enter new english level: \n");
            fflush(stdin);
            gets(tELv);
            strcpy(pStaff[i].elv, tELv);
            printf("Change successfully!!!\n");
            printf("Do you want to go on change: \n");
            printf("1: Continue this staff\n");
            printf("2: Another staff\n");
            printf("3: No, finish change\n");
            scanf("%d", &goOn);
            if (goOn == 1)
            {
                goto TS;
            }
            else if (goOn == 2)
            {
                goto AS;
            }
            else
            {
                break;
            }
        }
        case 5:
        {
            printf("Enter new Salary: \n");
            scanf("%d", &pStaff[i].sal);
            printf("Change successfully!!!\n");
            printf("Do you want to go on change: \n");
            printf("1: Continue this staff\n");
            printf("2: Another staff\n");
            printf("3: No, finish change\n");
            scanf("%d", &goOn);
            if (goOn == 1)
            {
                goto TS;
            }
            else if (goOn == 2)
            {
                goto AS;
            }
            else
            {
                break;
            }
        }
        case 6:
        {
            n++;
            printf("ID: \n");
            scanf("%d", &pStaff[n-1].ID);
            printf("Name: \n");
            fflush(stdin);
            gets(pStaff[n-1].name);
            printf("Department: \n");
            gets(pStaff[n-1].dpment);
            printf("Sex: \n");
            gets(pStaff[n-1].duty);
            printf("Birth: \n");
            gets(pStaff[n-1].birth);
            printf("Address: \n");
            gets(pStaff[n-1].add);
            printf("Phone number: \n");
            gets(pStaff[n-1].phNum);
            printf("English level: \n");
            gets(pStaff[n-1].elv);
            printf("Start time: \n");
            scanf("%s", &pStaff[n-1].stTime);
            printf("Salary: \n");
            scanf("%d", &pStaff[n-1].sal);
            printf("Add staff successfully\n");
            printf("Do you want to go on change: \n");
            printf("1: Continue this staff\n");
            printf("2: Another staff\n");
            printf("3: No, finish change\n");
            scanf("%d", &goOn);
            if (goOn == 1)
            {
                goto TS;
            }
            else if (goOn == 2)
            {
                goto AS;
            }
            else
            {
                break;
            }
        }
        case 7:
        {
            //delete staff
            //input id 
            printf("Input ID want to delete: \n");
            scanf("%d", &tID);
            //check this ID
            check = 0;
            while(check != 1)
            {
                printf("ID: \n");
                scanf("%d", &tID);
                for(i = 0; i < n; i++)
                {
                    if (tID == pStaff[i].ID)
                    {
                        check = 1;
                        break;
                    }
                }
            }
            //create some variables to swap
            char swapName[100], swapDepartment[100];
            char swapBirth[100], swapAdd[100];
            char swapPhNum[100], swapELv[100];
            int swapTime, swapSalary, swapSex;
            for (i; i < n; ++i)
            {
                //name
                strcpy(swapName, pStaff[i].name);
                strcpy(pStaff[i].name, pStaff[i + 1].name);
                strcpy(pStaff[i + 1].name, swapName);
                //department
                strcpy(swapDepartment, pStaff[i].dpment);
                strcpy(pStaff[i].dpment, pStaff[i + 1].dpment);
                strcpy(pStaff[i + 1].dpment, swapDepartment);
                //sex
                swapSex = pStaff[i].sex;
                pStaff[i].sex = pStaff[i + 1].sex;
                pStaff[i + 1].sex = swapSex;
                //birth
                strcpy(swapBirth, pStaff[i].birth);
                strcpy(pStaff[i].birth, pStaff[i + 1].birth);
                strcpy(pStaff[i + 1].birth, swapBirth);
                //add   
                strcpy(swapAdd, pStaff[i].add);
                strcpy(pStaff[i].add, pStaff[i + 1].add);
                strcpy(pStaff[i + 1].add, swapAdd);  
                //phone
                strcpy(swapPhNum, pStaff[i].phNum);
                strcpy(pStaff[i].phNum, pStaff[i + 1].phNum);
                strcpy(pStaff[i + 1].phNum, swapPhNum);  
                //elv
                strcpy(swapELv, pStaff[i].elv);
                strcpy(pStaff[i].elv, pStaff[i + 1].elv);
                strcpy(pStaff[i + 1].elv, swapELv);
                //time
                swapTime = pStaff[i].stTime;
                pStaff[i].stTime = pStaff[i + 1].stTime;
                pStaff[i + 1].stTime = swapTime;
                //salary
                swapSalary = pStaff[i].sal;
                pStaff[i].sal = pStaff[i + 1].sal;
                pStaff[i + 1].sal = swapSalary;
            }
            n--;
            printf("Deleted!!!\n");
            printf("Do you want to go on change: \n");
            printf("1: Continue this staff\n");
            printf("2: Another staff\n");
            printf("3: No, finish change\n");
            scanf("%d", &goOn);
            if (goOn == 1)
            {
                goto TS;
            }
            else if (goOn == 2)
            {
                goto AS;
            }
            else
            {
                break;
            }
        }
    }
}


//truy xuat theo tham nien  struct stData staff[], int n
int workTime(struct stData staff[], int n)
{
    int k, time[100], i;
    printf("\nEnter work time: ");
    scanf("%d", &k);
    for (i = 0; i < gNumOfStaff; ++i)
    {
        time[i] = 2018 - staff[i].stTime;
    }
    printf("\nPerson who has worked for our company for %d years is:");
    for (i = 0; i < gNumOfStaff; ++i)
    {
        if (time[i] == k)
        {
            printf("\n%s", staff[i].name);
        }
    }
}

//tong ket luong chi tra

int paySalary(struct stData staff[], int n)
{
    int i, sumOfSalary;
    for (i = 0; i < n; ++i)
    {
        sumOfSalary += staff[i].sal;
    }
    printf("This month we need to pay %d USD for worker's salary!", sumOfSalary);
}

//du bao suy giam nhan luc
// NEED TO EDIT
/*
int reduceWorker(struct stData staff[], int n)
{
    int i, reduce, ageOfWorker[1000];
    for (i = 0; i < n; ++i)
    {
        ageOfWorker[i] = 2018 - staff[i].birth;
    }
    for (i = 0; i < n; ++i)
    {
        if (ageOfWorker[i] > 59)
        {
            reduce++;
        }
    }
    printf("\nWe count that %d staffs will retire!!!");
}
*/

















































































