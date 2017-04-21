#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //setw
#include "textediting.cpp"
#include <fstream>

using namespace std;

/*
    We can use these unicode chars: http://www.copypastecharacter.com/all-characters
    Game Report: https://docs.google.com/document/d/1W9t9L3NHXSCfmkRBUQDQo04xI60NdST3vGZK92s__sU/edit?usp=sharing
*/

//Stores play board, key, and data
struct boardType{
    int boardPlay[9][9] = {{0}};
    int boardKey[9][9] = {{0}};
    int data[9][9] = {{0}};
};

//Creates a type that stores game data
struct gameboard{
    string title = "Custom_Board";
    int diff = 0;
    int version = 0;
    boardType board;
};


class game{
public:
    //This is a constructor
    game(){
        exit = false;
        numLeft = 0;
        userIncorrect = 0;
    }

    //This is a deconstructor (Useless for now)
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
private:
    //Priavte Vars
    gameboard saveFile;   //Acts like game save data
    bool exit;     //Terminates game if true
    int numLeft;    //Total number of numbers left
    int userIncorrect;  //User's numbers incorrect
    string editCord1;  //Used to print user's selected cords
    string editCord2;  //Used to print user's selected cords
    string printing[20][10] = {{"                        A   B   C   D   E   F   G   H   I   ","","","","","","","","","\n",},
                               {"                      ┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓ ","","","","","","","","","\n",},
                               {"                   1❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n",},
                               {"                   2❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n",},
                               {"                   3❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫ ","","","","","","","","","\n",},
                               {"                   4❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n",},
                               {"                   5❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n",},
                               {"                   6❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫ ","","","","","","","","","\n",},
                               {"                   7❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n",},
                               {"                   8❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"       ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n",},
                               {"       9❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n",},
                               {"                      ┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛ ","","","","","","","","","\n",},};

    //Cin call functions durring game operation
    //These prevent any glitches/bugs/crashes
    char getInt();
    char getAlpha();
    void pause(bool);

    //Graphical functions
    void sizeScreen();
    void win();
    void title();
    void howToPlay();
    void credits();
    void clear();
    void print(gameboard &saveFile);
    void menu(gameboard &saveFile);

    //Import and Export Boards
    void getBoard(gameboard &saveFile, string boardName);
    void saveBoard(gameboard &saveFile);
    void getData(gameboard &savefile, vector<string> importData);
    void import(gameboard &saveFile);

    //Modify boards
    void dataBlock(gameboard &saveFile);
    void updateBoard(gameboard &saveFile, int main[][9], int key[][9]);

    //Game run functions
    void boardSelect(gameboard &saveFile);
    void check(gameboard &saveFile);
    void run(gameboard &saveFile);

    //Build in boards
    void copyBoard(gameboard &saveFile);
};



//Cin functions:***************************************************************************************************************

//Gets the user's 1 digit number the safe way to prevent crashing
char game::getInt(){
    string x;
    bool go = true;
    char num;
    cout << "⏩ ";
    cin >> x;
    cin.ignore(); //Clears cin buffer -> Prevents crashing

    //Searches for the first valid letter or '-'
    for(unsigned int i = 0; i <= x.length(); i++){
        if((isdigit(x[i]) && go) || (x[i] == '-' && go)){
            go = !go;
            num = x[0];
        }
    }
    return num;
}

//Gets the user's 1 letter alpha the safe way to prevent crashing
char game::getAlpha(){
    string x;
    bool go = true;
    char letter;
    cout << "⏩ ";
    cin >> x;
    cin.ignore(); //Clears cin buffer -> Prevents crashing

    //Searches for the first valid letter or '-'
    for(unsigned int i = 0; i <= x.length(); i++){
        if((isalpha(x[i]) && go) || (x[i] == '-' && go)){
            go = !go;
            letter = x[0];
        }
    }
    return letter;
}

//pause(true) will output "....Press enter..." pause(false) does not output anything but still pauses
void game::pause(bool enter){
    string dummy;
    if(enter) cout << setw(67) << white("-----Press enter to continue-----") << endl;
    getline(cin,dummy);
    if(dummy[0] == '-'){
        exit = true;
    }
}

//Graphical functions:*******************************************************************************************************

void game::sizeScreen(){
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                       Make sure you align your terminal                      ┃\n"
            "┃                            so you can see a box                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                       -----Press enter to continue-----                      ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┃                                                                              ┃\n"
            "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
    pause(false);
}

void game::win(){
    clear();
    cout << yellow("  ██╗   ██╗ ██████╗ ██╗   ██╗    ██╗    ██╗██╗███╗   ██╗██╗██╗██╗\n"
                   "  ╚██╗ ██╔╝██╔═══██╗██║   ██║    ██║    ██║██║████╗  ██║██║██║██║\n"
                   "   ╚████╔╝ ██║   ██║██║   ██║    ██║ █╗ ██║██║██╔██╗ ██║██║██║██║\n"
                   "    ╚██╔╝  ██║   ██║██║   ██║    ██║███╗██║██║██║╚██╗██║╚═╝╚═╝╚═╝\n"
                   "     ██║   ╚██████╔╝╚██████╔╝    ╚███╔███╔╝██║██║ ╚████║██╗██╗██╗\n"
                   "     ╚═╝    ╚═════╝  ╚═════╝      ╚══╝╚══╝ ╚═╝╚═╝  ╚═══╝╚═╝╚═╝╚═╝\n") << endl;
}

void game::title(){
    //testColors();
    cout << blue("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n")
         << lightblue("   _____                                           _      _     _            \n"
                      "  /  __ \\                                         | |    | |   (_)           \n"
                      "  | /  \\/ ___  _ __ ___  _ __ ___   __ _ _ __   __| |    | |    _ _ __   ___ \n"
                      "  | |    / _ \\| '_ ` _ \\| '_ ` _ \\ / _` | '_ \\ / _` |    | |   | | '_ \\ / _ \\\n"
                      "  | \\__/\\ (_) | | | | | | | | | | | (_| | | | | (_| |    | |___| | | | |  __/\n"
                      "   \\____/\\___/|_| |_| |_|_| |_| |_|\\__,_|_| |_|\\__,_|    \\_____/_|_| |_|\\___|\n")
         <<  red("                    _____             _         _                               \n"
                 "                   /  ___|           | |       | |                              \n"
                 "                   \\ `--.  _   _   __| |  ___  | | __ _   _                    \n"
                 "                    `--. \\| | | | / _` | / _ \\ | |/ /| | | |                  \n"
                 "                   /\\__/ /| |_| || (_| || (_) ||   < | |_| |                   \n"
                 "                   \\____/  \\__,_| \\__,_| \\___/ |_|\\_\\ \\__,_|             \n\n") << endl;
    cout << setw(67) << white("-----Press enter to continue-----") << endl;
    cout << blue("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛") << endl;
    pause(false);

}

//Tells user how to play and what command there are
void game::howToPlay(){
    clear();
    //cout << "Total________________________________screen_______________________________Length" << endl;
    cout << blue("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n")
         << "                       Use numbers to navigate the menu                       \n"
         << "        Enter a dash character to exit to menu anytime durring the game.      \n"
         << "      If you want to stop playing make sure you save your game (Option6).     \n"
         << "  All " << green("green") << " numbers on the board are defult numbers. You cannot change them.\n"
         << "                       Enter 0 as answer to clear spot                        \n"
         << "                                                                              \n"
         << lightblue("                             Normal sudoku rules:                             \n")
         << "                The objective is to fill a 9x9 grid so that each              \n"
         << "                column, each row, and each of the nine 3x3 boxes              \n"
         << "       contains the digits from 1 to 9. The amount of empty spaces and how    \n"
         << "             many you have gotten correct is labled above the board.          \n"
         << "                            Good luck and have FUN!                           \n"
         << blue("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n\n\n\n\n\n\n") << endl;
    pause(true);
}

void game::credits(){
    clear();
    cout << lightblue("                                       ____  _   _    __    _  _  _  _  ___ \n"
                      "                                      (_  _)( )_( )  /__\\  ( \\( )( )/ )/ __)\n"
                      "                                        )(   ) _ (  /(__)\\  )  (  )  ( \\__ \\\n"
                      "                                       (__) (_) (_)(__)(__)(_)\\_)(_)\\_)(___/\n")
         << lightblue("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━┓") << lightblue("                   ____  _____  ____ \n")
         << lightblue("        Game made by:                          ") << lightblue("( ___)(  _  )(  _ \\\n")
         << lightblue(" John Wiesner & Aaron Wagner                   ") << lightblue(" )__)  )(_)(  )   /\n")
         << lightblue("       2017 Copyright                          ") << lightblue("(__)  (_____)(_)\\_)\n")
         << lightblue("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━┛")  << lightblue("         ____  __      __   _  _  ____  _  _  ___ \n")
         << lightblue("                                     (  _ \\(  )    /__\\ ( \\/ )(_  _)( \\( )/ __)\n"
                      "                                      )___/ )(__  /(__)\\ \\  /  _)(_  )  (( (_-.\n"
                      "                                     (__)  (____)(__)(__)(__) (____)(_)\\_)\\___/\n") << endl;
}

//Clears terminal
void game::clear(){
    cout << string( 24, '\n' );
}

//Prints fancy board
void game::print(gameboard &saveFile){
    int validrow = 0;
    clear();
    cout << "Number of empty boxes: " << numLeft << endl;
    cout << "Incorrect values: " << userIncorrect << endl;
    for(unsigned int row = 0; row <= 19; row++){
        for(unsigned int col = 0; col <= 8; col++){
            if(row == 17 && col == 0){
                cout << red("   Editing Cord");
            }else if(row == 18 && col == 0){
                cout << red("       (") << red(editCord1) << red(",") << red(editCord2) << red(")");
            }
            cout << gray(printing[row][col]);
            if(row % 2 == 0 && row != 0){
                validrow = row/2;
                if(saveFile.board.boardPlay[row-(validrow+1)][col] == 0){
                    cout << " ";
                }else if(saveFile.board.data[row-(validrow+1)][col] == 9){
                    cout << green(to_string(saveFile.board.boardPlay[row-(validrow+1)][col]));
                }else{
                    cout << white(to_string(saveFile.board.boardPlay[row-(validrow+1)][col]));
                }
            }
        }
        cout << gray(printing[row][9]);
    }
}

void game::getBoard(gameboard &saveFile, string boardName){
    string fileName = "../Sudoku/Boards.txt";

    fstream infile;
    infile.open(fileName, ios::in);

    if(infile){
        string temp;
        int count = 0;
        bool found = false;
        vector<string> importData;

        while(!infile.eof() && !found){
            getline(infile, temp);
            if(temp == boardName){
                found = true;
                importData.push_back(temp);
            }
        }
        while(!infile.eof() && (count < 30)){
            getline(infile, temp);
            importData.push_back(temp);
            count++;
        }
        infile.close();
        getData(saveFile, importData);
        run(saveFile);
    }else{
        infile.close();
        clear();
        fileName = "";
        cout << "Missing Boards.txt from directory" << endl;
        pause(true);
        clear();
        menu(saveFile);
    }

}

//Menu system for the game
void game::menu(gameboard &saveFile){
    if(!exit){
        int option = -1;
        clear();
        while(option < 0 || option > 7){
            if(option != -1) cout << "Must enter 0-7" << endl;
            cout << lightblue("                               _____             \n"
                              "                              |     |___ ___ _ _ \n"
                              "                              | | | | -_|   | | |\n"
                              "                              |_|_|_|___|_|_|___|\n\n")
                 << blue(    "                             ┏━━━━━━━━━━━━━━━━━━━━━┓\n")
                 << red("                               1) New game\n"
                        "                               2) Back to game\n"
                        "                               3) Screen Size\n"
                        "                               4) How to play\n"
                        "                               5) Import Board\n"
                        "                               6) Save Game\n"
                        "                               7) Credits\n"
                        "                               0) Exit Game\n")
                 << blue(     "                             ┗━━━━━━━━━━━━━━━━━━━━━┛")
                 << "\n\n\n\n\n\n\n\n\n";
            char temp = getInt();
            if(isdigit(temp)){
                option = temp - '0';
            }
            else if(temp == '-') option = 0;
        }
        if(option == 1){
            clear();
            boardSelect(saveFile);
            run(saveFile);
        }else if(option == 2){
            clear();
            run(saveFile);
        }else if(option == 3){
            sizeScreen();
            menu(saveFile);
        }else if(option == 4){
            howToPlay();
            menu(saveFile);
        }else if(option == 5){
            clear();
            import(saveFile);
        }else if(option == 6){
            clear();
            saveBoard(saveFile);
        }else if(option == 7){
            credits();
            pause(true);
            menu(saveFile);
        }else if(option == 0){
            clear();
            exit = true;
        }
    }
}

//Import and Export Boards***************************************************************************************

//Saves the current saveFile board to a user defined .txt file
void game::saveBoard(gameboard &saveFile){
    string name;
    string fileOutName = "../Sudoku/";
    string temp;
    temp = saveFile.title;
    temp += "\n";

    cout << "Enter name of file." << endl;
    getline(cin, name);

    if(name[0] == '-') menu(saveFile);
    else{
        fileOutName += name;
        fileOutName += ".txt";

        fstream outfile;
        outfile.open(fileOutName, ios::out);

        for(int b = 0; b < 3; b++){
            if(b == 0) outfile << temp;
            else if(b == 1) outfile << "Key:\n";
            else if(b == 2) outfile << "Data:\n";
            for(unsigned int row = 0; row < 9; row++){
                for(unsigned int col = 0; col < 9; col++){
                    if(b == 0) outfile << saveFile.board.boardPlay[row][col];
                    else if(b == 1) outfile << saveFile.board.boardKey[row][col];
                    else if(b == 2) outfile << saveFile.board.data[row][col];
                }
                outfile << "\n";
            }
        }
        outfile.close();

        cout << "Board Progress saved as: " << name << endl;
        exit = true;
        pause(true);
        clear();
    }
}

void game::getData(gameboard &savefile, vector<string> importData){
    string temp;
    int storeNum = 0;
    char temp2;
    int count = 0;
    savefile.title = importData[0];
    for(int r = 1; r < 30; r++){
        temp = importData[r];
        count = 0;
        for(unsigned int c = 0; c < temp.length(); c++){
            temp2 = temp[c];
            if(isdigit(temp2)) storeNum = temp2-'0';
            else storeNum = 0;

            if(r >= 1 && r < 10) savefile.board.boardPlay[r-1][count] = storeNum;
            else if(r >= 11 && r < 20) savefile.board.boardKey[r-11][count] = storeNum;
            else if(r >= 21 && r < 30) savefile.board.data[r-21][count] = storeNum;
            count++;
        }
    }
}

//Import a selected game board file.
void game::import(gameboard &saveFile){
    cout << "Enter the path of the .txt file with your board in it." << endl;
    string fileName;
    getline(cin, fileName);

    //DEFULT TEST: "../Sudoku/templateBoard.txt";

    //exits if player enters "-" char to quit to menu
    if(fileName[0] == '-'){
        menu(saveFile);
    }else{
        cout << "Using file directory: " << fileName << endl;
        fstream infile;

        infile.open(fileName, ios::in);

        if(infile){
            string temp;
            vector<string> importData;

            while(!infile.eof()){
                getline(infile, temp);
                importData.push_back(temp);
            }
            infile.close();
            getData(saveFile, importData);
            cout << "File Succesfully Imported" << endl;
            pause(true);
            run(saveFile);
        }else{
            infile.close();
            clear();
            fileName = "";
            cout << "Make sure files are where you are running this program." << endl;
            cout << "INVALID FILE NAME\n    """ << fileName << """ Was Not Found.      Enter a dash to return to menu." << endl;
            pause(true);
            clear();
            import(saveFile);
        }
    }
}

//Modify Board functions:********************************************************************************************

void game::dataBlock(gameboard &saveFile){
    for(int row = 0; row < 9; row++){
        for(int col = 0; col < 9; col++){
            if(saveFile.board.boardPlay[row][col] != 0){
                saveFile.board.data[row][col] = 9;
            }
        }
    }
}

//sets difficulty, board #, and loads it into "game memory"
void game::boardSelect(gameboard &saveFile){
    //Clears any values held before
    saveFile.diff = 0;
    saveFile.version = 0;
    string boardName;

    while(saveFile.diff != 1 && saveFile.diff != 2 && saveFile.diff != 3){
        if(saveFile.diff != 0){
            cout << yellow("Must enter 1 2 or 3") << endl;
        }
        cout << blue("                             ┏━━━━━━━━━━━━━━━━━━━━━┓\n")
             << bold("                                Choose difficulty:\n")
             << "                                   (1) Easy\n"
                "                                   (2) Medium\n"
                "                                   (3) Hard\n"
             << blue("                             ┗━━━━━━━━━━━━━━━━━━━━━┛\n")
             << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        char temp = getInt();
        if(isdigit(temp)){
            clear();
            saveFile.diff = temp - '0';
            if(saveFile.diff == 1) boardName = "Easy";
            else if(saveFile.diff == 2) boardName = "Medium";
            else if(saveFile.diff == 3) boardName = "Hard";
        }
        else if(temp == '-'){
            menu(saveFile);
        }
        cout << "\n";
    }

    while(saveFile.version < 1 || saveFile.version > 5){
        if(saveFile.version != 0) cout << "Must enter 1-5" << endl;
        cout << blue("                             ┏━━━━━━━━━━━━━━━━━━━━━━┓\n")
             << bold("                                Choose board number:\n")
             << "                                   (1) Board 1\n"
                "                                   (2) Board 2\n"
                "                                   (3) Board 3\n"
                "                                   (4) Board 4\n"
                "                                   (5) Board 5\n"
             << blue("                             ┗━━━━━━━━━━━━━━━━━━━━━━┛\n")
             << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
        char temp = getInt();
        if(isdigit(temp)){
            clear();
            saveFile.version = temp - '0';
            if(saveFile.version == 1) boardName += "1";
            else if(saveFile.version == 2) boardName += "2";
            else if(saveFile.version == 3) boardName += "3";
            else if(saveFile.version == 4) boardName += "4";
            else if(saveFile.version == 5) boardName += "5";
        }
        else if(temp == '-') menu(saveFile);
    }
    //getBoard(saveFile, boardName);
    //Copies board to saveFile and updates defult numbers
    copyBoard(saveFile);
    dataBlock(saveFile);
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

//Game Run functions:********************************************************************************************
//Code run logic
void game::run(gameboard &saveFile){
    bool go = true;
    char charcord1, sanswer, scord2;
    int cord1, cord2, answer = 0;

    check(saveFile);
    if(go && !(numLeft == 81)){
        do{
            if(!exit){
                editCord1 = " ";
                editCord2 = " ";
                print(saveFile);
            }
            charcord1 = 'Z';
            while(go && (charcord1 < 'A' || charcord1 > 'I') && !exit){
                cout << "Enter (A-I) cordinate: ";
                charcord1 = getAlpha();
                if(isalpha(charcord1)){
                    charcord1 = toupper(charcord1);
                    editCord1 = charcord1;
                    print(saveFile);
                }
                else if(charcord1 == '-') menu(saveFile);
            }
            cord1 = double(charcord1)-65;

            cord2 = -1;
            while(go && (cord2 < 0 || cord2 > 9) && !exit){
                cout << "Enter (1-9) cordinate: ";
                scord2= getInt();
                if(isdigit(scord2)){
                    editCord2 = scord2;
                    cord2 = scord2 - '0';
                    print(saveFile);
                }
                else if(scord2 == '-') menu(saveFile);
            }

            if(go && !exit){
                if(saveFile.board.data[cord2-1][cord1] == 9){
                    cout << "Not allowed to edit predefined numbers. Press Enter to Continue.";
                    pause(false);
                }else{
                    answer = -1;
                    while(go && (answer < 0 || answer > 9) && !exit){
                        cout << "Enter (1-9) answer: ";
                        sanswer = getInt();
                        if(isdigit(sanswer)){
                            answer = sanswer - '0';
                        }
                        else if(sanswer == '-') menu(saveFile);
                    }

                    //Update number in board and check for errors
                    saveFile.board.boardPlay[cord2-1][cord1] = answer;
                    check(saveFile);

                    //Does user win game? go == false
                    if((numLeft + userIncorrect) == 0){
                        exit = true;
                        go = false;
                    }
                }
            }
        }while(go && !exit);

        //User has won/solved puzzle
        if(!go && exit){
            win();
        }
    }else if(numLeft == 81 && !exit){
        clear();
        cout << "No game currently running..." << endl;
        pause(true);
        menu(saveFile);
    }else{
        clear();
        cout << "CORRUPTION IN RUN... Sorry for the error." << endl;
        pause(true);
        exit = true;
    }
}

//Checks to see if board is correct and sets error number in saveFile
void game::check(gameboard &saveFile){
    numLeft = 0;
    userIncorrect = 0;
    for(unsigned int row = 0; row < 9; row++){
        for(unsigned int col = 0; col < 9; col++){
            if((saveFile.board.boardPlay[row][col] != 0) && !(saveFile.board.boardPlay[row][col] == saveFile.board.boardKey[row][col])){
                userIncorrect++;
            }
            if(saveFile.board.boardPlay[row][col] == 0){
                numLeft++;
            }
        }
    }
}

//Suduko Boards
//Copies saved boards to game save file
void game::copyBoard(gameboard &saveFile){
    //Easy
    if(saveFile.diff == 1){
        if(saveFile.version == 1){
            saveFile.title = "Easy1";
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
            updateBoard(saveFile, main, key);
        }else if(saveFile.version == 2){
            saveFile.title = "Easy2";
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
            saveFile.title = "Easy3";
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
            saveFile.title = "Easy4";
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
            saveFile.title = "Easy5";
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
            saveFile.title = "Medium1";
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
            saveFile.title = "Medium2";
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
            saveFile.title = "Medium3";
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
            saveFile.title = "Medium4";
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
            saveFile.title = "Medium5";
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
            saveFile.title = "Hard1";
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
            saveFile.title = "Hard2";
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
            saveFile.title = "Hard3";
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
            saveFile.title = "Hard4";
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
            saveFile.title = "Hard5";
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

