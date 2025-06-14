#include "CheckingAccount.h"

CheckingAccount::CheckingAccount(const std::string& accountNumber, const float balance, const float overDraftLimit) : Account(accountNumber, balance), overDraftLimit(overDraftLimit) {}
CheckingAccount::CheckingAccount() : Account(), overDraftLimit(0.00f) {}

void CheckingAccount:: display() const{
    std::cout << "Checking Account - ";
    std::cout << "Account Number: " << getAccountNumber() << ", ";
    std::cout << "Balance: $" << getBalance() << ", ";
    std::cout << "OverDraftLimit: $" << getOverDraftLimit() << "\n\n";
}

bool CheckingAccount::withdrawal(const float withdrawAmount) {
    if(withdrawAmount > 0.00f && withdrawAmount < (getBalance() + getOverDraftLimit())) {
        setBalance(getBalance() - withdrawAmount);
        return true;
    }
    else {
        std::cerr << "Invalid withdraw amount";
        return false;
    }
}

void CheckingAccount::setOverDraftLimit(const float overDraftLimit) {this->overDraftLimit = overDraftLimit;}
float CheckingAccount::getOverDraftLimit() const {return this->overDraftLimit;}

std::ostream& operator<<(std::ostream& os, const CheckingAccount& checking) {
    os << static_cast<const Account&>(checking);
    os << "Overdraft Limit: $" << checking.getOverDraftLimit() << "\n";
    return os;
}

std::istream& operator>>(std::istream& is, CheckingAccount& checking) {
    float overDraftLimit;
    is >> static_cast<Account&>(checking);

    std::cout << "Enter OverDraftLimit: $";
    is >> overDraftLimit;
    if(overDraftLimit > 0.00f && overDraftLimit < 1000.00f) {
        checking.setOverDraftLimit(overDraftLimit);
    }
    else {
        std::cerr << "Invalid OverDraftLimit Value" << "\n";
    }
    return is;
}