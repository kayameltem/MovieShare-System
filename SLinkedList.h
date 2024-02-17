#ifndef ASIGT2_SLINKEDLIST_H
#define ASIGT2_SLINKEDLIST_H
#include <string>
#include "Movie.h"
using namespace std;

template<class T> struct SNode {
    T* data;
    SNode<T>* next;
};

class SLinkedList{
private:
    SNode<Movie>* head, *tail;
    public:
        SLinkedList(){
            head = NULL;
            tail = NULL;
        }

        bool isEmpty(){
            if (head == NULL  ){
                return 1;
            }return 0;
        }
        bool insert(Movie* data);
        bool del(int id);
        Movie* search(int id);
        string print(bool c);

};

#endif //ASIGT2_SLINKEDLIST_H
