//
// Created by יובל קרן on 11/17/2022.
//

#ifndef MAIN_CPP_AVL_TREE_H
#define MAIN_CPP_AVL_TREE_H

#include <cmath>
#include <math.h>
#include <ostream>
#include <iostream>
#include "wet2util.h"



using namespace std;


template <class T>
class AVL_Tree{

private:
    class Node;
    bool was_tree_rotated;
    Node* rotated_node;
    Node* main_root;

    typename AVL_Tree<T>::Node *insert_AUX(AVL_Tree::Node *current_root, T *data, StatusType *status);
    typename AVL_Tree<T>::Node *delete_AUX(AVL_Tree::Node *current_root, T *data, StatusType *status);
    typename AVL_Tree<T>::Node *search_AUX(AVL_Tree::Node *current_root, T *data, StatusType *status) const;
    void destroy_AUX(AVL_Tree::Node *root);
    static void fixLeavesHeight(Node* root);
    int balance(Node* node);

    //rotation functions
    void LL_rotation(Node* node);
    void LR_rotation(Node* node);
    void RR_rotation(Node *node);
    void RL_rotation(Node* node);

    void findLargerNeighbor_AUX(T*& orig, Node* current_node, Node *&current_closest_node) const;
    void findSmallerNeighbor_AUX(T*& orig, Node* current_node, Node *&current_closest_node) const;

    void setMainRoot( Node* new_root);

    void putDataInArrayInorder_AUX(AVL_Tree::Node *node, T *&output, int *counter) const;
    void emptyTree_AUX(Node *node);

    void putPTRDataInArrayInorder_AUX(AVL_Tree::Node *node, T **output, int *counter) const;
    void fillEmptyTreeInorder_AUX(AVL_Tree::Node *node, T **output, int &counter) const;

    T* select_AUX(Node* node, int k) const;


public:
    AVL_Tree(): was_tree_rotated(false), rotated_node(nullptr), main_root(nullptr) {};
    ~AVL_Tree(){  destroy_AUX(main_root);  }
    AVL_Tree& operator=(const AVL_Tree<T>& other);
    StatusType insert(T* data);
    StatusType Delete(T* data);
    void simple_print_inorder() const;
    void emptyTree();
//    Node* getRoot();
//    T* getRootData();
    T* search(T* data_ptr ,StatusType *status ) const;
    T* get_max_in_tree();
    typename AVL_Tree<T>::Node *find_closest(AVL_Tree::Node *current_root);
    void setTreeToNull();
    void destroy();
    AVL_Tree<T>* Empty_almost_Full_Tree_Build(int numOfNodes);
    static typename AVL_Tree<T>::Node *build_full_tree_aux(int hight);

    static typename AVL_Tree<T>::Node * delete_spare_nodes(  Node* current ,int spare_nodes);
    static typename AVL_Tree<T>::Node * delete_spare_nodes_Aux(  Node* current ,int* spare_nodes);

    T* select(int k) const;


    //Functions for finding neighbors
    T* findLargerNeighbor(T* orig) const;
    T* findSmallerNeighbor(T* orig) const;

    void putDataInArrayInorder(T *output) const;
    void putPTRDataInArrayInorder(T **output) const;
    void fillEmptyTreeInorder(T **output) const;

    //Yuval's functions for testing
    string printInOrderTest(ostringstream &output) const;

    void putDataInArrayInorderWithLimits(T *output, T *lowerBound, T *upperBound, int &counterReferenceToReturn) const;
    void putDataInArrayInorderWithLimits_AUX(AVL_Tree::Node *node, T *&output, int &counter, T *lowerBound, T *upperBound) const;
};


/** Node Implication */
template<class T>
class AVL_Tree<T>::Node{

private:
    T* data;
    Node* left;
    Node* right;
    long long int height;
    long long int rank;
    friend class AVL_Tree<T>;
    Node(): data(nullptr), left(nullptr), right(nullptr), height(0), rank(1) {};


public:
    static Node* newNode(T* data);
    static int get_height(Node* node);
    static int get_rank(Node* node);
};

