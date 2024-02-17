#include <iostream>
#include "SLinkedList.h"
#include <sstream>
//inserts movie from head if movie does not exist in the linkedlist.
bool SLinkedList::insert(Movie* data){
    if(head== NULL) {
        head = new SNode<Movie>();
        head->data = data;
        head->next = head;
        tail = head;
        return 1;
    }
    else if (!search(data->getID())) {
        SNode<Movie> *temp = new SNode<Movie>();
        temp->data = data;
        temp->next = head;
        tail->next = temp;
        tail = temp;
        return 1;
    } return 0;
}
//searches movie. If movie exists returns the movie,else returns null.
Movie* SLinkedList::search(int id){
    if(head != NULL) {
        if (head->data->getID() == id) {
            return head->data;
        }
        SNode<Movie>* temp = head->next;
        for(; temp != head; temp = temp->next) {
            if(temp->data->getID() == id)
                return temp->data;
        }
    } return NULL ;

}
//prints contents of the linkedlist.
string SLinkedList::print(bool c){
    string str ="";
    SNode<Movie>* temp = head;
    if(head != NULL){
        do{
            str.append(temp->data->display(c)) ;
            temp = temp->next;
        } while(temp != head);
    }
    return str;

}
//deletes movie object.
bool SLinkedList::del(int id){
    SNode<Movie>* deleted = NULL ;
    if (head != NULL ) {
        if (head->data->getID() == id) {
            deleted  = head;
            if (head == tail) { // searched node at the head and list contains only one node
                tail = NULL;
                head = tail;
            }
            else if(head->next == tail) { //searched node at the head and list contains two nodes.
                tail->next = tail;
                head = tail;
            }
            else {
                head = head->next; //searched node at the head and list contains more than two nodes.
                tail->next = head;
            }
           delete deleted;
            deleted = NULL;
            return 1;
        }
        else if(tail->data->getID() == id && head->next == tail){
            deleted = tail;
            head->next = head;
            tail = head;
            delete deleted;
            deleted = NULL;
            return 1;
        }
        SNode<Movie> *temp = head;
        SNode<Movie> *next;
        do {
            if(temp->next->data->getID() == id) {
                deleted = temp->next;
                if(temp->next == tail) {
                    temp->next = head;
                    tail = temp;
                    delete deleted;
                    deleted = NULL;
                    return 1;
                }
                next = temp->next->next;
                temp->next = next;
                delete deleted;
                deleted = NULL;
                return 1;
            } temp = temp->next;
        }while(temp != head );
    }
    return 0;

}
