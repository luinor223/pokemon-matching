#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

void GoTo(SHORT posY, SHORT posX);
void SetWindowSize(SHORT width, SHORT height);
void SetColor(int backgound_color, int text_color);

void clear();