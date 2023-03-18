#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>

using namespace std;

#define SIZE 12

char deathIcon = 'X', aliveIcon = '~';
char board[2][SIZE][SIZE];
int state[SIZE][SIZE]; // 0 = dead, 1 = alive
bool isSelected[SIZE][SIZE];

bool visited[SIZE][SIZE];

int dx[] = {-1, 1, 0, 0},
    dy[] = {0, 0, -1, 1};

struct Point{
    int x, y;
};

Point cur{1, 1};
int cur_NumofSelectedPoint = 0, Max_NumofSelectedPoint = 3;
vector <Point> selectedPoint;
bool isInMap(int x, int y)
{
    return x > 0 && x < SIZE - 1 && y > 0 && y < SIZE - 1;
}


void DFS(Point curPoint, Point destination, int turnNum, int direction, vector <Point> result)
{
    visited[curPoint.x][curPoint.y] = true;
    result.push_back({curPoint.x, curPoint.y});    
  //  if (re)
}

void clear()
{
	system("cls");
}

void displayBoard()
{
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++)
        {
            if (i == cur.x && j == cur.y && isSelected[i][j])
                cout << "\033[37;42m"; // escape sequence
            else if (i == cur.x && j == cur.y)
                cout << "\033[7m"; // white background
            else if (isSelected[i][j])
                cout << "\033[1;32m"; // green text

            cout << board[state[i][j]][i][j] << "\033[0m ";
        }
        cout << endl;
    }
    cout << "Current Position : " << cur.x << " " << cur.y << endl;
}
// rand() & vector.size()a
void getInput() 
{
    char c = getch(); // get direct input
    switch (c){ 
    case 's':
        if (isInMap(cur.x + 1, cur.y))
            cur.x++;
        break;
    case 'd':
        if (isInMap(cur.x, cur.y + 1))
            cur.y++;
        break;
    case 'a':
        if (isInMap(cur.x, cur.y - 1))    
            cur.y--;
        break;
    case 'w':
        if (isInMap(cur.x - 1, cur.y))
            cur.x--;
        break;
    case ' ':
        {
            if (isSelected[cur.x][cur.y] == true) // if already selected
            {
                // Deselect point
                isSelected[cur.x][cur.y] = false;
                cur_NumofSelectedPoint--;
                for (int i = 0; i < selectedPoint.size(); i++)
                    if (selectedPoint[i].x == cur.x && selectedPoint[i].y == cur.y)
                        selectedPoint.erase(selectedPoint.begin() + i);
            }
            else // if not, select that point
            {
                if (cur_NumofSelectedPoint < Max_NumofSelectedPoint) // check if number of selected point exceed the limit
                {
                    isSelected[cur.x][cur.y] = true;
                    cur_NumofSelectedPoint++;
                    selectedPoint.push_back({cur.x, cur.y});
                }
            }
        }
        break;
    }
}

int main()
{
    cout << "This is some \033[7mhighlighted\033[0m text.\n";
    // INIT MAP
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
        {
            board[0][i][j] = deathIcon;
            board[1][i][j] = aliveIcon;
        }
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            state[i][j] = 0;
    for (int i = 1; i < SIZE-1; i++)
        for (int j = 1; j < SIZE-1; j++)
        {
            state[i][j] = 1;
            isSelected[i][j] = false;
        }
    ////////////////////////
    while (true)
    {
            
        displayBoard();
        cout << "current selected Point Pos : ";
        for (int i = 0; i < selectedPoint.size(); i++)
            cout << selectedPoint[i].x << " " << selectedPoint[i].y << endl;
        getInput();
        
        //changeState(x, y, 0);
        clear();
    }
    return 0;
}