#include "board.h"
#include "background.cpp"

void make_board(char board[][MAX], int& m, int& n) {
    srand(time(NULL));
    char alphabet[] = {'A', 'G', 'U', 'P', 'V', 'X', 'Z', 'M', 'L'};
    int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);

    std::vector<std::pair<int, int>> avail_pos;
    for (int i = 0; i < m; i++) 
        for (int j = 0; j < n; j++) 
                avail_pos.push_back(std::make_pair(i, j));

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

//, char** background, int mb, int nb
//Display board to the monitor (cellSize must be odd)
void showBoard(char a[][MAX], int m, int n, int cellSize, char cellRowChar, char cellColumnChar, char** background, int mb, int nb)
{
    int current_bgx, current_bgy;
    for (int i = 0; i < (mb - m * cellSize)/2; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            cout << background[i][j];
            current_bgy = j;
        }
        current_bgx = i;
        cout << endl;
    }

    for (int i = 0; i < m; i++)
    {
        //Hàng đầu tiên của cell
        current_bgx ++;
        for(int j = 0; j < (nb - n*(cellSize + 2)) / 2; j++)  //Xuất background bên trái của hàng
        {
            cout << background[current_bgx][j];
            current_bgy = j;
        }
        for (int j = 0; j < n; j++)    //Xuất hàng cuối của cell: -------
        {
            if(a[i][j] != '\0')
            {
                for(int k = 0; k < cellSize + 2; k++)
                    cout << cellColumnChar;
            }
            else
            {
                for (int k = 0; k < (cellSize+2); k++)
                {
                    cout << background[current_bgx][current_bgy++];
                }   
            }
        }
        for (int j = (nb + n*(cellSize + 2)) / 2; j < nb; j++) //Xuất background bên phải của hàng
            cout << background[current_bgx][j];
        cout << endl;

        //Hàng thứ 2 của cell
        current_bgx ++;
        for(int j = 0; j < (nb - n*(cellSize + 2)) / 2; j++) //Xuất background bên trái của hàng
        {
            cout << background[current_bgx][j];
            current_bgy = j+1;
        }
        for (int j = 0; j < n; j++) //Xuất hàng thứ 2 của cell: |         |
        {
            if (a[i][j] != '\0')
            {
                cout << cellRowChar;
                for (int k = 0; k < cellSize; k++)
                    cout << " ";
                cout << cellRowChar;
            }
            else
            {
                for (int k = 0; k < (cellSize+2); k++)
                {
                    cout << background[current_bgx][current_bgy++];
                }   
            }
        }
        for (int j = (nb + n*(cellSize + 2)) / 2; j < nb; j++) //Xuất background bên phải của hàng
            cout << background[current_bgx][j];
        cout << endl;

        //Hàng thứ 3 của cell
        current_bgx ++;
        for(int j = 0; j < (nb - n*(cellSize + 2)) / 2; j++) //Xuất background bên trái của hàng
        {
            cout << background[current_bgx][j];
            current_bgy = j+1;
        }
        for (int j = 0; j < n; j++)  //Xuất hàng giữa (có chứa kí tự) của cell: |    char   |
        {
            if(a[i][j] != '\0')
            {
                cout << cellRowChar;
                for (int k = 0; k < (cellSize - 1)/2; k++)
                    cout << " ";

                cout << a[i][j];    

                for (int k = 0; k < (cellSize - 1)/2; k++)
                    cout << " ";
                cout << cellRowChar;
            }
            else
            {
                for (int k = 0; k < (cellSize+2); k++)
                {
                    cout << background[current_bgx][current_bgy++];
                }
            }
            
        }
        for (int j = (nb + n*(cellSize + 2)) / 2; j < nb; j++) //Xuất background bên phải của hàng
            cout << background[current_bgx][j];
        cout << endl;
        
        //Hàng kề cuối của cell
        current_bgx ++;
        for(int j = 0; j < (nb - n*(cellSize + 2)) / 2; j++) //Xuất background bên trái của hàng
        {
            cout << background[current_bgx][j];
            current_bgy = j+1;
        }
        for (int j = 0; j < n; j++) //Xuất hàng kề cuối của cell: |         |
        {
            if (a[i][j] != '\0')
            {
                cout << cellRowChar;
                for (int k = 0; k < cellSize; k++)
                    cout << " ";
                cout << cellRowChar;
            }
            else
            {
                for (int k = 0; k < (cellSize+2); k++)
                {
                    cout << background[current_bgx][current_bgy++];
                }   
            }
        }
        for (int j = (nb + n*(cellSize + 2)) / 2; j < nb; j++) //Xuất background bên phải của hàng
            cout << background[current_bgx][j];
        cout << endl;

        //Hàng cuối cùng của cell
        current_bgx ++;
        for(int j = 0; j < (nb - n*(cellSize + 2)) / 2; j++) //Xuất background bên trái của hàng
        {
            cout << background[current_bgx][j];
            current_bgy = j+1;
        }
        for (int j = 0; j < n; j++)    //Xuất hàng cuối của cell: -------
        {
            if(a[i][j] != '\0')
            {
                for(int k = 0; k < cellSize + 2; k++)
                    cout << cellColumnChar;
            }
            else
            {
                for (int k = 0; k < (cellSize+2); k++)
                {
                    cout << background[current_bgx][current_bgy++];
                }   
            }
        }
        for (int j = (nb + n*(cellSize + 2)) / 2; j < nb; j++) //Xuất background bên phải của hàng
            cout << background[current_bgx][j];
        cout << endl;
    }

    current_bgx++;
    for (int i = current_bgx; i < mb; i++)
    {
        for (int j = 0; j < nb; j++)
        {
            cout << background[i][j];
        }
        cout << endl;
    }
}

int main()
{
    char board[MAX][MAX];
    int row = 4, column = 4;
    int cellSize = 5;
    char cellRowChar = '|';
    char cellColumnChar = '-';
    make_board(board, row, column);

    char** background;
    int bg_row = row, bg_column = column;

    // background = new char *[5*(bg_row+2)];
    // for (int i = 0; i < 5 * (bg_row + 2); i++)
    //     background[i] = new char[7 * (bg_column + 2)];
    
    getFileContent(background, bg_row, bg_column);

    int max_turns = 20;
    int turn = 0;
    while (turn < max_turns)
    {
        showBoard(board, row, column, cellSize, cellRowChar, cellColumnChar, background, bg_row, bg_column);
    
        cout << "Nhap o muon xoa: ";
        int x, y;
        cin >> x >> y;
        board[x][y] = '\0';
        turn;
    }

    deleteBg(row, column, background);

    return 0;
}
