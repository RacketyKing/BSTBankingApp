#pragma once
#include "Account.h"

class CheckingAccount : public Account {
public:
    friend std::ostream& operator<<(std::ostream&, const CheckingAccount&);
    friend std::istream& operator>>(std::istream&, CheckingAccount&);

    CheckingAccount(const std::string&, const float, const float);
    CheckingAccount();

    void display() const override;
    bool withdrawal(const float) override;

    void setOverDraftLimit(const float);
    float getOverDraftLimit() const;
private:
    float overDraftLimit = 0.00f;
};