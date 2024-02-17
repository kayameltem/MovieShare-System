#include "DLinkedList.h"

//adds user if does not exists in the linkedlist otherwise returns error message.
bool DLinkedList::insert(User* data){
    if(head == NULL) {
        head = new DNode<User>();
        head->data = data;
        head->next = head;
        head->prev = head;
        return 1;
    }
    else if (search(data->getID()) == NULL) {
        DNode<User> *temp = new DNode<User>();
        temp->data = data;
        if (head->next == head){
            head->prev = temp;
            head->next = temp;
            temp->prev = head;
            temp->next = head;
        }
        else {
            temp->next = head;
            temp->prev = head->prev;
            head->prev->next = temp;
            head->prev = temp;
        }

        return 1;
    }
    return 0;
}
//deletes movie if exists otherwise returns error message.
bool DLinkedList::del(int id){
    DNode<User>* deleted = NULL;
    if(head != NULL) {
        if (head->data->getID() == id) {
            if (head->next == head) { // contains only one value
                head = NULL;
            }
            else if (head->next == head->prev ){ // contains two value and delete head
                deleted = head;
                head = head->prev;
                head->prev = head;
                head->next = head;
            }
            else {
                deleted = head;
                head->next->prev = head->prev;
                head->prev->next = head->next;
                head = head->next;
            }
            delete deleted;
            deleted = NULL;
            return 1;
        }
        else if (head->next == head->prev && head->prev->data->getID() == id){ // contains two value and delete tail
            deleted = head->prev;
            head->prev = head;
            head->next = head;
            delete deleted;
            deleted = NULL;
            return 1;
        }
        deleted = head->next;
        DNode<User>* prev;
        DNode<User>* next;
        for(;deleted != head ; deleted = deleted->next){
            if(deleted->data->getID() == id) {
                prev =deleted->prev;
                next = deleted->next;
                next->prev = prev;
                prev->next = next;
                delete deleted;
                deleted = NULL;
                return 1;
            }

        }
    }
    deleted = NULL;
    delete deleted;
    return 0;
}
//search movie. If movie exists, returns the movie pointer else returns null.
User* DLinkedList::search(int id){
    if(head != NULL) {
        if (head->data->getID() == id) {
            return head->data;
        }
        DNode<User>* temp = head->next;
        for(; temp != head; temp = temp->next) {
            if(temp->data->getID() == id)
                return temp->data;
        }
    } return NULL ;

}