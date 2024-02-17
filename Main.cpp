using namespace std;
#include "LibrarySystem.h"
/* Before testing the program,please convert txt files to UNIX format.
*/
int main(int argc,char* argv[]) {

    LibrarySystem* library = new LibrarySystem(argv[1],argv[2]);
    delete library;
    return 0;
}
