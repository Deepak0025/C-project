]#include <iostream>
#include <string>
using namespace std;

// Base class for a general bank account
class BankAccount {
protected:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    // Constructor
    BankAccount(string name, int accNum, double initialBalance)
    {
         accountHolderName=name, accountNumber=accNum, balance=initialBalance ;
    }

    // Deposit method
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Deposited: " << amount << ". New Balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount!" << endl;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Withdrawn: " << amount << ". Remaining Balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance!" << endl;
        }
    }

    // Method to display account details
    void displayAccountDetails() {
        cout << "Account Holder: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

// Derived class for a savings account
class SavingsAccount : public BankAccount {
private:
    double interestRate;

public:
    // Constructor
SavingsAccount(string name, int accNum, double initialBalance, double rate)
    {
        // Call the base class constructor explicitly using a method (you can't directly call a base class constructor in traditional style)
        BankAccount::accountHolderName = name;
        BankAccount::accountNumber = accNum;
        BankAccount::balance = initialBalance;
        interestRate = rate;
    }
    // Method to display details with interest rate
    void displayAccountDetails() {
        BankAccount::displayAccountDetails(); // Call base class method
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

int main() {
    string name;
    double initialDeposit, interestRate;
    int accountNumber = 1001; // Starting account number
    char choice;

    cout << "Welcome to the Bank Management System!" << endl;
    cout << "Enter your name: ";
    getline(cin, name);

    cout << "Enter initial deposit amount: ";
    cin >> initialDeposit;

    cout << "Enter interest rate for savings account (in %): ";
    cin >> interestRate;


    SavingsAccount myAccount(name, accountNumber, initialDeposit, interestRate);
    cout << "\nAccount created successfully! Your account number is " << accountNumber << endl;

    do {
        int operation;
        cout << "\nSelect an operation:" << endl;
        cout << "1. Deposit money" << endl;
        cout << "2. Withdraw money" << endl;
        cout << "3. Display account details" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> operation;

        switch (operation) {
            case 1: {
                double amount;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                myAccount.deposit(amount);
                break;
            }
            case 2: {
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                myAccount.withdraw(amount);
                break;
            }
            case 3:
                myAccount.displayAccountDetails();
                break;
            case 4:
                cout << "Thank you for using our services!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
        cout << "\nDo you want to perform another operation? (y/n): ";
        cin >> choice;

    } while (choice == 'y' || choice == 'Y');

    cout << "Goodbye!" << endl;

    return 0;
}
