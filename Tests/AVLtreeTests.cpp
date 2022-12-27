//
// Created by eladm on 26/12/2022.
//
#include <iostream>
#include "../AVL_tree.h"

bool Rank_TEST1()
{
        AVL_Tree<string> tree;
        string a = "1" ;
        string b= "2";
        string c="3";
        string d = "4";
        string e = "5";

        string* q1 = &a;
        string* q2 = &b;
        string* q3 = &c;
        string* q4 = &d;
        string* q5 = &e;

        tree.insert(q2);
        tree.insert(q1);
        tree.insert(q3);
        tree.insert(q4);
        tree.insert(q5);
        string  s1 = *tree.select(2);
       // tree.simple_print_inorder();
    return 0;
}


int main(){
Rank_TEST1();
    return  0;
}