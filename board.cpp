#include "board.h"
#include "background.cpp"

void make_board(char board[][MAX], int& m, int& n) {
    srand(time(NULL));
    m = 8;
    n = 8;
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

    for (int i = 0; i < m; i++){
        for (int j = 0; j < (cellSize+2)*n; j++)    //##########
            cout << cellColumnChar;
        cout << endl;

        for (int j = 0; j < n; j++) //#         #
        {
            cout << cellRowChar;
            for (int k = 0; k < cellSize; k++)
                cout << " ";
            cout << cellRowChar;
        }
        cout << endl;

        for (int j = 0; j < n; j++)  //#    char   #
        {
            cout << cellRowChar;
            for (int k = 0; k < (cellSize - 1)/2; k++)
                cout << " ";

            cout << a[i][j];    

            for (int k = 0; k < (cellSize - 1)/2; k++)
                cout << " ";
            cout << cellRowChar;
        }
        cout << endl;

        for (int j = 0; j < n; j++) //#         #
        {
            cout << cellRowChar;
            for (int k = 0; k < cellSize; k++)
                cout << " ";
            cout << cellRowChar;
        }
        cout << endl;

        for (int j = 0; j < (cellSize+2)*n; j++)    //##########
            cout << cellColumnChar;
        cout << endl;
    }
}

int main()
{
    char board[MAX][MAX];
    int row, column;
    int cellSize = 5;
    char cellRowChar = '|';
    char cellColumnChar = '-';
    make_board(board, row, column);

    char** background;
    int bg_row = row, bg_column = column;
    
    getFileContent(background, bg_row, bg_column);

    showBoard(board, row, column, cellSize, cellRowChar, cellColumnChar, background, bg_row, bg_column);

    deleteBg(row, column, background);

    return 0;
}