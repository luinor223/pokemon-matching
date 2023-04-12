#include "account.h"

void mask(char text[], char mask)
{
    for (int i = 0; i < strlen(text); i++)
    {
        text[i] = text[i] ^ mask;
    }
}

void processReg(string filename, char* name, char* password, savefile &account, bool &isLogged, PlayerInfo players[])
{
    fstream file(filename, ios::binary | ios::in | ios::out); // open file in read and write mode

    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        clear();
        return;
    }

    bool isExist = false;
    savefile tempAccount;
    int position = 0;

    while (file.read((char*)&tempAccount, sizeof(tempAccount))) // read data from file
    {
        mask(tempAccount.name, tempAccount.mask);  //Unmask name
        if (strcmp(tempAccount.name, name) == 0) // check if username already exists
        {
            isExist = true;
            cout << "Username already exists. Press any key to go back...";
            getch();
            clear();
            break;
        }
        position++;
    }

    if (!isExist) // if username does not exist, write player data to file
    {
        file.clear();
        file.seekp(0, ios::end);

        strcpy(account.name, name);
        strcpy(account.password, password);
        account.mask = 'A' + rand() % 26;
        mask(account.name, account.mask);  //mask to write into file
        mask(account.password, account.mask);  //mask to write into file
        account.position = position;

        file.write((char*)&account, sizeof(account));
        for (int i = 0; i < 5; i++)
            cout << account.record[i].points << " ";
        cout << "Registration successful! Press any key to continue...";
        getch();
        isLogged = true;
        getLdBoard(players, filename);
        clear();

        mask(account.name, account.mask);   //unmask to display in-game
        mask(account.password, account.mask);   //unmask to display in-game
    }

    file.close(); // close file
}

void processLogin(string filename, char* name, char* password, savefile &account, PlayerInfo players[] ,bool &isLogged)
{
    ifstream file(filename, ios::binary);
    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        clear();
        return;
    }

    int position = 0;

    while (file.read((char*)&account, sizeof(account))) // read data from file
    {
        mask(account.name, account.mask);  //UnMask username
        mask(account.password, account.mask); // UnMask password

        if (strcmp(account.name, name) == 0) // check if username exists
        {
            if (strcmp(account.password, password) == 0) //check if password matches
            {
                cout << "Login successful! Press any key to continue...";
                getch();
                getLdBoard(players, filename);
                isLogged = true;
                account.position = position;
                clear();
                break;
            }
            else
            {
                break;
            }
        }
        position ++;
    }

    if(!isLogged)
    {
        cout << "Username or Password is not correct! Press any key to go back...";
        getch();
        memset(&account, 0, sizeof(account));
        clear();
    }
    

    file.close();  
}

void displayForm(string filename, savefile &account, PlayerInfo players[], int choice, bool &isLogged)
{
    string title = "";
    char temp_name[NAMESIZE];
    char temp_password[PASSSIZE];
    if (choice == 1)
        title = "LOG IN";
    else
        title = "REGISTER";
    int box_size = 20;

    int posX = 15;

    GoTo(posX, (WinColumn - title.length()) / 2);
    cout << title;
    
    GoTo(posX + 4, (WinColumn - 10 - box_size) / 2);
    cout << "Username: ";
    drawCell(" ", posX + 3, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);

    GoTo(posX + 7, (WinColumn - 10 - box_size) / 2);
    cout << "Password: ";
    drawCell(" ", posX + 6, (WinColumn - 10 - box_size) / 2 + 10, 3, 20);

    GoTo(posX + 4, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(temp_name, 20);

    GoTo(posX + 7, (WinColumn - 10 - box_size) / 2 + 12);
    cin.getline(temp_password, 20);

    GoTo(posX + 9, (WinColumn - 50 - box_size) / 2 + 12);

    if (choice == 1)
        processLogin(filename, temp_name, temp_password, account, players, isLogged);
    else
        processReg(filename, temp_name, temp_password, account, isLogged, players);
}

void displayLoginRegisterMenu(savefile &account, string filename, PlayerInfo players[], char** title, int title_row, int title_col, bool &run, bool &isLogged, int &choice)
{
    string username;

    int cellRowSize = 3;
    int cellColumnSize = 15;

    vector<string> options;
    options.push_back("LOG IN");
    options.push_back("REGISTER");
    options.push_back("QUIT");
    
    displayGameTitle(title, title_row, title_col);

    int posX = 15, posY = (WinColumn - cellColumnSize) / 2;
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
                clear();
                displayGameTitle (title, title_row, title_col);
                displayForm(filename, account, players, choice, isLogged);
            }
            else
            {
                run = false;
                return;
            }
            break;
    }
}

