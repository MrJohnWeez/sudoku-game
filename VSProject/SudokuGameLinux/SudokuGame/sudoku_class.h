#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip> //setw
#include <fstream>

#include "textediting.h"

using namespace std;

/*

This Sudoku c++ game was for a school project for the Spring 2017.
Copyright 2017 All rights reserved.
Last Edited 4/26/17


We used these unicode chars: http://www.copypastecharacter.com/all-characters
Game Report: https://docs.google.com/document/d/1W9t9L3NHXSCfmkRBUQDQo04xI60NdST3vGZK92s__sU/edit?usp=sharing


NOTE:
If the game terminal is not in color or if it has random characters the platform does not support Unicode
*This program was writen for Linux
*/

//Stores play board, key, and data
struct boardType {
	int boardPlay[9][9] = { { 0 } };
	int boardKey[9][9] = { { 0 } };
	int data[9][9] = { { 0 } };
};

//Creates a type that stores game data
struct gameboard {
	string title = "Custom_Board";
	int diff = 0;
	int version = 0;
	boardType board;
};


class game {
public:
	//This is a constructor
	game();

	//This is a deconstructor
	~game();

	//Start game:
	void sudukoGame();
private:
	//Priavte Vars
	gameboard saveFile;   //Acts like game save data
	bool exit;     //Terminates game if true
	int numLeft;    //Total number of numbers left
	int userIncorrect;  //User's numbers incorrect
	string editCord1;  //Used to print user's selected cords
	string editCord2;  //Used to print user's selected cords
	string printing[20][10] = { { "                        A   B   C   D   E   F   G   H   I   ","","","","","","","","","\n", },
	{ "                      ┏━━━┯━━━┯━━━┳━━━┯━━━┯━━━┳━━━┯━━━┯━━━┓ ","","","","","","","","","\n", },
	{ "                   1❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n", },
	{ "                   2❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n", },
	{ "                   3❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫ ","","","","","","","","","\n", },
	{ "                   4❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n", },
	{ "                   5❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n", },
	{ "                   6❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┣━━━┿━━━┿━━━╋━━━┿━━━┿━━━╋━━━┿━━━┿━━━┫ ","","","","","","","","","\n", },
	{ "                   7❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n", },
	{ "                   8❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "       ┠───┼───┼───╂───┼───┼───╂───┼───┼───┨ ","","","","","","","","","\n", },
	{ "       9❱ ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ "," │ "," │ "," ┃ \n", },
	{ "                      ┗━━━┷━━━┷━━━┻━━━┷━━━┷━━━┻━━━┷━━━┷━━━┛ ","","","","","","","","","\n", }, };

	//Cin call functions durring game operation. These prevent any glitches/bugs/crashes
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
	void print(const gameboard &saveFile);
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
};