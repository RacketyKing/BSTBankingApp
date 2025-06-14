#pragma once

#include "TreeNode.h"

template<typename NODE>
class Tree {
public:
    Tree();
    ~Tree();

    void insertNode(NODE*);
    void display() const;

    void setRootPtr(TreeNode<NODE>*);
    TreeNode<NODE>* getRootPtr() const;

private:
    TreeNode<NODE>* rootPtr = nullptr;

    void insertHelper(TreeNode<NODE>*&, NODE*);
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
    else {
        insertHelper(current->getRightPtr(), account);
    }
}

template <typename NODE>
void Tree<NODE>::display() const { displayHelper(getRootPtr()); }
template <typename NODE>
void Tree<NODE>::displayHelper(TreeNode<NODE>* current) const {
    if(current == nullptr) {
        std::cout << "Tree is empty\n";
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