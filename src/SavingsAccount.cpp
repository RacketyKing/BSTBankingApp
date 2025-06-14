#include "SavingsAccount.h"

SavingsAccount::SavingsAccount(const std::string& accountNumber, const float balance, const float interest): Account(accountNumber, balance), interest(interest) {}
SavingsAccount::SavingsAccount(): Account(), interest(0.00f) {}

void SavingsAccount::display() const {
    std::cout << "Savings Account - ";
    std::cout << "Account Number: " << getAccountNumber() << ", ";
    std::cout << "Balance: $" << getBalance() << ", ";
    std::cout << "Interest Rate: " << (getInterestRate() * 100) << "%" << "\n\n";
}

bool SavingsAccount::withdrawal(const float withdrawAmount) {
     if(withdrawAmount > 0.00f && withdrawAmount + (withdrawAmount * getInterestRate())  < getBalance()) {
        setBalance(getBalance() - (withdrawAmount + (withdrawAmount * getInterestRate())));
        return true;
    }
    else {
        std::cerr << "Invalid withdraw amount";
        return false; 
    }
}

void SavingsAccount::setInterestRate(const float interest) {this->interest = (interest / 100);}
float SavingsAccount::getInterestRate() const {return this->interest;}

std::ostream& operator<<(std::ostream& os, const SavingsAccount& savings) {
    os << static_cast<const Account&>(savings) << "\n";
    os << "Interest Rate: " << savings.getInterestRate() << "%" << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, SavingsAccount& savings) {
    float interest;
    is >> static_cast<Account&>(savings);

    std::cout << "Enter interest rate: ";
    is >> interest;
    if(interest > 0.00f && interest >= 100.00f) {
        savings.setInterestRate(interest);
    }
    else {
        std::cerr << "Invalid interest rate value!" << std::endl;
    }
    return is;
}
