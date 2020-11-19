#include <iostream>
#include "../include/Session.h"

using namespace std;

//kiskashta
int main(int argc, char** argv){
    cout<<"starts here<==============" << endl;
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    cout<<"calling Session" << endl;

    Session sess(argv[1]);
    sess.simulate();

    cout << "print this before return 0" << endl;

    return 0;
}
