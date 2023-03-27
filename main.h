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

#define MAX 12
#define PADDING 500 // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100

using namespace std;

bool isSelected[MAX][MAX];
int row, col;
int WinColumn = 120;
int WinRow = 60;

const int white = 7;
const int black = 0;
const int yellow = 6;

struct Point{
    int x, y;
};

Point cur{0, 0};
int Max_NumofSelectedPoint = 2;
vector <Point> selectedPoint;

struct State{ //Representing a board state
    int row = 4;
    int column = 6; // Size of the board game
    int cur_x = 1;
    int cur_y = 1; // Current cursor position
    char board[100] = {0}; // Current board state
// 500 byte NULL
};

struct savefile{
    //char mask; // You are required to transfer all char-type variables by performing xor each with the mask-variable, bit-by-bit.
    char name[20]; // username
    char password[20]; // password
    // 500 byte NULL
    int recEasy[5] = {0, 0, 0, 0, 0}; // List of sorted best records
    int recMedium[5] = {0, 0, 0, 0, 0};
    int recHard[5] = {0, 0, 0, 0, 0};
    State state; // List of save state
};