#include "LibrarySystem.h"
#include <sstream>
#include <vector>

LibrarySystem::LibrarySystem(string inputFile,string outputFile) {
    out.open(outputFile);
    this->inputFile = inputFile;
    users = new DLinkedList();
    notChecked = new SLinkedList();
    fileIO();
    delete users;
    users = NULL;
    delete notChecked;
    notChecked = NULL;
}
LibrarySystem::~LibrarySystem(){
    delete users;
    delete notChecked;
}
// adds movie if does not exist in the library, otherwise returns error message.
void LibrarySystem::addMovie(const int movieID,const string movieTitle,const int year){
    stringstream str;
    Movie* movie = new Movie(movieID,movieTitle,year);
    DNode<User>* user = users->getHead();
    if (user != NULL ){
        do {
            if(user->data->getMovies()->search(movieID) != NULL){
                str <<"Movie " << movieID <<" already exists\n";
                out<< str.str();
                return;
            }
            user = user->next;
        } while(user != users->getHead());
    }
    if(notChecked->insert(movie)){
        str<<"Movie " << movieID << " has been added\n";
    }
    else {str<<"Movie " << movieID <<" already exists\n"; }
    out << str.str();
}
//adds user if does not exist in the library, otherwise returns error message.
void LibrarySystem::addUser(const int userID, const string userName){
    stringstream str;
    User* user = new User(userID,userName);
    if(users->insert(user)) {
        str << "User " << userID << " has been added\n";
    }
    else {
            str << "User " << userID << " already exists\n";}
    out << str.str();
}
//deletes user if exists, otherwise returns error message.
void LibrarySystem::deleteUser(const int userID) {
    stringstream str;
    if(users->del(userID)) {
        str <<"User "<<userID<< " has been deleted\n";
    }
    else {str <<"User "<<userID<<" does not exist\n";}
    out << str.str();
}
// returns movie is checked out or not if exists, otherwise returns error message.
void LibrarySystem::checkoutMovie(const int movieID,const int userID){
    stringstream str;
    if(notChecked->search(movieID)!= NULL){
        if (!users->search(userID)){
            str << "User " << userID << " does not exist for checkout\n";
        }
        else {
            Movie* movie = new Movie(notChecked->search(movieID));
            movie->setStatus(userID);
            users->search(userID)->getMovies()->insert(movie);
            notChecked->del(movieID);
            str << "Movie " << movieID << " has been checked out by User " << userID << "\n";
        }
    }
    else {str << "Movie " << movieID << " does not exist for checkout\n";}
    out << str.str();
}
//returns movie to library back if exists, otherwise returns error message.
void LibrarySystem::returnMovie(const int movieID){
    stringstream str;
    if(notChecked->search(movieID) != NULL) {
        str<< "Movie " << movieID <<" has not been checked out\n";
    }
    else if(notChecked->search(movieID) == NULL) {
        DNode<User> *user = users->getHead();
        if (user != NULL) {
            do {
                if (user->data->getMovies()->search(movieID)) {
                    Movie* movie = new Movie(user->data->getMovies()->search(movieID)) ;
                    movie->setStatus(-1);
                    user->data->getMovies()->del(movieID);
                    notChecked->insert(movie);
                    str << "Movie " << movieID << " has been returned\n";
                    break;
                }
                user = user->next;
            } while (user != users->getHead());
        }
    }
    if(str.str().size() == 0) {
        str << "Movie " << movieID<< " not exist in the library\n";
    }
    out << str.str();
}
//shows all movies in library.
void LibrarySystem::showAllMovie(){
    stringstream str;
    str << notChecked->print(0);
    DNode<User> *user = users->getHead();
    if (user != NULL) {
        do{
            str << user->data->getMovies()->print(0);
            user = user->next;
        }while (user != users->getHead());
    }
    out << str.str();
}
//shows movie if exists, otherwise returns error message.
void LibrarySystem::showMovie(const int movieID){
    stringstream str;
    Movie* movie = notChecked->search(movieID);
    if(movie) {
        str << movie->display(0);
    }
    else {
        DNode<User> *user = users->getHead();
        if (user != NULL) {
            do {
                movie = user->data->getMovies()->search(movieID);
                if (movie != NULL) {
                    str << movie->display(0);
                    break;
                }
                user = user->next;
            } while (user != users->getHead());
        }

    }

    if(str.str().size() == 0){
        str <<"Movie with the id " << movieID <<" does not exist\n";
    }
    out << str.str();
    }
