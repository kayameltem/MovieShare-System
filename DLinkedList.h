#ifndef ASIGT2_DLINKEDLIST_H
#define ASIGT2_DLINKEDLIST_H
#include "User.h"
template<class T> struct DNode {
    T* data;
    DNode<T>* next;
    DNode<T>* prev;
};

class DLinkedList {

    private:
        DNode<User>* head;
    public:
        DLinkedList(){
            head = NULL;

        }
        DNode<User>* getHead() {
            return head;

        }
        bool insert(User* data);
        bool del(int id);
        User* search(int id);
};


#endif //ASIGT2_DLINKEDLIST_H
