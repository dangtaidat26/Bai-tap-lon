#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

#define YEAR 2018
#define MAX_NAME 30
#define MAX_DPMENT 30
#define MAX_DUTY 30
#define MAX_BIRTH 30
#define MAX_ADD 100
#define MAX_ELV 15
#define MAX_PHONE 25
#define MAX_MAIL 32

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
void instruction(void);
int checkChr(char str[]);
int checkPhoneNumb(char str[]);
int checkDate(char str[]);
int checkMail(char str[]);
int checkDegree(char str[], char str2[]);
int checkToFind(char str[], char str2[]);
void mainMenu();
void insertRecord();
void deleteRecord();
void showAllList();
void findOptions();
void idFind();
void nameFind();
void dpmtFind();
void timeFind();
void dataUpdate();
void depUpdate();
void dutyUpdate();
void addUpdate();
void salUpdate();
void allPayment();
int main()
{
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
    printf("\nID is an integer number which belongs to [1, 32000] and it isn't a coincidence to any other's one");
    printf("\nIn the fields: Name, Department, Duty");
    printf("\nThey are all strings of Latin letters and space, not contains numbers or special characters");
    printf("\nDepartment: Name of the Department which the staff is in");
    printf("\nDuty: The position of that staff in the Department");
    printf("\nSex: 1 equal to Male, 0 equal to Female");
    printf("\nDate of birth: dd/mm/yyyy. Eg: 26/04/1999, 04/12/1998, 22/07/1999");
    printf("\nAddress: Not exceed more than 100 characters");
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
    int i = 1, view;
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
    scanf("%d", &view);
    if(view == 1)
    {
        mainMenu();
    }
    
}

void showToDel(int choice)
{
    struct stData* p;
    int i = 1, back;
    if(choice == 1)
    {
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
        }
    }
}


