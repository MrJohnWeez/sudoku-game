#include <iostream>
#include <string>
#include <vector>
#include <cmath>

#include <iomanip> //setw
#include "textediting.cpp"
#include <limits>

using namespace std;

/*
What to do...

    Graphical Functions
      -Find a way to display boards. ~ Possibly with an array of strings?
      -Fill credits
      -Fill how to play
      -Print out a board with pretty display

    Game run functions
      -After edit point is entered display point. User needs to enter "-" to re-enter point.

    KNOWN ERRORS
      -Pressing continue game before game started is an error


       We can use these chars: http://www.copypastecharacter.com/all-characters









TEMP EXAMPLE OF A CLASS /\/\/\/\/\\//////////////////////\\\\\\\\\\\\\\\\\\\\\/////////////////\\\\\\\\\\\\\\\\\/\/\/\/\/\\//////////////////////


#include <iostream>

using namespace std;

class info{
private:
    int x;
    int y;
    int z;
public:
    info(){
        x = 0;
        y = 0;
        z = 0;
    }
    info(int inx, int iny, int inz){
        x = inx;
        y = iny;
        z = inz;
    }

    int getx(){
        return x;
    }
};

int main()
{
    info box;
    cout << box.getx() << endl;


    return 0;
}

/\/\/\/\/\\//////////////////////\\\\\\\\\\\\\\\\\\\\\/////////////////\\\\\\\\\\\\\\\\\/\/\/\/\/\\//////////////////////\\\\\\\\\\\\\\\\\\\\\////












Q & A
*/

//Creates a type stored in gameboard that stores play board and the key
struct boardType{
    int boardPlay[9][9] = {{0}};
    int boardKey[9][9] = {{0}};
};

//Creates a type that stores game data
struct gameboard{
    string title = "Untitled_Save";
    int diff = 0;
    int version = 0;
    boardType board;
    int incorrect = 0;
};



class game{
private:
    //Priavte Vars
    gameboard saveFile;
    bool exit;

    //Cin call functions durring game operation
    //These prevent any glitches/bugs/crashes
    int getInt();
    char getAlpha();
    void pause(bool);

    //Graphical functions
    void title();
    void howToPlay();
    void credits();
    void clear();
    void print(gameboard &saveFile);
    void menu(gameboard &saveFile);

    //Game run functions
    void boardSelect(gameboard &saveFile);
    void updateBoard(gameboard &saveFile, int main[][9], int key[][9]);
    void copyBoard(gameboard &saveFile);
    int check(gameboard &saveFile);
    void run(gameboard &saveFile);

public:

    //This is a constructor
    game(){
        exit = false;
    }

    //This is a deconstructor
    ~game(){
        exit = false;
    }

    //Start game:
    void sudukoGame(){
        title();
        clear();
        menu(saveFile); //Whole game runs from menu
        credits();
    }


};


//Cin functions:***********************************************************************

//Gets the user's number the safe way to prevent crashing
int game::getInt(){
    string x;
    cin >> x;
    cin.ignore(); //Clears cin buffer -> Prevents crashing
    string newString;
    //Takes first number found
    for(unsigned int i = 0; i <= x.length(); i++){
        if(isdigit(x[i])){
            newString += x[i];
        }
    }
    return atof(newString.c_str()); //Converts string -> c string (chars) -> double
}

//Gets the user's  alpha the safe way to prevent crashing
char game::getAlpha(){
    string x;
    bool go = true;
    char letter;
    cin >> x;
    cin.ignore(); //Clears cin buffer -> Prevents crashing
    for(unsigned int i = 0; i <= x.length(); i++){
        if(isalpha(x[i]) && go){
            go = !go;
            letter = x[i];
        }
    }
    return letter;
}

//pause(true) will output "Press enter..." pause(false) does not output anything
void game::pause(bool enter){
    string dummy;
    if(enter) cout << setw(55) << "-----Press enter to continue-----" << endl;
    getline(cin,dummy);

}


