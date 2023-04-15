#include "account.h"

const char maskCh[] = {'=', ';', '+', '-', '<', '>'};

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
        account.mask = maskCh[rand() % 6];
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
                getLdBoard(players, filename); //load leaderboard from save file
                isLogged = true;    
                account.position = position;    //save the position of the player in the file
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
        memset(&account, 0, sizeof(account));   //Reset account
        clear();
    }
    

    file.close();  
}


/// @brief Load saved board from account to in-game board
/// @param game in-game struct
/// @param account account struct
/// @param index index of the saved board (0-4)
/// @param bg_file background file
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
            game.board[i][j] = account.state[index].board[i*game.col + j] ^ account.mask;  //unmask each character of the board;
            if (game.board[i][j] != '\0')
                game.move_count++;  
        }
    }
    game.move_count /= 2;

    mask(account.state[index].file_background, account.mask);   //unmask background
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
            account.state[index].board[i*game.col + j] = game.board[i][j] ^ account.mask; //mask each character of the board then save

    account.state[index].time_left = game.time_left;
    account.state[index].score = game.score;
    account.state[index].difficulty = game.difficulty;
    account.state[index].mode = game.mode;
    account.state[index].stage = game.stage;
    account.state[index].help_count = game.help_count;
    account.state[index].shuffle_count = game.shuffle_count;
}


/// @brief Get leaderboard from file
void getLdBoard(PlayerInfo players[], string account_file)
{
    ifstream file(account_file, ios::binary);   //Open binary file in read mode
    if (!file)  //Failed to open file
    {
        cout << "Error, missing " << account_file << ".";
        getch();
        return;
    }

    savefile tempAccount;   //temporary account
    while(file.read((char*)&tempAccount, sizeof(tempAccount)))  //scan all the account in the file.
    {
        mask(tempAccount.name, tempAccount.mask);   //Unmask name to display in leaderboard
        updateLdBoard(players, tempAccount);
    }

    file.close();
}

/// @brief Check if the current account's elo is high enough to place on leaderboard and then update it
void updateLdBoard(PlayerInfo players[], savefile account)
{
    if (account.getElo() > players[MAXPLAYERS - 1].elo)     //Check if the elo of an account is higher than the last player on the leaderboard
    {
        int i =  checkNameOnLB(account, players);   //Check if player's name already in leaderboard
        if (i != -1)    //If yes, update elo then sort the leaderboard
        {
            players[i].elo = account.getElo();
            sortLB(players);
        }
        else    //If no, update the last player then sort the leaderboard
        {
            players[MAXPLAYERS - 1].name = account.name;
            players[MAXPLAYERS - 1].elo = account.getElo();
            players[MAXPLAYERS - 1].rank = players[MAXPLAYERS - 1].getRank();

            sortLB(players);
        }
    }
}

/// @brief Sort Leaderboard
/// @param arr An array of players infomation to be displayed in leaderboard
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


/// @brief Check if the current account is already on leaderboard
/// @param account Current account
/// @param players An array of players infomation to be displayed in leaderboard
/// @return Index of the account on ldboard if it's already in leaderboard, else return -1.
int checkNameOnLB(savefile account, PlayerInfo players[])
{
    for (int i = 0; i < MAXPLAYERS; i++)
        if (players[i].name == account.name)
            return i;

    return -1;
}


/// @brief Save the current account struct to file
/// @param filename Save file's name
/// @param account current account
void saveGame(string filename, savefile account)
{
    fstream file(filename, ios::binary |ios::in | ios::out); // open binary file in read and write mode 
    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! " << filename << " is missing!";
        getch();
        return;
    }
    file.seekp(account.position*sizeof(account), ios::beg); //Go to the account's position in file 

    mask(account.name, account.mask);   //Mask name
    mask(account.password, account.mask);   //Mask password
    file.write((char*)&account, sizeof(account));   //Write

    file.close();
}