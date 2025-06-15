#pragma once

#include "Tree.h"
#include "Account.h"
#include "SavingsAccount.h"
#include "CheckingAccount.h"
#include <string>

class BankingApp {
public:
    BankingApp();
    ~BankingApp();

    void addAccount(const std::string&);
    void depositAccount(const std::string&, const float);
    void withdrawAccount(const std::string&, const float);
    void viewAccount() const;

private:
    Tree<Account>* accountTree;
};