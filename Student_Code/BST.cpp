//
//  BST.cpp
//  6_lab_tester
//
//  Created by William Pinkston on 11/21/16.
//  Copyright © 2016 Xunil_programming. All rights reserved.
//

#include <stdio.h>
#include "BST.h"

//----------------------------------------------------------

BST::BST()
{
    _Root = NULL;
}

BST::~BST() {}

//----------------------------------------------------------

NodeInterface* BST::getRootNode()
{
    return _Root;
}

//----------------------------------------------------------

bool BST::add(int data)
{
//    cout << "add(" << data << ")" << endl;
    return addHelper(_Root, data);
}
bool BST::remove(int data)
{
//    cout << "remove(" << data << ")" << endl;
    Node* remR = _Root;
    return removeHelper(remR, data);
}

//-----
//-----

bool BST::addHelper(Node* &here, int data)
{
//    cout << "addHelper(" << data << ")" << endl;
    if (here == NULL)
    {
        here = new Node();
        here->value = data;
        return true;
    }
    if (here->value == data)
    {
        return false;
    }
    
    if (data < here->value)
    {
        return addHelper(here->leftChild, data);
    }
    else if (data > here->value)
    {
        return addHelper(here->rightChild, data);
    }
    
    else
    {
        return false;
    }
}

//-----
//-----

bool BST::removeHelper(Node* here, int data)
{
//    cout << "removeHelper(" << data << ")" << endl;
    Node* parentNode = findVal(here, data);
    if (parentNode == NULL) return false;
    if (data == parentNode->value && parentNode == _Root)//delete root
    {
        /////
        if (parentNode->leftChild == NULL && parentNode->rightChild == NULL)
        {
            _Root = NULL;
            delete parentNode;
        }
        else
        {
            if (parentNode->leftChild != NULL && parentNode->rightChild != NULL)
            {
                //else check for replacement on left tree
                Node* replaceRoot = findLeftGreatest(parentNode->leftChild);
                if (replaceRoot == NULL)
                {
                    //left tree empty
                    _Root = parentNode->rightChild;
                    delete parentNode;
                }
                else
                {
                    int hold = replaceRoot->value;
                    remove(hold);
                    parentNode->value = hold;
                }
            }
            else if (parentNode->leftChild == NULL)
            {
                _Root = parentNode->rightChild;
                delete parentNode;
            }
            else
            {
                _Root = parentNode->leftChild;
                delete parentNode;
            }
        }
        return true;
        
        
        /////
    }
    
    Node* temp = NULL;
    bool isLeft = false;
    if (data < parentNode->value)
    {
        temp = parentNode->leftChild;
        isLeft = true;
    }
    if (data > parentNode->value)
    {
        temp = parentNode->rightChild;
        isLeft = false;
    }
    
    
    if (temp->getLeftChild() != NULL && temp->getRightChild() != NULL)
    {
        Node* replaceVal = findLeftGreatest(temp->leftChild);
        int hold = replaceVal->value;
        remove(hold);
        temp->value = hold;
    }
    else
    {
        //use the skip link thing
        if (temp->getLeftChild() == NULL)
        {
            if (isLeft)
            {
                parentNode->leftChild = temp->rightChild;
            }
            else
            {
                parentNode->rightChild = temp->rightChild;
            }
        }
        else
        {
            if (isLeft)
            {
                parentNode->leftChild = temp->leftChild;
            }
            else
            {
                parentNode->rightChild = temp->leftChild;
            }
        }
        delete temp;
        temp = NULL;
    }
    return true;
}

//-----
//-----

BST::Node* BST::findVal(Node* find, int data)
{
//    cout << "findVal(" << data << ")" << endl;
    //check the root
    if (find == NULL) return NULL;
    if (find->value == data) return find;
    
    return findValR(find, data);
}

BST::Node* BST::findValR(Node* find, int data)
{
//    cout << "findValR(" << find->value << ", " << data << ")" << endl;
    //checks one node ahead, so that it can return the parent node
    if (find->leftChild == NULL && find->rightChild == NULL) return NULL;
    if (data < find->value && find->leftChild == NULL) return NULL;
    if (data < find->value)
    {
        if (find->leftChild->value == data) return find;
        return findValR(find->leftChild, data);
    }
    else
    {
        if (data > find->value && find->rightChild == NULL) return NULL;
        if (find->rightChild->value == data) return find;
        return findValR(find->rightChild, data);
    }
}

//-----
//-----

BST::Node* BST::findLeftGreatest(Node* remL_Child)
{
//    cout << "findLeftGreatest(" << remL_Child->value << ")" << endl;
    if (remL_Child == NULL) return NULL;
    if (remL_Child->rightChild == NULL)
    {
        return remL_Child;
    }
    else return findLeftGreatest(remL_Child->rightChild);
}

//----------------------------------------------------------

void BST::clear()
{
    Node* clearCheck = clearHelper(_Root);
//    if (clearCheck!= NULL) cout << "error in clearHelper" << endl;
    _Root = clearCheck;
}

//-----
//-----

BST::Node* BST::clearHelper(Node* here) {
    
    if (here == NULL) return NULL;
    
    Node* temp = here;
    Node* left = temp->leftChild;
    Node* right = temp->rightChild;
    
    clearHelper(left);
    clearHelper(right);
    
    delete temp;
    temp = NULL;
    return temp;
}

//----------------------------------------------------------







