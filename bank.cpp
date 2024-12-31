#include <iostream>
#include <string>
using namespace std;

// Base class to represent a general bank account
class BankAccount {
protected:
    string accountHolderName;
    int accountNumber;
    double balance;

public:
    // Constructor
    BankAccount(string name, int accNum, double initialBalance) {
        accountHolderName = name;
        accountNumber = accNum;
        balance = initialBalance;
    }

    // Virtual method to deposit money
    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            cout << "Amount deposited successfully. Current balance: " << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    // Virtual method to withdraw money
    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            cout << "Amount withdrawn successfully. Current balance: " << balance << endl;
        } else {
            cout << "Invalid withdrawal amount or insufficient balance." << endl;
        }
    }

    // Method to check balance
    void checkBalance() const {
        cout << "Current balance: " << balance << endl;
    }

    // Virtual method to display account details
    virtual void displayAccountDetails() const {
        cout << "Account Holder Name: " << accountHolderName << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Current Balance: " << balance << endl;
    }

    // Getter for account number
    int getAccountNumber() const {
        return accountNumber;
    }

    // Virtual destructor
    virtual ~BankAccount() {}
};

// Derived class to represent a savings account
class SavingsAccount : public BankAccount {
private:
    double interestRate; // Interest rate specific to savings account

public:
    // Constructor
    SavingsAccount(string name, int accNum, double initialBalance, double rate)
        : BankAccount(name, accNum, initialBalance), interestRate(rate) {}

    // Override method to display account details
    void displayAccountDetails() const override {
        cout << "[Savings Account]" << endl;
        BankAccount::displayAccountDetails();
        cout << "Interest Rate: " << interestRate << "%" << endl;
    }
};

// Class to manage multiple bank accounts
class Bank {
private:
    BankAccount* accounts[100]; // Array to store account pointers
    int totalAccounts;         // Counter for total accounts

public:
    // Constructor
    Bank() {
        totalAccounts = 0;
    }

    // Destructor to clean up dynamically allocated memory
    ~Bank() {
        for (int i = 0; i < totalAccounts; i++) {
            delete accounts[i];
        }
    }

    // Method to create a new account
    void createAccount() {
        string name;
        double initialDeposit, interestRate;
        int accountType;

        cout << "Enter account holder's name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter initial deposit amount: ";
        cin >> initialDeposit;

        if (initialDeposit < 0) {
            cout << "Initial deposit cannot be negative." << endl;
            return;
        }

        cout << "Select account type (1. Savings Account): ";
        cin >> accountType;

        int accountNumber = 1001 + totalAccounts; // Generate unique account number

        if (accountType == 1) {
            cout << "Enter interest rate (in %): ";
            cin >> interestRate;
            accounts[totalAccounts] = new SavingsAccount(name, accountNumber, initialDeposit, interestRate);
        } else {
            cout << "Invalid account type selected." << endl;
            return;
        }

        totalAccounts++;
        cout << "Account created successfully! Your account number is " << accountNumber << endl;
    }

    // Method to find an account by account number
    BankAccount* findAccount(int accountNumber) {
        for (int i = 0; i < totalAccounts; i++) {
            if (accounts[i]->getAccountNumber() == accountNumber) {
                return accounts[i];
            }
        }
        cout << "Account not found." << endl;
        return nullptr;
    }

    // Method to perform banking operations
    void performOperations() {
        int choice;
        do {
            cout << "\n----- Banking Management System -----" << endl;
            cout << "1. Create New Account" << endl;
            cout << "2. Deposit Amount" << endl;
            cout << "3. Withdraw Amount" << endl;
            cout << "4. Balance Enquiry" << endl;
            cout << "5. Display Account Details" << endl;
            cout << "6. Exit" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    createAccount();
                    break;
                case 2: {
                    int accNum;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> accNum;
                    BankAccount* account = findAccount(accNum);
                    if (account) {
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        account->deposit(amount);
                    }
                    break;
                }
                case 3: {
                    int accNum;
                    double amount;
                    cout << "Enter account number: ";
                    cin >> accNum;
                    BankAccount* account = findAccount(accNum);
                    if (account) {
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        account->withdraw(amount);
                    }
                    break;
                }
                case 4: {
                    int accNum;
                    cout << "Enter account number: ";
                    cin >> accNum;
                    BankAccount* account = findAccount(accNum);
                    if (account) {
                        account->checkBalance();
                    }
                    break;
                }
                case 5: {
                    int accNum;
                    cout << "Enter account number: ";
                    cin >> accNum;
                    BankAccount* account = findAccount(accNum);
                    if (account) {
                        account->displayAccountDetails();
                    }
                    break;
                }
                case 6:
                    cout << "Exiting the system. Thank you for using our service!" << endl;
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
            }
        } while (choice != 6);
    }
};

int main() {
    Bank bank;
    bank.performOperations();
    return 0;
}
