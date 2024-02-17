#ifndef ASIGT2_USER_H
#define ASIGT2_USER_H
#include "SLinkedList.h"
using namespace std;

class User {
    private:
        int id;
        string name;
        SLinkedList* movies ;

    public:
        User(int id,string name){
            this->id = id;
            this->name = name;
            movies = new SLinkedList();
        }
        int getID() {
            return id;
        }
        string getName() {
            return name;
        }
        SLinkedList* getMovies(){
            return movies;
        }
};
#endif //ASIGT2_USER_H