/*Insert a record at the terminal*/
void insertRecord()
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
        /*This part is used to check pre-existence of the typed ID. It hasn't worked*/
        /*
        if(gNumOfStaff > 1)
        {
            while(curNode != NULL && curNode->ID != temp->ID)
            {
                prevNode = curNode;
                curNode = curNode->pNext;
            }
            if(curNode->ID == temp->ID)
            {
                do
                {
                    system("cls");
                    printf("This ID is used for Another! Please type other ID");
                    printf("\nID: ");
                    scanf("%d", &temp->ID);
                }
                while(curNode->ID != temp->ID);
            }
        }
        */
        printf("Name: ");
        fflush(stdin);
        gets(temp->name);
        while(!checkChr(temp->name))
        {
            printf("Invalid Name, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Invalid Sex, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Invalid Department, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Invalid Duty, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Invalid Birthday, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Invalid Phone Number, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Invalid name, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Degree type denied, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
            printf("Invalid Salary, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
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
        printf("\nType 1 to continue inserting other record or type 0 to come back the menu\nYour choice is: ");
        scanf("%d", &choice);
    }
    while(choice == 1);
    mainMenu();   
}


void deleteRecord()
{
    struct stData *prevNode, *curNode, *temp;
    int find, i, findOut = 0, view;
    if(first == NULL)
    {
        printf("\nThe list is empty, you have to have data before delete");
        printf("\nType any key to get back menu");
        getch();
        mainMenu();
    }
    system("cls");
    printf("It's necessary to know exact the staff's ID, whose you want to remove from the list");
    printf("\nDo you want to have a look to the list once before find him or her?");
    printf("\nType 0 to skip or 1 to view: ");
    scanf("%d", &view);
    showToDel(view);
    printf("\nEnter the ID whose you want to delete: ");
    scanf("%d", &find);
    prevNode = curNode = first;
    if(curNode->ID == find)
    {
        temp = first;
        first = first->pNext;
        free(temp);
        gNumOfStaff--;
        printf("\nDeleted, type any key to get back menu");
        getch();
        mainMenu();
    }
    else
    {
        while(curNode->pNext != NULL && curNode->ID != find)
        {
            prevNode = curNode;
            curNode = curNode->pNext;
        }
        if(curNode->ID == find)
        {
            prevNode->pNext = curNode->pNext;
            if(curNode->pNext == NULL)
            {
                last = prevNode;
            }
            free(curNode);
            gNumOfStaff--;
            printf("\nDeleted, type any key to get back menu");
            getch();
            mainMenu();
        }
        else
        {
            printf("\nWe can't find any staff who has that ID");
            printf("\nDo you want to try other ID ?");
            printf("\nType any key to view menu and try again or do something else");
            getch();    
            mainMenu();
        }
    }
}

void mainMenu()
{
    int choice;
    system("cls");
    printf("\n+------+---------------+-----------+-----+---+---+----+------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------******* MENU *******------------+---------------+-----+------+");
    printf("\n+------+---------------+-------------------------------------------+---------------+-----+------+");
    printf("\n|------+---------------+--->>      1. Insert Record               <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      2. Show Data                   <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      3. Delete Record               <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      4. Find Staff                  <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      5. Update Data                 <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      6. Salary Payment      <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      7. Exit                        <<---------------+-----+------|");
    printf("\n+------+---------------+-----------------------------------------------------------+-----+------+");
    do
    {
        printf("\nYour choice is: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            {
                system("cls");
                insertRecord();
                break;
            }
            case 2:
            {
                showAllList();
                break;
            }
            case 3:
            {
                system("cls");
                deleteRecord();
                break;
            }
            case 4:
            {
                findOptions();
                break;
            }
            case 5:
            {
                dataUpdate();
                break;
            }  
            case 6:
            {
                allPayment();
                break;
            }
            case 7:
            {
                system("cls");
                printf("Thanks for using");
                getch();
                free(first);
                exit(0);
            }
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

void findOptions()
{
    int choice;
    system("cls");
    printf("\n+------+---------------+-----------+-----+---+---+----+------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------*****  Options *****------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------+------------------+------------+---------------+-----+------+");
    printf("\n|------+---------------+--->>      1. Find By ID                  <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      2. Find By Name                <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      3. Find By Department          <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      4. Find By Worktime            <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      5. Back To Main Menu           <<---------------+-----+------|");
    printf("\n+------+---------------+-----------------------------------------------------------+-----+------+");
    do
    {
        printf("\nYour choice is: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            {
                system("cls");
                idFind();
                break;
            }
            case 2:
            {
                system("cls");
                nameFind();
                break;
            }
            case 3:
            {
                system("cls");
                dpmtFind();
                break;
            }
            case 4:
            {
                system("cls");
                timeFind();
                break;
            }       
            case 5:
            {
                mainMenu();
                break;
            }
            default:
            {
                system("cls");
                printf("\nWrong Selection!");
                printf("\nType any key to come back Options menu");
                getch();
                findOptions();
                break;
            }
        }
    }
    while (1);
}

void idFind()
{
    struct stData * check;
    int idFind, go, count = 0;
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("Enter the ID whose you want to find: ");
    scanf("%d", &idFind);
    check = first;
    while(check != NULL)
    {
        if(check->ID == idFind)
        {
            count++;
            system("cls");
            printf("Staff's Information:");
            printf("\nID: %d", check->ID);
            printf("\nName: %s", check->name);
            printf("\nSex: ");
            if(check->sex == 1)
            {
                printf("Male");
            }
            else
            {
                printf("Female");
            }
            printf("\nDepartment: %s", check->dpment);
            printf("\nDuty: %s", check->duty);
            printf("\nDate of birth: %s", check->birth);
            printf("\nAddress: %s", check->add);
            printf("\nPhone number: %s", check->phNum);
            printf("\nStart working time: %d years", check->stTime);
            printf("\nSalary: %d USD", check->sal);
            printf("\nEnglish level: %s", check->elv);
            break;
        }
        else
        {
            check = check->pNext;
        }
    }
    if(count == 0)
    {
        printf("\nSorry, we can't find this staff in the list");
    }
    printf("\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    printf("\nYour choice is: ");
    scanf("%d", &go);
    if(go == 1)
    {
        mainMenu();
    }
    else if(go == 2)
    {
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        getch();
        exit(0);
    }
}

void nameFind()
{
    struct stData * check;
    int go, count = 0;
    char tempName[30];
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("Enter the name whose you want to find: ");
    fflush(stdin);
    gets(tempName);
    check = first;
    while(check != NULL)
    {
        if(checkToFind(tempName, check->name))
        {
            count++;
            system("cls");
            printf("Staff's Information:");
            printf("\nID: ", check->ID);
            printf("\nName: %s", check->name);
            printf("\nSex: ");
            if(check->sex == 1)
            {
                printf("Male");
            }
            else
            {
                printf("Female");
            }
            printf("\nDepartment: %s", check->dpment);
            printf("\nDuty: %s", check->duty);
            printf("\nDate of birth: %s", check->birth);
            printf("\nAddress: %s", check->add);
            printf("\nPhone number: %s", check->phNum);
            printf("\nStart working time: %d years", check->stTime);
            printf("\nSalary: %d USD", check->sal);
            printf("\nEnglish level: %s", check->elv);
            break;
        }
        else
        {
            check = check->pNext;
        }
    }
    if(count == 0)
    {
        printf("\nSorry, we can't find this staff in the list");
    }
    printf("\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    printf("\nYour choice is: ");
    scanf("%d", &go);
    if(go == 1)
    {
        mainMenu();
    }
    else if(go == 2)
    {
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        getch();
        exit(0);
    }
}

void dpmtFind()
{
    struct stData * check;
    int go, count = 0;
    char tempDep[30];
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("Enter the department which you want to find: ");
    fflush(stdin);
    gets(tempDep);
    check = first;
    while(check != NULL)
    {
        if(checkToFind(tempDep, check->dpment))
        {
            count++;
            system("cls");
            printf("Staff's Information:");
            printf("\nID: ", check->ID);
            printf("\nName: %s", check->name);
            printf("\nSex: ");
            if(check->sex == 1)
            {
                printf("Male");
            }
            else
            {
                printf("Female");
            }
            printf("\nDepartment: %s", check->dpment);
            printf("\nDuty: %s", check->duty);
            printf("\nDate of birth: %s", check->birth);
            printf("\nAddress: %s", check->add);
            printf("\nPhone number: %s", check->phNum);
            printf("\nStart working time: %d years", check->stTime);
            printf("\nSalary: %d USD", check->sal);
            printf("\nEnglish level: %s", check->elv);
            break;
        }
        else
        {
            check = check->pNext;
        }
    }
    if(count == 0)
    {
        printf("\nSorry, we can't find this staff in the list");
    }
    printf("\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    printf("\nYour choice is: ");
    scanf("%d", &go);
    if(go == 1)
    {
        mainMenu();
    }
    else if(go == 2)
    {
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        getch();
        exit(0);
    }
}

void timeFind()
{
    struct stData * check;
    int go, time, count = 0;
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("We divide whole staffs into 3 Group:");
    printf("\nGroup 1: less than 3 years experience");
    printf("\nGroup 2: 3 - 5 years experience");
    printf("\nGroup 3: more than 5 years experience");
    printf("\nEnter the Group you want to find: Group ");
    scanf("%d", &time);
    if(time < 1 || time > 3)
    {
        do
        {
            printf("\nInvalid Group. You have to type 1, 2 or 3");
            printf("\nGroup: ");
            scanf("%d", &time);
        }
        while(1 <= time && time <= 3);
    }
    check = first;
    if(time == 1)
    {
        system("cls");    
        while(check != NULL)
        {
            if((YEAR - check->stTime) < 3)
            {
                count++;
                printf("\nStaff[%d]'s information:", count);
                printf("\nID: ", check->ID);
                printf("\nName: %s", check->name);
                printf("\nSex: ");
                if(check->sex == 1)
                {
                    printf("Male");
                }
                else
                {
                    printf("Female");
                }
                printf("\nDepartment: %s", check->dpment);
                printf("\nDuty: %s", check->duty);
                printf("\nDate of birth: %s", check->birth);
                printf("\nAddress: %s", check->add);
                printf("\nPhone number: %s", check->phNum);
                printf("\nStart working time: %d years", check->stTime);
                printf("\nSalary: %d USD", check->sal);
                printf("\nEnglish level: %s", check->elv);
                break;
            }
            else
            {
                check = check->pNext;
            }  
        }
        if(count == 0)
        {
            printf("\nThere is no suitable record to this Group");
        }   
    }
    else if(time == 2)
    {
        system("cls");    
        while(check != NULL)
        {
            if((YEAR - check->stTime) <= 5 && (YEAR - check->stTime) >= 3)
            {
                count++;
                printf("\nStaff[%d]'s information:", count);
                printf("\nID: ", check->ID);
                printf("\nName: %s", check->name);
                printf("\nSex: ");
                if(check->sex == 1)
                {
                    printf("Male");
                }
                else
                {
                    printf("Female");
                }
                printf("\nDepartment: %s", check->dpment);
                printf("\nDuty: %s", check->duty);
                printf("\nDate of birth: %s", check->birth);
                printf("\nAddress: %s", check->add);
                printf("\nPhone number: %s", check->phNum);
                printf("\nStart working time: %d years", check->stTime);
                printf("\nSalary: %d USD", check->sal);
                printf("\nEnglish level: %s", check->elv);
                break;
            }
            else
            {
                check = check->pNext;
            }  
        }
        if(count == 0)
        {
            printf("\nThere is no suitable record to this Group");
        }   
    }
    else
    {
        system("cls");    
        while(check != NULL)
        {
            if((YEAR - check->stTime) > 5)
            {
                count++;
                printf("\nStaff[%d]'s information:", count);
                printf("\nID: ", check->ID);
                printf("\nName: %s", check->name);
                printf("\nSex: ");
                if(check->sex == 1)
                {
                    printf("Male");
                }
                else
                {
                    printf("Female");
                }
                printf("\nDepartment: %s", check->dpment);
                printf("\nDuty: %s", check->duty);
                printf("\nDate of birth: %s", check->birth);
                printf("\nAddress: %s", check->add);
                printf("\nPhone number: %s", check->phNum);
                printf("\nStart working time: %d years", check->stTime);
                printf("\nSalary: %d USD", check->sal);
                printf("\nEnglish level: %s", check->elv);
                break;
            }
            else
            {
                check = check->pNext;
            }  
        }
        if(count == 0)
        {
            printf("\nThere is no suitable record to this Group");
        }   
    }
    printf("\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    printf("\nYour choice is: ");
    scanf("%d", &go);
    if(go == 1)
    {
        mainMenu();
    }
    else if(go == 2)
    {
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        getch();
        exit(0);
    }
}


void dataUpdate()
{
    int choice;
    system("cls");
    printf("\n+------+---------------+-----------+-----+---+---+----+------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------*****   Update *****------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------+------------------+------------+---------------+-----+------+");
    printf("\n|------+---------------+--->>      1. Update Department           <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      2. Update Duty                 <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      3. Update Address              <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      4. Update Salary               <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      5. Back To Main Menu           <<---------------+-----+------|");
    printf("\n+------+---------------+-----------------------------------------------------------+-----+------+");
    do
    {
        printf("\nYour choice is: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            {
                system("cls");
                depUpdate();
                break;
            }
            case 2:
            {
                system("cls");
                dutyUpdate();
                break;
            }
            case 3:
            {
                system("cls");
                addUpdate();
                break;
            }
            case 4:
            {
                system("cls");
                salUpdate();
                break;
            }     
            case 5:
            {
                mainMenu();
                break;
            }
            default:
            {
                system("cls");
                printf("\nWrong Selection!");
                printf("\nType any key to come back Update menu");
                getch();
                dataUpdate();
                break;
            }
        }
    }
    while (1);
}

void depUpdate()
{
    struct stData *change;
    int supID, choice;
    change = first;
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("Staff ID is used to support update process");
    printf("\nType the ID whose you want to update his or her data: ");
    scanf("%d", &supID);
    while(change != NULL)
    {
        if(change->ID == supID)
        {
            if(change->sex)
            {
                printf("\nHis new department is: ");
                fflush(stdin);
                gets(change->dpment);
                while(!checkChr(change->dpment))
                {
                    printf("Invalid Department, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new department is: ");
                        fflush(stdin);
                        gets(change->dpment);
                    }
                    else if(choice == 0)
                    {
                        printf("His new department is: ");
                        fflush(stdin);
                        gets(change->dpment);
                    }
                }
            }
            else
            {
                printf("\nHer new department is: ");
                fflush(stdin);
                gets(change->dpment);
                while(!checkChr(change->dpment))
                {
                    printf("Invalid Department, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new department is: ");
                        fflush(stdin);
                        gets(change->dpment);
                    }
                    else if(choice == 0)
                    {
                        printf("Her new department is: ");
                        fflush(stdin);
                        gets(change->dpment);
                    }
                }
            }
            break;
        }
        else
        {
            change = change->pNext;
        }
    }
    if(change == NULL)
    {
        printf("\nThere is no suitable record in the list!");
    }
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        dataUpdate();
    }
    else if(choice == 2)
    {
        mainMenu();
    }
    else if(choice == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        exit(0);
    }
}

void dutyUpdate()
{
    struct stData *change;
    int supID, choice;
    change = first;
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("Staff ID is used to support update process");
    printf("\nType the ID whose you want to update his or her data: ");
    scanf("%d", &supID);
    while(change != NULL)
    {
        if(change->ID == supID)
        {
            if(change->sex)
            {
                printf("\nHis new duty is: ");
                fflush(stdin);
                gets(change->duty);
                while(!checkChr(change->duty))
                {
                    printf("Invalid Duty, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new duty is: ");
                        fflush(stdin);
                        gets(change->duty);
                    }
                    else if(choice == 0)
                    {
                        printf("His new duty is: ");
                        fflush(stdin);
                        gets(change->duty);
                    }
                }
            }
            else
            {
                printf("\nHer new Duty is: ");
                fflush(stdin);
                gets(change->duty);
                while(!checkChr(change->duty))
                {
                    printf("Invalid Duty, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new Duty is: ");
                        fflush(stdin);
                        gets(change->duty);
                    }
                    else if(choice == 0)
                    {
                        printf("Her new Duty is: ");
                        fflush(stdin);
                        gets(change->duty);
                    }
                }
            }
            break;
        }
        else
        {
            change = change->pNext;
        }
    }
    if(change == NULL)
    {
        printf("\nThere is no suitable record in the list!");
    }
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        dataUpdate();
    }
    else if(choice == 2)
    {
        mainMenu();
    }
    else if(choice == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        exit(0);
    }
}