//shows user if exists,otherwise returns error message.
void LibrarySystem::showUser(const int userID){
    User* user = users->search(userID);
    stringstream str;
    if(user != NULL){
        str << "User id: " << userID << " User name: " << user->getName()<< "\n"
        << "User " <<userID << " checked out the following Movies:\n";
        if(!user->getMovies()->isEmpty()) {
            str<< "Movie id - Movie name - Year\n" ;
        }
        str << user->getMovies()->print(1);
    }
    else {str<<"User "<< userID << " does not exist\n";}
    out  << str.str();

}
//Deletes movie if exists, otherwise returns error message.
void LibrarySystem::deleteMovie(const int movieID) {
    stringstream str;
    Movie* movie = notChecked->search(movieID);
    if ( movie != NULL) {
        notChecked->del(movieID);
        str << "Movie " << movieID <<" has not been checked out\nMovie "<< movieID <<" has been deleted\n";
    }
    else {
        DNode<User> *user = users->getHead();
        if (user != NULL) {
            do {
                movie = user->data->getMovies()->search(movieID);
                if (movie != NULL) {
                    user->data->getMovies()->del(movieID);
                    str << "Movie " << movieID << " has been checked out\nMovie " << movieID << " has been deleted\n";
                    break;
                } else {
                    user = user->next;
                }
            } while (user != users->getHead());
        }

    }

    if(str.str().size() == 0) {
        str << "Movie " << movieID << " does not exist\n";
    }
    out << str.str();
    }
//while reading input file, fills the output file given from command line.
void LibrarySystem::fileIO() {
    vector<string> v(4);
    string line;
    string prev;
    ifstream in(inputFile);
    out<< "===Movie Library System===\n";
    while (getline(in, line)) {
        if (line.empty()){
            continue;
        }
        if (line[line.length()-1] == '\n') {
            line = line.substr(0, line.find("\n"));
        }
        int i = 0;
        for(; i<4; line = line.substr(line.find("\t")+1), i++){          
            if(line.find("\t") == -1 ) {
				v[i] = line;
                break;
            }
	    	v[i] = line.substr(0,line.find("\t"));
        }
        if (v[0] == "deleteUser") {
            if(v[0] != prev){
                out <<"\n===deleteUser() method test===\n";
            }
            deleteUser(stoi(v[1]));

        }
        else if (v[0] == "addUser") {
            if(v[0] != prev) {
                out << "\n===addUser() method test===\n";
            }
            addUser(stoi(v[1]),v[2]);
        }
        else if (v[0] == "addMovie") {
            if(v[0] != prev) {
                out << "\n===addMovie() method test===\n";
            }
            addMovie(stoi(v[1]),v[2],stoi(v[3]));
        }
        else if (v[0] == "returnMovie") {
            if(v[0] != prev) {
                out << "\n===returnMovie() method test===\n";
            }
            returnMovie(stoi(v[1]));
        }
        else if (v[0] == "showMovie") {
            if(v[0] != prev) {
                out << "\n===showMovie() method test===\n";
            }
            showMovie(stoi(v[1]));
        }
        else if (v[0] == "showAllMovie") {
            if(v[0] != prev) {
                out << "\n===showAllMovie() method test===\nMovie id - Movie name - Year - Status\n";
            }
            showAllMovie();
        }
        else if (v[0] == "checkoutMovie") {
            if(v[0] != prev) {
                out << "\n===checkoutMovie() method test===\n";
            }
            checkoutMovie(stoi(v[1]),stoi(v[2]));
        }
        else if (v[0] == "showUser") {
            if(v[0] != prev) {
                out << "\n===showUser() method test===\n";
            }
            showUser(stoi(v[1]));
        }
        else if (v[0] == "deleteMovie") {
            if(v[0] != prev) {
                out << "\n===deleteMovie() method test===\n";
            }
            deleteMovie(stoi(v[1]));

        }
        prev = v[0];
    }
    in.close();
    out.close();
}