/**
 *  Function that creates a node
 * @tparam T the type of data
 * @param data_ptr ptr to data
 * @return new note storing the received data
 */
template<class T>
typename AVL_Tree<T>::Node* AVL_Tree<T>::Node::newNode(T* data_ptr) {
    Node *node = new Node();
    node->data = data_ptr;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;
    return (node);
}

/**
 * Function that calculates and returns the height of a node, according to definition.
 * @tparam T
 * @param node
 * @return height of the node.
 */
template<class T>
int AVL_Tree<T>::Node::get_height(AVL_Tree<T>::Node *node) {
    if (node == nullptr) {
        return -1;
    }
    return node->height;
}


template<class T>
int AVL_Tree<T>::Node::get_rank(AVL_Tree<T>::Node *node) {
    if (node == nullptr) {
        return 0;
    }
    return node->rank;
}



/** AVL tree implication */

template<class T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::insert_AUX(AVL_Tree::Node* current_root, T *data_ptr, StatusType *status) {
    if (current_root == nullptr){
        //we have reached end of tree and insert the node
        current_root = Node::newNode(data_ptr);

        //checking if allocation succeed
        if (current_root != nullptr){
            *status = StatusType::SUCCESS;
            return current_root;
        }
        else{
            *status = StatusType::ALLOCATION_ERROR;
            return current_root;
        }
    }

    if (*(current_root->data) > *data_ptr ){
        //going into left node
        current_root->left = insert_AUX(current_root->left, data_ptr, status);
        current_root->rank += 1;
        if (Node::get_height(current_root->left) + 1 <= Node::get_height(current_root)){
            return current_root;

        }
        current_root->height = 1 + max(Node::get_height(current_root->left), Node::get_height(current_root->right));
        balance(current_root);
        if (was_tree_rotated){
            current_root = rotated_node;
            was_tree_rotated = false;
        }
        return current_root;
    }
    //going into right node
    else{
        current_root->right = insert_AUX(current_root->right, data_ptr, status);
        current_root->rank += 1;
        if (Node::get_height(current_root->right) + 1 <= Node::get_height(current_root)){
            return current_root;   //balance was not broken
        }
        current_root->height = 1 + max(Node::get_height(current_root->left), Node::get_height(current_root->right));
        balance(current_root);
        if (was_tree_rotated){
            current_root = rotated_node;
            was_tree_rotated = false;
        }
        return current_root;
    }
}


template<class T>
StatusType AVL_Tree<T>::insert(T *data_ptr) {
    if (!data_ptr){
        return StatusType::INVALID_INPUT;
    }
    StatusType tempStatus = StatusType::SUCCESS;
    StatusType* status = &tempStatus;

    if (main_root == nullptr){
        main_root = Node::newNode(data_ptr);
        if (main_root == nullptr)
            return StatusType::ALLOCATION_ERROR;
        else
            return StatusType::SUCCESS;
    }
    insert_AUX(main_root, data_ptr, status);
    return (*status);
}

template<class T>
int AVL_Tree<T>::balance(AVL_Tree::Node *node) {
    if(node== nullptr)
        return  0;
    int right_height = Node::get_height(node->right);
    int left_height = Node::get_height(node->left);
    int balance_factor = left_height - right_height;
    if (abs(balance_factor)< 2 )
        return  balance_factor;

    //tree is not balanced, and we check which kind of rotation is needed
    else{
        if(balance_factor==2)
        {
            if(balance(node->left)==-1)
            {
                LR_rotation(node);
                return 0;
            }
            else
            {
                LL_rotation(node);
                return 0;
            }
        }
        else
        {
            if(balance(node->right)==1)
            {
                RL_rotation(node);
                return 0;
            }
            else
            {
                RR_rotation(node);
                return  0;
            }
        }
    }
}