void addUpdate()
{
    struct stData *change;
    int supID, choice;
    change = first;
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("Staff ID is used to support update process");
    printf("\nType the ID whose you want to update his or her data: ");
    scanf("%d", &supID);
    while(change != NULL)
    {
        if(change->ID == supID)
        {
            if(change->sex)
            {
                printf("\nHis new address is: ");
                fflush(stdin);
                gets(change->add);
                while(strlen(change->add) > 100)
                {
                    printf("Invalid Address, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new address is: ");
                        fflush(stdin);
                        gets(change->add);
                    }
                    else if(choice == 0)
                    {
                        printf("His new address is: ");
                        fflush(stdin);
                        gets(change->add);
                    }
                }
            }
            else
            {
                printf("\nHer new Address is: ");
                fflush(stdin);
                gets(change->add);
                while(strlen(change->add) > 100)
                {
                    printf("Invalid Address, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new Address is: ");
                        fflush(stdin);
                        gets(change->add);
                    }
                    else if(choice == 0)
                    {
                        printf("Her new Address is: ");
                        fflush(stdin);
                        gets(change->add);
                    }
                }
            }
            break;
        }
        else
        {
            change = change->pNext;
        }
    }
    if(change == NULL)
    {
        printf("\nThere is no suitable record in the list!");
    }
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        dataUpdate();
    }
    else if(choice == 2)
    {
        mainMenu();
    }
    else if(choice == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        exit(0);
    }
}


