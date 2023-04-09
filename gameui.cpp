#include "gameui.h"

void displayGameUI(GameState game)
{
    drawCell(" ", 0, 0, gameboxrow, gameboxcol);
    drawCell(" ", 0, gameboxcol, infoboxrow, infoboxcol);
    drawCell(" ", gameboxrow, 0, timeboxrow, timeboxcol);

    GoTo(1, (WinColumn + gameboxcol - 7) / 2);
    cout << "Stage " << game.stage;

    GoTo(5, gameboxcol + 2);
    cout << "Score: ";

    GoTo(6, gameboxcol + 2);
    cout << "Move suggestion count: ";
    
    GoTo(7, gameboxcol + 2);
    cout << "Board shuffling count: ";

    GoTo(10, gameboxcol + 2);
    cout << "Press ";
    drawCell("W", 9, gameboxcol + 2 + sizeof("Press"), 3, 5);
    drawCell("A", 9, gameboxcol + 2 + sizeof("Press") + 5, 3, 5);
    drawCell("S", 9, gameboxcol + 2 + sizeof("Press") + 10, 3, 5);
    drawCell("D", 9, gameboxcol + 2 + sizeof("Press") + 15, 3, 5);
    GoTo(10, gameboxcol + 2 + 6 + 15 + 5);
    cout << " to move!";

    GoTo(13, gameboxcol + 2);
    cout << "Press ";
    drawCell("Space", 12, gameboxcol + 2 + sizeof("Press"), 3, 20); //20: Space bar box size
    GoTo(13, gameboxcol + 2 + sizeof("Press") + 20); ////20: Space bar box size
    cout << " to select!"; 

    GoTo(16, gameboxcol + 2);
    cout << "Press ";
    drawCell("H", 15, gameboxcol + 2 + sizeof("Press"), 3, 5);
    GoTo(16, gameboxcol + 2 + sizeof("Press") + 5);
    cout << " for move suggestion!";

    GoTo(19, gameboxcol + 2);
    cout << "Press ";
    drawCell("R", 18, gameboxcol + 2 + sizeof("Press"), 3, 5);
    GoTo(19, gameboxcol + 2 + sizeof("Press") + 5);
    cout << " to shuffle the board!";

    GoTo(22, gameboxcol + 2);
    cout << "Press ";
    drawCell("P", 21, gameboxcol + 2 + sizeof("Press"), 3, 5);
    GoTo(22, gameboxcol + 2 + sizeof("Press") + 5);
    cout << " to save current game!";

    GoTo(25, gameboxcol + 2);
    cout << "Press ";
    drawCell("Esc", 24, gameboxcol + 2 + sizeof("Press"), 3, 7);
    GoTo(25, gameboxcol + 2 + sizeof("Press") + 7);
    cout << " to return to Menu!";


    GoTo(gameboxrow + 1, 3);
    cout << "Time left: ";
    GoTo(gameboxrow + 2, 14);
    for (int i = 1; i <= WinColumn - 20; i++)
    {
        char c = 223;
        cout << c;
    }
}

void updateUI(GameState &game, int start_time)
{
    GoTo(5, WinColumn - 37);
    cout << game.score;

    GoTo(6, WinColumn - 22);
    cout << game.help_count;
    
    GoTo(7, WinColumn - 22);
    cout << game.shuffle_count;

    time_t current_time = time(0);
    game.time_left = (int)game.total_time - (difftime(current_time, start_time));

    GoTo(WinRow - 3, 3);
    cout << game.time_left << "s";
    
    if (game.time_left < game.total_time)
    {
        GoTo(WinRow - 3, int(game.time_left/game.total_time * (WinColumn - 20)) + 14);
        for (int i = 0; i < (WinColumn - 20) / game.total_time; i++)
            cout << " ";
    }
}

void GameOver(GameState game)
{
    game.score = 0;
    game.mode = 1;
    game.stage = 1;
    game.help_count = 3;
    game.shuffle_count = 3;
    drawCell(" ", (WinRow - 6) / 2, (WinColumn - 40) / 2, 6, 40);
    GoTo((WinRow - 2)/2, (WinColumn - 34)/2);
    cout << "Time's up! Your total score is " << game.score;
    GoTo((WinRow - 2)/2 + 1, (WinColumn - 34)/2);
    cout << "Press any key to return to menu...";
    getch();
    clear();
}

void updateScore(GameState &game, savefile &account, PlayerInfo players[])
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

    if (game.score > account.record[4].points)
    {
        GoTo(5, WinColumn - 31);
        cout << "New High Score!";

        account.record[4].points = game.score;
        time_t now = time(0);
        tm *ltm = localtime(&now);
        account.record[4].date.day = ltm->tm_mday;
        account.record[4].date.month = ltm->tm_mon + 1;
        account.record[4].date.year = ltm->tm_year + 1900;

        sortRecord(account.record, 5);
        if (account.getElo() > players[9].elo)
        {
            if (checkNameOnLB(account, players))
                sortLB;
            else
            {
                players[9].elo = account.getElo();
                sortLB;
            }
        }
    }
}

bool checkNameOnLB(savefile account, PlayerInfo players[])
{
    for (int i = 0; i < 10; i++)
        if (players[i].name == account.name)
            return true;

    return false;
}

