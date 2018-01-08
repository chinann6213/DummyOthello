/*
    Program: TT02_P2_NG_CHIN_ANN.cpp
    Course: Bachelor of Computer Science (Hons.)
    Subject: TCP1101 Programming Fundamentals
    Year: 2015/2016 Trimester 1
    Name: NG CHIN ANN
    ID: 1142701684
    Email: chinann6213@gmail.com
    Phone: 011-1076 6957
*/
###
#include <iostream>
#include <string>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>

using namespace std;

char board[8][8];
int Ochance1 = 1, Xchance1 = 1;
int Ochance2 = 1, Xchance2 = 1;

char menu(); // Function used to print Main Menu;
void saveGame(string& FileName, int player, int Ochance1, int Xchance1, int Ochance2, int Xchance2, int NoValidMove, int NoValidMove2); //Function to save game.
void loadGame(int& player, int& Ochance1, int& Xchance1, int& Ochance2, int& Xchance2, int& NoValidMove, int& NoValidMove2); // Function to load game.
void iniBoard(int& player, int& Odisk, int& Xdisk, int& NoValidMove, int& NoValidMove2, int& IWantToPlay); // Function used to initialize the value of array to become blank.
void printBoard(); // Function used to print out the board of array by using loop.
int ASCIIvalue(int& intInput1, int& intInput2, string& input1); // Function used to convert the string input to integer.
int validMove(int& player); // Function used to check the whole board to see whether there is a valid move.
void score(int& Odisk, int& Xdisk); // Function used to calculate the player score after placing a disc.
char input(int& player, int& Odisk, int& Xdisk, int& NoValidMove, int& NoValidMove2); // Function to let player input coordinate.
char legalMove(int& intInput1, int& intInput2, int& player, int& flipDisk); // Function to check the input and flip disc.
int superMove(int& Odisk, int& Xdisk, int& Ochance1, int& Xchance1, int& player); // Function of Super Power 1.
int superMove2(int& player, int& Ochance2, int& Xchance2); // Function of Super Power 2.
char game(int ReadGame); // Function used to display the structure of whole game.
char help(); // Function used to display help menu.

int main()
{
    menu();
    return 0;
}

void saveGame(string& FileName, int player, int Ochance1, int Xchance1, int Ochance2, int Xchance2, int NoValidMove, int NoValidMove2) // Function used to save game.
{
    ofstream save;

	save.open(FileName.c_str());

    //Loop to save current board of the game.
	for (int row = 0; row <= 7; row++)
    {
        for (int column = 0; column <= 7; column++)
        {
            if (board[row][column] == 'O')
            {
                save << "1" << endl;
            }
            else if (board[row][column] == 'X')
            {
                save << "2" << endl;
            }
            else if (board[row][column] == ' ')
            {
                save << "3" << endl;
            }
        }
    }
    save << player << endl;         // Save player turn.
    save << Ochance1 << endl;       // Save valid move for super power 1 of player O.
    save << Xchance1 << endl;       // Save valid move for super power 1 of player X.
    save << Ochance2 << endl;       // Save valid move for super power 2 of player O.
    save << Xchance2 << endl;       // Save valid move for super power 2 of player X.
    save << NoValidMove << endl;    // Save valid input condition.
    save << NoValidMove2 << endl;   // Save win condition.

    save.close();

    cout << "Game saved to " <<FileName <<"."<<endl
         << "Please continue to input."<<endl
         << "==> ";
}

void loadGame(int& player, int& Ochance1, int& Xchance1, int& Ochance2, int& Xchance2, int& NoValidMove, int& NoValidMove2) // Function used to load game.
{
    ifstream load;
    cout << "Please enter filename: ";
	string FileName;
	getline(cin, FileName, '\n');

    load.open(FileName.c_str());

    if (load.fail())
    {
        cout << "You have enter an invalid file name."<<endl
             << "Please press any key to back to menu.";
             getch();
        system("CLS");
        menu();
    }

    // Loop to load current state of the game.
    string checkBoard;
        for (int row = 0; row <= 7; row++)
        {
            for (int column = 0; column <= 7; column++)
            {
                load >> checkBoard;
                    if (checkBoard == "1")
                    {
                        board[row][column] = 'O';
                    }
                    else if (checkBoard == "2")
                    {
                        board[row][column] = 'X';
                    }
                    else if (checkBoard == "3")
                    {
                        board[row][column] = ' ';
                    }
            }
        }
    load >> player;        // Load player turn.
    load >> Ochance1;      // Load valid move of super power 1 for player O.
    load >> Xchance1;      // Load valid move of super power 1 for player X.
    load >> Ochance2;      // Load valid move of super power 2 for player O.
    load >> Xchance2;      // Load valid move of super power 2 for player X.
    load >> NoValidMove;   // Load valid input condition.
    load >> NoValidMove2;  // Load win condition.

    load.close();
}

