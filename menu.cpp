#include "menu.h"


/// @brief This function generate the login/register menu
void displayLoginRegisterMenu(savefile &account, string account_file, PlayerInfo players[], char** title, int title_row, int title_col, bool &run, bool &isLogged, int &choice)
{
    //Display the game title: "Pokemon Matching"
    displayGameTitle(title, title_row, title_col);

    int cellRowSize = 3;    //Size of the box's row
    int cellColumnSize = 15;    //Size of the box's column

    vector<string> options;
    options.push_back("LOG IN");
    options.push_back("REGISTER");
    options.push_back("QUIT");


    int posX = 15, posY = (WinColumn - cellColumnSize) / 2; //The start position to draw box
    for (int i = 0; i < options.size(); i++)
    {
        if (choice == i + 1)    //If the current option is chosen, set color yellow
        {
            drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, yellow, black);
            posX += 4;
        }
        else    //Else, set grey
        {
            drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, grey, black);
            posX += 4;
        }
    }
    //Get input
    char input = getch();
    input = toupper(input);

    PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);

    //Check input
    switch(input)
    {
        //Go up
        case 'W':
            if (choice > 1 )
                choice --;
            break;
        //Go down
        case 'S':
            if (choice < options.size())
                choice ++;
            break;
        //Select
        case ' ':
            if (choice == 1 || choice == 2)
            {
                clear();
                displayGameTitle (title, title_row, title_col);
                displayForm(account_file, account, players, choice, isLogged);
            }
            else
            {
                run = false;
                return;
            }
            break;
    }
}


