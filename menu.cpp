#include "menu.h"
/*
Page 1 = New Game / Load Game / Account / Leaderboard / Credit / Quit
Page 2 = Difficulty choice
Page 3 = Custom board page
Page 4 = Load Game
Page 5 = Account
Page 6 = Show leaderboard
Page 7 = Show game credit
Page 8 = Gameplay
Page 9 = Save game
*/

void generateMenu(savefile &account, GameState &game, string filename, int &page, int &choice, char** title, int title_row, int title_col, bool &run, bool &hackMode, bool &continue_game)
{
    char input; 

    if (page == main_page) //Page 1 = Start / Leaderboard / Credit / Quit
    {
        displayGameTitle(title, title_row, title_col);
        displayMainMenu(choice);

        input = getch();
        input = toupper(input);
        switch(input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 6)
                    choice ++;
                break;
            case ' ':
                if (choice == 1) //New Game
                {
                    clear();
                    page = diff_page;
                    choice  = 1;
                }
                else if (choice == 2) //Load Game
                {   
                    clear();
                    page = load_page;
                    choice = 1;
                }
                else if (choice == 3) //Account info
                {
                    clear();
                    page = account_page;
                    choice  = 1;
                }
                else if (choice == 4) // LeaderBoard
                {
                    clear();
                    page = ldboard_page;
                    choice = 1;
                }
                else if (choice  == 5) //Credit
                {
                    clear();
                    page = credit_page;
                    choice = 1;
                }
                else    //Quit
                {
                    run = false;
                    saveGame(filename, account);
                    page = 0;
                }
                break;
        }
    }
    else if (page == diff_page) //Page 2 = Difficulty choice
    {
        displayGameTitle(title, title_row, title_col);
        displayDifficultyChoice(choice);

        input = getch();
        input = toupper(input);
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
                    page = gameplay_page;
                }
                else //Custom Mode
                {
                    page = custom_page; //Go to custom board page
                    choice = 1;
                    game.difficulty = 0;
                }
                break;
            case 27:
                page = 1;
                break;
        }
    }
    else if (page == custom_page) //Page 3 = Custom board
    {
        displayCustomBoardPage(game, choice);

        input = getch();
        input = toupper(input);
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
    else if (page == load_page)
    {
        displayLoadGamePage(account, choice);
        input = getch();
        input = toupper(input);
        switch(input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 5)
                    choice ++;
                break;
            case ' ':
                if (account.state[choice - 1].row != 0) //Start
                {
                    loadBoard(game, account, choice - 1);
                    page = gameplay_page;
                    continue_game = true;
                }
                break;
            case 27:
                page = 1;
                break;
        }
    }
    else if (page == account_page)
    {
        displayAccountInfo(account, choice, hackMode);
        input = getch();
        input = toupper(input);
        if (!hackMode)
            switch(input)
            {
                case 'A':
                    if (choice > 1)
                        choice --;
                    break;
                case 'D':
                    if (choice < 4)
                        choice ++;
                    break;
                case ' ':
                    if (choice == 1) //Change username
                    {
                        bool changed = false;
                        changeNameForm(account, filename, changed);
                        if (changed)
                            saveGame(filename, account);
                    }
                    else if (choice == 2) //Change Password
                    {   
                        bool changed = false;
                        changePasswordForm(account, changed);
                        if (changed)
                            saveGame(filename, account);
                    }
                    else if (choice == 3) //Hack Mode: ON
                    {
                        hackMode = true;
                    }
                    else    //Return to main menu
                        page = 1;
                    break;
            }
        else
        {
            input = getch();
            input = toupper(input);
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
                case 'A':
                    if (choice != 6 && account.record[choice - 1].points >= 10)
                        account.record[choice - 1].points -=10;
                    break;
                case 'D':
                    if (choice != 6 && account.record[choice - 1].points < INT_MAX)
                        account.record[choice - 1].points +=10;
                    break;
                case ' ':
                    if (choice == 6) //Save
                    {
                        sortRecord(account.record, 5);
                        saveGame(filename, account);
                        hackMode = false;
                    }
                    break;
            }
        }
    }
    else if (page == save_page)
    {
        displaySavePage(game, account, choice);

        input = getch();
        input = toupper(input);
        switch(input)
        {
            case 'W':
                if (choice > 1)
                    choice --;
                break;
            case 'S':
                if (choice < 5)
                    choice ++;
                break;
            case ' ':
                saveBoard(game, account, choice - 1); //Save board
                page = gameplay_page;
                continue_game = true;
                break;
            case 27:
                page = 1;  
                break;
        }
    }
    else 
        page = 1;
}

