#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_ACCOUNTS 100

struct Account {
    int accountNumber;
    char name[50];
    char password[4];
    float balance;
};

void waiting(unsigned int mseconds)
{
	clock_t limit = mseconds + clock();
	while (limit > clock());
}

int accountCount = 0;
struct Account accounts[MAX_ACCOUNTS];

//presenting a welcome screen for the user
void welcome()
{
	printf("\n\t\t\t\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n");
	printf("\t\t\t\xBA          \xFE\xFE\xFE     \xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE  \xFE         \xFE  \xBA\n");
	printf("\t\t\t\xBA         \xFE\xFE\xFE\xFE\xFE         \xFE\xFE\xFE       \xFE\xFE       \xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA        \xFE\xFE\xFE \xFE\xFE\xFE        \xFE\xFE\xFE       \xFE\xFE\xFE     \xFE\xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA       \xFE\xFE\xFE   \xFE\xFE\xFE       \xFE\xFE\xFE       \xFE\xFE\xFE\xFE   \xFE\xFE\xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA      \xFE\xFE\xFE     \xFE\xFE\xFE      \xFE\xFE\xFE       \xFE\xFE \xFE\xFE \xFE\xFE \xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA     \xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE\xFE     \xFE\xFE\xFE       \xFE\xFE  \xFE\xFE\xFE  \xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA    \xFE\xFE\xFE         \xFE\xFE\xFE    \xFE\xFE\xFE       \xFE\xFE   \xFE   \xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA   \xFE\xFE\xFE           \xFE\xFE\xFE   \xFE\xFE\xFE       \xFE\xFE       \xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA  \xFE\xFE\xFE             \xFE\xFE\xFE  \xFE\xFE\xFE       \xFE\xFE       \xFE\xFE  \xBA\n");
	printf("\t\t\t\xBA                                              \xBA\n");
	printf("\t\t\t\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCDSIMULATION\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n");
	printf("\n");
}

/*
void reciept()
{
	printf("\n\t\t\t\xC9\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xC8\xBB\n");
}
*/

// Function to create a new account
void createAccount() {
    if (accountCount < MAX_ACCOUNTS) {
        struct Account newAccount;

        printf("\t\t\tEnter name: ");
        scanf("%s", newAccount.name);

        printf("\t\t\tEnter account number: ");
        scanf("%d", &newAccount.accountNumber);

        printf("\t\t\tEnter your 4-digit password: ");
        scanf("%s", newAccount.password);

        // Set the default balance to 0
        newAccount.balance = 0.0;

        accounts[accountCount] = newAccount;
        accountCount++;

        // Save the account to the file
        FILE *file = fopen("accounts.txt", "a");
        fprintf(file, "%d %s %s %.2f\n", newAccount.accountNumber, newAccount.name,
                newAccount.password, newAccount.balance);
        fclose(file);

        printf("\t\t\t_______________________________________________\n\n");
        printf("\t\t\tAccount created successfully.\n");
    } else {
        printf("\t\t\t_______________________________________________\n\n");
        printf("\t\t\tMaximum account limit reached.\n");
    }
}

/* Function to find account index by account number,
searches the account in the database and returns the account number,
return the account number if found or returns -1 if account not found*/
int findAccountIndex(int accountNumber) {
    for (int i = 0; i < accountCount; i++) {
        if (accounts[i].accountNumber == accountNumber) {
            return i;
        }
    }
    return -1;
}

/*Function to authenticate user this function takes input the account number
and the password given and runs the findaccountindex function within the function
compares the account number with the password given and returns true in the form of strcmp or false*/
bool authenticate(int accountNumber, const char *password) {
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        return strcmp(accounts[index].password, password) == 0;
    }
    return false;
}

/*Function to display account balance
this function is pretty self explanatory, it takes input the account number and printsthe balance
or prits account not found*/
void checkBalance(int accountNumber) {
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
    	printf("\t\t\t_______________________________________________\n\n");
        printf("\t\t\tYour balance: %.2f\n", accounts[index].balance);
    } else {
        printf("\t\t\tAccount not found.\n");
        printf("\t\t\t_______________________________________________\n\n");
    }
}

/*This Function simulates the action of depositing money into the account
it takes account number and the amount to be deposited as input
and deposits the money into the bank account*/
void deposit(int accountNumber, float amount) {
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        accounts[index].balance += amount;
        printf("\n\t\t\tDeposit successful.\n");
        printf("\t\t\t_______________________________________________\n\n");
        printf("\t\t\tYour New Balance : %.2f\n\n", accounts[index].balance);

        // Update the file with the new balance
        FILE *file = fopen("accounts.txt", "w");
        for (int i = 0; i < accountCount; i++) {
            fprintf(file, "%d %s %d %s %.2f\n", accounts[i].accountNumber, accounts[i].name,
                    atoi(accounts[i].password), accounts[i].password, accounts[i].balance);
        }
        fclose(file);
    } else {
        printf("\t\t\tAccount not found.\n");
    }
}

