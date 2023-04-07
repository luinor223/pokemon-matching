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
    cout << "Stage " << game.stage;

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

void updateUI(GameState game, int start_time)
{
    GoTo(5, 82);
    cout << game.score;

    GoTo(6, 98);
    cout << game.help_count;
    
    GoTo(7, 98);
    cout << game.shuffle_count;

    time_t current_time = time(0);
    game.time_left = (int)game.total_time - (difftime(current_time, start_time));
    
    if (game.time_left < game.total_time)
    {
        GoTo(37, int(game.time_left/game.total_time * (WinColumn - 20)) + 14);
        for (int i = 0; i < (WinColumn - 20) / game.total_time; i++)
            cout << " ";
    }
}

void displayGameOver(GameState game)
{
    drawCell(" ", (WinRow - 6) / 2, (WinColumn - 40) / 2, 6, 40);
    GoTo((WinRow - 2)/2, (WinColumn - 34)/2);
    cout << "Time's up! Your total score is " << game.score;
    GoTo((WinRow - 2)/2 + 1, (WinColumn - 34)/2);
    cout << "Press any key to return to menu...";
    getch();
}

void updateScore(GameState &game, savefile &account)
{
    switch(game.difficulty)
    {
        case 1:
            game.score += 10;
            break;
        case 2:
            game.score += 15;
            break;
        case 3:
            game.score += 20;
            break;
        default:
            game.score += 10;
            break;
    }
    
    if (game.score > account.record[5].points)
    {
        GoTo(5, 90);
        cout << "New High Score!";
        account.record[5].points = game.score;
        sortRecord(account.record, 5);
    }
    
}

