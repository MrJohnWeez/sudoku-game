#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip> //setw


using namespace std;


//What to do...

    //Grindy
      //5 Hard Boards need filling in

    //Graphical
      //Find a way to display boards. ~ Possibly with an array of strings?
      // cout << "►" << endl;

      // We can use these chars: http://www.copypastecharacter.com/all-characters

        //Board prototype Needs Help
//           A B C    D E F    G H I
//         ___________________________
//      1) | 0 0 0 |  0 0 0 |  0 0 0 |
//      2) | 0 0 0 |  0 0 0 |  0 0 0 |
//      3) | 0 0 0 |  0 0 0 |  0 0 0 |
//         |-------|--------|--------|
//      4) | 0 0 0 |  0 0 0 |  0 0 0 |
//      5) | 0 0 0 |  0 0 0 |  0 0 0 |
//      6) | 0 0 0 |  0 0 0 |  0 0 0 |
//         |-------|--------|--------|
//      7) | 0 0 0 |  0 0 0 |  0 0 0 |
//      8) | 0 0 0 |  0 0 0 |  0 0 0 |
//      9) | 0 0 0 |  0 0 0 |  0 0 0 |
//         ---------------------------

    //Functions
      //Add Begin game function
      //Add function to compare boards

    //Logic
      //User can restart anytime
      //User can quit anytime
      //If user entered a void cord make them re-enter it. Also tell them "Invalid cordinate"


//Q & A
    //Is Aaron going to edit this over the weekend?



//Creates a type stored in gameboard that stores play board and the key
struct boardType{
    int boardPlay[9][9] = {{0}};
    int boardKey[9][9] = {{0}};
};

//Creates a type that stores game data
struct gameboard{
    string title = "Untitled_Save";
    boardType board;
};



class game{
public:
    //Runs game when class is called ~ This is a constructor
    game(){
        // Displays title screen
        title();
        gameboard saveFile;
        //Options and Board setup ~ saves to game file
        boardSelect(saveFile);
    }

    //Runs when game is exited
    ~game(){
        cout << "Thanks for playing our game." << endl;
    }

private:
    //Call functions durring game operation
    void title(){

        cout << setw(67) << "\033[1;31m _____             _         _           \n"
             << setw(60) << "/  ___|           | |       | |          \n"
             << setw(60) << "\\ `--.  _   _   __| |  ___  | | __ _   _ \n"
             << setw(60) << " `--. \\| | | | / _` | / _ \\ | |/ /| | | |\n"
             << setw(60) << "/\\__/ /| |_| || (_| || (_) ||   < | |_| |\n"
             << setw(61) << "\\____/  \\__,_| \\__,_| \\___/ |_|\\_\\ \\__,_|\n\n";
        cout << setw(61) << "-----Press enter to play game-----\033[0m\n";
        cin.get(); //Pause until enter
//cout <<"\033[1;31mbold red text\033[0m\n";


        }

    //Copies board to main "game memory" ~ var name used: saveFile
    void updateBoard(gameboard &start, int main[][9], int key[][9]){
        for(unsigned int row = 0; row < 9; row++){
            for(unsigned int col = 0; col < 9; col++){
                start.board.boardPlay[row][col] = main[row][col];
                start.board.boardKey[row][col] = key[row][col];
            }
        }
    }


