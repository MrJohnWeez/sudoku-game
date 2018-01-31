#include <string>
#include <iostream>

using namespace std;

//Functions for manipulating strings

void testColors(){
    string number;
    string newtext;
    string tag1 = "\033[1;";
    string tag2 = "\033[0m";
    for(int i = 0; i <= 100; i++){
        tag1 = "\033[1;";
        number = to_string(i);
        tag1 += to_string(i);
        tag1 += "m";
        newtext += tag1;
        newtext += number;
        newtext += tag2;
        cout << newtext << endl;
        newtext = "";
    }
}

string bold(string text){
    string newtext;
    newtext += "\e[1m";
    newtext += text;
    newtext += "\e[0m";
    return newtext;
}

string white(string text){
    string newtext;
    newtext += "\033[1;1m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}

string red(string text){
    string newtext;
    newtext += "\033[1;31m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}

string black(string text){
    string newtext;
    newtext += "\033[1;30m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}

string green(string text){
    string newtext;
    newtext += "\033[1;32m"; //"\033[1;32m"
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}

string yellow(string text){
    string newtext;
    newtext += "\033[1;33m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}

string blue(string text){
    string newtext;
    newtext += "\033[0;34m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}

string lightblue(string text){
    string newtext;
    newtext += "\033[1;36m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}

string gray(string text){
    string newtext;
    newtext += "\033[2;1m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}
