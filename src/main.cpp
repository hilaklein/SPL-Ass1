#include <iostream>
#include "../include/Session.h"

using namespace std;

int main(int argc, char** argv){
    cout<<"starts here<==============" << endl;
    if(argc != 2){
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }
    cout<<"calling Session" << endl;

    Session sess(argv[1]);
    cout<<"main: next command -> 'sess.simulate();'" << endl;
    sess.simulate();

    cout << "print this before return 0" << endl;

    return 0;
}
