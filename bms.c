#include <stdio.h>
#include <string.h>
struct account_information
{
    int accNo;
    char name[50];
    float balance;
};
void create();
void display();
void search();
void deposit();
void withdraw();
int main()
{
    // printf("\n\n\n\n\n");
    int userinput;
    int i;
    
    
    for(i = 0; i < 103; i++){
        printf("=");
    }
    printf("\n");

    
    printf("\n|                                   BANK MANAGEMENT SYSTEM                                            |\n\n");

    for(i = 0; i < 103; i++){
        printf("=");
    }
    printf("\n");

  
    printf("|   # MENU OPERATIONS                  |   # STATUS PANEL                |  # Additonal Information   |\n");

    for(i = 0; i < 103; i++){
        printf("-");
    }
    printf("\n");

    
    printf("|  * Create Account                    | Database : CONNECTED            | Branch Status : OPEN       |\n");
    printf("|  * Display All Accounts              | Server   : RUNNING              | ATM Network   : ONLINE     |\n");
    printf("|  * Search Account                    | Security : HIGH LEVEL           | Interest Rate : 6.5%%       |\n");
    printf("|  * Deposit Money                     | Backup   : ENABLED              | Audit Status  : COMPLETED  |\n");
    printf("|  * Withdraw Money                    | Logs     : ACTIVE               | Secure Alerts : 00         |\n");
    printf("|  * Exit                              | Traffic  : NORMAL               | Day Report    : PENDING    |\n");

    for(i = 0; i < 103; i++)
        printf("-");
    printf("\n\n");

  
    printf("Welcome, Administrator.\n");
	printf("The banking system is active and ready to process account operations and transactions.\n");
	printf("Please select an option from the menu below.\n\n");
	printf("================================ MAIN MENU ================================\n");
    printf("\n1. Create Account\n\n");
    printf("2. Display All Accounts\n\n");
    printf("3. Search Account\n\n");
    printf("4. Deposit Money\n\n");
    printf("5. Withdraw Money\n\n");
    printf("6. Exit\n");
    do
    {
        printf("-------------------------------------\nEnter your choice: ");
        scanf("%d", &userinput);

        switch(userinput)
        {
            case 1:
                create();
                break;

            case 2:
                display();
                break;

            case 3:
                search();
                break;

            case 4:
                deposit();
                break;

            case 5:
                withdraw();
                break;

            case 6:
                printf("\n Thank You!!!\n");
                break;

            default:
                printf("\nInvalid Choice.\n");
        }

    } while(userinput != 6);

    printf("\n\n\n");
    for(i = 0; i < 103; i++)
        printf("=");
    printf("\n");

    return 0;
}


/* ================= CREATE ACCOUNT ================= */
void create()
{
    FILE *fp = fopen("bank.txt", "a+");
    struct account_information a, temp;
    int exists = 0;

    printf("\nEnter Account Number: ");
    scanf("%d", &a.accNo);

    while(fscanf(fp, "%d %s %f", &temp.accNo, temp.name, &temp.balance) != EOF)
    {
        if(temp.accNo == a.accNo)
        {
            exists = 1;
        }
    }

    if(exists)
    {
        printf("Account already exists!\n");
        fclose(fp);
        return;
    }

    printf("Enter Name: ");
    scanf("%s", a.name);

    printf("Enter Initial Balance: ");
    scanf("%f", &a.balance);

    fprintf(fp, "%d %s %f\n", a.accNo, a.name, a.balance);

    fclose(fp);

    printf("Account created successfully!\n");
}

/* =============== DISPLAY ACCOUNTS ================ */
void display()
{
    FILE *fp = fopen("bank.txt", "r");
    struct account_information a;

    if(fp == NULL)
    {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n----- ACCOUNT DETAILS -----\n");

    while(fscanf(fp, "%d %s %f", &a.accNo, a.name, &a.balance) != EOF)
    {
        printf("Account No : %d\n", a.accNo);
        printf("Name       : %s\n", a.name);
        printf("Balance    : %f\n\n", a.balance);
    }

    fclose(fp);
}

/* ================ SEARCH ACCOUNT ============= */
void search()
{
    FILE *fp = fopen("bank.txt", "r");
    struct account_information a;
    int id, found = 0;

    printf("\nEnter account number to search: ");
    scanf("%d", &id);

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    while(fscanf(fp, "%d %s %f", &a.accNo, a.name, &a.balance) != EOF)
    {
        if(a.accNo == id)
        {
            printf("\nAccount Found!\n");
            printf("Account No : %d\n", a.accNo);
            printf("Name       : %s\n", a.name);
            printf("Balance    : %f\n", a.balance);
            found = 1;
        }
    }

    if(!found)
        printf("Account not found!\n");

    fclose(fp);
}

/* ================= DEPOSIT MONEY ======== */
void deposit()
{
    FILE *fp = fopen("bank.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct account_information a;
    int id, found = 0;
    float amount;

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\nEnter account number: ");
    scanf("%d", &id);

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    while(fscanf(fp, "%d %s %f", &a.accNo, a.name, &a.balance) != EOF)
    {
        if(a.accNo == id)
        {
            a.balance += amount;
            found = 1;
        }

        fprintf(temp, "%d %s %f\n", a.accNo, a.name, a.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("bank.txt");
    rename("temp.txt", "bank.txt");

    if(found)
        printf("Deposit successful!\n");
    else
        printf("Account not found!\n");
}

/* ========== WITHDRAW MONEY ================= */
void withdraw()
{
    FILE *fp = fopen("bank.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    struct account_information a;
    int id, found = 0;
    float amount;

    if(fp == NULL)
    {
        printf("No records found!\n");
        return;
    }

    printf("\nEnter account number: ");
    scanf("%d", &id);

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    while(fscanf(fp, "%d %s %f", &a.accNo, a.name, &a.balance) != EOF)
    {
        if(a.accNo == id)
        {
            found = 1;

            if(amount <= a.balance)
            {
                a.balance -= amount;
                printf("Withdrawal successful!\n");
            }
            else
            {
                printf("Insufficient balance!\n");
            }
        }

        fprintf(temp, "%d %s %f\n", a.accNo, a.name, a.balance);
    }

    fclose(fp);
    fclose(temp);

    remove("bank.txt");
    rename("temp.txt", "bank.txt");
    if(!found)
        printf("Account not found!\n");
}
