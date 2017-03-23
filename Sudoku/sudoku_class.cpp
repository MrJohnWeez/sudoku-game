#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip> //setw


using namespace std;

class game{
public:
    game(){
        //initulize vars???
    }

private:
    //Call functions durring game operation
    void title(){
        cout << setw(60) << " _____             _         _           \n"
             << setw(60) << "/  ___|           | |       | |          \n"
             << setw(60) << "\\ `--.  _   _   __| |  ___  | | __ _   _ \n"
             << setw(60) << " `--. \\| | | | / _` | / _ \\ | |/ /| | | |\n"
             << setw(60) << "/\\__/ /| |_| || (_| || (_) ||   < | |_| |\n"
             << setw(61) << "\\____/  \\__,_| \\__,_| \\___/ |_|\\_\\ \\__,_|\n\n";
        cout << setw(55) << "-----Press enter to play game-----";
        cin.get();
    }

public:
    void setup(){
        title();

    }
};
