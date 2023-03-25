#include "menu.h"
#include "draw.cpp"

void displayMenu(int menu_page, int choice)
{
    clear();
    string gname = "Pokemon Puzzle!";

    vector<string> options;
    options.push_back("START");
    options.push_back("LEADERBOARD");
    options.push_back("QUIT");
    //options.push_back("CREDIT");
    
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