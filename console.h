#pragma once
#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

void GoTo(SHORT posY, SHORT posX);
void SetWindowSize(SHORT width, SHORT height);


// 0 = Black   8 = Gray   
// 1 = Blue    9 = Light Blue  
// 2 = Green   10 = Light Green   
// 3 = Aqua    11 = Light Aqua   
// 4 = Red     12 = Light Red   
// 5 = Purple   13 = Light Purple  
// 6 = Yellow     14 = Light Yellow
// 7 = White     15 = Bright White
void SetColor(int backgound_color, int text_color);

void clear();