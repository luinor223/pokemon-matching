#include "board.h"

void make_board(GameState &game) {
    char alphabet[] = {'A', 'G', 'U', 'P', 'V', 'X', 'Z', 'M', 'L', 'K' , 'I'};
    int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);
    
    if (game.stage == 1)
        switch (game.difficulty)
        {
            case 1:
                game.row = 4;
                game.col = 6;
                game.total_time = 120;
                break;
            case 2:
                game.row = 6;
                game.col = 8;
                game.total_time = 180;
                break;
            case 3:
                game.row = 8;
                game.col = 10;
                game.total_time = 240;
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
                    break;
                case 2:
                    game.total_time = game.time_left + 90;
                    break;
                case 3:
                    game.total_time = game.time_left + 120;
                    break;
                default:
                    game.total_time = game.time_left + 60;
                    break;
            }
    
    game.move_count = (game.row * game.col) / 2;

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
        char c = alphabet[rand() % alphabet_size];

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
    cout << "reaaa";
    getch();
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
    cout << "resss";
    getch();

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
    cout << "resetted";
    getch();
}