#include "board.h"

void initialize_board(GameState &game, int &alphabets)
{
    if (game.stage == 1)
    {
        game.mode = 1;
        switch (game.difficulty)
        {
            case 1:
                game.row = 4;
                game.col = 6;
                game.total_time = 120;
                alphabets = 8;
                break;
            case 2:
                game.row = 6;
                game.col = 8;
                game.total_time = 180;
                alphabets = 10;
                break;
            case 3:
                game.row = 8;
                game.col = 10;
                game.total_time = 240;
                alphabets = 12;
                break;
            default:
                if (game.total_time < 120)
                    game.total_time = 120;
                break;
        }
    }
    else
    {
        game.total_time = game.time_left + bouns_time;
        switch (game.difficulty)
            {
                case 1:
                    game.total_time = game.time_left + 60;
                    alphabets = 8;
                    if (game.stage < 6)
                        game.mode = game.stage;
                    else
                        game.mode = rand() % 4 + 1;
                    break;
                case 2:
                    game.total_time = game.time_left + 90;
                    alphabets = 10;
                    if (game.stage < 6)
                        game.mode = game.stage;
                    else
                        game.mode = rand() % 4 + 1;
                    break;
                case 3:
                    game.total_time = game.time_left + 120;
                    alphabets = 12;
                    if (game.stage < 6)
                        game.mode = game.stage;
                    else
                        game.mode = rand() % 4 + 1;
                    break;
                default:
                    game.total_time = game.time_left + 60;
                    alphabets = 10;
                    break;
            }
    }
    
    game.move_count = (game.row * game.col) / 2;
}

void make_board(GameState &game) {
    int alphabets;
    initialize_board(game, alphabets);

    game.board = new char *[game.row];
    vector<pair<int, int>> avail_pos;
    for (int i = 0; i < game.row; i++)
    {
        game.board[i] = new char[game.col]; 
        for (int j = 0; j < game.col; j++)
        {
            avail_pos.push_back(make_pair(i, j));
        } 
    }  

    const int pairs = avail_pos.size() / 2;
    for (int i = 0; i < pairs; i++) {
        char c = 'A' + rand() % alphabets; 

        int pos1 = rand() % avail_pos.size();
        int pos2;
        do { 
            pos2 = rand() % avail_pos.size(); // select next position
        } while (pos1 == pos2); // if same position is selected

        game.board[avail_pos[pos1].first][avail_pos[pos1].second] = c;
        game.board[avail_pos[pos2].first][avail_pos[pos2].second] = c;

        avail_pos.erase(avail_pos.begin() + max(pos1, pos2));

        avail_pos.erase(avail_pos.begin() + min(pos1, pos2));
    }
}

// This function sets up the game board according to the game mode.
void setBoard(GameState game)
{
    if (game.mode == 1) // If the game mode is "not shift", do nothing.
        return;
    if (game.mode == 2) // If the game mode is "shift left", shift all tiles in each row to the left as far as possible.
    {
        for (int i = 0; i < game.row; i++)
        {
            for (int j = 0; j < game.col; j++)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = j+1; k < game.col; k++)
                        if (game.board[i][k] != '\0')
                        {
                            swap(game.board[i][j], game.board[i][k]);
                            break;
                        }
                }
            }
        }          
    }
    if (game.mode == 3) // If the game mode is "shift right", shift all tiles in each row to the right as far as possible.
    {
        for (int i = 0; i < game.row; i++)
        {
            for (int j = game.col - 1; j >= 0; j--)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = j-1; k >= 0; k--)
                        if (game.board[i][k] != '\0')
                        {
                            swap(game.board[i][j], game.board[i][k]);
                            break;
                        }
                }
            }
        }  
    }
    if (game.mode == 4) // If the game mode is "shift up", shift all tiles in each column up as far as possible.
    {
        for (int j = 0; j < game.col; j++)
        {
            for (int i = 0; i < game.row; i++)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = i+1; k < game.row; k++)
                        if (game.board[k][j] != '\0')
                        {
                            swap(game.board[i][j], game.board[k][j]);
                            break;
                        }
                }
            }
        }  
    }
    if (game.mode == 5) // If the game mode is "shift down", shift all tiles in each column down as far as possible.
    {
        for (int j = 0; j < game.col; j++)
        {
            for (int i =  game.row - 1; i >= 0; i--)
            {
                if (game.board[i][j] == '\0')
                {
                    for (int k = i-1; k >= 0; k--)
                        if (game.board[k][j] != '\0')
                        {
                            swap(game.board[i][j], game.board[k][j]);
                            break;
                        }
                }
            }
        }  
    }
}

void deleteMemBoard(GameState &game)
{
    for (int i = 0; i < game.row; i++)
        delete[] game.board[i];
    
    delete[] game.board;
}

void showBoard(GameState game, char** background, int bg_row, int bg_column, int offset_x, int offset_y)
{
    printBg(background, bg_row, bg_column);

    int rowSize = game.cellSize;
    int colSize = rowSize + 3;

    GoTo(offset_x, offset_y);
    
    for (int i = 0; i < game.row; i++)
    {
        for (int j = 0; j < game.col; j++)
        {
            string s;
            s = game.board[i][j];
            if(game.board[i][j] != '\0'){
                drawCell(s, offset_x + i*(rowSize)-i, offset_y + j*(colSize)-j, rowSize, colSize);
            }
        }
    }
}

void shuffle_board(GameState &game)
{
    char count[26] = {0};
    vector <pair<int, int>> avail_pos;
    for (int i = 0; i < game.row; i++)
    {
        for (int j = 0; j < game.col; j++)
        {
            if (game.board[i][j] != '\0')
            {
                count[game.board[i][j] - 'A'] ++;
                avail_pos.push_back({i, j});
            }
        }
    }

    for (int i = 0; i < 26; i++)
    {
        while (count[i] > 0)
        {
            char c = i + 'A';

            int pos1 = rand() % avail_pos.size();
            int pos2;
            do { 
                pos2 = rand() % avail_pos.size(); // select next position
            } while (pos1 == pos2); // if same position is selected

            game.board[avail_pos[pos1].first][avail_pos[pos1].second] = c;
            game.board[avail_pos[pos2].first][avail_pos[pos2].second] = c;

            avail_pos.erase(avail_pos.begin() + max(pos1, pos2));
            avail_pos.erase(avail_pos.begin() + min(pos1, pos2));

            count[i] -= 2;
        }
    }
}