void displayGameTitle(char** title, int title_row, int title_col)
{
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
}

void displayMainMenu(int choice)
{
    vector<string> options;
    options.push_back("NEW GAME");
    options.push_back("LOAD GAME");
    options.push_back("ACCOUNT");
    options.push_back("LEADERBOARD");
    options.push_back("CREDIT");
    options.push_back("QUIT");

    int cellRowSize = 3;
    int cellColumnSize = 15;

    int posX = 15, posY = (WinColumn - cellColumnSize) / 2;


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

void displayDifficultyChoice(int choice)
{
    vector<string> difficulty;
    difficulty.push_back("EASY");
    difficulty.push_back("MEDIUM");
    difficulty.push_back("HARD");
    difficulty.push_back("CUSTOM");

    int cellRowSize = 3;
    int cellColumnSize = 15;

    int posX = 15, posY = (WinColumn - cellColumnSize) / 2;

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

void displayCustomBoardPage(GameState game, int choice)
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

    SetColor(); //Set Color back to default
}

void displayLoadGamePage(savefile account, int choice)
{
    int cellRowSize = 5;
    for (int i = 0; i < 5; i++)
    {
        string saved_inf;
        if (account.state[i].row != 0)
        {
            saved_inf = to_string(i+1) + ". Board: " + to_string(account.state[i].row) + "x" + to_string(account.state[i].col);
            saved_inf += ". Difficulty: " + to_string(account.state[i].difficulty) + ". Score: " + to_string(account.state[i].score);
        }
        else
        {
            saved_inf = to_string(i+1) + ". No saved game.";
        }
        
        if (choice == i + 1)
            drawCell(saved_inf, 7 + (cellRowSize+1)*i, (WinColumn - saved_inf.length())/2, cellRowSize, saved_inf.length() + 5, yellow, black);
        else
            drawCell(saved_inf, 7 + (cellRowSize+1)*i, (WinColumn - saved_inf.length())/2, cellRowSize, saved_inf.length() + 5, white, black);
    }
}

void displayAccountInfo(savefile account, int choice, bool hackMode)
{
    drawCell("Account Info", 5, 10, 3, 33);
    drawCell(" ", 8, 10, 15, 33);
    GoTo(9, 12);
    cout << "Username: " << account.name;
    GoTo(10, 12);
    cout << "Password: ";
    for (int i = 0; i < strlen(account.password); i++)
        cout << "*";

    drawCell("High Score", 5, 44, 3, 33);
    drawCell(" ", 8, 44, 15, 33);
    for (int i = 0; i < 5; i++)
    {
        GoTo(9 + 2*i, 46);
        cout << "1. Date: " << account.record[i].date.day << "/"<< account.record[i].date.month<< "/"<< account.record[i].date.year;
        GoTo(9 + 2*i+1, 46);
        cout << "Score: " << account.record[i].points;
    }

    drawCell("Summary", 5, 78, 3, 38);
    drawCell(" ", 8, 78, 15, 38);
    int avg = 0, count = 0;
    for (int i = 0; i < 5; i++)
    {
        if(account.record[i].points > 0)
        {
            avg += account.record[i].points;
            count++;
        }
    }
    if (count > 0)
        avg/=count;

    GoTo(10, 80);
    cout << "Your elo is: " << avg;

    GoTo(11, 80);
    cout << "Your current rank is: ";
    if (avg <= 1600)
        cout << "Bronze";
    else if (avg <= 3200)
        cout << "Silver";
    else if (avg <= 4800)
        cout << "Gold";
    else if (avg <= 6000)
        cout << "Platinum";
    else if (avg <= 7600)
        cout << "Master";
    else if (avg <= 9200)
        cout << "Challenger";

    if (!hackMode)
    {
        vector<string> options;
        options.push_back("Change Username");
        options.push_back("Change password");
        options.push_back("Don't choose here"); 
        options.push_back("Return");
        for (int i = 0; i < options.size(); i++)
        {
            if (choice == i + 1)
                drawCell(options[i], 25 ,(WinColumn - options.size()*22)/2 + i*22 + 1, 3, 22, yellow, black);
            else
                drawCell(options[i], 25 ,(WinColumn - options.size()*22)/2 + i*22 + 1, 3, 22, white, black);
        }
    }
    else
    {
        processHacking(account, choice);
    }
}

void changeNameForm(savefile &account, string filename, bool &changed)
{
    clear();
    string title = "Change Usernam";
    char temp_name[NAMESIZE];
    char temp_password[PASSSIZE];
    int box_size = 20;

    GoTo(0, (WinColumn - title.length()) / 2);
    cout << title;
    
    GoTo(4, (WinColumn - 10 - box_size) / 2);
    cout << "New username: ";
    drawCell(" ", 3, (WinColumn - 14 - box_size) / 2 + 14, 3, 20);

    GoTo(7, (WinColumn - 10 - box_size) / 2);
    cout << "Password: ";
    drawCell(" ", 6, (WinColumn - 14 - box_size) / 2 + 14, 3, 20);

    GoTo(4, (WinColumn - 14 - box_size) / 2 + 16);
    cin.getline(temp_name, 20);

    GoTo(7, (WinColumn - 14 - box_size) / 2 + 16);
    cin.getline(temp_password, 20);

    GoTo(9, (WinColumn - 50 - box_size) / 2 + 12);

    ifstream file(filename, ios::binary);
    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        return;
    }

    changed = true;
    savefile tempAccount;

    while (file.read((char*)&tempAccount, sizeof(tempAccount))) // read data from file
    {
        mask(tempAccount.name, tempAccount.mask);  //Unmask name
        if (strcmp(tempAccount.name, temp_name) == 0) // check if username already exists
        {
            changed = false;
            cout << "Username already exists. Press any key to go back...";
            getch();
            break;
        }
    }
    if (changed)
    {
        strcpy(account.name, temp_name);
        cout << "Changed username successfully. Press any key to go back...";
    }

    file.close();
}