void loadBoard(GameState &game, savefile account, int index, string &bg_file) 
{
    game.row = account.state[index].row;
    game.col = account.state[index].col;
    game.cur.x = account.state[index].cur_x;
    game.cur.y = account.state[index].cur_y;
    game.move_count = 0;

    game.board = new char *[game.row];
    for (int i = 0; i < game.row; i++)
    {
        game.board[i] = new char[game.col];
        for (int j = 0; j < game.col; j++)
        {
            game.board[i][j] = account.state[index].board[i*game.col + j] ^ account.mask;  //unmask
            if (game.board[i][j] != '\0')
                game.move_count++;
        }
    }
    game.move_count /= 2;

    bg_file = account.state[index].file_background;

    game.time_left = (account.state[index].time_left > 0) ? account.state[index].time_left : 120;
    game.score = account.state[index].score;
    game.difficulty = account.state[index].difficulty;
    game.mode = (account.state[index].mode > 0) ? account.state[index].mode : 1;
    game.stage = (account.state[index].stage > 0) ? account.state[index].stage : 1;
}

void saveBoard(GameState game, savefile &account, int index)
{
    account.state[index].row = game.row;
    account.state[index].col = game.col;
    account.state[index].cur_x = game.cur.x;
    account.state[index].cur_y = game.cur.y;

    for (int i = 0; i < game.row; i++)
        for (int j = 0; j < game.col; j++)
            account.state[index].board[i*game.col + j] = game.board[i][j] ^ account.mask; //mask

    account.state[index].time_left = game.time_left;
    account.state[index].score = game.score;
    account.state[index].difficulty = game.difficulty;
    account.state[index].mode = game.mode;
    account.state[index].stage = game.stage;
    account.state[index].help_count = game.help_count;
    account.state[index].shuffle_count = game.shuffle_count;
}

void getLdBoard(PlayerInfo players[], string account_file)
{
    ifstream file(account_file, ios::binary);
    if (!file)
    {
        cout << "Error, missing " << account_file << ".";
        getch();
        return;
    }

    savefile tempAccount;
    while(file.read((char*)&tempAccount, sizeof(tempAccount)))
    {
        updateLdBoard(players, tempAccount);
    }

    file.close();
}

void updateLdBoard(PlayerInfo players[], savefile account)
{
    if (account.getElo() > players[MAXPLAYERS - 1].elo)
    {
        int i =  checkNameOnLB(account, players);
        if (i != -1)
        {
            players[i].elo = account.getElo();
            sortLB(players);
        }
        else
        {
            players[MAXPLAYERS - 1].name = account.name;
            players[MAXPLAYERS - 1].elo = account.getElo();
            players[MAXPLAYERS - 1].rank = players[MAXPLAYERS - 1].getRank();

            sortLB(players);
        }
    }
}

void sortLB(PlayerInfo arr[]) {
    for (int i = 1; i < MAXPLAYERS; i++) {
        PlayerInfo key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].elo < key.elo) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void saveGame(string filename, savefile account)
{
    fstream file(filename, ios::binary |ios::in | ios::out); // open file in read and write mode
    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! " << filename << " is missing!";
        getch();
        return;
    }
    file.seekp(account.position*sizeof(account), ios::beg);

    mask(account.name, account.mask);
    mask(account.password, account.mask);
    file.write((char*)&account, sizeof(account));

    file.close();
}