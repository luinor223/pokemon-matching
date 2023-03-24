#pragma once
#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
#include <queue>

#define MAX 12

using namespace std;


bool** occupied;
bool isSelected[MAX][MAX];
int row, col;
int WinColumn = 120;
int WinRow = 60;

int white = 7;
int black = 0;
int yellow = 6;

struct Point{
    int x, y;
};

Point cur{0, 0};
int Max_NumofSelectedPoint = 2;
vector <Point> selectedPoint;