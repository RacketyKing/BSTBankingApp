#include <iostream>
#include "BankingApp.h"

int main() {
    BankingApp bank;
    bank.addAccount("checking");
    bank.addAccount("savings");
    bank.viewAccount();
}