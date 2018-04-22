#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>
#include<conio.h>

#define YEAR 2018
#define MAX_NAME 30
#define MAX_DPMENT 50
#define MAX_DUTY 30
#define MAX_BIRTH 30
#define MAX_ADD 100
#define MAX_ELV 15
#define MAX_PHONE 25
#define MAX_MAIL 42

/**********************************************************************************************************************
 *                                  This program is used to manage a company's stafves                                *
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

char cpny[100];

/**********************************************************************************************************************
 *****************************************************PROTOTYPE********************************************************
 *********************************************************************************************************************/
void instruction();
/*!
 *Function: {void} instruction(void)
 *
 *@Brief: Show instruction to help user understand all typing requirements and come back main menu after that
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void instrWithoutBack();
/*!
 *Function: {void} instrWithoutBack(void)
 *
 *@Brief: Show instruction to help user understand all typing requirements without backing the main menu
 *        All instruction will be saved on display until user changes to another menu
 *
 *@Param: <none>
 *
 *@Return: <none>
 */

int checkID(int NewID);
/*!
 *Function: {int} checkID(int NewID)
 *
 *@Brief: Check if the typed ID exist in the list or not           
 *
 *@Param: int NewID: the typed ID which user types for new staff
 *
 *@Return: Return 1 if the typed ID doesn't exist in the list
 *         Return 0 if it exists in the list 
 */
int checkChr(char *str);
/*!
 *Function: {int} checkChr(char *str)
 *
 *@Brief: Check if the typed string (such as name, department, duty ...) contains number, special character or not.         
 *
 *@Param: char *str: It is the pointer which points to the checking string
 *
 *@Return: Return 1 if the string is valid (the string contains only Latin letter)
 *         Return 0 if the string is invalid (the string have at least a number or special character: ' ', '@',...) 
 */
int checkPhoneNumb(char *str);
/*!
 *Function: {int} checkPhoneNumb(char *str)
 *
 *@Brief: Check if the typed string (the staff's phone number) is valid or not
 *        Require: -The string contain only numbers
 *                 -The string's length is 10 if it begins by '09' or it's length is 11 if it begin by '01'       
 *                  example: '0986061596' or '01663158685', ...
 *
 *@Param: char *str: It is the pointer which points to the checking string
 *
 *@Return: Return 1 if the string is valid
 *         Return 0 if the string is invalid 
 */
int checkDate(char *str);
/*!
 *Function: {int} checkDate(char *str)
 *
 *@Brief: Check if the typed string (staff's birthday) is valid or not
 *        Require: -The string contain only numbers and character '/' to separate day, month and year.
 *                 -The string's length is 10: +) 2 characters to express day
 *                                             +) 2 characters to express month
 *                                             +) 4 characters to express year   
 *                                             +) 2 characters '/' to separate: dd/mm/yyyy
 *
 *@Param: char *str: It is the pointer which points to the checking string
 *
 *@Return: Return 1 if the string is valid
 *         Return 0 if the string is invalid
 */
int checkMail(char *str);
/*!
 *Function: {int} checkMail(char *str)
 *
 *@Brief: Check if the typed string (staff's email) is valid or not
 *        Require: -Expected email types: yahoo, gmail, hotmail
 *                 -The minimum size is 16 characters in length and the maximum size is 42 characters
 *                  example: abcdef@gmail.com contains 16 characters
 *              
 *@Param: char *str: It is the pointer which points to the checking string
 *
 *@Return: Return 1 if the string is valid
 *         Return 0 if the string is invalid
 */
int checkDegree(char *str, char *str2);
/*!
 *Function: {int} checkDegree(char *str)
 *
 *@Brief: Check if the typed string (staff's degree) is valid or not
 *        Require: -Expected degree types: Vstep, Ielst, Toeic
 *
 *@Param: char *str: It is the pointer which points to the checking string
 *
 *@Return: Return 1 if the string is valid
 *         Return 0 if the string is invalid
 */
int checkToFind(char *str, char *str2);
/*!
 *Function: {int} checkToFind(char *str, char *str2)
 *
 *@Brief: Check if two strings are similar or not so we can use this function in searching staff's information
 *        They will be count as similar if the difference just be lower and upper case
 *        example: "Pham Tien Manh" and "pHam TIen mAnH" are similar
 *
 *@Param: char *str: It is the pointer which points to the first string
 *        char *str2: It is the pointer which points to the second string
 *
 *@Return: Return 1 if two strings are similar
 *         Return 0 if they are unsimilar
 */
char *stdization(char *str);
/*!
 *Function: {char*} stdization(char *str)
 *
 *@Brief: Standardize a string
 *        A string will be count as standardized if it meet below requirements:
 *          -The first character must be Latin letter
 *          -Two consecutive character can't both be space character
 *          -The first character in each word must be Upper Latin letter
 *          -A character which isn't the first character in each word must be Lower Latin letter 
 *
 *@Param: char *str: The pointer which points to the string need to be standardized
 *
 *@Return: Return pointer str after it is standardized
 */
void mainMenu();
/*!
 *Function: {void} mainMenu(void)
 *
 *@Brief: Show the Main Menu. You have multiple choices: 
 *          -Insert record: Insert a new staff to the list
 *          -Show all list: Show all staff's information
 *          -Delete record: Remove a record from the list by his or her ID
 *          -Find staff: Show finding options: find by ID, name, department,...
 *          -Update data: Update staff's information: address, deparment, duty, salary
 *          -All payment: Show amount of salary that the company need to pay for their stafves
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void insertRecord();
/*!
 *Function: {void} insertRecord(void)
 *
 *@Brief: Insert a new staff to the list
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void deleteRecord();
/*!
 *Function: {void} insertRecord(void)
 *
 *@Brief: Remove a staff from the list
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void showAllList();
/*!
 *Function: {void} showAllList(void)
 *
 *@Brief: Show all stafves's information
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void showToDel(int choice);
/*!
 *Function: {void} showToDel(int choice)
 *
 *@Brief: Show all stafves's information without menu called.
 *        It's more helpful than function 'showAllList' in supporting function 'deleteRecord'
 *
 *@Param: int choice: Express user's choice to view stafves's data or skip.
 *
 *@Return: <none>
 */
void findOptions();
/*!
 *Function: {void} findOptions(void)
 *
 *@Brief: Show finding ways
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void idFind();
/*!
 *Function: {void} iFind(void)
 *
 *@Brief: Find a staff from the list by the ID typed from keyboard 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void nameFind();
/*!
 *Function: {void} nameFind(void)
 *
 *@Brief: Find a staff from the list by the Name typed from keyboard 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void dpmtFind();
/*!
 *Function: {void} dpmtFind(void)
 *
 *@Brief: Find a staff from the list by the Department typed from keyboard 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void timeFind();
/*!
 *Function: {void} timeFind(void)
 *
 *@Brief: Find a staff from the list by the work-time group typed from keyboard 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void dataUpdate();
/*!
 *Function: {void} dataUpdate(void)
 *
 *@Brief: Show updating fields
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void depUpdate();
/*!
 *Function: {void} depUpdate(void)
 *
 *@Brief: Change staff's department information 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void dutyUpdate();
/*!
 *Function: {void} dutyUpdate(void)
 *
 *@Brief: Change staff's duty information 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void addUpdate();
/*!
 *Function: {void} addUpdate(void)
 *
 *@Brief: Change staff's address information 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void salUpdate();
/*!
 *Function: {void} salUpdate(void)
 *
 *@Brief: Change staff's salary information 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
void allPayment();
/*!
 *Function: {void} allPayment(void)
 *
 *@Brief: Change staff's address information 
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
int getYear(char *str);
/*!
 *Function: {int} getYear(char *str)
 *
 *@Brief: Get birthyear from date of birth 
 *
 *@Param: char *str: str is a pointer which points to the staff's date of birth
 *
 *@Return: The year from staff's date of birth
 */