//Graphical functions:***********************************************************************

void game::title(){
    cout <<"Total________________________________screen_______________________________Length" << endl;
    cout << red("                    _____             _         _           \n"
                "                   /  ___|           | |       | |          \n"
                "                   \\ `--.  _   _   __| |  ___  | | __ _   _ \n"
                "                    `--. \\| | | | / _` | / _ \\ | |/ /| | | |\n"
                "                   /\\__/ /| |_| || (_| || (_) ||   < | |_| |\n"
                "                   \\____/  \\__,_| \\__,_| \\___/ |_|\\_\\ \\__,_|\n\n");
    pause(true);
    }

void game::credits(){
    cout << "Taco Cat\nChuck Conner: Tester (The Best)\nalso john and aaron were there" << endl;
}


//Clears terminal
void game::clear(){
    cout << string( 24, '\n' );
}


//Printing A Aron THIS IS WHAT YOU SHOULD DO :)
void game::print(gameboard &saveFile){
    for(unsigned int row = 0; row < 9; row++){
        for(unsigned int col = 0; col < 9; col++){
            cout << saveFile.board.boardPlay[row][col];
        }
        cout << endl;
    }

    //        cout << "           A   B   C   D   E   F   G   H   I   "<< endl;
    //        cout << "         ┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓ "<< endl;
    //        cout << "      1❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ "<< endl;
    //        cout << "      2❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ "<< endl;
    //        cout << "      3❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫ "<< endl;
    //        cout << "      4❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ "<< endl;
    //        cout << "      5❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ "<< endl;
    //        cout << "      6❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫ "<< endl;
    //        cout << "      7❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ "<< endl;
    //        cout << "      8❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ "<< endl;
    //        cout << "      9❱ ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ 0 │ 0 │ 0 ┃ "<< endl;
    //        cout << "         ┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛ "<< endl;
}

//Tells user how to play and what command there are
void game::howToPlay(){
    cout << "Bla Bla Bla" << endl;
    pause(true);
}

void game::menu(gameboard &saveFile){
    if(!exit){
        int option = -1;
        clear();
        while(option < 0 || option > 3){
            if(option != -1){
                cout << "Must enter 0-3" << endl;
            }
            cout << bold("Menu") << endl;
            cout << "1) How to play\n"
                 << "2) New game\n"
                 << "3) Back to game\n"
                 << "0) Exit Game\n⏩ ";
            option = getInt();
        }

        if(option == 1){
            howToPlay();
            menu(saveFile);
        }else if(option == 2){
            boardSelect(saveFile);
            run(saveFile);
        }else if(option == 3){
            run(saveFile);
        }else if(option == 0){
            exit = true;
        }
    }
}


//Game Run functions:***********************************************************************

//sets difficulty, board #, and load it into "game memory"
void game::boardSelect(gameboard &saveFile){
    while(saveFile.diff != 1 && saveFile.diff != 2 && saveFile.diff != 3){
        if(saveFile.diff != 0){
            cout << "Must enter 1 2 or 3" << endl;
        }
        cout << bold("Choose difficulty:\n")
             << "(1) Easy\n"
             << "(2) Medium\n"
             << "(3) Hard\n⏩ ";
        saveFile.diff = getInt();
        cout << "\n";
    }

    while(saveFile.version < 1 || saveFile.version > 5){
        if(saveFile.version != 0){
            cout << "Must enter 1-5" << endl;
        }
        cout << bold("Choose board number:") << endl;
        cout << "(1) Enter 7 in (A,1) to win\n"
             << "(2) Board 2\n"
             << "(3) Board 3\n"
             << "(4) Board 4\n"
             << "(5) Board 5\n⏩ ";
        saveFile.version = getInt();
    }

    //Copies board to save file (pass by reference via void function)
    copyBoard(saveFile);
}