template<class T>
void AVL_Tree<T>::LL_rotation(AVL_Tree::Node *node) {

    bool isCurrentNodeTheMainRoot = false;
    if (main_root == node){
        isCurrentNodeTheMainRoot = true;
    }

    //preparing to roll
    Node* B = node;
    Node* AR = B->left->right;
    Node* A = B->left;

    //preparing to rank
    long long int BR_rank = Node::get_rank(B->right);
    long long int AR_rank = Node::get_rank(AR);
    long long int B_rank = Node::get_rank(B);





    //rotating
    B->left = AR;
    A->right = B;

    B->height = 1 + max(Node::get_height(B->left), Node::get_height(B->right));
    A->height =  1 + max(Node::get_height(A->left), Node::get_height(A->right));


    //updating rank
    B->rank = 1 + BR_rank + AR_rank;
    A->rank = B_rank;

    was_tree_rotated = true;
    rotated_node = A;

    if(isCurrentNodeTheMainRoot){
        main_root = A;
    }
}

template<class T>
void AVL_Tree<T>::RR_rotation(AVL_Tree::Node *node) {

    bool isCurrentNodeTheMainRoot = false;
    if (main_root == node){
        isCurrentNodeTheMainRoot = true;
    }

    Node* B = node;
    Node* A = B->right;
    Node* AL = A->left;

    //preparing to rank
    long long int BL_rank = Node::get_rank(B->left);
    long long int AL_rank = Node::get_rank(AL);
    long long int B_rank = Node::get_rank(B);

    //rotating
    B->right = AL;
    A->left = B;

    B->height = 1 + max(Node::get_height(B->left), Node::get_height(B->right));
    A->height =  1 + max(Node::get_height(A->left), Node::get_height(A->right));

    //updating rank
    B->rank = 1 + AL_rank + BL_rank;
    A->rank = B_rank;

    was_tree_rotated = true;
    rotated_node = A;

    if(isCurrentNodeTheMainRoot){
        main_root = A;
    }
}

template<class T>
void AVL_Tree<T>::LR_rotation(AVL_Tree::Node *node) {

    bool isCurrentNodeTheMainRoot = false;
    if (main_root == node){
        isCurrentNodeTheMainRoot = true;
    }

    Node* C = node;
    Node* A = C->left;
    Node* B = A->right;

    Node* BL = B->left;
    Node* BR = B->right;

    //preparing to rank
    long long int AL_rank = Node::get_rank(A->left);
    long long int BL_rank = Node::get_rank(BL);
    long long int BR_rank = Node::get_rank(BR);
    long long int CR_rank = Node::get_rank(C->right);


    //rotating
    C->left = BR;
    A->right = BL;
    B->left = A;
    B->right = C;

    A->height= 1 + max(Node::get_height(A->left), Node::get_height(A->right));
    C->height = 1 + max(Node::get_height(C->left), Node::get_height(C->right));
    B->height =  1 + max(Node::get_height(B->left), Node::get_height(B->right));


    //ranking
    C->rank = BR_rank + CR_rank + 1;
    A->rank = AL_rank + BL_rank + 1;
    B->rank = A->rank + C->rank + 1;

    was_tree_rotated = true;
    rotated_node = B;

    if(isCurrentNodeTheMainRoot){
        main_root = B;
    }
}

