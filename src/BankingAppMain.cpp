#include <iostream>
#include <string>
#include <regex>
#include <limits>
#include "BankingApp.h"

void bankMenu();
bool accountNumberHandler(const std::string&);
bool depositOrWithdrawHandler(const float);

int main() {
    BankingApp bank;
    enum CHOICE {SAVINGS = 1, CHECKING, DEPOSIT, WITHDRAW, DISPLAY, SAVE, DELETE, EXIT};
    unsigned int choice = 0;
    bool loop = true;

    while(loop) {
        bankMenu();
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin >> choice;

        switch (choice)
        {
        case SAVINGS:
            bank.addAccount("savings");
            break;
        case CHECKING:
            bank.addAccount("checking");
            break;
        case DEPOSIT:
        {
            float deposit;
            std::string accountNumber;
            try{
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                bool loop = true;
                while(loop) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter Account Number for Deposit: ";
                    std::getline(std::cin, accountNumber);
                    
                    std::cout << "Enter the deposit amount: ";
                    std::cin >> deposit;

                    if(accountNumberHandler(accountNumber) && depositOrWithdrawHandler(deposit)) {
                        std::cout << "\nValid inputs!\n";
                        loop = false;
                    }
                }
                if(bank.depositAccount(accountNumber, deposit)) {
                     std::cout << "\nDeposit Completed Successfully.\n\n";
                }
                else {
                    std::cout << "\nDeposit Unsuccessful. Account Number not Found!\n\n";
                }

            }
            catch(std::invalid_argument& e) {
                std::cerr << "Exception: " << e.what();
            }
            break;
        }
        case WITHDRAW:
        {
            float withdraw;
            std::string accountNumber;
            try{
                std::cin.clear();

                bool loop = true;
                while(loop) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter Account Number for Deposit: ";
                    std::getline(std::cin, accountNumber);
                    
                    std::cout << "Enter the deposit amount: ";
                    std::cin >> withdraw;

                    if(accountNumberHandler(accountNumber) && depositOrWithdrawHandler(withdraw)) {
                        std::cout << "\nValid inputs!\n";
                        loop = false;
                    }
                }
                if(bank.withdrawAccount(accountNumber, withdraw)) {
                     std::cout << "\nWithdrawal Completed Successfully.\n\n";
                }
                else {
                    std::cout << "\nWithdrawal Unsuccessful. Account Number not Found!\n\n";
                }

            }
            catch(std::invalid_argument& e) {
                std::cerr << "Exception: " << e.what();
            }
            break;
        }
        case DISPLAY:
            bank.viewAccount();
            break;
        case SAVE:
            std::cout << "Not implemented yet\n";
            break;
        case DELETE:
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string accountNumber;

             bool loop = true;
            while(loop) {
                std::cout << "Enter Account Number for Deposit: ";
                std::getline(std::cin, accountNumber);

                if(accountNumberHandler(accountNumber)) {
                    std::cout << "\nValid input!\n";
                    bank.deleteAccount(accountNumber);
                    loop = false;
                }
            }
            break;
        }
        case EXIT:
            loop = false;
            std::cout << "\n\nExiting the application.\n";
            break;
        
        default:
            std::cerr << "Invalid choice!\n";
            break;
        }
    }
    // bank.addAccount("checking");
    // bank.addAccount("savings");
    // bank.addAccount("checking");
    // bank.viewAccount();
    // bank.depositAccount("234567891", 100.50);
    // bank.withdrawAccount("012345678", 100.00);
    // bank.viewAccount();
    // bank.deleteAccount("234567891");
    // bank.viewAccount();
}

void bankMenu() {
    std::cout << "\nBanking Application Menu:\n";
    std::cout << "1. Create Savings Account\n";
    std::cout << "2. Create Checking Account\n";
    std::cout << "3. Deposit\n";
    std::cout << "4. Withdraw\n";
    std::cout << "5. Display Accounts\n";
    std::cout << "6. Save Accounts to File (not implemented yet)\n";
    std::cout << "7. Delete Account\n";
    std::cout << "8. Exit\n\n";
    std::cout << "Enter your choice: ";
}

bool accountNumberHandler(const std::string& accountNumber) {
    unsigned int N = 9;
    std::regex pattern("^\\d{" + std::to_string(N) + "}$");
    return std::regex_match(accountNumber, pattern);
}

bool depositOrWithdrawHandler(const float amount) {
    std::string input = std::to_string(amount);
    std::regex floatPattern(R"([+-]?([0-9]*[.])?[0-9]+([eE][+-]?[0-9]+)?)");
    return std::regex_match(input, floatPattern);
}