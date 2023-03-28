#include "board.h"

void memAllcBoard(GameState a)
{
    a.board = new char*[row];
    for (int i = 0; i < row; i++)
        a.board[i] = new char[col];
}

void make_board(GameState &game) {
    srand(time(NULL));
    char alphabet[] = {'A', 'G', 'U', 'P', 'V', 'X', 'Z', 'M', 'L', 'K' , 'I'};
    int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);
    
    switch (game.difficulty)
    {
        case 1:
            game.row = 4;
            game.col = 6;
            break;
        case 2:
            game.row = 6;
            game.col = 8;
            break;
        case 3:
            game.row = 8;
            game.col = 10;
            break;
    }

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
        int pos2 = rand() % avail_pos.size();
        while (pos1 == pos2) { // if same position is selected
            pos2 = rand() % avail_pos.size(); // select next position
        }

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

void showBoard(GameState game, char** background, int bg_row, int bg_column)
{
    GoTo(0, 0);
    printBg(background, bg_row, bg_column);

    int rowSize = game.cellSize;
    int colSize = rowSize + 3;

    int offset_x = (bg_row - game.row * (rowSize - 1) - 1)/ 2;
    int offset_y = (bg_column - game.col * (colSize - 1) - 1) / 2;
    offset_x = (offset_x < 0) ? 0 : offset_x;
    offset_y = (offset_y < 0) ? 0 : offset_y;
    GoTo(offset_x, offset_y);
    
    for (int i = 0; i < game.row; i++)
    {
        for (int j = 0; j < game.col; j++)
        {
            string s;
            s = game.board[i][j];
            if(game.board[i][j] != '\0'){
                drawCell(s, offset_x + i*(rowSize-1), offset_y + j*(colSize)-j, rowSize, colSize);
            }
        }
    }
}