void salUpdate()
{
    struct stData *change;
    int supID, choice;
    change = first;
    if(gNumOfStaff == 0)
    {
        system("cls");
        printf("ERROR:<There is no record in the list!\nYou have to have data first>");
        getch();
        mainMenu();
    }
    system("cls");
    printf("Staff ID is used to support update process");
    printf("\nType the ID whose you want to update his or her data: ");
    scanf("%d", &supID);
    while(change != NULL)
    {
        if(change->ID == supID)
        {
            if(change->sex)
            {
                printf("\nHis new salary is: ");
                scanf("%d", &change->sal);
                while(change->sal < 176)
                {
                    printf("Invalid sal, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new salary is: ");
                        scanf("%d", &change->sal);
                    }
                    else if(choice == 0)
                    {
                        printf("His new salary is: ");
                        scanf("%d", &change->sal);
                    }
                }
            }
            else
            {
                printf("\nHer new salary is: ");
                scanf("%d", &change->sal);
                while(change->sal < 176)
                {
                    printf("Invalid salary, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    scanf("%d", &choice);
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new salary is: ");
                        scanf("%d", &change->sal);
                    }
                    else if(choice == 0)
                    {
                        printf("Her new salary is: ");
                        scanf("%d", &change->sal);
                    }
                }
            }
            break;
        }
        else
        {
            change = change->pNext;
        }
    }
    if(change == NULL)
    {
        printf("\nThere is no suitable record in the list!");
    }
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    scanf("%d", &choice);
    if(choice == 1)
    {
        dataUpdate();
    }
    else if(choice == 2)
    {
        mainMenu();
    }
    else if(choice == 3)
    {
        system("cls");
        free(first);
        printf("Thanks for using");
        exit(0);
    }
}

void allPayment()
{
   struct stData *pay;
   long all = 0;
   pay = first;
   while(pay != NULL)
   {
        all += pay->sal;
        pay = pay->pNext;
   }
   system("cls");
   printf("Amount of salary your company need to pay per month is: %ld USD", all);
   printf("\nType any key to get back main menu");
   getch();
   mainMenu();
}

int getYear(char *str)
{
    int year = 0;
    year += (*(str + 6) - 48) * 1000;
    year += (*(str + 7) - 48) * 100;
    year += (*(str + 8) - 48) * 10;
    year += (*(str + 9) - 48);
    return year;
}