void game::run(gameboard &saveFile){
    bool go = true;
    char charcord1;
    int cord1 = 0;
    int cord2 = 0;
    int answer = 0;
    int incorrect = 0;
    check(saveFile);
    if(go && !(saveFile.incorrect == 81)){
        clear();
        print(saveFile);
        do{
            charcord1 = 'Z';
            while(go && (charcord1 < 'A' || charcord1 > 'I') && !exit){
                cout << "Enter (A-I) cordinate: ";
                charcord1 = getAlpha();
                charcord1 = toupper(charcord1);
                if(charcord1 == 26) menu(saveFile);

            }
            cord1 = double(charcord1)-65;

            cord2 = -1;
            while(go && (cord2 < 0 || cord2 > 9) && !exit){
                cout << "Enter (1-9) cordinate: ";
                cord2= getInt();
                if(cord2 == 0) menu(saveFile);
            }

            answer = -1;
            while(go && (answer < 0 || answer > 9) && !exit){
                cout << "Enter (1-9) answer: ";
                answer = getInt();
                if(answer == 0) menu(saveFile);


            }
            saveFile.board.boardPlay[cord2-1][cord1] = answer;
            incorrect = check(saveFile);

            //When this is false the user has won/quit
            if((saveFile.incorrect != 0) && !exit){
                clear();
                cout << "Incorrect = " << incorrect << endl;
                print(saveFile);
            }


            //Does user win game? go == false
            if(saveFile.incorrect == 0) go = false;

        }while(go && !exit);

        //User has won/solved puzzle
        if(!go && !exit){
            exit = true;
            clear();
            cout << "you won!!!" << endl;
        }
    }else if(saveFile.incorrect == 81 && !exit){
        clear();
        cout << "No game currently running" << endl;
        pause(true);
        menu(saveFile);
    }else if(exit){
        clear();
        credits();
    }
}


//Copies board to main "game memory"
void game::updateBoard(gameboard &saveFile, int main[][9], int key[][9]){
    for(unsigned int row = 0; row < 9; row++){
        for(unsigned int col = 0; col < 9; col++){
            saveFile.board.boardPlay[row][col] = main[row][col];
            saveFile.board.boardKey[row][col] = key[row][col];
        }
    }
}


//Checks to see if board is correct ~ also sets savefile incorrect # values
int game::check(gameboard &saveFile){
    int RealitiveIncorrect = 0;
    saveFile.incorrect = 0;
    for(unsigned int row = 0; row < 9; row++){
        for(unsigned int col = 0; col < 9; col++){
            if((saveFile.board.boardPlay[row][col] != 0) && !(saveFile.board.boardPlay[row][col] == saveFile.board.boardKey[row][col])){
                RealitiveIncorrect++;
            }
            if(!(saveFile.board.boardPlay[row][col] == saveFile.board.boardKey[row][col]) ||
                    (saveFile.board.boardPlay[row][col] == 0)){
                saveFile.incorrect++;
            }
        }
    }
    return RealitiveIncorrect;
}




