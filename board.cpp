#include "main.h"
#include "board.h"
#include "background.cpp"
#include "console.cpp"
#include "draw.cpp"

void init_board(char** &board)
{
    cout << "rows : ";
    cin >> row;
    cout << "col : ";
    cin >> col;

    board = new char*[row];
    for (int i = 0; i < row; i++)
        board[i] = new char[col];

  
}

void make_board(char** &board, int m, int n) {
    srand(time(NULL));
    char alphabet[] = {'A', 'G', 'U', 'P', 'V', 'X', 'Z', 'M', 'L', 'K' , 'I'};
    int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);

    //board = new char *[m];
    vector<pair<int, int>> avail_pos;
    for (int i = 0; i < m; i++)
    {
        //board[i] = new char[n]; 
        for (int j = 0; j < n; j++)
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

        board[avail_pos[pos1].first][avail_pos[pos1].second] = c;
        board[avail_pos[pos2].first][avail_pos[pos2].second] = c;

        avail_pos.erase(avail_pos.begin() + max(pos1, pos2));

        avail_pos.erase(avail_pos.begin() + min(pos1, pos2));
    }
}

void deleteMemBoard(char** &board, int m, int n)
{
    for (int i = 0; i < m; i++)
        delete[] board[i];
    
    delete[] board;
}

void showBoard(char** board, int row, int column, int cellSize, char** background, int bg_row, int bg_column)
{
    GoTo(0, 0);
    printBg(background, bg_row, bg_column);

    int offset_x = (bg_row - row * cellSize) / 2;
    int offset_y = (bg_column - column*(cellSize + 3)) / 2;
    offset_x = (offset_x < 0) ? 0 : offset_x;
    offset_y = (offset_y < 0) ? 0 : offset_y;
    GoTo(offset_x, offset_y);
    
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            string s;
            s = board[i][j];
            if(board[i][j] != '\0'){
                drawCell(s, offset_x + i*cellSize-i, offset_y + j*(cellSize + 3)-j, cellSize, cellSize + 3);
            }
        }
    }
}