/*this Function simulates the action of withdrawing money from the bank account
this function takes the account number and amount to be withdrawn as input
this function checks and returns appropriate output if
the amount to be withdrawn exceeds the account balance*/
void withdraw(int accountNumber, float amount) {
    int index = findAccountIndex(accountNumber);
    if (index != -1) {
        if (accounts[index].balance >= amount) {
            if ((accounts[index].balance) * 0.9 <= amount) {
                printf("\n\t\t\tYour Withdrawal Amount limit reached.");
                printf("\n\t\t\t________________________________________________\n\n");
            } else {
                accounts[index].balance -= amount;
                printf("\n\t\t\tWithdrawal successful");
                printf("\n\t\t\t________________________________________________\n\n");
                printf("\t\t\tYour New balance: %.2f\n", accounts[index].balance);

                // Update the file with the new balance
                FILE *file = fopen("accounts.txt", "w");
                for (int i = 0; i < accountCount; i++) {
                    fprintf(file, "%d %s %d %s %.2f\n", accounts[i].accountNumber, accounts[i].name,
                            atoi(accounts[i].password), accounts[i].password, accounts[i].balance);
                }
                fclose(file);
            }
        } else {
            printf("\n\t\t\t________________________________________________\n\n");
            printf("\t\t\tInsufficient balance.\n");
        }
    } else {
        printf("\n\t\t\t________________________________________________\n\n");
        printf("\t\t\tAccount not found.\n");
    }
}

/*this function is made to transfer funds among account*/
void transferFunds() {
    int senderAccountNumber, receiverAccountNumber;
    char senderPassword[20];
    float amount;

    // Get sender account details
    printf("\t\t\tEnter your account number: ");
    scanf("%d", &senderAccountNumber);
    printf("\t\t\tEnter your password: ");
    scanf("%s", senderPassword);

    // Authenticate sender
    if (authenticate(senderAccountNumber, senderPassword)) {
        // Get receiver account details
        printf("\t\t\tEnter the receiver's account number: ");
        scanf("%d", &receiverAccountNumber);

        // Find sender and receiver indices
        int senderIndex = findAccountIndex(senderAccountNumber);
        int receiverIndex = findAccountIndex(receiverAccountNumber);

        if (senderIndex != -1 && receiverIndex != -1) {
            // Check if sender has sufficient balance
            printf("\t\t\tEnter the amount to transfer: ");
            scanf("%f", &amount);

            if (accounts[senderIndex].balance >= amount) {
                // Perform the transfer
                accounts[senderIndex].balance -= amount;
                accounts[receiverIndex].balance += amount;

                printf("\t\t\tTransfer successful.\n");
                printf("\t\t\tYour New Balance: %.2f\n", accounts[senderIndex].balance);

                // Update the file with the new balances
                FILE *file = fopen("accounts.txt", "w");
                for (int i = 0; i < accountCount; i++) {
                    fprintf(file, "%d %s %d %s %.2f\n", accounts[i].accountNumber, accounts[i].name,
                            atoi(accounts[i].password), accounts[i].password, accounts[i].balance);
                }
                fclose(file);
            } else {
                printf("\t\t\tInsufficient balance for the transfer.\n");
            }
        } else {
            printf("\t\t\tInvalid account numbers.\n");
        }
    } else {
        printf("\t\t\tAuthentication failed.\n");
    }
}

/*
bool askForReceipt() {
    char choice;
    printf("\t\t\tDo you want a receipt? (Y/N): ");
    scanf(" %c", &choice);
    return (choice == 'Y' || choice == 'y');
}

void generateReceipt(int accountNumber, const char *transactionType, float amount) {
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    printf("\t      TRANSACTION RECEIPT                  \n");
    printf("\t\t\t                                                             \n");
    printf("\t\t\t   Date: %02d/%02d/%4d %02d:%02d:%02d                    \n",
           localTime->tm_mday, localTime->tm_mon + 1, localTime->tm_year + 1900,
           localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
    printf("\t\t\t                                                             \n");
    printf("\t\t\t   Account Number: %d                                       \n", accountNumber);
    printf("\t\t\t   Transaction Type: %s                                     \n", transactionType);
    printf("\t\t\t   Amount: %.2f                                               \n", amount);
    printf("\t\t\t                                                             ");
}*/


