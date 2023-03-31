// #include "main.h"
// #include <time.h>
// #include <iostream>
// #include "draw.cpp"
// #include <iomanip>
// #include <conio.h>

void displayGameUI(GameState game)
{
    drawCell(" ", 0, 0, 35, 73);
    drawCell(" ", 0, 73, 35, WinColumn - 73);
    drawCell(" ", 35, 0, 5, WinColumn);

    GoTo(1, (WinColumn + 68) / 2);
    cout << "Level 1";

    GoTo(5, 75);
    cout << "Score: ";

    GoTo(6, 75);
    cout << "Move suggestion count: ";
    
    GoTo(7, 75);
    cout << "Board shuffling count: ";

    GoTo(10, 75);
    cout << "Press ";
    drawCell("W", 9, 75 + 6, 3, 5);
    drawCell("A", 9, 75 + 6 + 5, 3, 5);
    drawCell("S", 9, 75 + 6 + 10, 3, 5);
    drawCell("D", 9, 75 + 6 + 15, 3, 5);
    GoTo(10, 75 + 6 + 15 + 5);
    cout << " to move!";

    GoTo(13, 75);
    cout << "Press ";
    drawCell("Space", 12, 75 + 6, 3, 20);
    GoTo(13, 75 + 6 + 20);
    cout << " to select!"; 

    GoTo(16, 75);
    cout << "Press ";
    drawCell("H", 15, 75 + 6, 3, 5);
    GoTo(16, 75 + 6 + 5);
    cout << " for move suggestion!";

    GoTo(19, 75);
    cout << "Press ";
    drawCell("R", 18, 75 + 6, 3, 5);
    GoTo(19, 75 + 6 + 5);
    cout << " to shuffle the board!";

    GoTo(22, 75);
    cout << "Press ";
    drawCell("P", 21, 75 + 6, 3, 5);
    GoTo(22, 75 + 6 + 5);
    cout << " to save current game!";

    GoTo(25, 75);
    cout << "Press ";
    drawCell("Esc", 24, 75 + 6, 3, 7);
    GoTo(25, 75 + 6 + 7);
    cout << " to return to Menu!";


    GoTo(37, 3);
    cout << "Time left: ";
    for (int i = 1; i <= WinColumn - 20; i++)
    {
        char c = 223;
        cout << c;
    }
}

void updateTime(GameState game, int &time_left, int start_time)
{

    time_t current_time = time(0);
    time_left = (int)game.total_time - (difftime(current_time, start_time));
    
    if (time_left < game.total_time)
    {
        GoTo(37, int(time_left/game.total_time * (WinColumn - 20)) + 14);
        for (int i = 0; i < (WinColumn - 20) / game.total_time; i++)
            cout << " ";
    }
}

// int main()
// {
//     GameState game;
//     ShowConsoleCursor(false);
//     displayGameUI(game);
//     time_t start_time = time(0);
//     int timeleft = 10;
//     game.difficulty = 3;
//     while (timeleft > 0)
//     {
//         updateTime(game, timeleft, start_time);
//     }


//     return 0;

// }
