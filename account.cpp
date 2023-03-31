#include "account.h"

void processReg(savefile &player, bool &isLogged)
{
    fstream file("account.bin", ios::binary | ios::in | ios::out); // open file in read and write mode

    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        return;
    }

    bool isExist = false;
    savefile tempPlayer;
    //cout << tempPlayer.name << " " << tempPlayer.password << endl;
    while (file.read((char*)&tempPlayer, sizeof(tempPlayer))) // read data from file
    {
        if (strcmp(tempPlayer.name, player.name) == 0) // check if username already exists
        {
            isExist = true;
            cout << "Username already exists. Press any key to go back...";
            getch();
            break;
        }
    }

    if (!isExist) // if username does not exist, write player data to file
    {
        file.clear();
        file.seekp(0, ios::end);
        file.write((char*)&player, sizeof(player));
        cout << "Registration successful! Press any key to continue...";
        getch();
        isLogged = true;
    }

    file.close(); // close file
}

void processLogin(savefile player, bool &isLogged)
{
    ifstream file("account.bin", ios::binary);
    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        return;
    }

    savefile tempPlayer;
    while (file.read((char*)&tempPlayer, sizeof(tempPlayer))) // read data from file
    {
        if (strcmp(tempPlayer.password, player.password) == 0) // check if username exists
        {
            if (strcmp(tempPlayer.password, player.password) == 0) //check if password matches
            {
                cout << "Login successful! Press any key to continue...";
                getch();
                isLogged = true;
                break;
            }
            else
            {
                break;
            }
        }
    }

    if(isLogged == false)
    {
        cout << "Username or Password is not correct! Press any key to go back.";
        getch();
    }
    
    file.close();  
}

void displayForm(savefile player,int choice, bool &isLogged)
{
    clear();
    string title = "";
    if (choice == 1)
        title = "LOG IN";
    else
        title = "REGISTER";
    int box_size = 20;

    GoTo(0, (WinColumn - title.length()) / 2);
    cout << title;
    
    GoTo(4, (WinColumn - 10 - box_size) / 2);
    cout << "Username: ";
    drawCell(" ", 3, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);

    GoTo(7, (WinColumn - 10 - box_size) / 2);
    cout << "Password: ";
    drawCell(" ", 6, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);

    GoTo(4, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(player.name, 20);

    GoTo(7, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(player.password, 20);

    GoTo(9, (WinColumn - 50 - box_size) / 2 + 12);

    if (choice == 1)
        processLogin(player, isLogged);
    else
        processReg(player, isLogged);
}

void displayLoginRegisterMenu(savefile &player)
{
    string title = "POKEMON PUZZLE!";
    string username;

    int cellRowSize = 3;
    int cellColumnSize = 15;

    vector<string> options;
    options.push_back("LOG IN");
    options.push_back("REGISTER");
    options.push_back("QUIT");

    int choice = 1;
    bool isLogged = false;
    bool displayMenu = true;
    
    while (!isLogged)
    {
        if (displayMenu)
        {
            clear();
            GoTo(0, (WinColumn - title.length()) / 2);
            cout << title;

            int posX = 2, posY = (WinColumn - cellColumnSize) / 2;
            for (int i = 0; i < options.size(); i++)
            {
                if (choice == i + 1)
                {
                    drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, yellow, black);
                    posX += 4;
                }
                else
                {
                    drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, white, black);
                    posX += 4;
                }
            }
            char input = getch();
            input = toupper(input);
            switch(input)
            {
                case 'W':
                    if (choice > 1 )
                        choice --;
                    break;
                case 'S':
                    if (choice < options.size())
                        choice ++;
                    break;
                case ' ':
                    if (choice == 1 || choice == 2)
                    {
                        displayForm(player, choice, isLogged);
                    }
                    else
                    {
                        //HOW QUIT CONSOLE?
                    }
                    break;
            }
        }
    }
}

void saveGame(savefile player, char** board);


// int main()
// {
//     SetWindowSize(120, 30);
//     // clear();
//     // int page = 1, choice = 1;
//     // while (page <= 4 && choice <= 4)
//     // {
//     //     generateMenu(page, choice);
//     //     if (page == 0)
//     //         break;
//     // }
//     savefile player;
//     displayLoginRegisterMenu(player);

//     return 0;
// }