//giving a menu for user-interaction
void menu()
{
    printf("\t\t\t[ 1 ] Create Account\n");
    printf("\t\t\t[ 2 ] Check Balance\n");
    printf("\t\t\t[ 3 ] Deposit\n");
    printf("\t\t\t[ 4 ] Withdraw\n");
    printf("\t\t\t[ 5 ] Transfer\n");
	printf("\t\t\t[ 6 ] Exit ATM");
	printf("\n\t\t\t________________________________________________\n\n");
    printf("\t\t\tEnter your choice: ");
}

/*the program starts here and the main function is the backbone of the program*/
int main() {
	
	FILE *file = fopen("accounts.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%d %s %d %s %f", &accounts[accountCount].accountNumber,
                      accounts[accountCount].name, &accounts[accountCount].password,
                      &accounts[accountCount].password, &accounts[accountCount].balance) == 5) {
            accountCount++;
            if (accountCount >= MAX_ACCOUNTS) {
                break;
            }
        }
        fclose(file);
    }
    
    int choice, accountNumber;
    float amount;
    char password[20];
    while (1) {
    	l0:
    	welcome();
    	menu();
        scanf("%d", &choice);
        system("cls");
        welcome();
        printf("\t\t\t_______________________________________________\n\n");
		printf("\n\t\t\tWait Loading . . .");
        waiting(1000);
        system("cls");
        welcome();
        
        
        switch (choice)
		{
            case 1:
                createAccount();
                printf("\n\t\t\tWait Loading . . .");
                waiting(1000);
                system("cls");
                break;
            case 2:
            	l1:
            	system("cls");
            	welcome();
            		printf("\n\t\t\tWait Loading . . .");
            		waiting(1000);
            		system("cls");
            		welcome();
            		printf("\t\t\tEnter your account number: ");
                	scanf("%d", &accountNumber);
                	printf("\t\t\tEnter your password: ");
                	scanf("%s", password);
        			if (authenticate(accountNumber, password))
					{
        				checkBalance(accountNumber);
        				printf("\n\t\t\tWait Loading . . .");
        				waiting(3500);
        				system("cls");
    				}
					else
					{
        				printf("\n");
        				printf("\t\t\t_______________________________________________\n\n");
    					printf("\t\t\tAuthentication failed.\n");
	    				printf("\n\t\t\tWait Loading . . .");
						waiting(1000);
						system("cls");
    				}
				break;
            case 3:
            	l2:
            	printf("\t\t\tEnter your account number: ");
        		scanf("%d", &accountNumber);
	            printf("\t\t\tEnter the amount to deposit: ");
    	        scanf("%f", &amount);
    	        
    	        system("cls");
            	welcome();
				deposit(accountNumber, amount);
				waiting(2000);/*
				system("cls");
				welcome();
				generateReceipt(accountNumber, "DEPOSIT", amount);*/
                waiting(2000);
                system("cls");
                break;
            case 4:
            	l3:
            	system("cls");
            	welcome();
            	printf("\t\t\tEnter your account number: ");
                scanf("%d", &accountNumber);
	            printf("\t\t\tEnter your password: ");
		        scanf("%s", password);
		        
		        system("cls");
            	welcome();
				if (authenticate(accountNumber, password))
				{
                    printf("\t\t\tEnter the amount to withdraw: ");
                    scanf("%f", &amount);
                    withdraw(accountNumber, amount);
                    printf("\n\t\t\tWait Loading . . .");/*
                    generateReceipt(accountNumber, "WITHDRAWAL", amount);*/
                   	waiting(2000);
                   	system("cls");
           		}
				else
				{
               		printf("_______________________________________________\n\n");
                   	printf("\t\t\tAuthentication failed.\n\n");
                	printf("\t\t\tWait Loading . . .");
                	waiting(1500);
	            	system("cls");
                }
                break;
            case 5:
    			transferFunds();
    			printf("\n\t\t\t________________________________________________\n\n");
    			printf("\n\t\t\tWait Loading . . .");
    			waiting(2000);
    			system("cls");
			    break;

            case 6:
                printf("\t\t\tExiting ATM. Have a nice day!\n\n");
                printf("\t\t\tWait Loading . . .\n\n\n\t\t\t");
                waiting(2000);
                return 0;
            default:
            	printf("\t\t\t_______________________________________________\n\n");
                printf("\t\t\tInvalid choice.");
            	printf("\n\n\t\t\tWait Loading . . .");
            	waiting(1000);
                system("cls");
                break;
        }
    }
    return 0;
}
