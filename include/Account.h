#pragma once
#include <string>
#include <iostream>
#include <ostream>
#include <regex>

class Account {
public:
    friend std::ostream& operator<<(std::ostream&, const Account&);
    friend std::istream& operator>>(std::istream&, Account&);

    Account(const std::string, const float);
    Account();
    virtual ~Account() = default;

    bool deposit(const float);
    virtual bool withdrawal(const float);
    virtual void display() const;

    void setAccountNumber(const std::string&);
    std::string getAccountNumber() const;

    void setBalance(const float);
    float getBalance() const;

private:
    std::string accountNumber;
    float balance;
};