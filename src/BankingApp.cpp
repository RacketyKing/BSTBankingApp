#include "BankingApp.h"

BankingApp::BankingApp() : accountTree(new Tree<Account>) {}
BankingApp::~BankingApp() { delete accountTree; }

void BankingApp::addAccount(const std::string& accountType) {
    if(accountType == "savings") {
        Account* accountSavings = new SavingsAccount();
        SavingsAccount* savings = dynamic_cast<SavingsAccount*>(accountSavings);
        std::cin >> *savings;

        if(savings) {
            accountTree->insertNode(savings);
        }
        else {
            std::cerr << "Cast failed: Not a SavingsAccount" << std::endl;
        }
    }
    else if (accountType == "checking") {
        Account* accountChecking = new CheckingAccount();
        CheckingAccount* checking = dynamic_cast<CheckingAccount*>(accountChecking);
        std::cin >> *checking;
        
        if(checking) {
            accountTree->insertNode(checking);
        }
        else {
           std::cerr << "Cast failed: Not a CheckingAccount" << std::endl;
        }
    }
}

void:: BankingApp::viewAccount() const {
    accountTree->display();
}