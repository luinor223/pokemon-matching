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
#include <windows.h>
#include <mmsystem.h>

#define MAX 12
#define PADDING 500 // bytes
#define NAMESIZE 50
#define PASSSIZE 50
#define BOARDSIZE 999
#define URLSIZE 100
#define MAXPLAYERS 10

using namespace std;

const int WinColumn = 130;
const int WinRow = 45;

const int gameboxrow = WinRow - 5;
const int gameboxcol = WinColumn - 47;
const int infoboxrow = gameboxrow;
const int infoboxcol = 47;
const int timeboxrow = 5;
const int timeboxcol = WinColumn;

const int Max_NumofSelectedPoint = 2;

const int black = 0;
const int white = 15;
const int yellow = 6;
const int grey = 8;

const string Cheat_page = "H4CK";
const string Cheat_shuffle = "s4uffle";
const string Cheat_help = "call911";
const string Cheat_score = "easygame";
const string Cheat_time = "bounstime";

const int bouns_time = 60;

const int main_page = 1;
const int diff_page = 2;
const int custom_page = 3;
const int load_page = 4;
const int account_page = 5;
const int hack_page = 6;
const int ldboard_page = 7;
const int credit_page = 8;
const int gameplay_page = 9;
const int save_page = 10;

struct Point{
    int x, y;
};

Point cur{0, 0};
vector <Point> selectedPoint;

struct GameState{
    char** board = nullptr;
    int row = 4;
    int col = 6;
    Point cur {0, 0};
    int move_count = 0;
    int difficulty = 0; //0:Custom, 1: Easy,  2: Medium,  3: Hard
    int cellSize = 5;
    double total_time = 0;
    int mode = 1; //1: Normal, 2: Shift left, 3: Shift right, 4: Shift up, 5: Shift down
    int stage = 1;
    int score = 0;
    int time_left = 120;
    int help_count = 3;
    int shuffle_count = 3;
};

struct SaveState{ //Representing a board state
    int row = 0, col = 0; // Size of the board game
    int cur_x = 0, cur_y = 0; // Current cursor position
    char board[BOARDSIZE] = {0}; // Current board state
    char file_background[URLSIZE] = {0}; // Link to background file. This variable’s value is NULL if there is no current background
    // Extra variables
    int time_left = 120;
    int score = 0;
    int difficulty = 0;
    int mode = 1;
    int stage = 1;
    int help_count = 3;
    int shuffle_count = 3;
    //500 - (sizeof(int)) * 7 = 472
    char null_bytes[PADDING - sizeof(int)*7] = {0};
};

struct Date{
    int day = 1;
    int month = 1; 
    int year = 2023;
};


struct Record{
    Date date; // Date of completed record (12 bytes)
    int points = 0; // points achieved (4 bytes)
    // 500 byte NULL
    char null_bytes[500] = {0};
};


struct savefile{
    char mask = 'Q'; // You are required to transfer all char-type variables by performing xor each withthe mask-variable, bit-by-bit.
    char name[NAMESIZE] = {0}; // username
    char password[PASSSIZE] = {0}; // password

    //Extra variables
    int position = 0;

    // 500 - 4 byte NULL
    char null_bytes[PADDING - 4] = {0};
    ///////////////////////////

    Record record[5]; // List of sorted best records
    SaveState state[5] = {{0, 0, 0}, 0, 0}; // List of save state

    int getElo(){
        int avg = 0, count = 0;
        for (int i = 0; i < 5; i++)
            if(record[i].points > 0)
            {
                avg += record[i].points;
                count++;
            }
        if (count > 0)
            avg/=count;

        return avg;
    }
}; 

struct PlayerInfo {
    string name = "";
    int elo = 0;
    string rank = "";

    string getRank(){
        if (elo <= 1600)
            return "Bronze";
        else if (elo <= 3200)
            return "Silver";
        else if (elo <= 4800)
            return "Gold";
        else if (elo <= 6000)
            return "Platinum";
        else if (elo <= 7600)
            return "Master";
        return "Challenger";
    }

    
};