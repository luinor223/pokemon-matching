#include "console.h"

void GoTo(SHORT posY, SHORT posX)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

	SetConsoleCursorPosition(hStdout, Position);
}

void SetWindowSize(SHORT width, SHORT height)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    SMALL_RECT WindowSize;
    WindowSize.Top = 0;
    WindowSize.Left = 0;
    WindowSize.Right = width;
    WindowSize.Bottom = height;
 
    SetConsoleWindowInfo(hStdout, 1, &WindowSize);
}

void SetColor(int backgound_color = 0, int text_color = 7)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

// 0 = Black   8 = Gray   
// 1 = Blue    9 = Light Blue  
// 2 = Green   10 = Light Green   
// 3 = Aqua    11 = Light Aqua   
// 4 = Red     12 = Light Red   
// 5 = Purple   13 = Light Purple  
// 6 = Yellow     14 = Light Yellow
// 7 = White     15 = Bright White
void clear()
{
	system("cls");
}





