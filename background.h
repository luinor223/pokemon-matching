#pragma once
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>

using namespace std;

void getFileContent(char **&background, int &m, int &n);
void deleteBg(int m, int n, char **&background);