void changePasswordForm(savefile &account, bool &changed)
{
    clear();
    string title = "Change Password";
    char old_password[PASSSIZE];
    char new_password[PASSSIZE];
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
    cin.getline(old_password, 20);

    GoTo(7, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(new_password, 20);

    GoTo(9, (WinColumn - 50 - box_size) / 2 + 12);
    if (strcmp(old_password, account.password) != 0)
    {
        cout << "You entered old password incorrectly! Press any key to go back...";
        getch();
        changed = false;   
    }
    else if (strcmp(new_password, account.password) == 0)
    {
        cout << "Your new password can't be the same as old passowrd...";
        getch();
        changed = false;
    }
    else
    {  
        strcpy(account.password, new_password);
        changed = true;
        cout << "Password changed successfully! Press any key to continue...";
    }
}

void processHacking(savefile account, int choice)
{
    for (int i = 0; i < 5; i++)
    {
        GoTo(9 + 2*i+1, 53);
        if (choice == i+1)
            SetColor(black, yellow);
        else
            SetColor();
        cout << "< " << account.record[i].points << " >";
    }

    if (choice == 6)
        drawCell("Save", 25, (WinColumn - 22) / 2, 3, 22, yellow, black);
    else
        drawCell("Save", 25, (WinColumn - 22) / 2, 3, 22, white, black);
}

void sortRecord(Record record[], int n) {
    for (int i = 1; i < n; i++) {
        Record temp = record[i];
        int j = i - 1;
        while (j >= 0 && record[j].points < temp.points) {
            record[j + 1] = record[j];
            j--;
        }
        record[j + 1] = temp;
    }
}

void displayCreditPage()
{
    GoTo(2, (WinColumn - 6) / 2);
    cout << "Credit";

    GoTo(3, (WinColumn - 36) / 2);
    cout << "22127258 - Le Tri Man - 22CLC10 - HCMUS";

    GoTo(4, (WinColumn - 36) / 2);
    cout << "22127452 - Le Ngoc Vi - 22CLC10 - HCMUS";
}

void displaySavePage(GameState game, savefile account, int choice)
{
    GoTo(1, (WinColumn - 34)/2);
    cout << "Choose the slot you want to save.";
    int cellRowSize = 5;
    for (int i = 0; i < 5; i++)
    {
        string saved_inf;
        if (account.state[i].row != 0)
        {
            saved_inf = to_string(i+1) + ". Board: " + to_string(account.state[i].row) + "x" + to_string(account.state[i].col);
            saved_inf += ". Difficulty: " + to_string(account.state[i].difficulty) + ". Score: " + to_string(account.state[i].score);
        }
        else
        {
            saved_inf = to_string(i+1) + ". No saved game.";
        }
        
        if (choice == i + 1)
            drawCell(saved_inf, 7 + 5*i, (WinColumn - saved_inf.length())/2, cellRowSize, saved_inf.length() + 5, yellow, black);
        else
            drawCell(saved_inf, 7 + 5*i, (WinColumn - saved_inf.length())/2, cellRowSize, saved_inf.length() + 5, white, black);
    }
}