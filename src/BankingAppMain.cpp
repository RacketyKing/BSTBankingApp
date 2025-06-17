#include <iostream>
#include <string>
#include <regex>
#include <limits>
#include "BankingApp.h"

void bankMenu();
bool accountNumberHandler(const std::string&);
bool depositOrWithdrawHandler(const float);
bool choiceHandler(const unsigned int);

int main() {
    BankingApp bank;
    enum CHOICE {SAVINGS = 1, CHECKING, DEPOSIT, WITHDRAW, DISPLAY, SAVE, DELETE, EXIT};
    unsigned int choice = 0;
    bool loop = true;

    while(loop) {
        bankMenu();
        while(true) {
            std::cin >> choice;

            if(choiceHandler(choice)) {
                break;
            }
            else {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Invalid input. Please enter a digit from 1 to 8 only.\n";
                std::cout << "Enter your choice: ";
            }
        }

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
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            float deposit;
            std::string accountNumber;
            try{
                while(true) {
                    std::cout << "Enter Account Number for Deposit: ";
                    std::getline(std::cin, accountNumber);
                    
                    std::cout << "Enter the deposit amount: ";
                    std::cin >> deposit;

                    if(accountNumberHandler(accountNumber) && depositOrWithdrawHandler(deposit)) {
                        std::cout << "\nValid inputs!\n";
                        bank.depositAccount(accountNumber, deposit);
                        break;
                    }
                    else {
                        std::cout << "Invalid input. Try again.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
                }

            }
            catch(std::invalid_argument& e) {
                std::cerr << "Exception: " << e.what();
            }
            break;
        }
        case WITHDRAW:
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            float withdraw;
            std::string accountNumber;
            try{
                while(true) {
                    std::cout << "Enter Account Number for Withdrawal: ";
                    std::getline(std::cin, accountNumber);
                    
                    std::cout << "Enter the withdrawal amount: ";
                    std::cin >> withdraw;

                    if(accountNumberHandler(accountNumber) && depositOrWithdrawHandler(withdraw)) {
                        std::cout << "\nValid inputs!\n";
                        bank.withdrawAccount(accountNumber, withdraw);
                        break;
                    }
                    else {
                        std::cout << "Invalid input. Try again.\n";
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    }
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
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string fileName;
            std::cout << "Enter file name: ";
            std::getline(std::cin, fileName);

            bank.saveToFile(fileName);
            break;
        }
        case DELETE:
        {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::string accountNumber;

            while(true) {
                std::cout << "Enter Account Number for Deposit: ";
                std::getline(std::cin, accountNumber);

                if(accountNumberHandler(accountNumber)) {
                    std::cout << "\nValid input!\n";
                    bank.deleteAccount(accountNumber);
                    break;
                }
                else {
                    std::cout << "Invalid input. Try again.\n";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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

        std::cin.clear(); 
    }
}

void bankMenu() {
    std::cout << "\nBanking Application Menu:\n";
    std::cout << "1. Create Savings Account\n";
    std::cout << "2. Create Checking Account\n";
    std::cout << "3. Deposit\n";
    std::cout << "4. Withdraw\n";
    std::cout << "5. Display Accounts\n";
    std::cout << "6. Save Accounts to File\n";
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

bool choiceHandler(const unsigned int choice) {
    std::string input = std::to_string(choice);
    std::regex choicePattern(R"(^[1-8$])");
    return std::regex_match(input, choicePattern);
}