/// @brief This function display the form to input name and password
void displayForm(string account_file, savefile &account, PlayerInfo players[], int choice, bool &isLogged)
{
    int box_size = 20;
    int posX = 15;

    /*Display "LOG IN" OR "REGISTER"*/
    string title = "";
    char temp_name[NAMESIZE];
    char temp_password[PASSSIZE];
    if (choice == 1)
        title = "LOG IN";
    else
        title = "REGISTER";
    GoTo(posX, (WinColumn - title.length()) / 2);
    cout << title;
    /////////////////////////////////////

    /*Display box for username*/
    GoTo(posX + 4, (WinColumn - 10 - box_size) / 2);
    cout << "Username: ";
    drawCell(" ", posX + 3, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);
    //////////////////////////////////////////////////////////////////////

    /*Display box for password*/
    GoTo(posX + 7, (WinColumn - 10 - box_size) / 2);
    cout << "Password: ";
    drawCell(" ", posX + 6, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);
    //////////////////////////////////////////////////////////////////////

    /*Get input*/
    ShowConsoleCursor(true);
    GoTo(posX + 4, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(temp_name, 20);

    GoTo(posX + 7, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(temp_password, 20);
    ShowConsoleCursor(false);
    ///////////////////////////////////////////////////

    //Endline
    GoTo(posX + 9, (WinColumn - 50 - box_size) / 2 + 12);

    //Check login / register 
    if (choice == 1)
        processLogin(account_file, temp_name, temp_password, account, players, isLogged);
    else
        processReg(account_file, temp_name, temp_password, account, isLogged, players);
}

/**
 * This function generate the main menu
 * Page 1 = New Game / Load Game / Account / Leaderboard / Credit / Quit
 * Page 2 = Difficulty choice
 * Page 3 = Custom board page
 * Page 4 = Load Game
 * Page 5 = Account
 * Page 6 = Hack
 * Page 7 = Show leaderboard
 * Page 8 = Show game credit
 * Page 9 = Gameplay
 * Page 10 = Save game
 */
void generateMenu(savefile &account, GameState &game, PlayerInfo players[], string account_file, int &page, int &choice, char** title, int title_row, int title_col, bool &run, bool &continue_game, int &word_count, bool &isLogged, string &bg_file)
{
    char input; 

    if (page == main_page) //Page 1 = Start / Leaderboard / Credit / Quit
    {
        displayGameTitle(title, title_row, title_col);
        displayMainMenu(choice);

        input = getch();
        input = toupper(input);

        //Play sound
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);

        //Check input
        switch(input)
        {
            case 'W':   //Go up
                if (choice > 1)
                    choice --;
                break;
            case 'S':   //Go Down
                if (choice < 7)
                    choice ++;
                break;
            case ' ':
                if (choice == 1) //New Game
                {
                    clear();
                    page = diff_page;   //Go to difficulty choice page
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
                    displayAccountInfo(account);
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
                else if (choice == 6)   //Log out
                {
                    saveGame(account_file, account);    //Save the current account to file
                    isLogged = false;   //Reset the check log-in variable to false
                    memset(&account, 0, sizeof(account));   //reset memory of the account struct.
                    clear();
                }
                else    //Quit game
                {
                    run = false;
                    saveGame(account_file, account);    //Save the current account to file
                }
                break;
        }
    }
    else if (page == diff_page) //Page 2 = Difficulty choice
    {
        //Display the title
        displayGameTitle(title, title_row, title_col);
        //Display the menu choice
        displayDifficultyChoice(choice);

        //Handle input
        input = getch();
        input = toupper(input);
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
                    page = gameplay_page;   //Go to gameplay page
                }
                else //Custom Mode
                {
                    page = custom_page; //Go to custom board page
                    clear();
                    choice = 1;
                    game.difficulty = 0;    //0: Custom
                }
                break;
            case 27:    //Esc = 27, exit to main menu
                clear();
                page = main_page;
                break;
        }
    }
    else if (page == custom_page) //Page 3 = Custom board
    {
        //Display the title
        displayGameTitle(title, title_row, title_col);
        //Display menu choice
        displayCustomBoardPage(game, choice);

        //Handle input
        input = getch();
        input = toupper(input);
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);
        switch(input)
        {
            case 'W':   //Go up
                if (choice > 1)
                    choice--;
                break;
            case 'S':   //Go down
                if (choice < 4)
                    choice ++;
                break;
            case 'A':   //Decrease
                if (game.row > 4)
                    game.row -= (choice == 1);
                if (game.col > 4)
                    game.col -= (choice == 2);
                if (game.total_time > 10)
                    game.total_time -= 10*(choice == 3);
                if (game.mode > 1)
                    game.mode -= (choice == 4);
                break;
            case 'D':   //Increase
                //Increase game row
                if (game.row < 8)
                    game.row += (choice == 1); //(choice == 1) return 1 if true, 0 otherwise
                
                //Increase game column
                if (game.col < 10)
                    game.col += (choice == 2);  //(choice == 2) return 1 if true, 0 otherwise

                //Increase total time
                if (game.total_time < 300)
                    game.total_time += 10 * (choice  == 3); //(choice == 3) return 1 if true, 0 otherwise

                //Increase game mode
                if (game.mode < 5)
                    game.mode += (choice == 4); //(choice == 4) return 1 if true, 0 otherwise
                break;
            case ' ':   
                //Check if the number of cells is even
                if (game.row * game.col % 2 == 0)   //if yes,
                    page = gameplay_page;   //Go to gameplay page
                else    //if no,
                {
                    //Deliver a warning 
                    GoTo(5, (WinColumn - 34)/2);
                    cout <<"Board size must be even!"; 
                    std::this_thread::sleep_for(800ms);
                }
                break;
            case 27:    //Esc = 27
                clear();
                page = main_page;
                break;
        }
    }
    else if (page == load_page)
    {
        //Display menu choice
        displayLoadGamePage(account, choice);

        //Handle input
        input = getch();
        input = toupper(input);
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);
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
                    loadBoard(game, account, choice - 1, bg_file);  //Load saved board from account to the in-game board
                    page = gameplay_page;   //Go to gameplay page
                    continue_game = true;   //This mean the board is all set, only need to set time, offset then play
                }
                break;
            case 27:
                clear();
                page = main_page;
                break;
        }
    }
    else if (page == account_page)
    {
        //Display menu choice
        displayAccOptions(choice);

        //Handle input
        input = getch();
        input = toupper(input);
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);

        //Check if player enter the cheat code correctly
        if (checkCheatCode(input, word_count, Cheat_page))
        {
            clear();
            displayAccountInfo(account);
            page = hack_page;
        }
        switch(input)
        {
            case 'A':  //Go left
                if (choice > 1)
                    choice --;
                break;
            case 'D':   //Go right
                if (choice < 3)
                    choice ++;
                break;
            case ' ':   //Select
                if (choice == 1) //Change username
                {
                    bool changed = false;
                    changeNameForm(account, account_file, changed);
                    if (changed)
                        saveGame(account_file, account);
                    
                    clear();
                    displayAccountInfo(account);
                }
                else if (choice == 2) //Change Password
                {   
                    bool changed = false;
                    changePasswordForm(account, account_file ,changed);
                    if (changed)
                        saveGame(account_file, account);
                    
                    clear();
                    displayAccountInfo(account);
                }
                else    //Return to main menu
                {
                    page = main_page;
                    clear();
                }
                break;
        }
    }
    else if (page == hack_page)
    {
        processHacking(account, choice);
        input = getch();
        input = toupper(input);
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);
        switch(input)
        {
            case 'W':   //Go up
                if (choice > 1)
                    choice --;
                break;
            case 'S':   //Go down
                if (choice < 6)
                    choice ++;
                break;
            case 'A':   //Decrease points
                if (choice != 6 && account.record[choice - 1].points >= 10)
                    account.record[choice - 1].points -=10;
                break;
            case 'D':   //Increase points
                if (choice != 6 && account.record[choice - 1].points < INT_MAX)
                    account.record[choice - 1].points +=10;
                break;
            case ' ':
                if (choice == 6) //Save
                {
                    sortRecord(account.record, 5);
                    saveGame(account_file, account);
                    updateLdBoard(players, account);
                    page = account_page;
                    clear();
                    displayAccountInfo(account);
                    choice = 1;
                }
                break;
        }
    }
    else if (page == save_page)
    {
        displaySavePage(game, account, choice);

        //Handle input
        input = getch();
        input = toupper(input);
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);
        switch(input)
        {
            case 'W':   //Go up
                if (choice > 1)
                    choice --;
                break;
            case 'S':   //Go down
                if (choice < 5)
                    choice ++;
                break;
            case ' ':
                saveBoard(game, account, choice - 1); //Save board
                //Go back to gameplay
                page = gameplay_page;
                continue_game = true;
                break;
            case 27: //Esc
                //Go back to gameplay
                page = gameplay_page;
                continue_game = true;
                break;
        }
    }
    else if (page == ldboard_page)
    {
        displayLdBoard(players);
        input = getch();
        PlaySound(TEXT("SoundSFX/navigate.wav"), NULL, SND_FILENAME | SND_ASYNC);
        if (input == 27)    //Esc
        {
            clear();
            page = main_page;
        }
    }
}
void displayMainMenu(int choice)
{
    vector<string> options;
    options.push_back("NEW GAME");
    options.push_back("LOAD GAME");
    options.push_back("ACCOUNT");
    options.push_back("LEADERBOARD");
    options.push_back("CREDIT");
    options.push_back("LOG OUT");
    options.push_back("QUIT");

    int cellRowSize = 3;
    int cellColumnSize = 15;

    int posX = 15, posY = (WinColumn - cellColumnSize) / 2;


    for (int i = 0; i < options.size(); i++)
    {
        if (choice == i + 1)    //if the option is selected, set color yellow
        {
            drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, yellow, white);
            posX += cellRowSize;
        }
        else    //else, set grey 
        {
            drawCell(options[i], posX, posY, cellRowSize, cellColumnSize, grey, white);
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
        if (choice - 1 == i)    //if the option is selected, set color yellow
        {
            drawCell(difficulty[i], posX, posY, cellRowSize, cellColumnSize, yellow, white);
            posX += cellRowSize;
        }
        else    //else, set grey 
        {
            drawCell(difficulty[i], posX, posY, cellRowSize, cellColumnSize, grey, white);
            posX += cellRowSize;
        }
        
    }
}

