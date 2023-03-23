#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
#include <queue>

#include "board.cpp"
#include "console.cpp"
#include "background.cpp"

#define SIZE 12

using namespace std;


bool** occupied;
bool isSelected[SIZE][SIZE];
int row, col;

struct Point{
    int x, y;
};

Point cur{0, 0};
int Max_NumofSelectedPoint = 2;
vector <Point> selectedPoint;