template<class T>
void AVL_Tree<T>::RL_rotation(AVL_Tree::Node *node) {

    bool isCurrentNodeTheMainRoot = false;
    if (main_root == node){
        isCurrentNodeTheMainRoot = true;
    }

    Node* C = node;
    Node* A = C->right;
    Node* B = A->left;

    Node* BL = B->left;
    Node* BR = B->right;

    //preparing to rank
    long long int BL_rank = Node::get_rank(BL);
    long long int BR_rank = Node::get_rank(BR);
    long long int CL_rank = Node::get_rank(C->left);
    long long int AR_rank = Node::get_rank(A->right);


    //rotating
     C->right = BL;
     A->left = BR;
     B->left = C;
     B->right = A;

    A->height= 1 + max(Node::get_height(A->left), Node::get_height(A->right));
    C->height = 1 + max(Node::get_height(C->left), Node::get_height(C->right));
    B->height =  1 + max(Node::get_height(B->left), Node::get_height(B->right));

    A->rank = AR_rank + BR_rank +1;
    C->rank = BL_rank + CL_rank + 1;
    B->rank = A->rank + C->rank + 1;

    was_tree_rotated = true;
    rotated_node = B;

    if(isCurrentNodeTheMainRoot){
        main_root = B;
    }
}
template<class T>
 T* AVL_Tree<T>::search(T* data_ptr ,StatusType *status ) const
{
    if(data_ptr== nullptr)
    {
        *status = StatusType::INVALID_INPUT;
        return nullptr;
    }
    if(main_root == nullptr)
    {
        *status = StatusType::FAILURE;
        return nullptr;
    }
   Node* temp = search_AUX(main_root,data_ptr,status);
    if(temp != nullptr)
        return  temp->data;

    return nullptr;
}
template<class T>
typename AVL_Tree<T>::Node* AVL_Tree<T>::search_AUX(AVL_Tree<T>::Node *current_root, T* data_ptr, StatusType *status) const {
    if (current_root == nullptr) {
        *status = StatusType::FAILURE;
        return nullptr;
    }
    if (*(current_root->data) == *data_ptr) {
        *status = StatusType::SUCCESS;
        return current_root;
    }

    if (*(current_root->data) > *data_ptr) {
        current_root = current_root->left;
      return  search_AUX(current_root, data_ptr, status);
    } else {
        current_root = current_root->right;
       return search_AUX(current_root, data_ptr, status);
    }

}

template<class T>
StatusType AVL_Tree<T>::Delete(T *data_ptr) {
    if (!data_ptr){
        return StatusType::INVALID_INPUT;
    }
    StatusType tempStatus = StatusType::SUCCESS;
    StatusType* status = &tempStatus;

    if (main_root == nullptr){
        *status = StatusType::FAILURE;
        return *status;
    }
    if(search(data_ptr,status)!= nullptr)
    {
        main_root = delete_AUX(main_root, data_ptr, status);
    } else
    {
        *status = StatusType::FAILURE;
        return *status;
    }

    return *status;
}

template<class T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::delete_AUX(AVL_Tree::Node *current_root, T *data_ptr, StatusType *status) {
    if (current_root == nullptr) {
        *status = StatusType::FAILURE;
        return nullptr;
    } else if (*(current_root->data) > *data_ptr) {
        //going into left node
        current_root->left = delete_AUX(current_root->left, data_ptr, status);
    } else if (*(current_root->data) < *data_ptr) {
        //going into right node
        current_root->right = delete_AUX(current_root->right, data_ptr, status);
    }

        //found the node to be deleted
    else if (current_root->right != nullptr && current_root->left != nullptr){//has 2 sons
        Node *closest_node = current_root;
        closest_node = find_closest(current_root);
        T* temp = closest_node->data;
        closest_node->data = current_root->data;
        current_root->data = temp;
        current_root->right = delete_AUX(current_root->right,data_ptr,status);
    }
    else {// one son or non sons
        if (current_root->right == nullptr && current_root->left == nullptr)// if leaf
        {
            Node *temp = current_root;
            delete temp;
            current_root = nullptr;
            *status = StatusType::SUCCESS;

        } else {
            if (current_root->right == nullptr || current_root->left == nullptr)// has 1 son
            {
                if (current_root->left != nullptr)// if has  left son
                {
                    T *temp = current_root->left->data;
                    current_root->left->data = current_root->data;
                    current_root->data = temp;
                    delete current_root->left;
                    current_root->left = nullptr;
                    *status = StatusType::SUCCESS;
                }
                if (current_root->right != nullptr)// if has right son
                {
                    T *temp = current_root->right->data;
                    current_root->right->data = current_root->data;
                    current_root->data = temp;
                    delete current_root->right;
                    current_root->right = nullptr;
                    *status = StatusType::SUCCESS;

                }
            }
        }
    }
    if (current_root == nullptr) {
        return current_root;
    }
    current_root->rank -= 1;
    current_root->height = 1 + max(Node::get_height(current_root->left), Node::get_height(current_root->right));//updating hight
    //current_root->rank=-1;
    balance(current_root);// balance the tree if needed
    if (was_tree_rotated) {
        current_root = rotated_node;
        was_tree_rotated = false;
    }
    return  current_root;
}

