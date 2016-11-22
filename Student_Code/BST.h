//
//  BST.h
//  6_lab_tester
//
//  Created by William Pinkston on 11/21/16.
//  Copyright © 2016 Xunil_programming. All rights reserved.
//

#ifndef BST_h
#define BST_h

#include "BSTInterface.h"
#include "NodeInterface.h"
//#include "Node.h"

class BST : public BSTInterface {
    
private:
    //
    class Node : public NodeInterface {
    public:
        Node* leftChild;
        Node* rightChild;
        int value;

        Node() {
            leftChild = NULL;
            rightChild = NULL;
        }
        ~Node() {}
        int getData() {
            return value;
        }
        NodeInterface *getLeftChild() {
            return leftChild;
        }
        NodeInterface *getRightChild() {
            return rightChild;
        }
    };
    //
    Node* _Root;
    
public:
    BST();
    ~BST();
    NodeInterface * getRootNode();
    bool add(int data);
    bool remove(int data);
    void clear();
    
    // helper functions
    bool addHelper(Node* &here, int data);
    bool removeHelper(Node* here, int data);
    Node* findVal(Node* find, int data);
    Node* findValR(Node* find, int data);
    Node* findLeftGreatest(Node* remL_Child);
    Node* clearHelper(Node* here);
};

#endif /* BST_h */






