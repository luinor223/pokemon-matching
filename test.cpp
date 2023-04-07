#include <iostream>
#include <string>
#include "main.h"

using namespace std;

void loadBoard(GameState &game, savefile account, int index) 
{
    game.row = account.state[index].row;
    game.col = account.state[index].col;
    game.cur.x = account.state[index].cur_x;
    game.cur.y = account.state[index].cur_y;

    game.board = new char *[game.row];
    for (int i = 0; i < game.row; i++)
    {
        game.board[i] = new char[game.col];
        for (int j = 0; j < game.col; j++)
            game.board[i][j] = account.state[index].board[i*game.col + j] ^ account.mask;  //unmask
    }

    game.time_left = account.state[index].time_left;
    game.score = account.state[index].score;
    game.difficulty = account.state[index].difficulty;
    game.mode = account.state[index].mode;
    game.stage = account.state[index].stage;
    game.help_count = account.state[index].help_count;
    game.shuffle_count = account.state[index].shuffle_count;
}

int main() {
    savefile account;
    GameState game;

    ifstream file("sample.bin", ios::binary);
    if (!file.is_open()) // check if file is opened successfully
    {
        cout << "Error! File cannot be opened.";
        return 0;
    }

    savefile tempAccount;
    while (file.read((char*)&tempAccount, sizeof(tempAccount))) // read data from file
    {
        for (int i = 0; i < strlen(tempAccount.name); i++)
        {
            tempAccount.name[i] = tempAccount.name[i] ^ tempAccount.mask;
        }

        for (int i = 0; i < strlen(tempAccount.password); i++)
        {
            tempAccount.password[i] = tempAccount.password[i] ^ tempAccount.mask;
        }

        cout << tempAccount.state[0].row << " " << tempAccount.state[0].col <<endl;
        // for (int i = 0; i < sizeof(tempAccount.state)/sizeof(tempAccount.state[0]); i++)
        // {
        //     for (int j = 0; j < tempAccount.state[0].row * tempAccount.state[0].col; j++)
        //     {
        //         tempAccount.state[i].board[j] = tempAccount.state[i].board[j] ^ tempAccount.mask;
        //     }
        // }

        for (int i = 0; i < tempAccount.state[0].row; i++)
        {
            for (int j = 0; j < tempAccount.state[0].col; j++)
            {
                cout << tempAccount.state[0].board[i*tempAccount.state[0].col + j] << " ";
            }
            cout << endl;
        }
    }

    loadBoard(game, tempAccount, 0);
    cout << game.row << " " << game.col<< endl;
    for (int i = 0; i < game.row; i++)
    {
        for (int j = 0; j < game.col; j++)
            cout << game.board[i][j] << " ";
        cout << endl;
    }
    for (int i = 0; i < game.row; i++)
        delete[] game.board[i];
    delete game.board;
    
    file.close();  

    return 0;
}