//template<class T>
// typename AVL_Tree<T>::Node* AVL_Tree<T>::getRoot() {
//    return main_root;
//}
//template<class T>
//T* AVL_Tree<T>::getRootData() {
//    return main_root->data;
//}

template<class T>
void AVL_Tree<T>::putDataInArrayInorder(T *output) const {
    int counter =0;
    int* counter_ptr = &counter;
    AVL_Tree<T>::putDataInArrayInorder_AUX(main_root, output, counter_ptr);
}

template<class T>
void AVL_Tree<T>::putDataInArrayInorder_AUX(AVL_Tree::Node *node, T *&output, int *counter) const {
    if(node == nullptr){
        return;
    }
    putDataInArrayInorder_AUX(node->left, output, counter);
    output[*counter] = *(node->data);
    ++(*counter);
    putDataInArrayInorder_AUX(node->right, output, counter);
}

template<class T>
void AVL_Tree<T>::putDataInArrayInorderWithLimits(T *output, T *lowerBound, T *upperBound, int &counterReferenceToReturn) const {
    int counter =0;
    int& counterReference = counter;
    AVL_Tree<T>::putDataInArrayInorderWithLimits_AUX(main_root, output, counterReference, lowerBound, upperBound);
    counterReferenceToReturn = counterReference;
}

template<class T>
void AVL_Tree<T>::putDataInArrayInorderWithLimits_AUX(AVL_Tree::Node *node, T *&output, int &counter, T *lowerBound, T *upperBound) const {
    if(node == nullptr){
        return;
    }
    T* currentNodeData = node->data;
    if(*currentNodeData > *upperBound){
        putDataInArrayInorderWithLimits_AUX(node->left, output, counter, lowerBound, upperBound);
    }
    else if( *currentNodeData < *lowerBound){
        putDataInArrayInorderWithLimits_AUX(node->right, output, counter, lowerBound, upperBound);
    }
    else if( *currentNodeData == *lowerBound){
        output[counter] = *currentNodeData;
        ++(counter);
        putDataInArrayInorderWithLimits_AUX(node->right, output, counter, lowerBound, upperBound);
    }
    else if(*currentNodeData == *upperBound){
        putDataInArrayInorderWithLimits_AUX(node->left, output, counter, lowerBound, upperBound);
        output[counter] = *currentNodeData;
        ++(counter);
    }
    else {
        putDataInArrayInorderWithLimits_AUX(node->left, output, counter, lowerBound, upperBound);
        output[counter] = *currentNodeData;
        ++(counter);
        putDataInArrayInorderWithLimits_AUX(node->right, output, counter, lowerBound, upperBound);
    }
}

template<class T>
void AVL_Tree<T>::putPTRDataInArrayInorder(T  **Arr) const {
    int counter =0;
    int* counter_ptr = &counter;
    AVL_Tree<T>::putPTRDataInArrayInorder_AUX(main_root, Arr, counter_ptr);
}

template<class T>
void AVL_Tree<T>::putPTRDataInArrayInorder_AUX(AVL_Tree::Node *node, T **Arr, int *counter) const  {
    if(node == nullptr){
        return;
    }
    putPTRDataInArrayInorder_AUX(node->left, Arr, counter);
    Arr[*counter] = node->data;
    ++(*counter);
    putPTRDataInArrayInorder_AUX(node->right, Arr, counter);
}


template<class T>
void AVL_Tree<T>::fillEmptyTreeInorder(T** arr) const {
//    int counter =0;
    int counterRefrence =0;
//    int* counter_ptr = &counter;
    AVL_Tree<T>::fillEmptyTreeInorder_AUX(main_root, arr, counterRefrence);
}

