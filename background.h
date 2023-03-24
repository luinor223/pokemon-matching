#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

void getFileContent(char **&background, int &m, int &n, int cellSize);
void deleteBg(int m, int n, char **&background);
void printBg(char** background, int bg_row, int bg_column);