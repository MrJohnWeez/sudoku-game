#include <iostream>
#include "sudoku_class.cpp"
#include <fstream>

using namespace std;

int main()
{
    //Runs game
    game Suduko;
    gameboard saveFile;
    //Options and Board setup ~ saves to game file
    Suduko.boardSelect(saveFile);
    //Runs game
    Suduko.run(saveFile);
    return 0;

}
