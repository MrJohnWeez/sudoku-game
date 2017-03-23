#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <iomanip> //setw


using namespace std;


//What to do...
//All things that need done


//Q & A



//Creates a type stored in gameboard that stores play board and the key
struct holdBoard{
    int boardPlay[9][9] = {{0}};
    int boardKey[9][9] = {{0}};
};

//Creates a type that stores game data
struct gameboard{
    string title;
    holdBoard board;
};



class game{
public:
    game(){

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
        cin.get(); //Pause until enter
    }

    void updateBoard(gameboard &start, int main[][9], int key[][9]){
        for(unsigned int row = 0; row < 9; row++){
            for(unsigned int col = 0; col < 9; col++){
                start.board.boardPlay[row][col] = main[row][col];
                start.board.boardKey[row][col] = key[row][col];
            }
        }
    }

    void chooseBoard(int diff, gameboard &start){
        //easy
        if(diff == 1){
            int main[9][9] = {{3, 0, 6, 5, 0, 8, 4, 0, 0},
                              {5, 2, 0, 0, 0, 0, 0, 0, 0},
                              {0, 8, 7, 0, 0, 0, 0, 3, 1},
                              {0, 0, 3, 0, 1, 0, 0, 8, 0},
                              {9, 0, 0, 8, 6, 3, 0, 0, 5},
                              {0, 5, 0, 0, 9, 0, 6, 0, 0},
                              {1, 3, 0, 0, 0, 0, 2, 5, 0},
                              {0, 0, 0, 0, 0, 0, 0, 7, 4},
                              {0, 0, 5, 2, 0, 6, 3, 0, 0}};
            int key[9][9] = {{3, 1, 6, 5, 7, 8, 4, 9, 2},
                             {5, 2, 9, 1, 3, 4, 7, 6, 8},
                             {4, 8, 7, 6, 2, 9, 5, 3, 1},
                             {2, 6, 3, 4, 1, 5, 9, 8, 7},
                             {9, 7, 4, 8, 6, 3, 1, 2, 5},
                             {8, 5, 1, 7, 9, 2, 6, 4, 3},
                             {1, 3, 8, 9, 4, 7, 2, 5, 6},
                             {6, 9, 2, 3, 5, 1, 8, 7, 4},
                             {7, 4, 5, 2, 8, 6, 3, 1, 9}};
            //changes boards to selected option
            //Like start.board.boardPlay = main
            //start.board.boardPlay[row][col] = main[row][col]
            updateBoard(start, main, key);

            //medium
        }else if(diff == 2){
            int main[9][9] = {{4, 0, 6, 5, 0, 8, 4, 0, 0},
                              {5, 2, 0, 0, 0, 0, 0, 0, 0},
                              {0, 8, 7, 0, 0, 0, 0, 3, 1},
                              {0, 0, 3, 0, 1, 0, 0, 8, 0},
                              {9, 0, 0, 8, 6, 3, 0, 0, 5},
                              {0, 5, 0, 0, 9, 0, 6, 0, 0},
                              {1, 3, 0, 0, 0, 0, 2, 5, 0},
                              {0, 0, 0, 0, 0, 0, 0, 7, 4},
                              {0, 0, 5, 2, 0, 6, 3, 0, 0}};
            int key[9][9] = {{3, 1, 6, 5, 7, 8, 4, 9, 2},
                             {5, 2, 9, 1, 3, 4, 7, 6, 8},
                             {4, 8, 7, 6, 2, 9, 5, 3, 1},
                             {2, 6, 3, 4, 1, 5, 9, 8, 7},
                             {9, 7, 4, 8, 6, 3, 1, 2, 5},
                             {8, 5, 1, 7, 9, 2, 6, 4, 3},
                             {1, 3, 8, 9, 4, 7, 2, 5, 6},
                             {6, 9, 2, 3, 5, 1, 8, 7, 4},
                             {7, 4, 5, 2, 8, 6, 3, 1, 9}};
            updateBoard(start, main, key);

        //hard
        }else{
            int main[9][9] = {{5, 0, 6, 5, 0, 8, 4, 0, 0},
                                    {5, 2, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 8, 7, 0, 0, 0, 0, 3, 1},
                                    {0, 0, 3, 0, 1, 0, 0, 8, 0},
                                    {9, 0, 0, 8, 6, 3, 0, 0, 5},
                                    {0, 5, 0, 0, 9, 0, 6, 0, 0},
                                    {1, 3, 0, 0, 0, 0, 2, 5, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 7, 4},
                                    {0, 0, 5, 2, 0, 6, 3, 0, 0}};
            int key[9][9] = {{3, 1, 6, 5, 7, 8, 4, 9, 2},
                                       {5, 2, 9, 1, 3, 4, 7, 6, 8},
                                       {4, 8, 7, 6, 2, 9, 5, 3, 1},
                                       {2, 6, 3, 4, 1, 5, 9, 8, 7},
                                       {9, 7, 4, 8, 6, 3, 1, 2, 5},
                                       {8, 5, 1, 7, 9, 2, 6, 4, 3},
                                       {1, 3, 8, 9, 4, 7, 2, 5, 6},
                                       {6, 9, 2, 3, 5, 1, 8, 7, 4},
                                       {7, 4, 5, 2, 8, 6, 3, 1, 9}};
            updateBoard(start, main, key);
        }
    }


    gameboard boardSelect(){
        int diff = 0;
        int version = 0;
        while(diff != 1 && diff != 2 && diff != 3){
            if(diff != -1){
                cout << "Must enter 1 2 or 3" << endl;
            }
            cout << "Choose difficulty:\n"
                 << "(1) Easy\n"
                 << "(2) Medium\n"
                 << "(3) Hard\n";
            cin >> diff;
        }

        while(version < 1 && version > 5){
            if(version < 1 && version > 5){
                cout << "Must enter 1 2 or 3" << endl;
            }
            cout << "Choose difficulty:\n"
                 << "(1) Easy\n"
                 << "(2) Medium\n"
                 << "(3) Hard\n";
            cin >> diff;
        }
        gameboard playBoard;
        playBoard.title = "Easy #1";


        //Choose board also
        //Needs to go into this function below

        chooseBoard(diff, playBoard);



        //Temp Printing
        int row, col = 0;
        for(row = 0; row < 9; row++){
            for(col = 0; col < 9; col++){
                cout << playBoard.board.boardPlay[row][col];
            }
            cout << endl;
        }
        cout << "\n" << endl;
        for(row = 0; row < 9; row++){
            for(col = 0; col < 9; col++){
                cout << playBoard.board.boardKey[row][col];
            }
            cout << endl;
        }

        return playBoard;
    }

public:
    void playGame(){
        title();
        boardSelect();

    }
};
