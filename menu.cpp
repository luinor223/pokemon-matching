#include "menu.h"
/*
Page 1 = Start / Leaderboard / Credit / Quit
Page 2 = Difficulty choice
Page 3 = Custom board page
Page 4 = Show leaderboard
Page 5 = Show game credit
Page 6 = Gameplay
*/

void displayMenu(GameState &game, int page, int choice, char** title, int title_row, int title_col)
{
    vector<string> options;
    options.push_back("START");
    options.push_back("LEADERBOARD");
    options.push_back("CREDIT");
    options.push_back("QUIT");
    
    
    vector<string> difficulty;
    difficulty.push_back("EASY");
    difficulty.push_back("MEDIUM");
    difficulty.push_back("HARD");
    difficulty.push_back("CUSTOM");

    int cellRowSize = 3;
    int cellColumnSize = 15;

    //GoTo(0, (WinColumn - 67) / 2);
    for (int i = 0; i < title_row; i++)
    {
        GoTo(i, (WinColumn - 67) / 2);
        for (int j = 0; j < title_col; j++)
        {
            if (title[i][j] == '#')
                SetColor(0, 6);
            else
                SetColor(0, 1);
            cout << title[i][j];
        }
    }
    SetColor();

    int posX = title_row + 2, posY = (WinColumn - cellColumnSize) / 2;

    if (page == 1)
    {
        for (int i = 0; i < options.size(); i++)
        {
            if (choice == i + 1)
            {
                drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, yellow, black);
                posX += cellRowSize;
            }
            else
            {
                drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, white, black);
                posX += cellRowSize;
            }
            
        }
    }
    else if (page == 2)
    {
        for (int i = 0; i < difficulty.size(); i++)
        {
            if (choice - 1 == i)
            {
                drawCell(difficulty[i], posX, posY, cellRowSize, cellColumnSize, yellow, black);
                posX += cellRowSize;
            }
            else
            {
                drawCell(difficulty[i], posX, posY, cellRowSize, cellColumnSize, white, black);
                posX += cellRowSize;
            }
            
        }
    }
    else if (page == 3) //Custom board page
    {
        string title1 = "Custom";
        GoTo (2, (WinColumn - title1.length()) / 2);
        cout << title1;
    
        GoTo(3, (WinColumn - 34)/2);
        cout << "Select the number of rows: \t\t";
        if (choice == 1)
            SetColor(0, 6);
        cout << "< ";
        cout << game.row;
        cout << " >";
        SetColor(0, 7);//Set Color back to default

        GoTo(4, (WinColumn - 34)/2);
        cout << "Select the number of column: \t";
        if (choice == 2)
            SetColor(0, 6);
        cout << "< ";
        cout << game.col;
        cout << " >";

        SetColor(0, 7); //Set Color back to default
    }
    else if (page == 5)  //Credit
    {
        GoTo(2, (WinColumn - 6) / 2);
        cout << "Custom";

        GoTo(3, (WinColumn - 36) / 2);
        cout << "22127258 - Le Tri Man - 22CLC10 - HCMUS";
        
        GoTo(4, (WinColumn - 36) / 2);
        cout << "22127452 - Le Ngoc Vi - 22CLC10 - HCMUS";
    } 
}

void generateMenu(GameState &game, int &page, int &choice, char** title, int title_row, int title_col, bool &run)
{
    displayMenu(game, page, choice, title, title_row, title_col);

    char input = getch();
    input = toupper(input);

    if (page == 1) //Page 1 = Start / Leaderboard / Credit / Quit
    {
        switch(input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 4)
                    choice ++;
                break;
            case ' ':
                if (choice == 1) //Start
                {
                    clear();
                    page = 2;
                }
                else if (choice == 2) //Leaderboard
                {   
                    clear();
                    page = 4;
                }
                else if (choice == 3) //Credit
                {
                    clear();
                    page = 5;
                }
                else    //Quit
                {
                    run = false;
                    page = 0;
                }
                break;
        }
    }
    else if (page == 2) //Page 2 = Difficulty choice
    {
        switch (input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 4)
                    choice ++;
                break;
            case ' ':
                if (choice <= 3) //1:Easy  2:Medium  3:Hard 
                {
                    game.difficulty = choice;
                    page = 6;
                }
                else //Custom Mode
                {
                    page = 3; //Go to custom board page
                    choice = 1;
                    game.difficulty = 4;
                }
                break;
            case 27:
                page = 1;
                break;
        }
    }
    else if (page == 3) //Page 3 = Custom board
    {
        switch(input)
        {
            case 'W':
                if (choice > 1)
                    choice--;
                break;
            case 'S':
                if (choice < 2)
                    choice ++;
                break;
            case 'A':
                if (game.row > 4)
                    game.row -= (choice == 1);
                if (game.col > 4)
                    game.col -= (choice == 2);
                break;
            case 'D':
                if (game.row < 8)
                    game.row += (choice == 1);
                if (game.col < 10)
                    game.col += (choice == 2);
                break;
            case ' ':
                if (game.row * game.col % 2 == 0)
                    page = 6;
                else
                {
                    GoTo(5, (WinColumn - 34)/2);
                    cout <<"Board size must be even!"; 
                    std::this_thread::sleep_for(800ms);
                }
                break;
            case 27:
                page = 1;
                break;
        }
    }
    else if (page == 4)
    {
        if (input == 27)
            page = 1;
    }
    else if (page == 5)
    {
        if (input == 27)
            page = 1;
    }
    else 
    {
        if (input == 27)
            page = 1;
    }
}

void displayLeaderBoard()
{

}