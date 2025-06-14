#pragma once

#include <iostream>

template <typename NODE>
class TreeNode {
public:
    TreeNode(NODE*);
    ~TreeNode();

    void setAccount(NODE*);
    NODE* getAccount() const;

    void setLeftPtr(TreeNode<NODE>*);
    TreeNode<NODE>* getLeftPtr() const;
    TreeNode<NODE>*& getLeftPtr();

    void setRightPtr(TreeNode<NODE>*);
    TreeNode<NODE>* getRightPtr() const;
     TreeNode<NODE>*& getRightPtr();
private:
    NODE* account;
    TreeNode<NODE>* leftPtr;
    TreeNode<NODE>* rightPtr;
};

template <typename NODE>
TreeNode<NODE>::TreeNode(NODE* account) : account(account), leftPtr(nullptr), rightPtr(nullptr) {}
template <typename NODE>
TreeNode<NODE>::~TreeNode() {std::cout << "Deleting TreeNode variables - account, rightPtr, leftPtr!\n"; delete account; delete leftPtr; delete rightPtr;}

template<typename NODE>
void TreeNode<NODE>:: setAccount(NODE* account) {
    this->account = account;
}
template<typename NODE>
NODE* TreeNode<NODE>::getAccount() const {
    return this->account;
}

template<typename NODE>
void TreeNode<NODE>::setLeftPtr(TreeNode<NODE>* leftPtr) {
    this->leftPtr = leftPtr;
}
template<typename NODE>
TreeNode<NODE>* TreeNode<NODE>::getLeftPtr() const {
    return this->leftPtr;
}
template<typename NODE>
TreeNode<NODE>*& TreeNode<NODE>::getLeftPtr() {
    return this->leftPtr;
}

template <typename NODE>
void TreeNode<NODE>::setRightPtr(TreeNode<NODE>* rightPtr) {
    this->rightPtr = rightPtr;
}
template <typename NODE>
TreeNode<NODE>* TreeNode<NODE>::getRightPtr() const {
    return this->rightPtr;
}
template <typename NODE>
TreeNode<NODE>*& TreeNode<NODE>::getRightPtr() {
    return this->rightPtr;
}