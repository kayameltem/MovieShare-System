#ifndef ASIGT2_MOVIE_H
#define ASIGT2_MOVIE_H
#include <string>
#include <sstream>
using namespace std;

class Movie {
    private:
        int id;
        string title;
        int year;
        int status = -1;
    public :
        Movie(const int id, const string title, const int year){
            this->id = id;
            this->title = title;
            this->year = year;
        }
        Movie(Movie* movie){    // copy constructor
            id = movie->id;
            title = movie->title;
            year = movie->year;
        }
        //displays movie id, title year and whether checked out.
        string display(bool c) {
            stringstream str;
            if (c){
                str<< id <<" "<< title <<" " << year << "\n";
                return str.str();
            }
            else if(status != -1){
                str<< id <<" "<< title<<" "  << year << " Checked out by User " << status<< "\n";
                return str.str();
            }
            str<< id <<" "<< title  <<" "<< year<< " Not checked out\n" ;
            return str.str();
        }
        int getID() {
            return id;
        }
        void setStatus(int status){
            this->status = status;
        }
};

#endif //ASIGT2_MOVIE_H
