#ifndef ASIGT2_LIBRARYSYSTEM_H
#define ASIGT2_LIBRARYSYSTEM_H
#include <string>
#include  <fstream>
#include  <iostream>
#include "SLinkedList.h"
#include "DLinkedList.h"
using namespace std;

class LibrarySystem {
    private:
        DLinkedList* users;
        SLinkedList* notChecked;
        string inputFile;
        ofstream out;
    public:
        LibrarySystem(){}
        ~LibrarySystem();
        LibrarySystem(string inputFile,string outputFile);
        void addMovie(const int movieID,const string movieTitle,const int year);
        void addUser(const int userID, const string userName);
        void deleteUser(const int userID);
        void checkoutMovie(const int movieID,const int userID);
        void returnMovie(const int movieID);
        void showAllMovie();
        void showMovie(const int movieID);
        void showUser(const int userID);
        void deleteMovie(const int movieID);
        void fileIO();
};


#endif //ASIGT2_LIBRARYSYSTEM_H