/// @brief Display custom board page
void displayCustomBoardPage(GameState game, int choice)
{
    string title1 = "Custom";
    GoTo (15, (WinColumn - title1.length()) / 2);
    cout << title1;

    GoTo(16, (WinColumn - 34)/2);
    cout << "Select the number of rows: \t\t";

    if (choice == 1)
        SetColor(white, yellow);
    cout << "< ";
    cout << game.row;
    cout << " >";
    SetColor(); //Set Color back to default

    GoTo(17, (WinColumn - 34)/2);
    cout << "Select the number of column: \t\t";
    if (choice == 2)
        SetColor(white, yellow);
    cout << "< ";
    cout << game.col;
    cout << " >";
    SetColor(); //Set Color back to default

    GoTo(18, (WinColumn - 34)/2);
    cout << "Select timer: \t\t\t\t";
    if (choice  == 3)
        SetColor(white, yellow);
    cout << "< ";
    cout << game.total_time;
    cout << " >";
    SetColor();

    GoTo(19, (WinColumn - 34)/2);
    cout << "Select game mode: \t\t\t";
    string gameMode[] = {"Normal", "Shift left", "Shift right", "Shift up", "Shift down"};
    if (choice == 4)
        SetColor(white, yellow);
    cout << "< ";
    cout << gameMode[game.mode - 1];
    cout << " >      ";
    SetColor(); //Set Color back to default
}

