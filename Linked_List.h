//
// Created by יובל קרן on 12/26/2022.
//

#ifndef DS2_LINKED_LIST_H
#define DS2_LINKED_LIST_H

#include <cassert>

template <class T>
class Linked_List {
public:
    void insert(T* data);
    Linked_List() :first(nullptr), last(nullptr) {};
    ~Linked_List();

private:
    struct Linked_List_Node{
        T* data;
        Linked_List_Node* next;
        explicit Linked_List_Node(T* data) : data(data), next(nullptr) {};
    };
    Linked_List_Node* first;
    Linked_List_Node* last;
};

template<class T>
void Linked_List<T>::insert(T *data) {
    if(first == nullptr){
        first = new Linked_List_Node(data);
        last = first;
        return;
    }
    else{
        Linked_List_Node* oldLast = last;
        Linked_List_Node* newNode = new Linked_List_Node(data);
        assert(oldLast->next == nullptr);
        oldLast->next = newNode;
        last = newNode;
        return;
    }
}

template<class T>
Linked_List<T>::~Linked_List() {
    Linked_List_Node* node = first;
    if (node == nullptr){
        return;
    }
    else{
        while (node != nullptr){
            delete (node->data);
            Linked_List_Node* temp = node;
            node = node->next;
            delete temp;
        }
    }
}


#endif //DS2_LINKED_LIST_H