//Suduko Boards
//Copies saved boards to game save file
void game::copyBoard(gameboard &saveFile){
    //Easy
    if(saveFile.diff == 1){
        if(saveFile.version == 1){

            int main[9][9] = {{0, 6, 1,   2, 5, 9,   4, 3, 8},
                              {5, 4, 3,   8, 6, 7,   2, 9, 1},
                              {9, 8, 2,   3, 4, 1,   7, 5, 6},

                              {3, 2, 7,   1, 8, 5,   9, 6, 4},
                              {8, 5, 6,   7, 9, 4,   3, 1, 2},
                              {4, 1, 9,   6, 3, 2,   8, 7, 5},

                              {2, 3, 8,   9, 1, 6,   5, 4, 7},
                              {1, 7, 4,   5, 2, 3,   6, 8, 9},
                              {6, 9, 5,   4, 7, 8,   1, 2, 3}};
            int key[9][9] = {{7, 6, 1,   2, 5, 9,   4, 3, 8},
                             {5, 4, 3,   8, 6, 7,   2, 9, 1},
                             {9, 8, 2,   3, 4, 1,   7, 5, 6},

                             {3, 2, 7,   1, 8, 5,   9, 6, 4},
                             {8, 5, 6,   7, 9, 4,   3, 1, 2},
                             {4, 1, 9,   6, 3, 2,   8, 7, 5},

                             {2, 3, 8,   9, 1, 6,   5, 4, 7},
                             {1, 7, 4,   5, 2, 3,   6, 8, 9},
                             {6, 9, 5,   4, 7, 8,   1, 2, 3}};


            //                int main[9][9] = {{0, 6, 1,   0, 0, 0,   4, 3, 0},
            //                                  {0, 0, 0,   8, 0, 7,   0, 0, 0},
            //                                  {9, 8, 0,   0, 4, 0,   0, 5, 6},

            //                                  {0, 0, 7,   1, 0, 5,   9, 0, 0},
            //                                  {8, 0, 0,   0, 0, 0,   0, 0, 2},
            //                                  {0, 0, 9,   6, 0, 2,   8, 0, 0},

            //                                  {2, 3, 0,   0, 1, 0,   0, 4, 7},
            //                                  {0, 0, 0,   5, 0, 3,   0, 0, 0},
            //                                  {0, 9, 5,   0, 0, 0,   1, 2, 0}};
            //                int key[9][9] = {{7, 6, 1,   2, 5, 9,   4, 3, 8},
            //                                 {5, 4, 3,   8, 6, 7,   2, 9, 1},
            //                                 {9, 8, 2,   3, 4, 1,   7, 5, 6},

            //                                 {3, 2, 7,   1, 8, 5,   9, 6, 4},
            //                                 {8, 5, 6,   7, 9, 4,   3, 1, 2},
            //                                 {4, 1, 9,   6, 3, 2,   8, 7, 5},

            //                                 {2, 3, 8,   9, 1, 6,   5, 4, 7},
            //                                 {1, 7, 4,   5, 2, 3,   6, 8, 9},
            //                                 {6, 9, 5,   4, 7, 8,   1, 2, 3}};
            //changes boards to selected option
            //Similar to inccorect logic: saveFile.board.boardPlay = main
            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 2){
            int main[9][9] = {{6, 1, 0,   0, 0, 0,   2, 0, 4},
                              {0, 7, 3,   4, 0, 0,   0, 8, 5},
                              {8, 0, 0,   7, 9, 0,   0, 6, 0},

                              {0, 0, 0,   8, 0, 1,   7, 4, 0},
                              {0, 0, 1,   0, 3, 0,   6, 0, 0},
                              {0, 3, 6,   5, 0, 9,   0, 0, 0},

                              {0, 9, 0,   0, 2, 5,   0, 0, 7},
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
            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 3){
            int main[9][9] = {{9, 0, 0,   3, 0, 4,   0, 0, 0},
                              {7, 6, 0,   0, 0, 0,   0, 4, 9},
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
            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 4){
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
            updateBoard(saveFile, main, key);
        }else{ //saveFile.version = 5
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
            updateBoard(saveFile, main, key);
        }
        //Medium
    }else if(saveFile.diff == 2){
        if(saveFile.version == 1){
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
            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 2){
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
            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 3){
            int main[9][9] = {{0, 1, 0,   3, 0, 0,   8, 0, 0},
                              {7, 0, 0,   2, 0, 0,   0, 0, 6},
                              {6, 0, 0,   0, 1, 9,   0, 0, 5},

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

            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 4){
            int main[9][9] = {{0, 4, 9,   0, 0, 0,   1, 0, 0},
                              {0, 0, 0,   1, 4, 0,   0, 0, 5},
                              {7, 0, 0,   0, 0, 9,   0, 0, 4},

                              {0, 0, 5,   6, 0, 8,   0, 4, 0},
                              {0, 8, 0,   0, 3, 0,   0, 6, 0},
                              {0, 0, 4,   2, 0, 5,   7, 0, 0},

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

            updateBoard(saveFile, main, key);
        }else{ //saveFile.version = 5
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

            updateBoard(saveFile, main, key);
        }

        //hard
    }else{
        if(saveFile.version == 1){
            int main[9][9] = {{0, 2, 8,   0, 5, 0,   0, 0, 3},
                              {0, 6, 0,   0, 0, 0,   8, 0, 0},
                              {3, 0, 5,   0, 7, 2,   0, 0, 0},

                              {0, 0, 9,   3, 0, 0,   2, 0, 0},
                              {0, 0, 0,   4, 0, 9,   0, 0, 0},
                              {0, 0, 1,   0, 0, 8,   6, 0, 0},

                              {0, 0, 0,   1, 9, 0,   7, 0, 4},
                              {0, 0, 4,   0, 0, 0,   0, 6, 0},
                              {2, 0, 0,   0, 4, 0,   9, 3, 0}};
            int key[9][9] = {{9, 2, 8,   6, 5, 1,   4, 7, 3},
                             {1, 6, 7,   9, 3, 4,   8, 5, 2},
                             {3, 4, 5,   8, 7, 2,   1, 9, 6},

                             {4, 8, 9,   3, 6, 5,   2, 1, 7},
                             {6, 7, 2,   4, 1, 9,   3, 8, 5},
                             {5, 3, 1,   7, 2, 8,   6, 4, 9},

                             {8, 5, 3,   1, 9, 6,   7, 2, 4},
                             {7, 9, 4,   2, 8, 3,   5, 6, 1},
                             {2, 1, 6,   5, 4, 7,   9, 3, 8}};

            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 2){
            int main[9][9] = {{0, 9, 0,   1, 0, 0,   0, 8, 0},
                              {0, 0, 0,   6, 0, 0,   0, 9, 2},
                              {0, 0, 8,   2, 0, 4,   7, 1, 0},

                              {0, 6, 4,   0, 0, 0,   0, 0, 0},
                              {9, 0, 0,   0, 0, 0,   0, 0, 4},
                              {0, 0, 0,   0, 0, 0,   9, 3, 0},

                              {0, 4, 6,   3, 0, 1,   8, 0, 0},
                              {7, 8, 0,   0, 0, 5,   0, 0, 0},
                              {0, 1, 0,   0, 0, 7,   0, 2, 0}};
            int key[9][9] = {{2, 9, 7,   1, 5, 3,   4, 8, 6},
                             {4, 3, 1,   6, 7, 8,   5, 9, 2},
                             {6, 5, 8,   2, 9, 4,   7, 1, 3},

                             {1, 6, 4,   7, 3, 9,   2, 5, 8},
                             {9, 7, 3,   5, 8, 2,   1, 6, 4},
                             {8, 2, 5,   4, 1, 6,   9, 3, 7},

                             {5, 4, 6,   3, 2, 1,   8, 7, 9},
                             {7, 8, 2,   9, 6, 5,  3, 4, 1},
                             {3, 1, 9,   8, 4, 7,   6, 2, 5}};

            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 3){
            int main[9][9] = {{0, 9, 6,   2, 0, 3,   0, 0, 5},
                              {0, 2, 1,   0, 0, 0,   0, 0, 6},
                              {7, 0, 0,   4, 0, 0,   0, 0, 0},

                              {6, 8, 0,   0, 0, 2,   0, 0, 0},
                              {0, 7, 3,   0, 0, 0,   2, 4, 0},
                              {0, 0, 0,   9, 0, 0,   0, 6, 8},

                              {0, 0, 0,   0, 0, 5,   0, 0, 9},
                              {3, 0, 0,   0, 0, 0,   8, 7, 0},
                              {2, 0, 0,   7, 0, 4,   5, 1, 0}};
            int key[9][9] = {{4, 9, 6,   2, 1, 3,   7, 8, 5},
                             {8, 2, 1,   5, 7, 9,   4, 3, 6},
                             {7, 3, 5,   4, 6, 8,   1, 9, 2},

                             {6, 8, 4,   1, 3, 2,   9, 5, 7},
                             {9, 7, 3,   8, 5, 6,   2, 4, 1},
                             {5, 1, 2,   9, 4, 7,   3, 6, 8},

                             {1, 4, 7,   3, 8, 5,   6, 2, 9},
                             {3, 5, 9,   6, 2, 1,   8, 7, 4},
                             {2, 6, 8,   7, 9, 4,   5, 1, 3}};

            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 4){
            int main[9][9] = {{0, 3, 5,   0, 0, 0,   8, 0, 0},
                              {0, 0, 0,   2, 3, 0,   0, 0, 5},
                              {9, 0, 0,   0, 0, 8,   0, 0, 3},

                              {0, 0, 7,   5, 0, 3,   0, 1, 0},
                              {0, 1, 0,   0, 2, 0,   0, 3, 0},
                              {0, 5, 0,   8, 0, 6,   9, 0, 0},

                              {7, 0, 0,   3, 0, 0,   0, 0, 9},
                              {5, 0, 0,   0, 7, 4,   0, 0, 0},
                              {0, 0, 3,   0, 0, 0,   2, 6, 0}};
            int key[9][9] = {{2, 3, 5,   7, 4, 1,   8, 9, 6},
                             {1, 6, 8,   2, 3, 9,   7, 4, 5},
                             {9, 7, 4,   6, 5, 8,   1, 2, 3},

                             {8, 4, 7,   5, 9, 3,   6, 1, 2},
                             {6, 1, 9,   4, 2, 7,   5, 3, 8},
                             {3, 5, 2,   8, 1, 6,   9, 7, 4},

                             {7, 8, 1,   3, 6, 2,   4, 5, 9},
                             {5, 2, 6,   9, 7, 4,   3, 8, 1},
                             {4, 9, 3,   1, 8, 5,   2, 6, 7}};

            updateBoard(saveFile, main, key);
        }else{ //saveFile.version = 5
            int main[9][9] = {{0, 0, 0,   7, 8, 0,   0, 5, 6},
                              {5, 1, 0,   0, 3, 4,   0, 0, 7},
                              {0, 0, 0,   0, 0, 0,   0, 0, 0},

                              {0, 8, 0,   0, 0, 6,   0, 4, 0},
                              {0, 7, 2,   0, 0, 0,   5, 6, 0},
                              {0, 9, 0,   2, 0, 0,   0, 7, 0},

                              {0, 0, 0,   0, 0, 0,   0, 0, 0},
                              {7, 0, 0,   4, 1, 0,   0, 2, 3},
                              {6, 4, 0,   0, 9, 2,   0, 0, 0}};
            int key[9][9] = {{2, 3, 4,   7, 8, 9,   1, 5, 6},
                             {5, 1, 8,   6, 3, 4,   2, 9, 7},
                             {9, 6, 7,   1, 2, 5,   4, 3, 8},

                             {1, 8, 5,   9, 7, 6,   3, 4, 2},
                             {3, 7, 2,   8, 4, 1,   5, 6, 9},
                             {4, 9, 6,   2, 5, 3,   8, 7, 1},

                             {8, 2, 3,   5, 6, 7,   9, 1, 4},
                             {7, 5, 9,   4, 1, 8,   6, 2, 3},
                             {6, 4, 1,   3, 9, 2,   7, 8, 5}};
            updateBoard(saveFile, main, key);
        }
    }
}
