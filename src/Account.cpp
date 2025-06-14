#include "Account.h"

bool hasNDigits(const std::string& accountNumber) {
    unsigned int N = 9;
    std::regex pattern("^\\d{" + std::to_string(N) + "}$");
    return std::regex_match(accountNumber, pattern);
}

std::ostream& operator<<(std::ostream& os, const Account& account) {
    os << "Account Number: " << account.getAccountNumber() << std::endl;
    os << "Account Balance: $" << account.getBalance() << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, Account& account) {
    std::string accountNumber = {};
    float balance = 0;
    bool loop = true;
    while(loop) {
        std::cout << "Enter Account Number: ";
        is >> accountNumber;

        if(hasNDigits(accountNumber)) {
            account.setAccountNumber(accountNumber);
            loop = false;
        }
        else {
            std::cerr << "Invlaid account Number (must be 9 digits long)\n";
        }
    }

    loop = true;

    while(loop) {
        std::cout << "Enter Account Balance: ";
        is >> balance;

        if(balance > 0.00 || balance < 999999.99f) {
            account.setBalance(balance);
            loop = false;
        }
        else {
            std::cerr << "Invalid deposit amount\n";
        }
    }
    return is;
}

Account::Account(const std::string accountNumber, const float balance): accountNumber(accountNumber), balance(balance) {}
Account::Account(): accountNumber("nil"), balance(0.00f) {}

bool Account::deposit(const float depositAmount) {
    if(depositAmount > 0.00f || depositAmount < 9999999.99f) {
        setBalance(getBalance() + depositAmount);
        return true;
    }
    else {
        std::cerr << "Invalid deposit amount\n";
        return false;
    }
    
}

bool Account::withdrawal(const float withdrawAmount) {
    if(withdrawAmount > 0.00f && withdrawAmount < getBalance()) {
        setBalance(getBalance() - withdrawAmount);
        return true;
    }
    else {
        std::cerr << "Invalid withdraw amount";
        return false; 
    }
}

void Account::display() const{
    std::cout << "Welcome, dear customer!" << std::endl;
    std::cout << "Account Number: " << getAccountNumber() << std::endl;
    std::cout << "Account Balance: $" << getBalance() << "\n\n";
}


void Account::setAccountNumber(const std::string& accountNumber) {
    if(hasNDigits(accountNumber)) {
       this->accountNumber = accountNumber;
    }
    else {
        std::cerr << "Invlaid account Number (must be 9 digits long)\n";
    }
}
std::string Account::getAccountNumber() const {return this->accountNumber;}

void Account::setBalance(const float balance) {this->balance = balance;}
float Account::getBalance() const {return this->balance;}