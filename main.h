#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
#include <queue>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <io.h>
#include <ctime>

#define MAX 12
#define PADDING 500 // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

using namespace std;

const int WinColumn = 120;
const int WinRow = 40;

const int white = 7;
const int black = 0;
const int yellow = 6;

struct GameState{
    char** board = nullptr;
    int row = 4;
    int col = 6;
    int difficulty = 0; //1: Easy,  2: Medium,  3: Hard
    int cellSize = 5;
    double total_time = 0;
    int mode = 1;
    int stage = 1;
};

struct PlayerState {
    int score = 0;
    int time_left = 10;
    int help_count = 3;
    int shuffle_count =3;
};

struct Point{
    int x, y;
};

Point cur{0, 0};
int Max_NumofSelectedPoint = 2;
vector <Point> selectedPoint;

struct State{ //Representing a board state
    int row, col; // Size of the board game
    int cur_x, cur_y; // Current cursor position
    char board[BOARDSIZE] = {0}; // Current board state
    char file_background[URLSIZE] = {0}; // Link to background file. This variable’s value is NULL if there is no current background
    // Extra variables
    int time_left = 120;
    int score = 0;
    int difficulty = 0;
    int mode = 1;
    int stage = 1;
    //500 - (sizeof(int)) * 5 = 480
};

struct Date{
    int dd, mm, yy;
};


struct Record{
    Date date; // Date of completed record
    int points; // points achieved
    // 500 byte NULL
};


struct savefile{
    char mask; // You are required to transfer all char-type variables by performing xor each with the mask-variable, bit-by-bit.
    char name[20]; // username
    char password[20]; // password
    // 500 byte NULL
    int recEasy[5] = {0, 0, 0, 0, 0}; // List of sorted best records
    int recMedium[5] = {0, 0, 0, 0, 0};
    int recHard[5] = {0, 0, 0, 0, 0};
    State state; // List of save state
};