/// @brief Load Game Page
void displayLoadGamePage(savefile account, int choice)
{
    GoTo(2, (WinColumn - 10)/2);
    cout << "LOAD GAME";
    int cellRowSize = 5;
    for (int i = 0; i < 5; i++)
    {
        //Get saved board info
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
        
        //Display 
        if (choice == i + 1)
            drawCell(saved_inf, 7 + (cellRowSize+1)*i, (WinColumn - 50)/2, cellRowSize, 50, yellow, white);
        else
            drawCell(saved_inf, 7 + (cellRowSize+1)*i, (WinColumn - 50)/2, cellRowSize, 50, grey, white);
    }
}

/// @brief Display account information page
void displayAccountInfo(savefile account)
{
    //Display account username and password
    drawCell("Account Info", 5, 10, 3, 33);
    drawCell(" ", 8, 10, 15, 33);
    GoTo(9, 12);
    cout << "Username: " << account.name;
    GoTo(10, 12);
    cout << "Password: ";
    for (int i = 0; i < strlen(account.password); i++)
        cout << "*";
    /////////////////////////////////////////

    //Display High Score
    drawCell("High Score", 5, 44, 3, 33);
    drawCell(" ", 8, 44, 15, 33);
    for (int i = 0; i < 5; i++)
    {
        GoTo(9 + 2*i, 46);
        cout << "1. Date: " << account.record[i].date.day << "/"<< account.record[i].date.month<< "/"<< account.record[i].date.year;
        GoTo(9 + 2*i+1, 46);
        cout << "Score: " << account.record[i].points;
    }
    /////////////////////////////////////////////////

    //Display summary
    drawCell("Summary", 5, 78, 3, 38);
    drawCell(" ", 8, 78, 15, 38);

    int avg = account.getElo();
    GoTo(10, 80);
    cout << "Your elo is: " << account.getElo();

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
    else 
        cout << "Challenger";
    //////////////////////////////////////////////
}


/// @brief Display options for the account info page
/// @param choice current choice
void displayAccOptions(int choice)
{
    vector<string> options;
    options.push_back("Change Username");
    options.push_back("Change password");
    options.push_back("Return");
    for (int i = 0; i < options.size(); i++)
    {
        if (choice == i + 1)
            drawCell(options[i], 25 ,(WinColumn - options.size()*22)/2 + i*22 + 1, 3, 22, yellow, white);
        else
            drawCell(options[i], 25 ,(WinColumn - options.size()*22)/2 + i*22 + 1, 3, 22, grey, white);
    }
}


/// @brief display form for name changing
void changeNameForm(savefile &account, string account_file, bool &changed)
{
    clear();
    string title = "Change Username";
    char temp_name[NAMESIZE];
    char temp_password[PASSSIZE];
    int box_size = 20;

    GoTo(0, (WinColumn - title.length()) / 2);
    cout << title;
    
    GoTo(4, (WinColumn - 14 - box_size) / 2);
    cout << "New username: ";
    drawCell(" ", 3, (WinColumn - 14 - box_size) / 2 + 14, 3, 20);

    GoTo(7, (WinColumn - 14 - box_size) / 2);
    cout << "Password: ";
    drawCell(" ", 6, (WinColumn - 14 - box_size) / 2 + 14, 3, 20);

    ShowConsoleCursor(true);
    GoTo(4, (WinColumn - 14 - box_size) / 2 + 16);
    cin.getline(temp_name, 20);

    GoTo(7, (WinColumn - 14 - box_size) / 2 + 16);
    cin.getline(temp_password, 20);
    ShowConsoleCursor(false);

    GoTo(9, (WinColumn - 50 - box_size) / 2 + 12);

    /*Check if the username already existed*/
    ifstream file(account_file, ios::binary);
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
        saveGame(account_file, account);    //Save to file
        cout << "Changed username successfully. Press any key to go back...";
        getch();
    }

    file.close();
}

void changePasswordForm(savefile &account, string account_file, bool &changed)
{
    clear();
    string title = "Change Password";
    char old_password[PASSSIZE];
    char new_password[PASSSIZE];
    int box_size = 20;

    GoTo(0, (WinColumn - title.length()) / 2);
    cout << title;
    
    GoTo(4, (WinColumn - 14 - box_size) / 2);
    cout << "Old Password: ";
    drawCell(" ", 3, (WinColumn - 14 - box_size) / 2 + 14, 3, 20);

    GoTo(7, (WinColumn - 14 - box_size) / 2);
    cout << "New Password: ";
    drawCell(" ", 6, (WinColumn - 14 - box_size) / 2 + 14, 3, 20);

    ShowConsoleCursor(true);
    GoTo(4, (WinColumn - 14 - box_size) / 2 + 16);
    cin.getline(old_password, 20);

    GoTo(7, (WinColumn - 14 - box_size) / 2 + 16);
    cin.getline(new_password, 20);
    ShowConsoleCursor(false);

    GoTo(9, (WinColumn - 50 - box_size) / 2 + 16);
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
        saveGame(account_file, account);    //save to file
        changed = true;
        cout << "Password changed successfully! Press any key to continue...";
        getch();
    }
}

