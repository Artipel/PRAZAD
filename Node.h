//
// Created by Artur on 14.03.2018.
//

#ifndef PRAZAD_NODE_H
#define PRAZAD_NODE_H

#include <vector>

struct BreakLimit{

    int lawyer;
    bool start; //true => start of break, false => end of break

    BreakLimit(int l, bool s) : lawyer(l), start(s) {}

};

class Node{

public:
    const int hour;
    std::vector<int> freeLawyers; //freeLawyers are to be pushed in sorted, ascending order!!!
    std::vector<BreakLimit> limits; //also sorted, ascending order
    Node *parent, *left, *right;
    int balance = 0;

    Node(int h) : hour(h) {
        parent = nullptr;
        left = nullptr;
        right = nullptr;
    }

    Node(int h, int lawyer, bool start) : hour(h){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        limits.push_back(BreakLimit(lawyer, start));
    }

    Node(int h, int lawyer, bool start, std::vector<int> fl) : hour(h){
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        limits.push_back(BreakLimit(lawyer, start));
        freeLawyers = fl;
        freeLawyers.push_back(lawyer);
    }

    bool checkLinking(){ //0 means bad linking, 1 is correct linking
        if(left != nullptr)
            if(left->parent != this)
                return 0;
        if(right != nullptr)
            if(right->parent != this)
                return 0;
        if(parent != nullptr)
            if(parent->left != this && parent->right != this)
                return 0;
        return 1;
    }
};

#endif //PRAZAD_NODE_H
