//
// Created by Artur on 14.03.2018.
//

#ifndef PRAZAD_TREE_H
#define PRAZAD_TREE_H

#include "Node.h"

class Tree {

private:
    Node * root;

public:

    Tree(){
        root = nullptr;
    }

    void addNode(int hour, int lawyer, bool start);

    void rotateRR(Node * n){
        Node * temp = n->right;
        n->right = temp->left;
        if(n->right != nullptr)
            n->right->parent = n;
        temp->left = n;
        if(n != root) {
            if(n->parent->right == n) {
                temp->parent = n->parent;
                n->parent->right = temp;
            }
            else
            {
                temp->parent = n->parent;
                n->parent->left = temp;
            }
        }
        else
        {
            temp->parent = nullptr;
            root = temp;
        }
        n->parent = temp;
    }

    void rotateLL(Node * n){
        Node * temp = n->left;
        n->left = temp->right;
        if(n->left != nullptr)
            n->left->parent = n;
        temp->right = n;
        if(n != root) {
            temp->parent = n->parent;
            if(n->parent->right == n) {
                n->parent->right = temp;
            }
            else
            {
                n->parent->left = temp;
            }
        }
        else
        {
            temp->parent = nullptr;
            root = temp;
        }
        n->parent = temp;
    }

    void rotateRL(Node * n){
        rotateLL(n->right);
        rotateRR(n);
    }

    void rotateLR(Node * n){
        rotateRR(n->left);
        rotateLL(n);
    }

    void balanceUpwards(Node * n){
        while(n != root) {
            if (n->parent->left == n)
                --n->parent->balance;
            else
                ++n->parent->balance;
            if (n->parent->balance > 1) {
                switch (n->balance) {
                    case -1: //A = 2, B = -1
                        switch (n->left->balance) {
                            case -1:
                                n->parent->balance = 0;
                                n->balance = 1;
                                n->left->balance = 0;
                                break;
                            case 0:
                                n->parent->balance = 0;
                                n->balance = 0;
                                n->left->balance = 0;
                                break;
                            case 1:
                                n->parent->balance = -1;
                                n->balance = 0;
                                n->left->balance = 0;
                                break;
                        }
                        rotateRL(n->parent);
                        break;
                    case 0: //A = 2, B = 0;
                        n->parent->balance = 1;
                        n->balance = -1;
                        rotateRR(n->parent);
                        break;
                    case 1: //A = 2, B = 1
                        n->parent->balance = 0;
                        n->balance = 0;
                        rotateRR(n->parent);
                        break;
                }
                return;
            }
            if (n->parent->balance < -1) {
                switch(n->balance) {
                    case 1: //A = -2, B = 1
                        switch (n->right->balance) {
                            case -1:
                                n->parent->balance = 1;
                                n->balance = 0;
                                n->right->balance = 0;
                                break;
                            case 0:
                                n->parent->balance = 0;
                                n->balance = 0;
                                n->right->balance = 0;
                                break;
                            case 1:
                                n->parent->balance = 0;
                                n->balance = -1;
                                n->right->balance = 0;
                                break;
                        }
                        rotateLR(n->parent);
                        break;
                    case 0: //A = -2, B = 0
                        n->parent->balance = -1;
                        n->balance = 1;
                        rotateLL(n->parent);
                        break;
                    case -1:
                        n->parent->balance = 0;
                        n->balance = 0;
                        rotateLL(n->parent);
                        break;
                }
                return;
            }
            n = n->parent;
        }
    }

    void printAnswear();

    void eraseAll(Node * n){
        if(n->left != nullptr)
            eraseAll(n->left);
        if(n->right != nullptr)
            eraseAll(n->right);
        delete n;
    }

    ~Tree(){
        if(root != nullptr)
            eraseAll(root);
    }


};


#endif //PRAZAD_TREE_H
