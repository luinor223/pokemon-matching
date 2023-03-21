#include <iostream>
#include <ctime>
#include <stdio.h>
#include <vector>
#include <math.h>
#include <stack>

#define MAX 100

void make_board(char board[][MAX], int& m, int& n);
void showBoard(char a[][MAX], int m, int n, int cellSize, char cellRowChar, char cellColumnChar, char** background, int mb, int nb);
