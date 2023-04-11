#include "board.h"

void initialize_board(GameState &game, int &alphabets)
{
    if (game.stage == 1)
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
    else
        switch (game.difficulty)
            {
                case 1:
                    game.total_time = game.time_left + 60;
                    alphabets = 8;
                    break;
                case 2:
                    game.total_time = game.time_left + 90;
                    alphabets = 10;
                    break;
                case 3:
                    game.total_time = game.time_left + 120;
                    alphabets = 12;
                    break;
                default:
                    game.total_time = game.time_left + 60;
                    alphabets = 10;
                    break;
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