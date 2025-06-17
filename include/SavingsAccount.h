#pragma once
#include "Account.h"

class SavingsAccount : public Account {
public:
    friend std::ostream& operator<<(std::ostream&, const SavingsAccount&);
    friend std::istream& operator>>(std::istream&, SavingsAccount&);

    SavingsAccount(const std::string&, const float , const float);
    SavingsAccount();

    void display() const override;
    bool withdrawal(const float) override;
    Account* clone() const override {
        return new SavingsAccount(*this);
    }

    void setInterestRate(const float);
    float getInterestRate() const;
private:
    float interest;

};