    //sets difficulty, board #, and load it into "game memory"
    void boardSelect(gameboard &saveFile){
        int diff = 0;
        int version = 0;
        while(diff != 1 && diff != 2 && diff != 3){
            if(diff != 0){
                cout << "Must enter 1 2 or 3" << endl;
            }
            cout << "Choose difficulty:\n"
                 << "(1) Easy\n"
                 << "(2) Medium\n"
                 << "(3) Hard\n";
            cin >> diff;
        }

        while(version < 1 || version > 5){
            if(version != 0){
                cout << "Must enter 1-5" << endl;
            }
            cout << "Choose board number:\n"
                 << "(1) Board 1\n"
                 << "(2) Board 2\n"
                 << "(3) Board 3\n"
                 << "(4) Board 4\n"
                 << "(5) Board 5\n";
            cin >> version;
        }

        //copies board to save file (pass by reference via void function)
        copyBoard(diff, version, saveFile);


        //Temp Printing
        int row, col = 0;
        for(row = 0; row < 9; row++){
            for(col = 0; col < 9; col++){
                cout << saveFile.board.boardPlay[row][col];
            }
            cout << endl;
        }
        cout << "\n" << endl;
        for(row = 0; row < 9; row++){
            for(col = 0; col < 9; col++){
                cout << saveFile.board.boardKey[row][col];
            }
            cout << endl;
        }
    }



//Suduko Boards
    //Copies saved boards to game save file
    void copyBoard(int diff, int version, gameboard &start){
        //Easy
        if(diff == 1){
            if(version == 1){
                int main[9][9] = {{0, 6, 1,   0, 0, 0,   4, 3, 0},
                                  {0, 0, 0,   8, 0, 7,   0, 0, 0},
                                  {9, 8, 0,   0, 4, 0,   0, 5, 6},

                                  {0, 0, 7,   1, 0, 5,   9, 0, 0},
                                  {8, 0, 0,   0, 0, 0,   0, 0, 2},
                                  {0, 0, 9,   6, 0, 2,   8, 0, 0},

                                  {2, 3, 0,   0, 1, 0,   0, 4, 7},
                                  {0, 0, 0,   5, 0, 3,   0, 0, 0},
                                  {0, 9, 5,   0, 0, 0,   1, 2, 0}};
                int key[9][9] = {{7, 6, 1,   2, 5, 9,   4, 3, 8},
                                 {5, 4, 3,   8, 6, 7,   2, 9, 1},
                                 {9, 8, 2,   3, 4, 1,   7, 5, 6},

                                 {3, 2, 7,   1, 8, 5,   9, 6, 4},
                                 {8, 5, 6,   7, 9, 4,   3, 1, 2},
                                 {4, 1, 9,   6, 3, 2,   8, 7, 5},

                                 {2, 3, 8,   9, 1, 6,   5, 4, 7},
                                 {1, 7, 4,   5, 2, 3,   6, 8, 9},
                                 {6, 9, 5,   4, 7, 8,   1, 2, 3}};
                //changes boards to selected option
                //Similar to inccorect logic: start.board.boardPlay = main
                updateBoard(start, main, key);
            }else if(version == 2){
                int main[9][9] = {{6, 1, 0,   0, 0, 0,   2, 0, 4},
                                  {0, 7, 3,   4, 0, 0,   0, 8, 5},
                                  {8, 0, 0,   7, 9, 0,   0, 6, 0},

                                  {0, 0, 0,   8, 0, 1,   7, 4, 0},
                                  {0, 0, 1,   0, 3, 0,   6, 0, 0},
                                  {0, 3, 6,   5, 0, 9,   0, 0, 0},

                                  {9, 0, 0,   0, 2, 5,   0, 0, 7},
                                  {5, 4, 0,   0, 0, 3,   8, 9, 0},
                                  {3, 0, 7,   0, 0, 0,   0, 1, 2}};
                int key[9][9] = {{6, 1, 9,   3, 5, 8,   2, 7, 4},
                                 {2, 7, 3,   4, 1, 6,   9, 8, 5},
                                 {8, 5, 4,   7, 9, 2,   3, 6, 1},

                                 {9, 2, 5,   8, 6, 1,   7, 4, 3},
                                 {4, 8, 1,   2, 3, 7,   6, 5, 9},
                                 {7, 3, 6,   5, 4, 9,   1, 2, 8},

                                 {1, 9, 8,   6, 2, 5,   4, 3, 7},
                                 {5, 4, 2,   1, 7, 3,   8, 9, 6},
                                 {3, 6, 7,   9, 8, 4,   5, 1, 2}};
                updateBoard(start, main, key);
            }else if(version == 3){
                int main[9][9] = {{9, 0, 0,   3, 0, 4,   0, 0, 0},
                                  {7, 6, 0,   0, 0, 0,   4, 9, 0},
                                  {0, 4, 0,   0, 8, 0,   7, 0, 0},

                                  {0, 2, 0,   7, 4, 0,   0, 0, 1},
                                  {0, 0, 1,   0, 0, 0,   8, 0, 0},
                                  {5, 0, 0,   0, 3, 2,   0, 7, 0},

                                  {0, 0, 4,   0, 1, 0,   0, 5, 0},
                                  {8, 5, 0,   0, 0, 0,   0, 6, 3},
                                  {0, 0, 0,   2, 0, 6,   0, 0, 4}};
                int key[9][9] = {{9, 1, 5,   3, 7, 4,   6, 2, 8},
                                 {7, 6, 8,   5, 2, 1,   3, 4, 9},
                                 {2, 4, 3,   6, 8, 9,   7, 1, 5},

                                 {3, 2, 6,   7, 4, 8,   5, 9, 1},
                                 {4, 7, 1,   9, 6, 5,   8, 3, 2},
                                 {5, 8, 9,   1, 3, 2,   4, 7, 6},

                                 {6, 9, 4,   8, 1, 3,   2, 5, 7},
                                 {8, 5, 2,   4, 9, 7,   1, 6, 3},
                                 {1, 3, 7,   2, 5, 6,   9, 8, 4}};
                updateBoard(start, main, key);
            }else if(version == 4){
                int main[9][9] = {{0, 4, 1,   0, 2, 3,   0, 0, 0},
                                  {0, 7, 0,   0, 5, 0,   0, 4, 9},
                                  {0, 3, 0,   0, 0, 6,   0, 1, 0},

                                  {6, 0, 0,   0, 9, 0,   0, 0, 0},
                                  {9, 0, 3,   0, 0, 0,   1, 0, 8},
                                  {0, 0, 0,   0, 8, 0,   0, 0, 7},

                                  {0, 6, 0,   5, 0, 0,   0, 8, 0},
                                  {7, 2, 0,   0, 1, 0,   0, 3, 0},
                                  {0, 0, 0,   8, 3, 0,   2, 7, 0}};
                int key[9][9] = {{8, 4, 1,   9, 2, 3,   7, 6, 5},
                                 {2, 7, 6,   1, 5, 8,   3, 4, 9},
                                 {5, 3, 9,   7, 4, 6,   8, 1, 2},

                                 {6, 8, 7,   2, 9, 1,   4, 5, 3},
                                 {9, 5, 3,   4, 6, 7,   1, 2, 8},
                                 {4, 1, 2,   3, 8, 5,   6, 9, 7},

                                 {3, 6, 4,   5, 7, 2,   9, 8, 1},
                                 {7, 2, 8,   6, 1, 9,   5, 3, 4},
                                 {1, 9, 5,   8, 3, 4,   2, 7, 6}};
                updateBoard(start, main, key);
            }else{ //version = 5
                int main[9][9] = {{4, 0, 2,   6, 0, 0,   8, 0, 0},
                                  {0, 9, 0,   3, 0, 0,   6, 0, 7},
                                  {0, 6, 0,   1, 0, 5,   0, 3, 0},

                                  {0, 0, 3,   0, 5, 8,   1, 0, 0},
                                  {1, 5, 0,   0, 0, 0,   0, 4, 8},
                                  {0, 0, 6,   7, 9, 0,   2, 0, 0},

                                  {0, 7, 0,   8, 0, 3,   0, 9, 0},
                                  {2, 0, 9,   0, 0, 7,   0, 6, 0},
                                  {0, 0, 5,   0, 0, 2,   7, 0, 4}};
                int key[9][9] = {{4, 3, 2,   6, 7, 9,   8, 1, 5},
                                 {5, 9, 1,   3, 8, 4,   6, 2, 7},
                                 {7, 6, 8,   1, 2, 5,   4, 3, 9},

                                 {9, 2, 3,   4, 5, 8,   1, 7, 6},
                                 {1, 5, 7,   2, 3, 6,   9, 4, 8},
                                 {8, 4, 6,   7, 9, 1,   2, 5, 3},

                                 {6, 7, 4,   8, 1, 3,   5, 9, 2},
                                 {2, 8, 9,   5, 4, 7,   3, 6, 1},
                                 {3, 1, 5,   9, 6, 2,   7, 8, 4}};
                updateBoard(start, main, key);
            }
        //Medium
        }else if(diff == 2){
            if(version == 1){
                int main[9][9] = {{0, 3, 6,   0, 0, 0,   0, 0, 0},
                                  {5, 0, 0,   8, 0, 6,   0, 0, 2},
                                  {9, 8, 0,   0, 0, 3,   0, 7, 0},

                                  {6, 0, 0,   0, 0, 0,   0, 1, 0},
                                  {1, 0, 4,   5, 9, 7,   8, 0, 3},
                                  {0, 7, 0,   0, 0, 0,   0, 0, 9},

                                  {0, 6, 0,   4, 0, 0,   0, 8, 1},
                                  {2, 0, 0,   6, 0, 9,   0, 0, 7},
                                  {0, 0, 0,   0, 0, 0,   5, 2, }};
                int key[9][9] = {{7, 3, 6,   9, 4, 2,   1, 5, 8},
                                  {5, 4, 1,   8, 7, 6,   3, 9, 2},
                                  {9, 8, 2,   1, 5, 3,   6, 7, 4},

                                  {6, 9, 3,   2, 8, 4,   7, 1, 5},
                                  {1, 2, 4,   5, 9, 7,   8, 6, 3},
                                  {8, 7, 5,   3, 6, 1,   2, 4, 9},

                                  {3, 6, 7,   4, 2, 5,   9, 8, 1},
                                  {2, 5, 8,   6, 1, 9,   4, 3, 7},
                                  {4, 1, 9,   7, 3, 8,   5, 2, 6}};
                updateBoard(start, main, key);
            }else if(version == 2){
                int main[9][9] = {{0, 0, 0,   0, 4, 0,   8, 7, 9},
                                  {9, 3, 0,   7, 5, 0,   0, 2, 0},
                                  {0, 0, 0,   0, 0, 0,   5, 0, 0},

                                  {0, 0, 0,   3, 0, 0,   0, 0, 8},
                                  {2, 4, 0,   8, 0, 9,   0, 5, 6},
                                  {6, 0, 0,   0, 0, 2,   0, 0, 0},

                                  {0, 0, 1,   0, 0, 0,   0, 0, 0},
                                  {0, 2, 0,   0, 8, 7,   0, 1, 3},
                                  {4, 7, 8,   0, 3, 0,   0, 0, 0}};
                int key[9][9] = {{1, 5, 2,   6, 4, 3,   8, 7, 9},
                                 {9, 3, 4,   7, 5, 8,   6, 2, 1},
                                 {8, 6, 7,   2, 9, 1,   5, 3, 4},

                                 {7, 1, 5,   3, 6, 4,   2, 9, 8},
                                 {2, 4, 3,   8, 7, 9,   1, 5, 6},
                                 {6, 8, 9,   5, 1, 2,   3, 4, 7},

                                 {3, 9, 1,   4, 2, 6,   7, 8, 5},
                                 {5, 2, 6,   9, 8, 7,   4, 1, 3},
                                 {4, 7, 8,   1, 3, 5,   9, 6, 2}};
                updateBoard(start, main, key);
            }else if(version == 3){
                int main[9][9] = {{0, 1, 0,   3, 0, 0,   8, 0, 0},
                                  {7, 0, 0,   2, 0, 0,   0, 0, 6},
                                  {3, 0, 0,   0, 1, 9,   0, 0, 5},

                                  {0, 0, 6,   0, 5, 7,   0, 0, 9},
                                  {0, 0, 0,   0, 0, 0,   0, 0, 0},
                                  {9, 0, 0,   8, 2, 0,   1, 0, 0},

                                  {5, 0, 0,   4, 3, 0,   9, 0, 0},
                                  {8, 0, 0,   0, 0, 6,   0, 0, 4},
                                  {0, 0, 4,   0, 0, 2,   0, 7, 0}};
                int key[9][9] = {{4, 1, 2,   3, 6, 5,   8, 9, 7},
                                 {7, 5, 9,   2, 4, 8,   3, 1, 6},
                                 {6, 8, 3,   7, 1, 9,   2, 4, 5},

                                 {2, 3, 6,   1, 5, 7,   4, 8, 9},
                                 {1, 4, 8,   6, 9, 3,   7, 5, 2},
                                 {9, 7, 5,   8, 2, 4,   1, 6, 3},

                                 {5, 6, 7,   4, 3, 1,   9, 2, 8},
                                 {8, 2, 1,   9, 7, 6,   5, 3, 4},
                                 {3, 9, 4,   5, 8, 2,   6, 7, 1}};

                updateBoard(start, main, key);
            }else if(version == 4){
                int main[9][9] = {{0, 4, 9,   0, 0, 0,   1, 0, 0},
                                  {0, 0, 0,   1, 4, 0,   0, 0, 5},
                                  {7, 0, 0,   0, 0, 9,   0, 0, 4},

                                  {0, 0, 5,   6, 0, 8,   0, 4, 0},
                                  {0, 8, 0,   0, 3, 0,   0, 6, 0},
                                  {0, 0, 3,   2, 0, 5,   7, 0, 0},

                                  {2, 0, 0,   4, 0, 0,   0, 0, 6},
                                  {5, 0, 0,   0, 6, 1,   0, 0, 0},
                                  {0, 0, 7,   0, 0, 0,   3, 8, 0}};
                int key[9][9] = {{8, 4, 9,   5, 2, 6,   1, 3, 7},
                                 {3, 2, 6,   1, 4, 7,   8, 9, 5},
                                 {7, 5, 1,   3, 8, 9,   6, 2, 4},

                                 {9, 7, 5,   6, 1, 8,   2, 4, 3},
                                 {1, 8, 2,   7, 3, 4,   5, 6, 9},
                                 {6, 3, 4,   2, 9, 5,   7, 1, 8},

                                 {2, 1, 8,   4, 7, 3,   9, 5, 6},
                                 {5, 9, 3,   8, 6, 1,   4, 7, 2},
                                 {4, 6, 7,   9, 5, 2,   3, 8, 1}};

                updateBoard(start, main, key);
            }else{ //version = 5
                int main[9][9] = {{0, 0, 3,   4, 5, 0,   2, 0, 0},
                                  {0, 0, 4,   0, 0, 0,   0, 0, 1},
                                  {8, 0, 0,   6, 0, 0,   7, 9, 0},

                                  {0, 4, 9,   0, 2, 3,   0, 0, 0},
                                  {0, 0, 0,   0, 0, 0,   0, 0, 0},
                                  {0, 0, 0,   1, 4, 0,   8, 6, 0},

                                  {0, 1, 7,   0, 0, 9,   0, 0, 2},
                                  {9, 0, 0,   0, 0, 0,   1, 0, 0},
                                  {0, 0, 5,   0, 1, 6,   9, 0, 0}};
                int key[9][9] = {{7, 9, 3,   4, 5, 1,   2, 8, 6},
                                 {2, 6, 4,   7, 9, 8,   3, 5, 1},
                                 {8, 5, 1,   6, 3, 2,   7, 9, 4},

                                 {6, 4, 9,   8, 2, 3,   5, 1, 7},
                                 {1, 7, 8,   9, 6, 5,   4, 2, 3},
                                 {5, 3, 2,   1, 4, 7,   8, 6, 9},

                                 {3, 1, 7,   5, 8, 9,   6, 4, 2},
                                 {9, 8, 6,   2, 7, 4,   1, 3, 5},
                                 {4, 2, 5,   3, 1, 6,   9, 7, 8}};

                updateBoard(start, main, key);
            }

        //hard
        }else{
//            if(version == 1){
//                int main[9][9] = {{, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , }};
//                int key[9][9] = {{, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , }};
//                updateBoard(start, main, key);
//            }else if(version == 2){
//                cout << "Not done yet" << endl;
//                int main[9][9] = {{, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , }};
//                int key[9][9] = {{, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , }};
//                updateBoard(start, main, key);
//            }else if(version == 3){
//                cout << "Not done yet" << endl;
//                int main[9][9] = {{, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , }};
//                int key[9][9] = {{, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , }};
//                updateBoard(start, main, key);
//            }else if(version == 4){
//                cout << "Not done yet" << endl;
//                int main[9][9] = {{, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , }};
//                int key[9][9] = {{, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , }};
//                updateBoard(start, main, key);
//            }else{ //version = 5
//                cout << "Not done yet" << endl;
//                int main[9][9] = {{, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , },
//                                  {, , ,   , , ,   , , }};
//                int key[9][9] = {{, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , },
//                                 {, , ,   , , ,   , , }};
//                updateBoard(start, main, key);
//            }
        }
    }
};
