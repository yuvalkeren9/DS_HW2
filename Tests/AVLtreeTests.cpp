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
    string c="4";
    string d = "5";
    string e = "6";

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

    string  s1 = *tree.select(1);
    string  s2 = *tree.select(2);
    string  s3 = *tree.select(3);
    string  s4 = *tree.select(4);
    string  s5 = *tree.select(5);

    cout << "s1: "<< s1 << endl;
    cout << "s2: "<< s2 << endl;
    cout << "s3: "<< s3 << endl;
    cout << "s4: "<< s4 << endl;
    cout << "s5: "<< s5 << endl;

    cout << endl << endl;
    tree.Delete(q1);
    a="3";
    tree.insert(q1);

    s1 = *tree.select(1);
    s2 = *tree.select(2);
    s3 = *tree.select(3);
    s4 = *tree.select(4);
    s5 = *tree.select(5);

    cout << "s1: "<< s1 << endl;
    cout << "s2: "<< s2 << endl;
    cout << "s3: "<< s3 << endl;
    cout << "s4: "<< s4 << endl;
    cout << "s5: "<< s5 << endl;

    return 0;
}


int main(){
Rank_TEST1();
    return  0;
}