//Display hacking options
void processHacking(savefile account, int choice)
{
    for (int i = 0; i < 5; i++)
    {
        GoTo(9 + 2*i+1, 53);
        if (choice == i+1)
            SetColor(white, yellow);
        else
            SetColor();
        cout << "< " << account.record[i].points << " >";
    }

    if (choice == 6)
        drawCell("Save", 25, (WinColumn - 22) / 2, 3, 22, yellow, white);
    else
        drawCell("Save", 25, (WinColumn - 22) / 2, 3, 22, grey, white);
}

//Check cheate code
bool checkCheatCode(char c, int &count, string cheatCode)
{
    if (c == cheatCode[count])
        count++;
    else
        count = 0;
    
    return count == cheatCode.length();
}

//Sort the record array to descending order
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

//Display Credit page
void displayCreditPage()
{
    GoTo(2, (WinColumn - 6) / 2);
    cout << "Credit";

    GoTo(4, (WinColumn - 36)/2);
    cout << "Student name: ";
    GoTo(5, (WinColumn - 36) / 2);
    cout << "22127258 - Le Tri Man - 22CLC10 - HCMUS";

    GoTo(6, (WinColumn - 36) / 2);
    cout << "22127452 - Le Ngoc Vi - 22CLC10 - HCMUS";

    GoTo(8, (WinColumn - 36) / 2);
    cout << "Advisors:";
    GoTo(9, (WinColumn - 36) / 2);
    cout << "Nguyen Thanh Phuong - HCMUS";
    GoTo(9, (WinColumn - 36) / 2);
    cout << "Buy Huy Thong - HCMUS";
    GoTo(9, (WinColumn - 36) / 2);
    cout << "Nguyen Ngoc Thao - HCMUS";
    GoTo(9, (WinColumn - 36) / 2);
    cout << "Tran Thao Nhi - HCMUS";
}

//Display game saving page
void displaySavePage(GameState game, savefile account, int choice)
{
    GoTo(4, (WinColumn - 34)/2);
    cout << "Choose the slot you want to save.";
    int cellRowSize = 5;
    for (int i = 0; i < 5; i++)
    {
        //Get saved board info
        string saved_inf;
        if (account.state[i].row != 0)
        {
            saved_inf = to_string(i+1) + ". Board: " + to_string(account.state[i].row) + "x" + to_string(account.state[i].col);
            saved_inf += ". Difficulty: " + to_string(account.state[i].difficulty) + ". Score: " + to_string(account.state[i].score);
        }
        else
            saved_inf = to_string(i+1) + ". No saved game.";
        /////////////////////////////////////////////////////

        if (choice == i + 1)
            drawCell(saved_inf, 7 + 5*i, (WinColumn - saved_inf.length())/2, cellRowSize, saved_inf.length() + 5, yellow, white);
        else
            drawCell(saved_inf, 7 + 5*i, (WinColumn - saved_inf.length())/2, cellRowSize, saved_inf.length() + 5, grey, white);
    }
}

//Display leaderboard
void displayLdBoard(PlayerInfo players[])
{
    GoTo(1, (WinColumn -12)/2);
    cout << "LeaderBoard";
    
    int numbersize = 5;
    int namesize = 40;
    int ratingsize = 20;
    int ranksize = 20;

    int totalsize = numbersize + namesize + ratingsize + ranksize;

    drawCell("#", 5, (WinColumn - totalsize)/2, 3, numbersize);
    drawCell("Name", 5, (WinColumn - totalsize)/2 + numbersize, 3, namesize);
    drawCell("Rating", 5, (WinColumn - totalsize)/2 + numbersize + namesize, 3, ratingsize);
    drawCell("Rank", 5, (WinColumn - totalsize)/2 + numbersize + namesize + ratingsize, 3, ranksize);

    for (int i = 0; i < MAXPLAYERS; i++)
    {
        GoTo(8 + 2*i, (WinColumn - totalsize)/2 + numbersize/2);
        cout << i+1;

        GoTo(8+ 2*i, (WinColumn - totalsize)/2 + numbersize + 2);
        cout << players[i].name;

        GoTo(8+ 2*i, (WinColumn - totalsize)/2 + numbersize + namesize + 5);
        cout << players[i].elo;

        GoTo(8+ 2*i, (WinColumn - totalsize)/2 + numbersize + namesize + ratingsize + 3);
        cout << players[i].rank;
    }
}