char menu() // Function used to print Main Menu;
{
    string option;
    cout<<"|********************************|"<<endl    //*****************************
        <<"|          Othello Game          |"<<endl    //*                           *
        <<"|********************************|"<<endl    //*        Main Menu          *
        <<"1. New game."<<endl                          //*          of the           *
        <<"2. Load game."<<endl                         //*       Othello Game        *
        <<"3. Help."<<endl                              //*                           *
        <<"4. Quit."<<endl                              //*****************************
        <<"Please select an option(1, 2, 3 or 4 ONLY): ";
    cin >> option;
    cout<<endl;
    while (option != "1" && option != "2" && option != "3" && option != "4") // Error checking. If the option enter is not 1/2/3, it will display invalid.
    {
        cout << "Invalid input. Please select an option again(1, 2, 3 or 4 ONLY).";
        cin >> option;
        cout <<endl;
    }
    cin.ignore(1000, '\n');
    int ReadGame = 0;
        if (option == "1")
        {
            system("CLS");
            ReadGame = 0;
            if (game(ReadGame) == 'M') // Call the new game function to main function.
            {
                system("CLS");
                menu();
            }
        }
        else if (option == "2")
        {
            system("CLS");
            ReadGame = 1;
            if (game(ReadGame) == 'M') // Call the saved game function to main function.
            {
                system("CLS");
                menu();
            }
        }
        else if (option == "3")
        {
            system("CLS");
            if (help() == 'M')// Call the help function to main function.
            {
                system("CLS");
                menu();
            }
        }
        else if (option == "4")
        {
            return 0;
        }
}

void iniBoard(int& player, int& Odisk, int& Xdisk, int& NoValidMove, int& NoValidMove2, int& IWantToPlay) // Function used to initialize the value of array to become blank.
{
//Nested loop to make every memory location of array become blank.
for (int x=0;x<=7;x++)
{
    for (int y=0;y<=7;y++)
    {
        board[x][y]=' ';
    }
}
board [3][3] = 'X'; //Assign 'X' to d 4.
board [4][4] = 'X'; //Assign 'X' to e 5.
board [4][3] = 'O'; //Assign 'O' to d 5.
board [3][4] = 'O'; //Assign 'O' to e 4.

player = 0; // Initialize player to become 0.
Odisk = 2, Xdisk = 2;
NoValidMove = 0, NoValidMove2 = 0;
IWantToPlay = 1;
}

void printBoard() // Function used to print out the board of array by using loop.
{
int numBoard = 7; // Initialize the value of row in board[8][8] (2D array) to 7.
int numBoard2 = 0; // Initialize the value of column in board[8][8] (2D array) to 0.
for (int n = 8; n >= 1; n--) //Loop for cell at horizontal line.
{
    cout<<" |---+---+---+---+---+---+---+---|"<<endl;
    cout << n << "| "; // n represent the number of row of the game board.
        for (int m = 1; m <= 8; m++) //Loop for cell at vertical line.
        {
            cout << board[numBoard][numBoard2] <<" " <<"| "; //Print empty cell from row 7 to row 0 and from column 0 to column 7;
            numBoard2++;
        }
    numBoard--; //Decrease the value of row by 1 for each loop so it will print from 7 to 0;.
    numBoard2 = 0; // After each time of loop, reset the column of the board to become 0 and loop again from 0 to 7;
    cout<<endl;
}
    cout<<" |---+---+---+---+---+---+---+---|"<<endl
        <<"   a   b   c   d   e   f   g   h"<<endl; // Alphabet to represent the column of the game board.
}

int ASCIIvalue(int& intInput1, int& intInput2, string& input1) // Function used to convert the string input to integer.
{
    intInput1 = input1[0]-97; //Change char to int by subtracting input1[0]'s ASCII value to get int from 0-7.
    intInput2 = input1[2]-49; // Change char to int by subtracting input1[1]'s ASCII value to get int from 0-7.
}

