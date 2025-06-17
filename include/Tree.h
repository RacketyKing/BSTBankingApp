#pragma once

#include "TreeNode.h"
#include <fstream>

template<typename NODE>
class Tree {
public:
    Tree();
    ~Tree();

    void insertNode(NODE*);
    void deleteNode(const std::string&);
    void depositNode(const std::string&, const float);
    void withdrawNode(const std::string&, const float);
    void display() const;

    void saveToFile(const std::string&) const;

    void setRootPtr(TreeNode<NODE>*);
    TreeNode<NODE>* getRootPtr() const;

private:
    TreeNode<NODE>* rootPtr = nullptr;

    void insertHelper(TreeNode<NODE>*&, NODE*);
    void deleteHelper(TreeNode<NODE>*&, const std::string&);
    void depositHelper(TreeNode<NODE>*, const std::string&, const float);
    void withdrawHelper(TreeNode<NODE>*, const std::string&, const float);
    void displayHelper(TreeNode<NODE>*) const;

    void saveToFileHelper(const TreeNode<NODE>*, std::ofstream& outFile) const;
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
void Tree<NODE>::saveToFile(const std::string& fileName) const{
    std::ofstream outFile(fileName);
    if(!outFile) {
        throw std::runtime_error("Unable to open file: " + fileName);
    }
    saveToFileHelper(rootPtr, outFile);
    outFile.close();
}
template <typename NODE>
void Tree<NODE>::saveToFileHelper(const TreeNode<NODE>* current, std::ofstream& outFile) const{
    if(current) {
        saveToFileHelper(current->getLeftPtr(), outFile);
        outFile << *current->getAccount() << "\n";
        saveToFileHelper(current->getRightPtr(), outFile);
    }
}

template <typename NODE>
TreeNode<NODE>*& getSuccessor(TreeNode<NODE>*& current) {
    current = current->getRightPtr();
    while(current != nullptr && current->getLeftPtr() != nullptr) {
        current = current->getLeftPtr();
    }
    return current;
}

template <typename NODE>
void Tree<NODE>::deleteNode(const std::string& accountNumber) { deleteHelper(rootPtr, accountNumber); }
template <typename NODE>
void Tree<NODE>::deleteHelper(TreeNode<NODE>*& current, const std::string& accountNumber) {
    if(current == nullptr) {
        return;
    }

    if(accountNumber < current->getAccount()->getAccountNumber()) {
        deleteHelper(current->getLeftPtr(), accountNumber);
    }
    else if(accountNumber > current->getAccount()->getAccountNumber()) {
        deleteHelper(current->getRightPtr(), accountNumber);
    }
    else {
        //case leaf node
        if(current->getLeftPtr() == nullptr && current->getRightPtr() == nullptr) {
            delete current;
            current = nullptr;
            return;
        }

        //cases with one child
        if(current->getLeftPtr() == nullptr) {
            TreeNode<NODE>* temp = current;
            current = current->getRightPtr();
            temp->setRightPtr(nullptr);
            delete temp->getAccount();
            delete temp;
            return;
        }
        if(current->getRightPtr() == nullptr) {
            TreeNode<NODE>* temp = current;
            current = current->getLeftPtr();
            temp->setLeftPtr(nullptr);
            delete temp->getAccount();
            delete temp;
            return;
        }

        //case with two children
        if(current->getLeftPtr() != nullptr && current->getRightPtr() != nullptr) {
            TreeNode<NODE>*& successor = getSuccessor(current);
            current->setAccount(successor->getAccount()->clone());
            deleteHelper(current->getRightPtr(), successor->getAccount()->getAccountNumber());
        }
    }
}

template <typename NODE>
void Tree<NODE>::depositNode(const std::string& accountNumber, const float amount) { 
    depositHelper(rootPtr, accountNumber, amount);
}
template <typename NODE>
void Tree<NODE>::depositHelper(TreeNode<NODE>* current, const std::string& accountNumber, const float amount) {
    if(current == nullptr) {
        std::cout << "\nDeposit Unsuccessful. Account Not Found!\n";
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
            std::cout << "\nDeposit Successful!\n";
            return;
        }
    }
}

template<typename NODE>
void Tree<NODE>::withdrawNode(const std::string& accountNumber, const float amount) { 
    withdrawHelper(rootPtr, accountNumber, amount);
}
template<typename NODE>
void Tree<NODE>::withdrawHelper(TreeNode<NODE>* current, const std::string& accountNumber, const float amount) {
     if(current == nullptr) {
        std::cout << "\nWithdraw Unsuccessful. Account Not Found!\n";
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
            std::cout << "\nWithdraw Successful!\n";
            return;
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