template<class T>
void AVL_Tree<T>::fillEmptyTreeInorder_AUX(AVL_Tree::Node *node, T **arr, int &counter) const {
    if(node == nullptr){
        return;
    }
    fillEmptyTreeInorder_AUX(node->left, arr, counter);
    node->data = arr[counter];
    ++(counter);
    fillEmptyTreeInorder_AUX(node->right, arr, counter);
}


template<class T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::find_closest(AVL_Tree::Node *current_root) {
    if( current_root->right== nullptr)
     return current_root;
    current_root = current_root->right;
    while (current_root->left != nullptr) {    //REVIEW::::: MAYBE THERE IS A SEG FAULT HERE?
        current_root = current_root->left;
    }
    return  current_root;
}

template<class T>
T* AVL_Tree<T>::get_max_in_tree() {
    AVL_Tree<T>::Node* runner = main_root;
    if(runner== nullptr)
    {
        return nullptr;
    }
    while (runner->right != nullptr) {    //REVIEW::::: MAYBE THERE IS A SEG FAULT HERE?
        runner = runner->right;
    }
    return  runner->data;
}

template<class T>
T *AVL_Tree<T>::findLargerNeighbor(T *orig) const {
    if (main_root == nullptr){
        return nullptr;
    }
    Node* current_closest_node = nullptr;
    findLargerNeighbor_AUX(orig, main_root, current_closest_node);
    if(current_closest_node == nullptr){
        return nullptr;
    }
    else {
        return current_closest_node->data;
    }
}

template<class T>
T *AVL_Tree<T>::findSmallerNeighbor(T *orig) const {
    if (main_root == nullptr){
        return nullptr;
    }
    Node* current_closest_node = nullptr;
    findSmallerNeighbor_AUX(orig, main_root, current_closest_node);
    if(current_closest_node == nullptr){
        return nullptr;
    }
    else {
        return current_closest_node->data;
    }
}

template<class T>
typename AVL_Tree<T>::Node *AVL_Tree<T>::build_full_tree_aux(int height) {
    if (height < 0){
        return nullptr;
    }

    Node* node=  AVL_Tree<T>::Node::newNode(nullptr);

    node->height=height;
    node->left = build_full_tree_aux(height-1);
    node->right = build_full_tree_aux(height-1);
    return node;
}

template<class T>
void AVL_Tree<T>::setMainRoot(AVL_Tree::Node *new_root) {
    this->main_root=new_root;
}
template<class T>
 typename AVL_Tree<T>::Node *AVL_Tree<T>::delete_spare_nodes(AVL_Tree::Node *current, int spare_nodes) {
   int nun_of_nodes_to_delete = spare_nodes;
   int *spare_nodes_ptr = nullptr;
   spare_nodes_ptr= &nun_of_nodes_to_delete;
   current = delete_spare_nodes_Aux(current,spare_nodes_ptr);
   fixLeavesHeight(current);
    return  current;
}

template<class T>
 typename AVL_Tree<T>::Node* AVL_Tree<T>::delete_spare_nodes_Aux(  Node* current ,int* spare_nodes) {

    if (current == nullptr) {
        return nullptr;
    }
    if (*spare_nodes == 0) {
        return current;
    }
    if (current->left == nullptr && current->right == nullptr)// if leaf
    {
        Node *temp = current;
        delete temp;
        current = nullptr;
        *spare_nodes= (*spare_nodes)-1;
        return nullptr;
    }
    current->right = delete_spare_nodes_Aux(current->right,spare_nodes);
    current->left = delete_spare_nodes_Aux(current->left,spare_nodes);
    return  current;
}

