#include "menu.h"

void drawCell(string text, int x, int y, int cellSizeRow, int cellSizeColumn, int bg_color, int text_color)
{
    // Create a separate wcout stream object
    //std::wostream& wcout = std::wcout;

    // Set the output mode to Unicode for the wcout object
    _setmode(_fileno(stdout), _O_U16TEXT);

    for (int i = 0; i < cellSizeRow; i++)
    {
        GoTo(x+i, y);
        for (int j = 0; j < cellSizeColumn; j++)
        {
            SetColor (text_color, bg_color);
            if (i == 0 && j == 0) 
                wcout << L"\u250C";
            else if (i == 0 && j == cellSizeColumn - 1)
                wcout << L"\u2510";
            else if (i == cellSizeRow - 1 && j == 0)
                wcout << L"\u2514";
            else if (i == cellSizeRow - 1 && j == cellSizeColumn - 1)
                wcout << L"\u2518";
            else if (i == 0 || i == cellSizeRow-1)
                wcout << L"\u2500";
            else if (j == 0 || j == cellSizeColumn-1) 
                wcout << L"\u2502";
            else
            {
                SetColor(bg_color, text_color);
                wcout << " ";
            }
        }
    }
    SetColor(0, 7);
    // Set the output mode back to ASCII for stdout
    _setmode(_fileno(stdout), _O_TEXT);

    GoTo(x + cellSizeRow / 2 , y + (cellSizeColumn - text.length()) / 2);
    SetColor(bg_color, text_color);
    cout << text;
    SetColor(0, 7);
}

void displayMenu(int menu_page, int choice)
{
    clear();
    string gname = "Pokemon Puzzle!";

    vector<string> options;
    options.push_back("START");
    options.push_back("LEADERBOARD");
    options.push_back("QUIT");
    
    vector<string> difficulty;
    difficulty.push_back("EASY");
    difficulty.push_back("MEDIUM");
    difficulty.push_back("HARD");
    difficulty.push_back("CUSTOM");

    int cellRowSize = 3;
    int cellColumnSize = 15;

    GoTo(0, (WinColumn - gname.length()) / 2);
    cout << gname;

    int posX = 2, posY = (WinColumn - cellColumnSize) / 2;
    if (menu_page == 1)
        for (int i = 0; i < options.size(); i++)
        {
            if (choice - 1 == i)
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
    else if (menu_page == 2)
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
}

void generateMenu(int &menu_page, int &choice)
{
    displayMenu(menu_page, choice);
    char input = getch();
    input = toupper(input);

    if (menu_page == 1)
    {
        cout << input;
        switch(input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 3)
                    choice ++;
                break;
            case ' ':
                if (choice == 1)
                    menu_page = 2;
                else if (choice == 2)
                    menu_page = 4;
                else
                    menu_page = 0;
                choice = 1;
                break;
        }
    }
    else if (menu_page == 2)
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
                menu_page = choice;
                break;
        }
    }
    else 
    {
        cout << "Error!";
    }
}


int main()
{
    SetWindowSize(120, 30);
    clear();
    int menu_page = 1, choice = 1;
    while (menu_page <= 4 && choice <= 4)
    {
        generateMenu(menu_page, choice);
        if (menu_page == 0)
            break;
    }

    return 0;
}