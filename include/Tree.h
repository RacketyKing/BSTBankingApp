#pragma once

#include "TreeNode.h"

template<typename NODE>
class Tree {
public:
    Tree();
    ~Tree();

    void insertNode(NODE*);
    void depositNode(const std::string&, const float);
    void withdrawNode(const std::string&, const float);
    void display() const;

    void setRootPtr(TreeNode<NODE>*);
    TreeNode<NODE>* getRootPtr() const;

private:
    TreeNode<NODE>* rootPtr = nullptr;

    void insertHelper(TreeNode<NODE>*&, NODE*);
    void depositHelper(TreeNode<NODE>*&, const std::string&, const float);
    void withdrawHelper(TreeNode<NODE>*&, const std::string&, const float);
    void displayHelper(TreeNode<NODE>*) const;
};

template <typename NODE>
Tree<NODE>::Tree(): rootPtr(nullptr) {}
template <typename NODE>
Tree<NODE>::~Tree() {std::cout << "Deleting rootPtr\n"; delete rootPtr;}

template <typename NODE>
void Tree<NODE>::insertNode(NODE* account) { insertHelper(rootPtr, account); }
template <typename NODE>
void Tree<NODE>::insertHelper(TreeNode<NODE>*& current, NODE* account) {
    if(current == nullptr) {
        current = new TreeNode<NODE>(account);
        return;
    }
    if(account->getAccountNumber() < current->getAccount()->getAccountNumber()) {
        insertHelper(current->getLeftPtr(), account);
    }
    else if(account->getAccountNumber() > current->getAccount()->getAccountNumber()) {
        insertHelper(current->getRightPtr(), account);
    }
}

template <typename NODE>
void Tree<NODE>::depositNode(const std::string& accountNumber, const float amount) { depositHelper(rootPtr, accountNumber, amount); }
template <typename NODE>
void Tree<NODE>::depositHelper(TreeNode<NODE>*& current, const std::string& accountNumber, const float amount) {
    if(current == nullptr) {
        return;
    }
    if(accountNumber < current->getAccount()->getAccountNumber()) {
        depositHelper(current->getLeftPtr(), accountNumber, amount);
    }
    else if(accountNumber > current->getAccount()->getAccountNumber()) {
        depositHelper(current->getRightPtr(), accountNumber, amount);
    }
    else if(accountNumber == current->getAccount()->getAccountNumber()) {
        if(current->getAccount()->deposit(amount)) {
            std::cout << "Deposit Completed Successfully.\n\n";
        }
    }
}

template<typename NODE>
void Tree<NODE>::withdrawNode(const std::string& accountNumber, const float amount) { withdrawHelper(rootPtr, accountNumber, amount); }
template<typename NODE>
void Tree<NODE>::withdrawHelper(TreeNode<NODE>*& current, const std::string& accountNumber, const float amount) {
     if(current == nullptr) {
        return;
    }
    if(accountNumber < current->getAccount()->getAccountNumber()) {
        depositHelper(current->getLeftPtr(), accountNumber, amount);
    }
    else if(accountNumber > current->getAccount()->getAccountNumber()) {
        depositHelper(current->getRightPtr(), accountNumber, amount);
    }
    else if(accountNumber == current->getAccount()->getAccountNumber()) {
        if(current->getAccount()->withdrawal(amount)) {
            std::cout << "Withdrawal Completed Successfully.\n\n";
        }
    }
}

template <typename NODE>
void Tree<NODE>::display() const { displayHelper(getRootPtr()); }
template <typename NODE>
void Tree<NODE>::displayHelper(TreeNode<NODE>* current) const {
    if(current == nullptr) {
        return;
    }
    else {
        displayHelper(current->getLeftPtr());
        current->getAccount()->display();
        displayHelper(current->getRightPtr());
    }
}

template <typename NODE>
void Tree<NODE>::setRootPtr(TreeNode<NODE>* rootPtr) { this->rootPtr = rootPtr; }
template <typename NODE>
TreeNode<NODE>* Tree<NODE>::getRootPtr() const { return this->rootPtr; }