template<class T>
void AVL_Tree<T>::findLargerNeighbor_AUX(T *&orig, AVL_Tree::Node *current_node, Node *&current_closest_node) const {
    if (current_node == nullptr){
        return;
    }
    if(*(current_node->data) > *orig){    //canadiate found
        if(current_closest_node == nullptr){   //if this is the first time
            current_closest_node = current_node;
        }
        else{
            if(*(current_node->data) < *(current_closest_node->data)){
                current_closest_node = current_node;
            }
        }
        findLargerNeighbor_AUX(orig, current_node->left, current_closest_node); //look if there is a smaller node
    }
    else{
        findLargerNeighbor_AUX(orig, current_node->right, current_closest_node); //look if there is a larger node
    }
}

template<class T>
void AVL_Tree<T>::findSmallerNeighbor_AUX(T *&orig, AVL_Tree::Node *current_node, Node *&current_closest_node) const {
    if (current_node == nullptr){
        return;
    }
    if(*(current_node->data) < *orig){    //canadiate found
        if(current_closest_node == nullptr){   //if this is the first time
            current_closest_node = current_node;
        }
        else{
            if(*(current_node->data) > *(current_closest_node->data)){
                current_closest_node = current_node;
            }
        }
        findSmallerNeighbor_AUX(orig, current_node->right, current_closest_node); //look if there is a larger node
    }
    else{
        findSmallerNeighbor_AUX(orig, current_node->left, current_closest_node); //look if there is a smaller node
    }
}


template<class T>
void AVL_Tree<T>::destroy_AUX(AVL_Tree<T>::Node* root) {
    if(root!= nullptr)
    {
        destroy_AUX(root->right);
        destroy_AUX(root->left);
        delete root;
    }
}
template<class T>
void AVL_Tree<T>::destroy() {
    destroy_AUX(this->main_root);
}



template<class T>
 AVL_Tree<T>* AVL_Tree<T>::Empty_almost_Full_Tree_Build(int numOfNodes) {

    AVL_Tree<T>* new_tree = new AVL_Tree<T>();//Try catch?
    if(numOfNodes==0){
        return new_tree;
    }
    int height = ceil(log2(numOfNodes+1)) - 1;
    Node* temp = nullptr;
    try{
        temp = build_full_tree_aux(height);  //first  making a full tree with many nodes, temp points to a root
    }catch (std::bad_alloc&){
        destroy_AUX(temp);
        throw (std::bad_alloc());
    }
    int spare_nodes = pow(2,height+1) - (1 + numOfNodes);
    temp = delete_spare_nodes(temp,spare_nodes);  //second
    new_tree->setMainRoot(temp);
    return  new_tree;
}

template<class T>
void AVL_Tree<T>::emptyTree() {
    emptyTree_AUX(main_root);
    main_root = nullptr;
}

template<class T>
void AVL_Tree<T>::emptyTree_AUX(AVL_Tree::Node *node) {
    if(node == nullptr){
        return;
    }
    emptyTree_AUX(node->left);
    emptyTree_AUX(node->right);
    delete node->data;
    delete node;
}

template<class T>
AVL_Tree<T> &AVL_Tree<T>::operator=(const AVL_Tree<T> &other) {
    destroy_AUX(main_root);
    main_root = other.main_root;
    return *this;
}

template<class T>
void AVL_Tree<T>::setTreeToNull(){
    main_root = nullptr;
}

template<class T>
void AVL_Tree<T>::fixLeavesHeight(Node* root){
    if( root == nullptr){
        return;
    }
    if (root->left == nullptr && root->right == nullptr){
        root->height = 0;
    }
    fixLeavesHeight(root->left);
    fixLeavesHeight(root->right);
}


template<class T>
T* AVL_Tree<T>::select(int k) const{
    Node* node = main_root;
    return select_AUX(node, k);
}

template<class T>
T* AVL_Tree<T>::select_AUX(Node* node, int k) const{
//    if(node == nullptr)
//    {
//        return nullptr;
//    }
    int rank = Node::get_rank(node->left);
    if (rank == k-1){
        return node->data;
    }
    else if (rank > k-1 ){
        return select_AUX(node->left, k);
    }
    else{
        return select_AUX(node->right, k - rank - 1);
    }

}









#endif //MAIN_CPP_AVL_TREE_H