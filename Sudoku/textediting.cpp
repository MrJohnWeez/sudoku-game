#include <string>

using namespace std;

//Functions for manipulating strings

string bold(string text){
    string newtext;
    newtext += "\e[1m";
    newtext += text;
    newtext += "\e[0m";
    return newtext;
}

string red(string text){
    string newtext;
    newtext += "\033[1;31m";
    newtext += text;
    newtext += "\033[0m";
    return newtext;
}
