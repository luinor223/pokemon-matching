#include "main.h"
#include "board.h"
#include "background.cpp"
#include "console.cpp"

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

// void drawCell(char a, int x, int y, int cellSize, char cellRowChar, char cellColumnChar, int backgourdColor, int outlineColor )
// {
//     for (int i = 0; i < cellSize; i++)
//     {
//         GoTo(x+i, y);
//         for (int j = 0; j < cellSize; j++)
//         {
//             if (i == 0 || i == cellSize-1)
//                 cout << cellColumnChar;
//             else if (j == 0 || j == cellSize-1) 
//                 cout << cellRowChar;
//             else if (i == j && i == cellSize / 2)
//                 cout << a;
//             else
//             {
//                 SetColor(backgourdColor, 7);
//                 cout << " ";
//                 SetColor(0, 7);
//             }
//         }
//     }
// }

void drawCell(string text, int x, int y, int cellSizeRow, int cellSizeColumn, int bg_color, int text_color)
{
    // Create a separate wcout stream object
    //std::wostream& wcout = std::wcout;

    // Set the output mode to Unicode for the wcout object
    _setmode(_fileno(stdout), _O_U16TEXT);

    for (int i = 0; i < cellSizeRow; i++)
    {
        GoTo(x+i, y);
        for (int j = 0; j < cellSizeColumn; j++)
        {
            if (i == 0 && j == 0) 
                wcout << L"\u250C";
            else if (i == 0 && j == cellSizeColumn - 1)
                wcout << L"\u2510";
            else if (i == cellSizeRow - 1 && j == 0)
                wcout << L"\u2514";
            else if (i == cellSizeRow - 1 && j == cellSizeColumn - 1)
                wcout << L"\u2518";
            else if (i == 0 || i == cellSizeRow-1)
                wcout << L"\u2500";
            else if (j == 0 || j == cellSizeColumn-1) 
                wcout << L"\u2502";
            else
            {
                SetColor(bg_color, text_color);
                wcout << " ";
                SetColor(0, 7);
            }
        }
    }
    // Set the output mode back to ASCII for stdout
    _setmode(_fileno(stdout), _O_TEXT);

    GoTo(x + cellSizeRow / 2 , y + (cellSizeColumn - text.length()) / 2);
    SetColor(bg_color, text_color);
    cout << text;
    SetColor(0, 7);
}

void showBoard(char** board, int row, int column, int cellSize, char** background, int bg_row, int bg_column)
{
    GoTo(0, 0);
    printBg(background, bg_row, bg_column);
    int offset_x = (bg_row - row * cellSize) / 2;
    int offset_y = (bg_column - column*cellSize) / 2;
    offset_x = (offset_x < 0) ? 0 : offset_x;
    offset_y = (offset_y < 0) ? 0 : offset_y;
    GoTo(offset_x, offset_y);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            // if (cur.x == i && cur.y == j)
            //     SetColor(7, 0);
            string s;
            s = board[i][j];
            if(board[i][j] != '\0'){
                drawCell(s, offset_x + i*cellSize-i, offset_y + j*(cellSize+2)-j, cellSize, cellSize + 2);
                if(i== cur.x && j == cur.y)
                    drawCell(s, offset_x + i*cellSize-i, offset_y + j*(cellSize+2)-j, cellSize, cellSize + 2, white, black);
            }
            //SetColor(0, 0);
        }
    }
}

// int main()
// {
//     // char** board;
//     // int row = 6, column = 8;
//     // int cellSize = 5;
//     // char cellRowChar = '|';
//     // char cellColumnChar = '-';
//     // make_board(board, row, column);

//     // char** background;
//     // int bg_row = row, bg_column = column;
    
//     // getFileContent(background, bg_row, bg_column, cellSize);

//     // int max_turns = 20;
//     // int turn = 0;
//     // system("cls");
//     // while (turn < max_turns)
//     // {
//     //     showBoard(board, row, column, cellSize, background, bg_row, bg_column);
    
//     //     cout << "Nhap o muon xoa: ";
//     //     int x, y;
//     //     cin >> x >> y;
//     //     board[x][y] = '\0';
//     //     turn;
//     // }

//     // deleteMemBoard(board, row, column);
//     // deleteBg(row, column, background);

//     // return 0;
// }