void HRDecPredict();
/*!
 *Function: {void} HRDecPredict(void)
 *
 *@Brief: Give a prediction about Human Resource Decline in a year typed from keyboard
 *
 *@Param: <none>
 *
 *@Return: <none>
 */
/**********************************************************************************************************************
 ******************************************************CODE************************************************************
 *********************************************************************************************************************/
int main()
{
    printf("Type your company's name: ");
    fflush(stdin);
    gets(cpny); 
    mainMenu();
    return 0;
}

/*This function will show data require*/
void instruction()
{
    printf("\nThis program is used to manage a company staff(s)'s information");
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
    printf("\nSalary has to meet the regional minimum salary. (>= 176 USD per month)");
    printf("\nAll difference will be count as wrong!");
    printf("\n\nType any key to get back main menu");
    getch();
    mainMenu();
}

void instrWithoutBack()
{
    printf("\nThis program is used to manage a company staff(s)'s information");
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
    printf("\nSalary has to meet the regional minimum salary. (>= 176 USD per month)");
    printf("\nAll difference will be count as wrong!");
}

int checkID(int NewID)
{
    struct stData *checkNode;
    /*checkNode is a pointer which point to each element of the list*/
    checkNode = first;
    /*If checkNode != NULL, check it's ID*/
    while(checkNode)
    {
        /*If the ID is existence, return 0 and finish*/
        if(checkNode->ID == NewID)
        {
            return 0;
        }
        checkNode = checkNode->pNext;
    }
    /*If we can't find that ID in the list, so it doesn't exist, return 1 and finish*/
    return 1;
}

/*This function is used to check some fields that only include Latin letter such as Name, Duty,...*/
int checkChr(char *str)
{
    int i;
    /*Check if there is any special character or number, return 0 if that true*/
    for(i = 0; i < strlen(str); i++)
    {
        if((str[i] < 65 && str[i] != ' ') || ((90 < str[i] && str[i] < 97)) || str[i] > 122)
        {
            return 0;
        }
    }
    /*If there is no special character or number, return 1*/
    return 1;
}

