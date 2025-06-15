#include <iostream>
#include "BankingApp.h"

int main() {
    BankingApp bank;
    bank.addAccount("checking");
    bank.addAccount("savings");
    bank.addAccount("checking");
    bank.addAccount("savings");
    bank.addAccount("checking");
    bank.viewAccount();
    bank.depositAccount("234567891", 100.50);
    bank.withdrawAccount("012345678", 100.00);
    bank.viewAccount();

}