int validMove(int& player) // Function used to check the whole board to see whether there is a valid move.
{
    int column, row, valid = 0; // Variable row is to check the row of whole board, variable to check the column of whole board, variable valid to check valid move.
    int OppoDisk = 0, IsMyDisk = 0; // Variable OppoDisk is to check cells surround an empty cell to check whether they are which player's disk.
    char playerDisk, playerDisk2; // Variable playerDisk is to represent self's disc and playerDisk2 are to represent opponent's disc.
    if (player == 0)
    {
        playerDisk = 'O';
        playerDisk2 = 'X';
    }
    else if (player == 1)
    {
        playerDisk = 'X';
        playerDisk2 = 'O';
    }
    for (int checkrow = 0; checkrow <= 7; checkrow ++)                 //*****************************
    {                                                                  //* loop the whole game board *
        for (int checkcolumn = 0; checkcolumn <= 7; checkcolumn ++)    //*****************************
        {
           if (board[checkrow][checkcolumn] == ' ') // If the particular cell is empty, continue the loop to check the surrounding discs.
           {
                OppoDisk = 0; IsMyDisk = 0; // Initialize the variable to 0 for every nested loop.
                for (column = checkcolumn + 1; column <= 7; column ++) // Loop to check the right side of an empty cell.
                {
                    if (board[checkrow][column] == ' ') // If the right side of an empty cell is also empty, break the particular loop
                    {                                   // because it means invalid move.
                        break;
                    }
                    else if (board[checkrow][column] == playerDisk2) // If the right side of an empty cell is opponent's disc,
                    {                                                // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[checkrow][column] == playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                                // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
                OppoDisk = 0; IsMyDisk = 0;
                for (row = checkrow - 1; row >= 0; row --) //Loop to check the bottom side of an empty cell.
                {
                    if (board[row][checkcolumn] == ' ') // If the bottom side of an empty cell is also empty, break the particular loop
                    {                                   // because it means invalid move.
                        break;
                    }
                    else if (board[row][checkcolumn] == playerDisk2) // If the bottom side of an empty cell is opponent's disc,
                    {                                                // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[row][checkcolumn] == playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                                // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
                OppoDisk = 0; IsMyDisk = 0;
                for (column = checkcolumn - 1; column >= 0; column --) //Loop the check the left side of an empty cell.
                {
                    if (board[checkrow][column] == ' ') // If the left side of an empty cell is also empty, break the particular loop
                    {                                   // because it means invalid move.
                        break;
                    }
                    else if (board[checkrow][column] == playerDisk2) // If the left side of an empty cell is opponent's disc,
                    {                                                // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[checkrow][column] == playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                                // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
                OppoDisk = 0; IsMyDisk = 0;
                for (row = checkrow + 1; row <= 7; row ++) // Loop to check the top side of an empty cell.
                {
                    if (board[row][checkcolumn] == ' ') // If the top side of an empty cell is also empty, break the particular loop
                    {                                   // because it means invalid move.
                        break;
                    }
                    else if (board[row][checkcolumn] == playerDisk2) // If the top side of an empty cell is opponent's disc,
                    {                                                // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[row][checkcolumn] == playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                                // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
                OppoDisk = 0; IsMyDisk = 0;
                for (row = checkrow + 1, column = checkcolumn + 1; row <= 7 && column <= 7; row ++) //Loop to check the top right side of an empty cell.
                {
                    if (board[row][column] == ' ') // If the top right side of an empty cell is also empty, break the particular loop
                    {                              // because it means invalid move.
                        break;
                    }
                    else if (board[row][column] == playerDisk2) // If the top right side of an empty cell is opponent's disc,
                    {                                           // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[row][column] ==  playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                            // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                    column ++;
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
                OppoDisk = 0; IsMyDisk = 0;
                for (row = checkrow - 1, column = checkcolumn + 1; row >= 0 && column <= 7; row --) //Loop the check the bottom right side of an empty cell.
                {
                    if (board[row][column] == ' ') // If the bottom right side of an empty cell is also empty, break the particular loop
                    {                              // because it means invalid move.
                        break;
                    }
                    else if (board[row][column] == playerDisk2) // If the bottom right side of an empty cell is opponent's disc,
                    {                                           // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[row][column] ==  playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                            // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                    column ++;
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
                OppoDisk = 0; IsMyDisk = 0;
                for (row = checkrow - 1, column = checkcolumn - 1; row >= 0 && column >= 0; row --) //Loop to check the bottom left side of an empty cell.
                {
                    if (board[row][column] == ' ') // If the bottom left side of an empty cell is also empty, break the particular loop
                    {                              // because it means invalid move.
                        break;
                    }
                    else if (board[row][column] == playerDisk2) // If the bottom left side of an empty cell is opponent's disc,
                    {                                           // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[row][column] ==  playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                            // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                    column ++;
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
                OppoDisk = 0; IsMyDisk = 0;
                for (row = checkrow + 1, column = checkcolumn - 1; row <= 7 && column >= 0; row ++) //Loop to check the top left side of an empty cell.
                {
                    if (board[row][column] == ' ') // If the top left side of an empty cell is also empty, break the particular loop
                    {                              // because it means invalid move.
                        break;
                    }
                    else if (board[row][column] == playerDisk2) // If the top left side of an empty cell is opponent's disc,
                    {                                           // assign value 1 as true to the variable OppoDisk.
                        OppoDisk = 1;
                    }
                    else if (board[row][column] ==  playerDisk && OppoDisk == 1) // If the next loop found the disc is self's disc and
                    {                                                            // the previous disc is opponent's disc, the move is valid.
                        IsMyDisk = 1; // If the move is valid, assign value 1(true) to variable IsMyDisk.
                    }
                    else
                    {
                        break; // If the condition is none of the above, break the loop. (e.g. the first cell next to the empty cell is self's disc.
                    }
                    column ++;
                }
                if (IsMyDisk == 1)
                {
                    valid = 1; // If the above condition is 1(meaning true), assign value 1(true) to variable valid, meaning there is a valid move.
                }
           }
        }
    }
    if (valid == 1) // If one of the loop found that the move is valid,
    {               // return 1(as there is a valid move) to game function.
        return 1;
    }
    else            // If all of the loop did not found any valid moves,
    {               // return -1 (as there is no valid moves) to game function.
        return -1;
    }
}

// Function used to check the input and flip disc. Almost the same structure with the validMove function above.
// 1. After player input a coordinate, if the cell next to the coordinate is not empty, the loop will
// check the cell whether it is opponent's disc. If the cell is opponent's disc,it will mark a value 1(true).
// 2. If the next loop found the disc is self's disc and the previous disc is opponent's disc, it will
// remember the value of the self's disc and verify the condition as true(by assign value 1 as true to variable IsMyDisk.
// 3. Again use a for loop to flip the opponent's discs which are valid to become self's discs. The loop will start
// from the cell next to the coordinate input and stop before the value remembered by the checking of statement 2.
// ***The structure will loop 8 times for 8 sides. (right, bottom, left, top, top right, bottom right, bottom left, top left)
char legalMove(int& intInput1, int& intInput2, int& player, int& flipDisk)
{
    int column, row;
    flipDisk = 0;
    int rmbMyDisk, rmbMyDisk2;
    int OppoDisk = 0, IsMyDisk = 0;
    char playerDisk, playerDisk2;
    if (player == 0)
    {
        playerDisk = 'O';
        playerDisk2 = 'X';
    }
    else if (player == 1)
    {
        playerDisk = 'X';
        playerDisk2 = 'O';
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (column = intInput1 + 1; column <= 7; column ++) //Loop to check the right side of the input coordinate.
    {
        if (board[intInput2][column] != ' ')
        {
            if (board[intInput2][column] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[intInput2][column] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = column;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    for (column = intInput1 + 1; column < rmbMyDisk && IsMyDisk == 1; column ++) // Loop to flip the discs of right side.
    {
        board[intInput2][column] = playerDisk;
        flipDisk ++;
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (row = intInput2 - 1; row >= 0; row --) //Loop to check the bottom side of the input coordinate.
    {
        if (board[row][intInput1] != ' ')
        {
            if (board[row][intInput1] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[row][intInput1] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = row;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    for (row = intInput2 - 1; row > rmbMyDisk && IsMyDisk == 1; row --) // Loop to flip the discs of bottom side.
    {
        board[row][intInput1] = playerDisk;
        flipDisk ++;
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (column = intInput1 - 1; column >= 0; column --) //Loop to check the left side of the input coordinate.
    {
        if (board[intInput2][column] != ' ')
        {
            if (board[intInput2][column] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[intInput2][column] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = column;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    for (column = intInput1 - 1; column > rmbMyDisk && IsMyDisk == 1; column --) // Loop to flip the discs of left side.
    {
        board[intInput2][column] = playerDisk;
        flipDisk ++;
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (row = intInput2 + 1; row <= 7; row ++) //Loop to check the top side of the input coordinate.
    {
        if (board[row][intInput1] != ' ')
        {
            if (board[row][intInput1] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[row][intInput1] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = row;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    for (row = intInput2 + 1; row < rmbMyDisk && IsMyDisk == 1; row ++) // Loop to flip the discs of top side.
    {
        board[row][intInput1] = playerDisk;
        flipDisk ++;
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (row = intInput2 + 1, column = intInput1 + 1; row <= 7 && column <= 7; row ++) //Loop to check the top right side of the input coordinate.
    {
        if (board[row][column] != ' ')
        {
            if (board[row][column] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[row][column] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = row;
                rmbMyDisk2 = column;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        column ++;
    }
    // Loop to flip the discs of top right side.
    for (row = intInput2 + 1, column = intInput1 + 1; row < rmbMyDisk && column < rmbMyDisk2 && IsMyDisk == 1; row ++)
    {
        board[row][column] = playerDisk;
        flipDisk ++;
        column++;
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (row = intInput2 - 1, column = intInput1 + 1; row >= 0 && column <= 7; row --) //Loop to check the bottom right side of the input coordinate.
    {
        if (board[row][column] != ' ')
        {
            if (board[row][column] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[row][column] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = row;
                rmbMyDisk2 = column;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        column ++;
    }
    // Loop to flip the discs of bottom right side.
    for (row = intInput2 - 1, column = intInput1 + 1; row > rmbMyDisk && column < rmbMyDisk2 && IsMyDisk == 1; row --)
    {
        board[row][column] = playerDisk;
        flipDisk ++;
        column++;
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (row = intInput2 - 1, column = intInput1 - 1; row >= 0 && column >= 0; row --) //Loop to check the bottom left side of the input coordinate.
    {
        if (board[row][column] != ' ')
        {
            if (board[row][column] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[row][column] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = row;
                rmbMyDisk2 = column;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        column --;
    }
    // Loop to flip the discs of bottom left side.
    for (row = intInput2 - 1, column = intInput1 - 1; row > rmbMyDisk && column > rmbMyDisk2 && IsMyDisk == 1; row --)
    {
        board[row][column] = playerDisk;
        flipDisk ++;
        column--;
    }
    OppoDisk = 0; IsMyDisk = 0;
    for (row = intInput2 + 1, column = intInput1 - 1; row <= 7 && column >= 0; row ++) //Loop to check the top left side of the input coordinate.
    {
        if (board[row][column] != ' ')
        {
             if (board[row][column] == playerDisk2)
            {
                OppoDisk = 1;
            }
            else if (board[row][column] == playerDisk && OppoDisk == 1)
            {
                rmbMyDisk = row;
                rmbMyDisk2 = column;
                IsMyDisk = 1;
                break;
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        column --;
    }
    // Loop to flip the discs of top left side.
    for (row = intInput2 + 1, column = intInput1 - 1; row < rmbMyDisk && column > rmbMyDisk2 && IsMyDisk == 1; row ++)
    {
        board[row][column] = playerDisk;
        flipDisk ++;
        column--;
    }
}

void score(int& Odisk, int& Xdisk) // Function used to calculate the player score after placing a disc.
{
    int row, column, Oscore = 0, Xscore = 0;
    for (row = 7; row >= 0; row --) // Loop through the whole game board to calculate the number of discs O and discs X.
    {
        for (column = 0; column <= 7; column ++)
        {
            if (board[row][column] == 'O')
            {
                Oscore ++;
            }
            else if (board[row][column] == 'X')
            {
                Xscore ++;
            }
        }
    }
    Odisk = Oscore; Xdisk = Xscore; // After calculating the number of discs, pass the value to the variable Odisk and Xdisk to display.
}

char input(int& player, int& Odisk, int& Xdisk, int& NoValidMove, int& NoValidMove2) // Function to let player input coordinate.
{
string input1;
int intInput1,intInput2, flipDisk;
int ValidMove = 0, ValidMove2 = 0;

do
{
    while (ValidMove2 == 0) // Statement help to loop the input coordinate if user input errors.
    {
        getline(cin, input1, '\n');
        if ((input1[0] == 'a' || input1[0] == 'b' || input1[0] == 'c' || input1[0] == 'd' || input1[0] == 'e' || input1[0] == 'f' ||
             input1[0] == 'g' || input1[0] == 'h') && (input1[2] == '1' || input1[2] == '2' || input1[2] == '3' || input1[2] == '4' ||
             input1[2] == '5' || input1[2] == '6' || input1[2] == '7' || input1[2] == '8') && input1[1] == ' ' && input1.length() == 3)
        {
            ASCIIvalue(intInput1, intInput2, input1); // Function used to convert the string input to integer after player inputs.
            legalMove(intInput1, intInput2, player, flipDisk); // Function to check the input and flip disc after player inputs.
            ValidMove2 = 1;
        }
        else if (input1 == "menu")
        {
            Ochance1 = 1; Xchance1 = 1; Ochance2 = 1; Xchance2 = 1; // Reset the valid move of super power every time user go back to menu.
            return 'M'; // Return 'M' to game function.
        }
        else if (input1 == "super1")
        {
            if (player == 0 && Ochance1 == 1)
            {
                NoValidMove = 0;
                return superMove(Odisk, Xdisk, Ochance1, Xchance1, player); // Function of Super Power 1.
            }
            else if (player == 1 && Xchance1 == 1)
            {
                NoValidMove = 0;
                return superMove(Odisk, Xdisk, Ochance1, Xchance1, player); // Function of Super Power 1.
            }
            else
            {
                cout << "Super power 1 is used!"<<endl
                     << "Please try another super power or continue input."<<endl
                     << "==> ";
            }
        }
        else if (input1 == "super2")
        {
            if (player == 0 && Ochance2 == 1)
            {
                NoValidMove = 0;
                return superMove2(player, Ochance2, Xchance2); // Function of Super Power 2.
            }
            else if (player == 1 && Xchance2 == 1)
            {
                NoValidMove = 0;
                return superMove2(player, Ochance2, Xchance2); // Function of Super Power 2.
            }
            else
            {
                cout << "Super power 2 is used!"<<endl
                     << "Please try another super power or continue input."<<endl
                     << "==> ";
            }
        }
        else if (input1 == "next player") //If player entered 'next player', break the inner loop.
        {
            break;
        }
        else if (input1[0] == 's' && input1[1] == 'a' && input1[2] == 'v' && input1[3] == 'e' && input1[4] == ' ')
        {
            string FileName;
            int inputLen = input1.length();
            for (int len = 5; len <= inputLen - 1; len ++)
            {
                if (len == 5)
                {
                    FileName = input1[len];
                }
                else
                {
                    FileName = FileName + input1[len];
                }
            }
            saveGame(FileName, player, Ochance1, Xchance1, Ochance2, Xchance2, NoValidMove, NoValidMove2);
        }
        // Error checking. If player did not input a coordinate which is from a-h and 1-8, without spacing and the length is not 3,
        // inform the player to input again.
        else
        {
            cout << "Invalid, please enter again! "<<endl
                 << "==> ";
        }
    }
    if (input1 == "next player") // If player entered 'next player', break the outer loop and proceed to next player.
    {
        break;
    }
    if (flipDisk == 0 || board[intInput2][intInput1] != ' ') // If the value of the flipDisk at legalMove function is 0 or not empty,
    {                                                        // inform the player to input again because the move is invalid.
        cout << "Invalid, please enter again! "<<endl
             << "==> ";
        ValidMove2 = 0;
    }
    else
    {
        ValidMove = 1; // If there is no errors at input, the value of the statement will become 1 and break the outer loop
    }
}while (ValidMove == 0);

    // After user input a coordinate, O or X will be placed on the input coordinate based on player turn.
    if(player == 0) // Set by default, player 0 will has disc O.
    {
        board[intInput2][intInput1] = 'O';
    }
    else if (player == 1) // Set by default, player 1 will has disc X.
    {
       board[intInput2][intInput1] = 'X';
    }

}

int superMove(int& Odisk, int& Xdisk, int& Ochance1, int& Xchance1, int& player) // Function of Super Power 1.
{
    int row, column;
    // Loop through the whole board to search for O discs and X discs, swap them.
    cout << "Swap the discs between two player."<<endl;
    system("pause");
    for (row = 7; row >= 0; row --)
    {
        for (column = 0; column <= 7; column++)
        {
            if (board[row][column] == 'X')
            {
                board[row][column] = 'O';
            }
            else if (board[row][column] == 'O')
            {
                board[row][column] = 'X';
            }
        }
    }
    swap(Odisk, Xdisk); // Swap the scores of O player and X player when the discs are swapped.
    if (player == 0)
    {
        Ochance1 = 0; // Valid move of super power for O player is set to 0 so that player cannot use this anymore.
    }
    else if (player == 1)
    {
        Xchance1 = 0; // Valid move of super power for X player is set to 0 so that player cannot use this anymore.
    }
}

int superMove2(int& player, int& Ochance2, int& Xchance2) // Function of Super Power 2.
{
char playerDisk, playerDisk2;
    if (player == 0)
    {
        playerDisk = 'O';
    }
    else if (player == 1)
    {
        playerDisk = 'X';
    }
cout << "Turns 1 row or 1 column randomly to become your discs." <<endl;
system("pause");
srand(time(NULL)); // Generate random number by using current time of computer.
int row, column;
int super2column, super2row;
int randomNum;
randomNum = rand();
    if (randomNum % 2 == 0)
    {
        super2column = (rand()) % 8;
        for (row = 7; row >= 0; row--) // For loop to turn a random column to current player's discs.
        {
            board[row][super2column] = playerDisk;
        }
    }
    else if (randomNum % 2 == 1)
    {
        super2row = (rand()) % 8;
        for (column = 0; column <= 7; column++) // For loop to turn a random row to current player's discs.
        {
            board[super2row][column] = playerDisk;
        }
    }
    if (player == 0)
    {
        Ochance2 = 0; // Valid move of super power for O player is set to 0 so that player cannot use this anymore.
    }
    else if (player == 1)
    {
        Xchance2 = 0; // Valid move of super power for X player is set to 0 so that player cannot use this anymore.
    }
}

char game(int ReadGame) // Function used to display the structure of whole game.
{
    int player;
    int Odisk, Xdisk;
    int NoValidMove, NoValidMove2;
    int IWantToPlay;
    if (ReadGame == 1)
    {
        loadGame(player, Ochance1, Xchance1, Ochance2, Xchance2, NoValidMove, NoValidMove2);
        score(Odisk, Xdisk);
    }
    else if (ReadGame == 0)
    {
        iniBoard(player, Odisk, Xdisk, NoValidMove, NoValidMove2, IWantToPlay);
        // Function used to initialize the value of array to become blank is called.
    }

    do
    {
        system("CLS");
        printBoard(); // Function used to print out the board of array by using loop is called.
        cout<<"       O score= "<<Odisk <<" X score= "<<Xdisk<<endl<<endl;
        if (validMove(player) == 1) // Function used to check the whole board is called to see whether there is a valid move.
        {                           // If there is a valid move, continue the loop.
            if (player == 0) // Set by default, player 0 will have O discs.
            {
                cout<< "O player input"<<endl
                    << "Enter 'next player' to forfeit move, 'super1'/'super2' for super move."<<endl
                    << "==> ";
                if (input(player, Odisk, Xdisk, NoValidMove, NoValidMove2) == 'M') // Function to let player input coordinate is called.
                {
                    return 'M'; // Return to Main Menu.
                }
                player ++;
            }
            else if (player == 1) // Set by default, player 1 will have X discs.
            {
                cout<< "X player input"<<endl
                    << "Enter 'next player' to forfeit move, 'super1'/'super2' for super move."<<endl
                    << "==> ";
                if (input(player, Odisk, Xdisk, NoValidMove, NoValidMove2) == 'M') // Function to let player input coordinate.
                {
                    return 'M'; // Return to Main Menu.
                }
                player --;
            }
            score(Odisk, Xdisk); // Function used to calculate the player score is called after placing a disc.
        }
        else
        {
            NoValidMove = 1; // Set the value of NoValidMove to 1, means no valid move for current player.
            if ((Odisk + Xdisk == 64  && (Ochance1 == 0 && Ochance2 == 0 && Xchance1 == 0 && Xchance2 == 0)) ||
                (Odisk == 0 && (Ochance1 == 0 && Ochance2 == 0 && Xchance1 == 0 && Xchance2 == 0)) ||
                (Xdisk == 0 && (Ochance1 == 0 && Ochance2 == 0 && Xchance1 == 0 && Xchance2 == 0)))
            {
                cout << "No more move for both side!"<<endl;
                break;
            }
            if (player == 0)
            {
                cout << "No more move for Player O!"<<endl
                     << "Enter 'next player' to proceed to next player"<<endl
                     << "or use Super Power if haven't used."<<endl
                     << "==> "; // If there is no valid move, inform the player type next player
                if (input(player, Odisk, Xdisk, NoValidMove, NoValidMove2) == 'M') // Function used to let user enter next player is called.
                {
                    return 'M'; // Return to Main Menu.
                }
                player ++;
            }
            else if (player == 1)
            {
                cout << "No more move for Player X! Proceed to next player..."<<endl
                     << "Enter 'next player' to proceed to next player"<<endl
                     << "or use Super Power if haven't used."<<endl
                     << "==> "; // If there is no valid move, inform the player type next player
                if (input(player, Odisk, Xdisk, NoValidMove, NoValidMove2) == 'M') // Function used to let user enter next player is called.
                {
                    return 'M'; // Return to Main Menu.
                }
                player --;
            }
            if (validMove(player) == -1 && NoValidMove == 1) // If there is also no valid move for next player,
            {                                                // set the value of NoValidMove2 to 1, means that the next player also
                NoValidMove2 = 1;                            // did not has a valid move then break the loop to calculate win condition.
                break;
            }
        }
    }while (Odisk + Xdisk != -1); // Loop condition to become -1 to create infinite loop.

cout <<endl << "Press any key to view the result..."<<endl;
getch();

if (Odisk + Xdisk == 64 || Odisk == 0 || Xdisk == 0 || NoValidMove2 == 1) // If else structure to calculate win condition.
{
    if (Odisk > Xdisk)
    {
        cout <<endl <<endl << "O player win!"<<endl <<endl;
    }
    else if (Xdisk > Odisk)
    {
        cout <<endl <<endl << "X player win!"<<endl <<endl;
    }
    else if (Odisk = Xdisk)
    {
        cout <<endl <<endl << "Tie."<<endl <<endl;
    }
}
// After calculating the win condition, ask the players whether to play again or quit.
char repeatplay;
do
{
cout << "Do you want to play again?(y/n) only."<<endl
     << "==> ";
cin >> repeatplay;
cin.ignore(1000, '\n');
if (repeatplay == 'y' || repeatplay == 'Y')
{
    system("CLS");
    ReadGame = 0;
    Ochance1 = 1; Xchance1 = 1; Ochance2 = 1; Xchance2 = 1;
    return game(ReadGame);
}
else if (repeatplay == 'n' || repeatplay == 'N')
{
    return 'M'; // Return to Main Menu.
}
}while (repeatplay != 'y' || repeatplay != 'y' || repeatplay != 'n' || repeatplay != 'N');

}

char help() // Function used to display help menu.
{
    string helptomenu;
    cout<<"|OXOXOXOXOXOXOXOXOXOXOXOXOXOXOXOXO|"<<endl
        <<"|  Welcome to Super Othello Game  |"<<endl
        <<"|XOXOXOXOXOXOXOXOXOXOXOXOXOXOXOXOX|"<<endl<<endl
        <<"INSTRUCTION:"<<endl<<endl
        <<"1. The starting player is 'player O' and followed by 'player X'."<<endl
        <<"2. Each player need to enter a coordinate based on the number and"<<endl
        <<"   alphabet stated on the vertical-axis and horizontal-axis on"<<endl
        <<"   the board. For example: 'a 1'.(with spacing)"<<endl
        <<"3. Once the player input a coordinate, the board will display 'O'"<<endl
        <<"   or 'X' on the particular coordinate."<<endl
        <<"4. If the move is valid and legal, it will flips the relative opponent's"<<endl
        <<"   discs to become your discs."<<endl
        <<"5. If the current player does not want to input any coordinate, enter 'next "<<endl
        <<"   player' for proceeding to next player."<<endl
        <<"6. The score below the board will automatically increased by according to the"<<endl
        <<"   number of discs on the board when the player input a coordinate."<<endl
        <<"7. Press 'menu' in the input to go back to the main menu."<<endl
        <<"8. This game is included with two super power, enter 'super1' or 'super2'"<<endl
        <<"   if you want to use them.(Note: You can only use one of the super power"<<endl
        <<"   each time and each of the super power can be only used 1 time! Be smart"<<endl
        <<"   when you want to use them."<<endl
        <<"9. Once the game board is fully filled with discs or there is no more moves"<<endl
        <<"   for either player, win condition will be determined."<<endl
        <<"10.Enter 'save <space> <file name>' at input if you want to save the game."<<endl
        <<"11.If you want to load the game you saved, select option 2 and enter the file"<<endl
        <<"   name you saved."<<endl
        <<endl<<"Please enter 'menu' to go back: ";
    getline(cin, helptomenu, '\n');
    if (helptomenu == "menu")
    {
        return 'M'; // Return to Main Menu.
    }
    while (helptomenu != "menu")
    {
        cout<<"Invalid command, please enter 'menu' again: ";
        getline(cin, helptomenu, '\n');
            if (helptomenu == "menu")
            {
                return 'M'; // Return to Main Menu.
            }
    }
}