/*This function is used to check if the phone number you type is right wrong in Vietnam's format*/
int checkPhoneNumb(char *str)
{
    int i;
    /*The first number must be 0*/
    if(str[0] != '0')
    {
        return 0;
    }
    /*If the beginning is '01', the phone number length must be 11 digit. In other case, the length must be 10 digit.
      This condition base on Vietnamese phone number format*/
    else if((str[1] == '1' && strlen(str) != 11) || (str[1] != '1' && strlen(str) != 10)) 
    {
        return 0;
    }
    /*If these are right, check the last condition: phone number mustn't include Latin letter or special character*/
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
int checkDate(char *str)
{
    int i;
    /*The length must be 10 characters: dd/mm/yyyy*/
    if(strlen(str) != 10)
    {
        return 0;
    }
    /*Check if two characters '/' are located in right position or not*/ 
    if((48 > str[2] && str[2] != '/') || str[2] > 57 || (48 < str[5] && str[5] != '/') || str[5] > 57)
    {
        return 0;
    }
    /*Except 2 characters '/' to separate day, month and year, others must be digit*/
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
int checkMail(char *str)
{
    int i, count = 0;
    char mailType1[] = "yahoo", mailType2[] = "gmail", mailType3[] = "hotmail";
    /*User name might be 6 to 32 characters so all form length might be up to 42 characters*/
    if(16 > strlen(str) || strlen(str) > 42)
    {
        return 0;
    }
    /*Check the tail '.com'*/
    if(str[strlen(str) - 4] != '.' || str[strlen(str) - 3] != 'c' || str[strlen(str) - 2] != 'o' ||
        str[strlen(str) - 1] != 'm')
    {
        return 0;
    }
    /*Check if the typed mail is expected kind (gmail, hotmail, yahoo) or not*/
    if(!strstr(str, mailType1) && !strstr(str, mailType2) && !strstr(str, mailType3))
    {
        return 0;
    }
    return 1;
}

/*This function is used to check the head of typed string is similar to expected kind*/
int checkDegree(char *str, char *str2)
{
    int i;
    /*Their difference just be lower or upper case*/
    for(i = 0; i < 5; i++)
    {
        /*65 -> 90 are ASCII code of upper Latin letters A -> Z
        The below IF STATEMENT tells us that both of lower type and upper type are accept*/
        if(65 <= str[i] && str[i] <= 90)
        {
            if(str2[i] != str[i] && str2[i] != str[i] + 32)
            {
                return 0;
            }
        }
        /*97 -> 122 are ASCII code of lower Latin letters a -> z
        The meaning is similar to IF STATEMENT above*/
        else if(97 <= str[i] && str[i] <= 122)
        {
            if(str2[i] != str[i] && str2[i] != str[i] - 32)
            {
                return 0;
            }
        }
    }
}


/*This function is used to check if two strings are similar or not.
  We can use this function in searching staff's information
  They will be count as similar if the difference just be lower and upper case
  example: "Pham Tien Manh" and "pHam TIen mAnH" are similar*/
int checkToFind(char *str, char *str2)
{
    int i;
    /*Check two string length. If they are different from each other so they can't be the same*/
    if(strlen(str) != strlen(str2))
    {
        return 0;
    }
    else
    {
        for(i = 0; i < strlen(str); i++)
        {
            /*65 -> 90 are ASCII code of upper Latin letters A -> Z
            The below IF STATEMENT tells us that both of lower type and upper type are accept*/
            if(65 <= str[i] && str[i] <= 90)
            {
                if(str2[i] != str[i] && str2[i] != str[i] + 32)
                {
                    return 0;
                }
            }
            /*97 -> 122 are ASCII code of lower Latin letters a -> z
            The meaning is similar to IF STATEMENT above*/
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

/*This function is used to view all stafves's information*/
void showAllList()
{
    struct stData* p;
    int i = 1;
    int view;
    /*p is a pointer pointing to nodes in the stafves data
      i is the running variable to count stafves quantity
      view is a variable to express user choice*/ 
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
    printf("Type 1 if you want to show menu or other key to exit program: ");
    scanf("%d", &view);
    if(view == 1)
    {
        mainMenu();
    }
}

/*There is a tiny difference between this function and function 'showAllList'
This function show stafves information without getting back Main Menu if there is no error*/
void showToDel(int choice)
{
    struct stData* p;
    int i = 1;
    /*choice = 1 express that user want view all stafves information to find the ID whose need to be remove*/
    if(choice == 1)
    {
        system("cls");
        p = first;
        /*If user hasn't inputed data, a notification will be show to him or her*/
        if(gNumOfStaff == 0)
        {
            printf("\nThere hasn't any record typed. You have to insert some record into the list.");
            getch();
            mainMenu();
        }
        else
        {
            /*If the list isn't empty, the list will be shown*/
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

char *stdization(char *str)
{
    int i, j, n;
    n = strlen(str);
    /*Step 1: Check if two consecutive elements are all space character
    If that's true, copy the string belows the first space character and replace it*/
    for(i = 0; i < n; i++)
    {
        while(str[i] == ' ' && str[i + 1] == ' ')
        {
            for(j = i; j < n - 1; j++)
            {
                str[j] = str[j + 1];
            }
            n--;
        }
    }
    /*Step 2: Check if the first character is space character or not
    If that's true, do the same thing as Step 1*/
    if(str[0] == ' ')
    {
        for(j = 0; j < n - 1; j++)
        {
            str[j] = str[j + 1];
        }
        n--;
    }
    /*Step 3: Check if the first character is lower Latin letter
    If that's right, make it Upper*/
    if(97 <= str[0] && str[0] <= 122)
    {
        str[0] -= 32;
    }
    /*Step 4: Make each letter belows space character become Upper*/
    for(i = 0; i < n - 1; i++)
    {
        if(str[i] == ' ' && (str[i + 1] >= 97 && str[i + 1] <= 122))
        {
            str[i + 1] -= 32;
        }
    }
    /*Step 5: Make all letter that belows first letter in each word Lower*/ 
    for(i = 0; i < n - 1; i++)
    {
        if(((65 <= str[i] && str[i] <= 90) || (97 <= str[i] && str[i] <= 122)) && (str[i + 1] >= 65 && str[i + 1] <= 90))
        {
            str[i + 1] += 32;
        }
    }
    /*Step 6: If the last character is space character, delete it*/
    if(str[n - 1] == ' ')
    {
        str[n - 1] = '\0';
    }
    /*Step 7: Cut unnecessary part*/
    str[n] = '\0';
    return str;
}

/*Insert a record at the terminal*/
void insertRecord()
{
    int choice = 0, findOut = 1;
    char deg1[] = "Ielts", deg2[] = "Toeic", deg3[] = "Toefl", deg4[] = "Vstep";
    do
    {
        gNumOfStaff++;
        /*Supply a suitable memory space to store new's record information*/
        temp = (struct stData*)malloc(sizeof(STAFF));
        /*If there isn't enough memory space, pointer Temp will be NULL, a notification will be shown*/
        if(!temp)
        {
            printf("\nThere isn't enough memory space to supply for the next record");
            getch();
            mainMenu();
        }
        else
        {
            /*Input data*/
            printf("\nType staff[%d]'s information:\n", gNumOfStaff);
            /*Enter ID and check it, ID is chosen as key so it must be unique*/
            printf("\nID: ");
            scanf("%d", &temp->ID);
            while(!checkID(temp->ID))
            {
                system("cls");
                printf("This ID is used for Another! Please type other ID");
                printf("\nID: ");
                scanf("%d", &temp->ID);
            }
            /*Enter Name and check if it is valid or not within 'chechChr' function*/
            printf("Name: ");
            fflush(stdin);
            gets(temp->name);
            stdization(temp->name);
            /*If the enterred name is invalid, force user try again until it is valid*/
            while(!checkChr(temp->name))
            {
                printf("Invalid Name, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: ");
                    fflush(stdin);
                    gets(temp->name);
                    stdization(temp->name);
                }
                else if(choice == 0)
                {
                    printf("Name: ");
                    fflush(stdin);
                    gets(temp->name);
                    stdization(temp->name);
                }
            }
            /*Enter sex by symbol: 1 equal to male, 0 equal to female.
            If the typed value is neither 1 nor 0, It will be count as wrong.
            Notification will be shown*/
            printf("Sex: ");
            scanf("%d", &temp->sex);
            while(temp->sex != 0 && temp->sex != 1)
            {
                printf("Invalid Sex, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    scanf("%d", &temp->sex);
                }
                else if(choice == 0)
                {
                    printf("Sex: ");
                    scanf("%d", &temp->sex);
                }
            }
            /*Enter Department and check if it is valid or not within 'chechChr' function*/
            printf("Department: ");
            fflush(stdin);
            gets(temp->dpment);
            stdization(temp->dpment);
            /*If the enterred Department is invalid, force user try again until it is valid*/
            while(!checkChr(temp->dpment))
            {
                printf("Invalid Department, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    if(temp->sex == 1)
                    {
                        printf("Male");
                    }
                    else
                    {
                        printf("Female");
                    }
                    printf("\nDepartment: ");
                    fflush(stdin);
                    gets(temp->dpment);
                    stdization(temp->dpment);
                }
                else if(choice == 0)
                {
                    printf("Department: ");
                    fflush(stdin);
                    gets(temp->dpment);
                    stdization(temp->dpment);
                }
            }
            /*Enter Duty and check if it is valid or not within 'chechChr' function*/
            printf("Duty: ");
            fflush(stdin);
            gets(temp->duty);
            stdization(temp->duty);
            /*If the enterred Duty is invalid, force user try again until it is valid*/
            while(!checkChr(temp->duty))
            {
                printf("Invalid Duty, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    if(temp->sex == 1)
                    {
                        printf("Male");
                    }
                    else
                    {
                        printf("Female");
                    }
                    printf("\nDepartment: %s", temp->dpment);
                    printf("\nDuty: ");
                    fflush(stdin);
                    gets(temp->duty);
                    stdization(temp->duty);
                }
                else if(choice == 0)
                {
                    printf("Duty: ");
                    fflush(stdin);
                    gets(temp->duty);
                    stdization(temp->duty);
                }
            }
            /*Enter date of birth*/
            printf("Date of birth: ");
            fflush(stdin);
            gets(temp->birth);
            /*Check if the date is formal or informal
            If it is informal, require user to retry*/
            while(!checkDate(temp->birth))
            {
                printf("Invalid Birthday, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    if(temp->sex == 1)
                    {
                        printf("Male");
                    }
                    else
                    {
                        printf("Female");
                    }
                    printf("\nDepartment: %s", temp->dpment);
                    printf("\nDuty: %s", temp->duty);
                    printf("\nBirthday: ");
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
            /*Enter address
            Address might have both Latin letter, digit and special character so that it is enterred without check*/
            printf("Address: ");
            fflush(stdin);
            gets(temp->add);
            stdization(temp->add);
            /*Enter phone number and check if it is valid or not*/
            printf("Phone number: ");
            fflush(stdin);
            gets(temp->phNum);
            /*If it is invalid, require user to retry*/
            while(!checkPhoneNumb(temp->phNum))
            {
                printf("Invalid Phone Number, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    if(temp->sex == 1)
                    {
                        printf("Male");
                    }
                    else
                    {
                        printf("Female");
                    }
                    printf("\nDepartment: %s", temp->dpment);
                    printf("\nDuty: %s", temp->duty);
                    printf("\nDate of birth: %s", temp->birth);
                    printf("\nAddress: %s", temp->add);
                    printf("\nPhone: ");
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
            /*Enter email*/
            printf("Email: ");
            fflush(stdin);
            gets(temp->mail);
            /*If it is invalid, require user to retry*/
            while(!checkMail(temp->mail))
            {
                printf("Invalid name, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    if(temp->sex == 1)
                    {
                        printf("Male");
                    }
                    else
                    {
                        printf("Female");
                    }
                    printf("\nDepartment: %s", temp->dpment);
                    printf("\nDuty: %s", temp->duty);
                    printf("\nDate of birth: %s", temp->birth);
                    printf("\nAddress: %s", temp->add);
                    printf("\nPhone number: %s", temp->phNum);
                    printf("\nEmail: ");
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
            /*Enter English level*/
            printf("English degree: ");
            fflush(stdin);
            gets(temp->elv);
            stdization(temp->elv);
            /*Check if it belongs to expected type group or not*/
            /*If degree type doesn't be accepted, require user to retry*/
            while(!checkDegree(temp->elv, deg1) && !checkDegree(temp->elv, deg2)
                 && !checkDegree(temp->elv, deg3) && !checkDegree(temp->elv, deg4))
            {
                printf("Degree type denied, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    if(temp->sex == 1)
                    {
                        printf("Male");
                    }
                    else
                    {
                        printf("Female");
                    }
                    printf("\nDepartment: %s", temp->dpment);
                    printf("\nDuty: %s", temp->duty);
                    printf("\nDate of birth: %s", temp->birth);
                    printf("\nAddress: %s", temp->add);
                    printf("\nPhone number: %s", temp->phNum);
                    printf("\nEmail: %s", temp->mail);
                    printf("\nEnglish degree: ");
                    fflush(stdin);
                    gets(temp->elv);
                    stdization(temp->elv);
                }
                else if(choice == 0)
                {
                    printf("English degree: ");
                    fflush(stdin);
                    gets(temp->elv);
                    stdization(temp->elv);
                }
            }
            /*Enter the year that the staff start to work for the company*/ 
            printf("Start working year: ");
            scanf("%d", &temp->stTime);
            /*Now is 2018 so the typed time can't be a future point*/
            while(YEAR - temp->stTime < 0)
            {
                system("cls");
                printf("\nID: %d", temp->ID);
                printf("\nName: %s", temp->name);
                printf("\nSex: ");
                if(temp->sex == 1)
                {
                    printf("Male");
                }
                else
                {
                    printf("Female");
                }
                printf("\nDepartment: %s", temp->dpment);
                printf("\nDuty: %s", temp->duty);
                printf("\nDate of birth: %s", temp->birth);
                printf("\nAddress: %s", temp->add);
                printf("\nPhone number: %s", temp->phNum);
                printf("\nEnglish level: %s", temp->elv);
                printf("\nEmail: %s", temp->mail);
                printf("\nNow is 2018, type again!");
                printf("\nStart working year: ");
                scanf("%d", &temp->stTime);
            }
            /*Enter salary*/
            printf("Salary: ");
            scanf("%d", &temp->sal);
            /*Check if it is less than the minimum value as law require*/
            while(temp->sal < 176)
            {
                printf("Invalid Salary, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                scanf("%d", &choice);
                if(choice == 1)
                {
                    system("cls");
                    instrWithoutBack();
                    printf("Type any key to continue typing\n");
                    getch();
                    system("cls");
                    printf("\nID: %d", temp->ID);
                    printf("\nName: %s", temp->name);
                    printf("\nSex: ");
                    if(temp->sex == 1)
                    {
                        printf("Male");
                    }
                    else
                    {
                        printf("Female");
                    }
                    printf("\nDepartment: %s", temp->dpment);
                    printf("\nDuty: %s", temp->duty);
                    printf("\nDate of birth: %s", temp->birth);
                    printf("\nAddress: %s", temp->add);
                    printf("\nPhone number: %s", temp->phNum);
                    printf("\nEnglish level: %s", temp->elv);
                    printf("\nEmail: %s", temp->mail);
                    printf("\nStart working time: %d", temp->stTime);
                    printf("\nSalary: ");
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
            /*If the list is empty, the typed node will be the first node*/
            if(first == NULL)
            {
                first = temp;
            }
            /*Else if it is typed, link the typed temp to the terminal of the list*/
            else
            {
                last->pNext = temp;
            }
            last = temp;
            last->pNext = NULL;
            printf("\nType 1 to continue inserting other record or type 0 to come back the menu\nYour choice is: ");
            scanf("%d", &choice);
        }
    }
    while(choice == 1);
    mainMenu();
}

void deleteRecord()
{
    struct stData *prevNode, *curNode;
    int find, view;
    /* struct stData *prevNode: used to store previous node of the node which need to be deleted
                     *curNode: used to store current node  which is compare to key
       int find: used to express the ID whose need to be deleted
           view: user choice to see all list or not */
    /*If there is no record, delete process can't happen*/
    if(first == NULL)
    {
        printf("\nThe list is empty, you have to have data before delete");
        printf("\nType any key to get back menu");
        getch();
        mainMenu();
    }
    /*If the list isn't empty, start by enterring user choice*/
    system("cls");
    printf("It's necessary to know exact the staff's ID, whose you want to remove from the list");
    printf("\nDo you want to have a look to the list once before find him or her?");
    /*Choose to view all list or not*/
    printf("\nType 0 to skip or 1 to view: ");
    scanf("%d", &view);
    showToDel(view);
    printf("\nEnter the ID whose you want to delete: ");
    scanf("%d", &find);
    /*At first, current node and previous node point to the first node*/
    prevNode = curNode = first;
    /*Check if this record's ID is similar to the typed ID*/
    /*If it is the node to be deleted, delete it*/
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
    /*If it isn't, the node to be deleted might be other record in the list*/
    else
    {
        /*Check all list to find the node to be deleted and delete it*/
        while(curNode->pNext != NULL && curNode->ID != find)
        {
            prevNode = curNode;
            curNode = curNode->pNext;
        }
        if(curNode->ID == find)
        {
            /*Delete method:
              the previous node's link pointer point to deleted node's next node*/
            prevNode->pNext = curNode->pNext;
            /*Check if the deleted node is the last node?
            If it is the last node, the pointer 'last' will point to the previous node of deleted node
            It is necessary to do this because insert method is terminal inserting*/
            if(curNode->pNext == NULL)
            {
                last = prevNode;
            }
            /*After previous node's link pointer was changed, free current node because if is unnecessary*/
            free(curNode);
            /*Amount of stafves quantity will reduce 1*/
            gNumOfStaff--;
            /*Notification to user*/
            printf("\nDeleted, type any key to get back menu");
            getch();
            mainMenu();
        }
        /*If there is no record whose ID is similar to typed ID, notice user this problem*/
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
    printf("%s's stafves management:", strupr(cpny));
    printf("\n+------+---------------+------------+----+---+---+----+------------+---------------+-----+------+");
    printf("\n+------+---------------+------------****** MENU  ******-----------+----------------+-----+------+");
    printf("\n+------+---------------+-------------------------------------------+---------------+-----+------+");
    printf("\n|------+---------------+--->>      1. Insert Record               <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      2. Show Data                   <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      3. Delete Record               <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      4. Find Staff                  <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      5. Update Data                 <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      6. Salary Payment              <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      7. View Instruction            <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      8. Human Resource Decline      <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      9. Exit                        <<---------------+-----+------|");
    printf("\n+------+---------------+-----------------------------------------------------------+-----+------+");
    do
    {
        printf("\nYour choice is: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
            {
                /*move to function 'insertRecord'*/
                system("cls");
                insertRecord();
                break;
            }
            case 2:
            {
                /*move to function 'showAllList'*/
                showAllList();
                break;
            }
            case 3:
            {
                /*move to function 'deleteRecord'*/
                system("cls");
                deleteRecord();
                break;
            }
            case 4:
            {
                /*move to function 'findOptions'*/
                findOptions();
                break;
            }
            case 5:
            {
                /*move to function 'dataUpdate'*/
                dataUpdate();
                break;
            }  
            case 6:
            {
                /*move to function 'allPayment'*/
                allPayment();
                break;
            }
            case 7:
            {
                /*View instruction*/
                system("cls");
                instruction();
                break;
            }
            case 8:
            {
                /*Human Resource Decline Predict*/
                system("cls");
                HRDecPredict();
                break;
            }
            case 9:
            {
                /*exit program*/
                system("cls");
                printf("Thank for using");
                getch();
                free(first);
                exit(0);
            }
            default:
            {
                /*other case*/
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
    /*show chooses*/
    printf("%s's stafves management:", strupr(cpny));
    printf("\n+------+---------------+-----------+-----+---+---+----+------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------*****  Options *****------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------+------------------+------------+---------------+-----+------+");
    printf("\n|------+---------------+--->>      1. Find By ID                  <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      2. Find By Name                <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      3. Find By Department          <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      4. Find By Worktime            <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      5. Back To Main Menu           <<---------------+-----+------|");
    printf("\n+------+---------------+-----------------------------------------------------------+-----+------+");
    /*do the loop while user choice is 1*/
    do
    {
        printf("\nYour choice is: ");
        /*save user choice*/
        scanf("%d", &choice);
        /*use the branch to do the user requiment*/
        switch(choice)
        {
            case 1:
            {
                system("cls");
                /*move to id find funtion*/
                idFind();
                break;
            }
            case 2:
            {
                system("cls");
                /*move to name find funtion*/
                nameFind();
                break;
            }
            case 3:
            {
                system("cls");
                /*move to department find funtion*/
                dpmtFind();
                break;
            }
            case 4:
            {
                system("cls");
                /*move to time find funtion*/
                timeFind();
                break;
            }       
            case 5:
            {
                /*come back main menu*/
                mainMenu();
                break;
            }
            /*wrong choice*/
            default:
            {
                system("cls");
                printf("\nWrong Selection!");
                printf("\nType any key to come back Options menu");
                getch();
                /*move to find option funtion*/
                findOptions();
                break;
            }
        }
    }
    while (1);
}

/*start new funtion to find ID*/
void idFind()
{
    /*transport struct pointer to this funtion*/
    /*struct pointer in this funtion is check poiter*/
    struct stData * check;
    /*create new variable*/
    /*go to save user choice*/
    /*count to check the number of the staff in this group*/
    /*idFind to save data enterred from keyboard*/
    int idFind, go, count = 0;
    /*start the branch command*/
    /*if the list has no staff notificate to user*/
    if(gNumOfStaff == 0)
    {
        system("cls");
        /*notification*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        getch();
        /*come back main menu*/
        mainMenu();
    }
    /*else we do the main thing in this funtion*/
    system("cls");
    printf("Enter the ID whose you want to find: ");
    /*save ID want to search*/
    scanf("%d", &idFind);
    /*struct pointer start at the first position*/
    check = first;
    /*when pointer check not point to NULL*/
    while(check != NULL)
    {
        /*check ID to find suitable data*/
        if(check->ID == idFind)
        {
            count++;
            system("cls");
            /*print basic information of this staff*/
            printf("\n\nStaff's Information:");
            printf("\nID: %d", check->ID);
            printf("\nName: %s", check->name);
            printf("\nSex: ");
            /*check gentle*/
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
            printf("\nStart working time: %d", check->stTime);
            printf("\nSalary: %d USD", check->sal);
            printf("\nEnglish level: %s", check->elv);
            break;
        }
        else
        {
            /*move to the next pointer*/
            check = check->pNext;
        }
    }
    /*print notification to user when no exist this department*/
    if(count == 0)
    {
        printf("\nSorry, we can't find this staff in the list");
    }
    printf("\n\n\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    printf("\nYour choice is: ");
    /*save user choise*/
    scanf("%d", &go);
    if(go == 1)
    {
        /*come back main menu*/
        mainMenu();
    }
    else if(go == 2)
    {
        /*move to find option funtion*/
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        free(first);
        printf("Thank for using");
        getch();
        /*exit this funtion*/
        exit(0);
    }
}

/*start new funtion to find name*/
void nameFind()
{
    /*transport struct pointer to this funtion*/
    /*struct pointer in this funtion is check poiter*/
    struct stData * check;
    /*create new variable*/
    /*go to save user choice*/
    /*count to check the number of the staff in this group*/
    int go;
    static int count = 0;
    /*create new char variable to save name want to search*/
    char tempName[30];
    /*start the branch command*/
    /*if the list has no staff notificate to user*/
    if(gNumOfStaff == 0)
    {
        system("cls");
        /*notification*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        getch();
        /*come back main menu*/
        mainMenu();
    }
    /*else we do the main thing in this funtion*/
    system("cls");
    printf("Enter the name whose you want to find: ");
    fflush(stdin);
    /*save name want to search*/
    gets(tempName);
    /*struct pointer start at the first position*/
    check = first;
    /*when pointer check not point to NULL*/
    while(check != NULL)
    {
        /*compare name to find suitable data*/
        if(checkToFind(tempName, check->name))
        {
            count++;
            /*print basic information of this staff*/
            printf("\nStaff[%d]'s Information:", count);
            printf("\nID: %d", check->ID);
            printf("\nName: %s", check->name);
            printf("\nSex: ");
            /*check gentle*/
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
            printf("\nStart working time: %d", check->stTime);
            printf("\nSalary: %d USD", check->sal);
            printf("\nEnglish level: %s", check->elv);
            printf("\n\n");
        }
        /*move to the next pointer*/
        check = check->pNext;
    }
    /*print notification to user when no exist this department*/
    if(count == 0)
    {
        printf("\nSorry, we can't find this staff in the list");
    }
    printf("\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    printf("\nYour choice is: ");
    /*save user choise*/
    scanf("%d", &go);
    if(go == 1)
    {
        /*come back main menu*/
        mainMenu();
    }
    else if(go == 2)
    {
        /*move to find option funtion*/
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        free(first);
        printf("Thank for using");
        getch();
        /*exit this funtion*/
        exit(0);
    }
}

/*start new funtion to find department*/
void dpmtFind()
{
    /*transport struct pointer to this funtion*/
    /*struct pointer in this funtion is check poiter*/
    struct stData * check;
    /*create new variable*/
    /*go to save user choice*/
    /*count to check the number of the staff in this group*/
    int go;
    static int count = 0;
    /*create new char variable to save department want to search*/
    char tempDep[30];
    /*start the branch command*/
    /*if the list has no staff notificate to user*/
    if(gNumOfStaff == 0)
    {
        system("cls");
        /*notification*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        getch();
        /*come back main menu*/
        mainMenu();
    }
    /*else we do the main thing in this funtion*/
    system("cls");
    printf("Enter the department which you want to find: ");
    fflush(stdin);
    /*save department want to search*/
    gets(tempDep);
    /*struct pointer start at the first position*/
    check = first;
    /*when pointer check not point to NULL*/
    while(check != NULL)
    {
        /*compare department to find suitable data*/
        if(checkToFind(tempDep, check->dpment))
        {
            count++;
            /*print basic information of this staff*/
            printf("\nStaff[%d]'s Information:", count);
            printf("\nID: %d", check->ID);
            printf("\nName: %s", check->name);
            printf("\nSex: ");
            /*check gentle*/
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
            printf("\nStart working time: %d", check->stTime);
            printf("\nSalary: %d USD", check->sal);
            printf("\nEnglish level: %s", check->elv);
            printf("\n\n");
        }
        /*move to the next pointer*/
        check = check->pNext;
    }
    /*print notification to user when no exist this department*/
    if(count == 0)
    {
        printf("\nSorry, we can't find this staff in the list");
    }
    printf("\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    printf("\nYour choice is: ");
    /*save user choise*/
    scanf("%d", &go);
    if(go == 1)
    {
        /*come back main menu*/
        mainMenu();
    }
    else if(go == 2)
    {
        /*move to find option funtion*/
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        free(first);
        printf("Thank for using");
        getch();
        /*exit this funtion*/
        exit(0);
    }
}

/*start funtion search work time*/
void timeFind()
{
    /*transport struct pointer to this funtion*/
    /*struct pointer in this funtion is check poiter*/
    struct stData * check;
    /*create new variable*/
    /*go to save user choice*/
    /*time to save group work time*/
    /*count to check the number of the staff in this group*/
    int go, time;
    static int count = 0;
    /*start the branch command*/
    /*if the list has no staff notificate to user*/
    if(gNumOfStaff == 0)
    {
        system("cls");
        /*notification*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        getch();
        /*come back main menu*/
        mainMenu();
    }
    /*else we do the main thing in this funtion*/
    system("cls");
    printf("We divide whole staffs into 3 Group:");
    printf("\nGroup 1: less than 3 years experience");
    printf("\nGroup 2: 3 - 5 years experience");
    printf("\nGroup 3: more than 5 years experience");
    printf("\nEnter the Group you want to find: Group ");
    /*save the group work time user want to check*/
    scanf("%d", &time);
    /*check user choise*/
    /*invalid user choice situation*/
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
    /*if user's choice is valid*/
    /*struct pointer start at the first position*/
    check = first;
    /*start search group base on user choice*/
    if(time == 1)
    {
        /*clear screen*/
        system("cls");
        /*when pointer check not point to NULL*/    
        while(check != NULL)
        {
            /*count work time and compare with the group*/
            if((YEAR - check->stTime) < 3)
            {
                count++;
                /*print basic information of this staff*/
                printf("\nStaff[%d]'s information:", count);
                printf("\nID: %d", check->ID);
                printf("\nName: %s", check->name);
                printf("\nSex: ");
                /*check gentle*/
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
                printf("\nStart working time: %d", check->stTime);
                printf("\nSalary: %d USD", check->sal);
                printf("\nEnglish level: %s", check->elv);
                printf("\n\n");
            }
            /*move to next pointer to check*/
            check = check->pNext;  
        }
        /*if not have any staff in this group notificate to user*/
        if(count == 0)
        {
            printf("\nThere is no suitable record to this Group");
        }   
    }
    else if(time == 2)
    {
        /*clear screen*/
        system("cls");
        /*when pointer check not point to NULL*/    
        while(check != NULL)
        {
            /*count work time and compare with the group*/
            if((YEAR - check->stTime) <= 5 && (YEAR - check->stTime) >= 3)
            {
                count++;
                /*print basic information of this staff*/
                printf("\nStaff[%d]'s information:", count);
                printf("\nID: %d", check->ID);
                printf("\nName: %s", check->name);
                printf("\nSex: ");
                /*check gentle*/
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
                printf("\nStart working time: %d", check->stTime);
                printf("\nSalary: %d USD", check->sal);
                printf("\nEnglish level: %s", check->elv);
                printf("\n\n");
            }
            /*move to next pointer to check*/
            check = check->pNext;
        }
        /*if not have any staff in this group notificate to user*/
        if(count == 0)
        {
            printf("\nThere is no suitable record to this Group");
        }   
    }
    else
    {
        /*clear screen*/
        system("cls");
        /*when pointer check not point to NULL*/    
        while(check != NULL)
        {
            /*count work time and compare with the group*/
            if((YEAR - check->stTime) > 5)
            {
                count++;
                /*print basic information of this staff*/
                printf("\nStaff[%d]'s information:", count);
                printf("\nID: %d", check->ID);
                printf("\nName: %s", check->name);
                printf("\nSex: ");
                /*check gentle*/
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
                printf("\nStart working time: %d", check->stTime);
                printf("\nSalary: %d USD", check->sal);
                printf("\nEnglish level: %s", check->elv);
                printf("\n\n");
            }
            /*move to next pointer to check*/
            check = check->pNext;
        }
        if(count == 0)
        {
            /*if not have any staff in this group notificate to user*/
            printf("\nThere is no suitable record to this Group");
        }   
    }
    /*print notification to user*/
    printf("\nType 1 to show Main Menu, 2 to show Finding Options or 3 to exit program");
    /*save user choice*/
    printf("\nYour choice is: ");
    scanf("%d", &go);
    /*do something suitable with user choice*/
    if(go == 1)
    {
        /*come back main menu*/
        mainMenu();
    }
    else if(go == 2)
    {
        /*move to funtion find option*/
        findOptions();
    }
    else if(go == 3)
    {
        system("cls");
        /*free memory pointer*/
        free(first);
        printf("Thank for using");
        getch();
        /*exit funtion*/
        exit(0);
    }
}

/*start new funtion*/
/*this funtion will save user choice to make some update about staff information*/
void dataUpdate()
{
    /*create new variable to save user choice*/
    int choice;
    /*clear screen*/
    system("cls");
    /*print menu funtion of the feather update*/
    printf("%s's stafves management:", strupr(cpny));
    printf("\n+------+---------------+-----------+----+---+---+----+-------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------******Update******--------------+---------------+-----+------+");
    printf("\n+------+---------------+-----------+------------------+------------+---------------+-----+------+");
    printf("\n|------+---------------+--->>      1. Update Department           <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      2. Update Duty                 <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      3. Update Address              <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      4. Update Salary               <<---------------+-----+------|");
    printf("\n|------+---------------+--->>      5. Back To Main Menu           <<---------------+-----+------|");
    printf("\n+------+---------------+-----------------------------------------------------------+-----+------+");
    /*start the loop to make diversity the update funtion*/
    do
    {
        /*save user choise*/
        printf("\nYour choice is: ");
        scanf("%d", &choice);
        /*start make branch command to do something suitable with user choice*/
        switch(choice)
        {
            case 1:
            {
                system("cls");
                /*move to funtion update department*/
                depUpdate();
                /*exit branch command*/
                break;
            }
            case 2:
            {
                system("cls");
                /*move to funtion update duty*/
                dutyUpdate();
                /*exit branch command*/
                break;
            }
            case 3:
            {
                system("cls");
                /*move to funtion update address*/
                addUpdate();
                /*exit branch command*/
                break;
            }
            case 4:
            {
                system("cls");
                /*move to funtion update salary*/
                salUpdate();
                /*exit branch command*/
                break;
            }     
            case 5:
            {
                /*come back main menu*/
                mainMenu();
                /*exit branch command*/
                break;
            }
            /*wrong choise*/
            default:
            {
                system("cls");
                printf("\nWrong Selection!");
                printf("\nType any key to come back Update menu");
                getch();
                /*come back menu update*/
                dataUpdate();
                /*exit branch command*/
                break;
            }
        }
    }
    /*if user choise after each funtion is 1 we continue funtion update infomation*/
    while (1);
}

/* start funtion update department of staff*/
void depUpdate()
{
    /*transport struct pointer to this funtion*/
    /*in this funtion struct pointer has new name is change pointer*/ 
    struct stData *change;
    /*create new variable*/
    /*supID is used to save ID template when user enter from keyboard*/
    /*supID is used to compare with ID of staff in struct poiter to find staff need to update department*/
    /*choise is used to save user's action*/
    int supID, choice;
    /*struct pointer start at the first position*/
    change = first;
    /*check number of staff*/
    /*if in the list not have staff we have no information to update*/
    if(gNumOfStaff == 0)
    {
        /*clear screen*/
        system("cls");
        /*notificate to user*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        /*stop program to show notification to user*/
        getch();
        /*comeback main menu*/
        mainMenu();
    }
    /*if in the list have any staff information we continue to the next step*/
    /*make screen clearer*/
    system("cls");
    /*start process*/
    printf("Staff ID is used to support update process");
    /*input supID*/
    printf("\nType the ID whose you want to update his or her data: ");
    /*save supID*/
    scanf("%d", &supID);
    /*start the loop to find staff have information need to update*/
    /*while poiter change point to valueable different NULL pointer*/
    while(change != NULL)
    {
        /*if ID have the same value with supID we start update*/
        if(change->ID == supID)
        {
            /*check gentle of this staff to show information*/
            /*if sex = 1 show require with gentle male*/
            if(change->sex == 1)
            {
                printf("\nHis new department is: ");
                fflush(stdin);
                /*save new department*/
                gets(change->dpment);
                stdization(change->dpment);
                /*check this new department with funtion checkChr*/
                while(!checkChr(change->dpment))
                {
                    printf("Invalid Department, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid department*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new department is: ");
                        fflush(stdin);
                        /*save new department*/
                        gets(change->dpment);
                        stdization(change->dpment);
                    }
                    /*if user choise = 0 requied user enter valid department*/
                    else if(choice == 0)
                    {
                        printf("His new department is: ");
                        fflush(stdin);
                        /*save new department*/
                        gets(change->dpment);
                        stdization(change->dpment);
                    }
                }
            }
            else
            {
                printf("\nHer new department is: ");
                fflush(stdin);
                /*save new department*/
                gets(change->dpment);
                stdization(change->dpment);
                /*check this new department with funtion checkChr*/
                while(!checkChr(change->dpment))
                {
                    printf("Invalid Department, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid department*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new department is: ");
                        fflush(stdin);
                        /*save new department*/
                        gets(change->dpment);
                        stdization(change->dpment);
                    }
                    /*if user choise = 0 requied user enter valid department*/
                    else if(choice == 0)
                    {
                        printf("Her new department is: ");
                        fflush(stdin);
                        /*save new department*/
                        gets(change->dpment);
                        stdization(change->dpment);
                    }
                }
            }
            /*break the loop*/
            break;
        }
        /*if supID not have the same value with this ID next to another staff*/
        else
        {
            /*next pointer*/
            change = change->pNext;
        }
    }
    /*if poiter change point to valueable different NULL pointer*/
    if(change == NULL)
    {
        /*show notification*/
        printf("\nThere is no suitable record in the list!");
    }
    /*show a new menu to user*/
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    /*save user choise*/
    scanf("%d", &choice);
    /*move to new funtion base on user choise*/
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
        /*free memory*/
        free(first);
        printf("Thank for using");
        /*exit this program*/
        exit(0);
    }
}

/*start new funtion to update staff's duty*/
void dutyUpdate()
{
    /*transport struct pointer to this funtion*/
    /*in this funtion struct pointer has new name is change pointer*/ 
    struct stData *change;
    /*create new variable*/
    /*supID is used to save ID template when user enter from keyboard*/
    /*supID is used to compare with ID of staff in struct poiter to find staff need to update department*/
    /*choise is used to save user's action*/
    int supID, choice;
    /*struct pointer start at the first position*/
    change = first;
    /*check number of staff*/
    /*if in the list not have staff we have no information to update*/
    if(gNumOfStaff == 0)
    {
        /*clear screen*/
        system("cls");
        /*notificate to user*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        /*stop program to show notification to user*/
        getch();
        /*comeback main menu*/
        mainMenu();
    }
    /*if in the list have any staff information we continue to the next step*/
    /*make screen clearer*/
    system("cls");
    /*start process*/
    printf("Staff ID is used to support update process");
    /*input supID*/
    scanf("%d", &supID);
    /*save supID*/
    printf("\nType the ID whose you want to update his or her data: ");
    scanf("%d", &supID);
    /*start the loop to find staff have information need to update*/
    /*while poiter change point to valueable different NULL pointer*/
    while(change != NULL)
    {
        /*if ID have the same value with supID we start update*/
        if(change->ID == supID)
        {
            /*check gentle of this staff to show information*/
            /*if sex = 1 show require with gentle male*/
            if(change->sex)
            {
                printf("\nHis new duty is: ");
                fflush(stdin);
                /*save new information*/
                gets(change->duty);
                stdization(change->duty);
                /*check this new information with funtion checkChr*/
                while(!checkChr(change->duty))
                {
                    printf("Invalid Duty, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid information*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new duty is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->duty);
                        stdization(change->duty);
                    }
                    /*if user choise = 0 requied user enter valid information*/
                    else if(choice == 0)
                    {
                        printf("His new duty is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->duty);
                        stdization(change->duty);
                    }
                }
            }
            else
            {
                printf("\nHer new Duty is: ");
                fflush(stdin);
                /*save new information*/
                gets(change->duty);
                stdization(change->duty);
                /*check this new information with funtion checkChr*/
                while(!checkChr(change->duty))
                {
                    printf("Invalid Duty, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid information*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new Duty is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->duty);
                        stdization(change->duty);
                    }
                    /*if user choise = 0 requied user enter valid information*/
                    else if(choice == 0)
                    {
                        printf("Her new Duty is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->duty);
                        stdization(change->duty);
                    }
                }
            }
            /*break the loop*/
            break;
        }
        /*if supID not have the same value with this ID next to another staff*/
        else
        {
            /*next pointer*/
            change = change->pNext;
        }
    }
    /*if poiter change point to valueable different NULL pointer*/
    if(change == NULL)
    {
        /*show notification*/
        printf("\nThere is no suitable record in the list!");
    }
    /*show a new menu to user*/
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    /*save user choise*/
    scanf("%d", &choice);
    /*move to new funtion base on user choise*/
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
        /*free memory*/
        free(first);
        printf("Thank for using");
        /*exit this program*/
        exit(0);
    }
}

/*start new funtion to update staff's information*/
void addUpdate()
{
    /*transport struct pointer to this funtion*/
    /*in this funtion struct pointer has new name is change pointer*/
    struct stData *change;
    /*create new variable*/
    /*supID is used to save ID template when user enter from keyboard*/
    /*supID is used to compare with ID of staff in struct poiter to find staff need to update department*/
    /*choise is used to save user's action*/
    int supID, choice;
    /*struct pointer start at the first position*/
    change = first;
    /*check number of staff*/
    /*if in the list not have staff we have no information to update*/
    if(gNumOfStaff == 0)
    {
        /*clear screen*/
        system("cls");
        /*notificate to user*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        /*stop program to show notification to user*/
        getch();
        /*comeback main menu*/
        mainMenu();
    }
    /*if in the list have any staff information we continue to the next step*/
    /*make screen clearer*/
    system("cls");
    /*start process*/
    printf("Staff ID is used to support update process");
    /*input supID*/
    printf("\nType the ID whose you want to update his or her data: ");
    /*save supID*/
    scanf("%d", &supID);
    /*start the loop to find staff have information need to update*/
    /*while poiter change point to valueable different NULL pointer*/
    while(change != NULL)
    {
        /*if ID have the same value with supID we start update*/
        if(change->ID == supID)
        {
            /*check gentle of this staff to show information*/
            /*if sex = 1 show require with gentle male*/
            if(change->sex)
            {
                printf("\nHis new address is: ");
                fflush(stdin);
                /*save new information*/
                gets(change->add);
                stdization(change->add);
                /*check this new information with funtion checkChr*/
                while(strlen(change->add) > 100)
                {
                    printf("Invalid Address, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid information*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new address is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->add);
                        stdization(change->add);
                    }
                    /*if user choise = 0 requied user enter valid information*/
                    else if(choice == 0)
                    {
                        printf("His new address is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->add);
                        stdization(change->add);
                    }
                }
            }
            else
            {
                printf("\nHer new Address is: ");
                fflush(stdin);
                /*save new information*/
                gets(change->add);
                /*check this new information with funtion checkChr*/
                while(strlen(change->add) > 100)
                {
                    printf("Invalid Address, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid information*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new Address is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->add);
                        stdization(change->add);
                    }
                    /*if user choise = 0 requied user enter valid information*/
                    else if(choice == 0)
                    {
                        printf("Her new Address is: ");
                        fflush(stdin);
                        /*save new information*/
                        gets(change->add);
                        stdization(change->add);
                    }
                }
            }
            /*break the loop*/
            break;
        }
        /*if supID not have the same value with this ID next to another staff*/
        else
        {
            /*next pointer*/
            change = change->pNext;
        }
    }
    /*if poiter change point to valueable different NULL pointer*/
    if(change == NULL)
    {
        /*show notification*/
        printf("\nThere is no suitable record in the list!");
    }
    /*show a new menu to user*/
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    /*save user choise*/
    scanf("%d", &choice);
    /*move to new funtion base on user choise*/
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
        /*free memory*/
        free(first);
        printf("Thank for using");
        /*exit this program*/
        exit(0);
    }
}

/*start new funtion to update staff's information*/
void salUpdate()
{
    /*transport struct pointer to this funtion*/
    /*in this funtion struct pointer has new name is change pointer*/
    struct stData *change;
    /*create new variable*/
    /*supID is used to save ID template when user enter from keyboard*/
    /*supID is used to compare with ID of staff in struct poiter to find staff need to update department*/
    /*choise is used to save user's action*/
    int supID, choice;
    /*struct pointer start at the first position*/
    change = first;
    /*check number of staff*/
    /*if in the list not have staff we have no information to update*/
    if(gNumOfStaff == 0)
    {
        /*clear screen*/
        system("cls");
        /*notificate to user*/
        printf("ERROR:<There is no record in the list! You have to have data first>");
        /*stop program to show notification to user*/
        getch();
        /*comeback main menu*/
        mainMenu();
    }
    /*if in the list have any staff information we continue to the next step*/
    /*make screen clearer*/
    system("cls");
    /*start process*/
    printf("Staff ID is used to support update process");
    /*input supID*/
    printf("\nType the ID whose you want to update his or her data: ");
    /*save supID*/
    scanf("%d", &supID);
    /*start the loop to find staff have information need to update*/
    /*while poiter change point to valueable different NULL pointer*/
    while(change != NULL)
    {
        /*if ID have the same value with supID we start update*/
        if(change->ID == supID)
        {
            /*check gentle of this staff to show information*/
            /*if sex = 1 show require with gentle male*/
            if(change->sex)
            {
                printf("\nHis new salary is: ");
                /*save new information*/
                scanf("%d", &change->sal);
                /*check information just inputed*/
                while(change->sal < 176)
                {
                    printf("Invalid sal, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid information*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("His new salary is: ");
                        /*save new information*/
                        scanf("%d", &change->sal);
                    }
                    /*if user choise = 0 requied user enter valid information*/
                    else if(choice == 0)
                    {
                        printf("His new salary is: ");
                        /*save new information*/
                        scanf("%d", &change->sal);
                    }
                }
            }
            else
            {
                printf("\nHer new salary is: ");
                /*save new information*/
                scanf("%d", &change->sal);
                while(change->sal < 176)
                {
                    printf("Invalid salary, type 1 to view instruction or type 0 to type again!\nYour choice is: ");
                    /*save user choise to next to next step*/
                    scanf("%d", &choice);
                    /*if choise = 1 show user intruction*/
                    /*then requied user enter valid information*/
                    if(choice == 1)
                    {
                        system("cls");
                        instruction();
                        printf("Type any key to continue typing\n");
                        getch();
                        system("cls");
                        printf("Her new salary is: ");
                        /*save new information*/
                        scanf("%d", &change->sal);
                    }
                    /*if user choise = 0 requied user enter valid information*/
                    else if(choice == 0)
                    {
                        printf("Her new salary is: ");
                        /*save new information*/
                        scanf("%d", &change->sal);
                    }
                }
            }
            /*break the loop*/
            break;
        }
        /*if supID not have the same value with this ID next to another staff*/
        else
        {
            /*next pointer*/
            change = change->pNext;
        }
    }
    /*if poiter change point to valueable different NULL pointer*/
    if(change == NULL)
    {
        /*show notification*/
        printf("\nThere is no suitable record in the list!");
    }
    /*show a new menu to user*/
    printf("\n\nType 1 to get back update menu, 2 to main menu, 3 to exit program: ");
    /*save user choise*/
    scanf("%d", &choice);
    /*move to new funtion base on user choise*/
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
        /*free memory*/
        free(first);
        printf("Thank for using");
        /*exit this program*/
        exit(0);
    }
}

/*start new funtion to update staff's information*/
void allPayment()
{
    /*transport struct pointer to this funtion*/
    /*in this funtion struct pointer has new name is paypointer*/
   struct stData *pay;
   /*create new variable to save sum of staff salary*/
   long all = 0;
   /*struct pointer start at the first position*/
   pay = first;
   /*while poiter change point to valueable different NULL pointer*/
   while(pay != NULL)
   {
        /*count sum of salary*/
        all += pay->sal;
        /*move to next pointer*/
        pay = pay->pNext;
   }
   /*clear screen*/
   system("cls");
   /*show sum of salary*/
   printf("Amount of salary your company need to pay per month is: %ld USD", all);
   printf("\nType any key to get back Main Menu\n");
   /*stop program to show notification*/
   getch();
   /*come back main menu*/
   mainMenu();
}

/*This function is used to support giving Human Resource Decline Prediction*/
int getYear(char *str)
{
    int year = 0;
    /*Date of birth has format: dd/mm/yyyy
    So the digits express the year is four last digits*/
    /*In ASCII code board, numbers 0 - 9 are express by 48 - 57 
    So the statement *(str + i) - 48 help us change a digit character into number*/
    year += (*(str + 6) - 48) * 1000;
    year += (*(str + 7) - 48) * 100;
    year += (*(str + 8) - 48) * 10;
    year += (*(str + 9) - 48);
    return year;
}

/*This function is used to give Human Resource Decline Prediction in a year typed from keyboard*/
void HRDecPredict()
{
    struct stData *dec;
    /*The pointer 'dec' is used to point to nodes in the list*/
    static int count = 0, i = 1;
    int predict;
    int choice;
    /*variable 'count' is used to count the quantity of stafves who will retire in the year you type
               'i' is used to express ordinal of stafves who will retire
               'predict' is the mentioned year
               'choice' is used to express user choice to show retirement list or not
    */
    dec = first;
    printf("Enter the year you want to view: ");
    scanf("%d", &predict);
    while(predict < 2018)
    {
        system("cls");
        printf("Now is 2018. Your request can't be accepted because you haven't had data at that point of time");
        printf("\nType again: ");
        scanf("%d", &predict);
    }
    /*If dec = NULL, show notification to user*/
    if(!dec)
    {
        printf("\nERROR:<There is no record in the list! You have to have data first>");
        printf("\n\nType any key to get back Main Menu\n");
        getch();
        mainMenu();
    }
    /*If the list isn't empty, check to find stafves who will retire in that year*/
    while(dec)
    {
        if(dec->sex)
        {
            if(predict - getYear(dec->birth) >= 59)
            {
                count++;
            }
        }
        else
        {
            if(predict - getYear(dec->birth) >= 54)
            {
                count++;
            }
        }
        dec = dec->pNext;
    }
    /*If count = 0, that mean there is no staff's going to retire in that year*/
    if(!count)
    {
        printf("\nThere is no staff's going to retire in that year");
        printf("\nType any key to get back Main Menu\n");
        getch();
        mainMenu();
    }
    /*If the retirement list isn't empty, show notification to user*/
    else
    {
        printf("\nThere is %.2f percent of stafves will retire in that year", 100 * (float)count / gNumOfStaff);
        /*Ask if user want show retirement list*/
        printf("\nDo you wanna know who they are? Type 1 to view or type 0 to skip: ");
        scanf("%d", &choice);
        /*If they want*/
        if(choice == 1)
        {
            dec = first;
            while(dec)
            {
                /*If the staff is male, retirement age is 60*/
                if(dec->sex)
                {
                    if(predict - getYear(dec->birth) >= 59)
                    {
                        printf("\nStaff %d:", i);
                        printf("\nID: %d", dec->ID);
                        printf("\nName: %s", dec->name);
                        printf("\nSex: Male");
                        printf("\nDepartment: %s", dec->dpment);
                        printf("\nDuty: %s", dec->duty);
                        printf("\nDate of birth: %s", dec->birth);
                        printf("\nAddress: %s", dec->add);
                        printf("\nPhone number: %s", dec->phNum);
                        printf("\nEnglish level: %s", dec->elv);
                        printf("\nEmail: %s", dec->mail);
                        printf("\nStart working time: %d", dec->stTime);
                        printf("\nSalary: %d USD", dec->sal);
                        printf("\n\n");
                        i++;
                    }
                }
                /*If the staff is male, retirement age is 55*/
                else
                {
                    if(predict - getYear(dec->birth) >= 54)
                    {
                        printf("\nStaff %d:", i);
                        printf("\nID: %d", dec->ID);
                        printf("\nName: %s", dec->name);
                        printf("\nSex: Female");
                        printf("\nDepartment: %s", dec->dpment);
                        printf("\nDuty: %s", dec->duty);
                        printf("\nDate of birth: %s", dec->birth);
                        printf("\nAddress: %s", dec->add);
                        printf("\nPhone number: %s", dec->phNum);
                        printf("\nEnglish level: %s", dec->elv);
                        printf("\nEmail: %s", dec->mail);
                        printf("\nStart working time: %d", dec->stTime);
                        printf("\nSalary: %d USD", dec->sal);
                        printf("\n\n");
                        i++;
                    }
                }
                dec = dec->pNext;
            }
            /*Get back Main Menu*/
            printf("\nType any key to get back Main Menu\n");
            getch();
            mainMenu();
        }
        /*If user don't want to view the list, get back Main Menu*/
        else if(!choice)
        {
            printf("\nType any key to get back Main Menu\n");
            getch();
            mainMenu();
        }
        /*If choice is neither 1 nor 0, that will be count as wrong choice*/
        else
        {
            printf("\nChoose again: ");
            scanf("%d", &choice);
        }
    }
}
