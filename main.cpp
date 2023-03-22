#include <iostream>
#include <conio.h>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
#include <queue>

#include "board.cpp"
using namespace std;

#define SIZE 12

bool** occupied;
bool isSelected[SIZE][SIZE];
char** board;
int row, col;
bool canMatch = false;

struct Point{
    int x, y;
};

Point cur{0, 0};
int Max_NumofSelectedPoint = 2;
vector <Point> selectedPoint;

void clear()
{
	system("cls");
}

bool isInMap(int x, int y)
{
    return x >= 0 && x < row  && y >= 0 && y < col;
}

void init_board()
{
    cout << "rows : ";
    cin >> row;
    cout << "col : ";
    cin >> col;

    board = new char*[row];
    for (int i = 0; i < row; i++)
        board[i] = new char[col];

    occupied = new bool*[row+2];  // for left, right, top, bottom outline
    for (int i = 0; i < row+2; i++)
        occupied[i] = new bool[col+2];
    
    for (int i = 0; i < row+2; i++)  // set all value to false
        for (int j = 0; j < col+2; j++)
            occupied[i][j] = false;
    
}

void make_board(){
    srand(time(NULL));
    char alphabet[] = {'A', 'G', 'U', 'P', 'V', 'X', 'Z', 'M', 'L'};
    int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);

    vector<pair<int, int>> avail_pos;
    for (int i = 0; i < row; i++) 
        for (int j = 0; j < col; j++)
        {
            // if (i == 0 || i == row || j == 0 || j == col) // board's outline
            //     board[i][j] = ' ';
            // else
            avail_pos.push_back(make_pair(i, j));
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
        occupied[avail_pos[pos1].first + 1][avail_pos[pos1].second + 1] = true; // offset 1 1

        board[avail_pos[pos2].first][avail_pos[pos2].second] = c;
        occupied[avail_pos[pos2].first + 1][avail_pos[pos2].second + 1] = true; // offset 1 1

        avail_pos.erase(avail_pos.begin() + max(pos1, pos2));

        avail_pos.erase(avail_pos.begin() + min(pos1, pos2));
    }
}

// void DFS(Point curPoint, Point destination, int turnNum, vector <string> result, bool visited[][SIZE])
// {
//     clear();
//     if (turnNum > 2 || canMatch == true)
//         return;
//     visited[curPoint.x+1][curPoint.y+1] = true;
//     for (int i = 0; i < row+2; i++){
//         for (int j = 0; j < col+2; j++)
//             cout << visited[i][j];
//         cout << endl;
//     }   
//     cout << endl;
//     this_thread::sleep_for(chrono::seconds(1));
//     if (curPoint.x == destination.x && curPoint.y == destination.y)
//     {
//         canMatch = true;
//         for (int i = 0; i < result.size(); i++)
//             cout << result[i] << " ";
//         this_thread::sleep_for(chrono::seconds(3));
//         return;
//     }
//     for (int i = 0; i < 4; i++)
//     {
//         Point newPos;
//         newPos.x = curPoint.x + dx[i];
//         newPos.y = curPoint.y + dy[i];

//         if (isInMap(newPos.x+1, newPos.y+1) && visited[newPos.x+1][newPos.y+1] == false)
//         {
//             string direction;
//             switch (i){
//                 case 0:
//                     direction = "UP";
//                     break;
//                 case 1:
//                     direction = "DOWN";
//                     break;
//                 case 2:
//                     direction = "LEFT";
//                     break;
//                 case 3:
//                     direction = "RIGHT";
//                     break;
//             }
//             result.push_back(direction);
//             if (result.size() > 0 && direction != result[result.size()-1])
//             {   
//                 cout << "newTurn" << endl;
//                 turnNum++;
//             }
//             DFS(newPos, destination, turnNum, result, visited);
//             visited[curPoint.x+1][curPoint.y+1] = false;      
//             result.pop_back();   
//         }
//     }

// }

vector<pair<int, int>> findPath(int _x, int _y, int x, int y)
{
	//INIT Graph
	vector<vector<int>> e(row + 2, vector<int>(col+ 2, 0));
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			e[i + 1][j + 1] = board[i][j] != '~';
		}
	}
	pair<int, int> s = { _x + 1, _y + 1 };
	pair<int, int> t = { x + 1, y + 1 };

	//BFS
	const int dx[4] = { -1, 0, 1, 0 };
	const int dy[4] = { 0, 1, 0, -1 };
	queue<pair<int, int>> q;
	vector<vector<pair<int, int>>> trace(e.size(), vector<pair<int, int>>(e[0].size(), make_pair(-1, -1)));
	q.push(t);
	trace[t.first][t.second] = make_pair(-2, -2);
	e[s.first][s.second] = 0;
	e[t.first][t.second] = 0;
	while (!q.empty()) {
		pair <int, int> u = q.front();
		q.pop();
		if (u == s) break;
		for (int i = 0; i < 4; ++i) {
			int x = u.first + dx[i];
			int y = u.second + dy[i];
			while (x >= 0 && x < e.size() && y >= 0 && y < e[0].size() && e[x][y] == 0) {
				if (trace[x][y].first == -1){
					trace[x][y] = u;
					q.push({ x, y });
				}
				x += dx[i];
				y += dy[i];
			}
		}
	}

	//trace back
	vector<pair<int, int>> res;
	if (trace[s.first][s.second].first != -1) {
		while (s.first != -2) {
			res.push_back({ s.first - 1, s.second - 1 });
			s = trace[s.first][s.second];
		}
	}
	return res;
}

void checkMatching()
{
    if (selectedPoint.size() < Max_NumofSelectedPoint) // not enough point
        return;
    
    Point s = selectedPoint[0];
    Point f = selectedPoint[1];

    if (board[s.x][s.y] != board[f.x][f.y]) // different character
    {  
        isSelected[s.x][s.y] = false;
        isSelected[f.x][f.y] = false;
        selectedPoint.clear();
        return;
    }

    bool visited[SIZE][SIZE];
    // visited = new bool*[row+2];  // for left, right, top, bottom outline
    // for (int i = 0; i < row+2; i++)
    //     visited[i] = new bool[col+2];
    
    for (int i = 0; i < row+2; i++)
        for (int j = 0; j < col+2; j++)
            visited[i][j] = occupied[i][j];

    visited[f.x+1][f.y+1] = false;

    for (int i = 0; i < row+2; i++){
        for (int j = 0; j < col+2; j++)
            cout << visited[i][j];
        cout << endl;
    }

    vector <pair<int, int>> res;
    res = findPath(s.x, s.y, f.x, f.y);
    for (int i = 0; i < res.size(); i++)
        cout << res[i].first << " " << res[i].second << endl;
    this_thread::sleep_for(chrono::seconds(3));
    // vector <string> result;
    // DFS(s, f, 0, result , visited);
    // for (int i = 0; i < row+2; i++)
    //     delete visited[i];
    
    // delete visited;
    if (res.size() <= 4 && res.size() >= 2)
    {
        board[s.x][s.y] = '\0';
        board[f.x][f.y] = '\0';
        occupied[s.x+1][s.y+1] = false;
        occupied[f.x+1][f.y+1] = false;
        //canMatch = false;
    }
    isSelected[s.x][s.y] = false;
    isSelected[f.x][f.y] = false;

    selectedPoint.clear();
}



// void displayBoard()
// {
//     for (int i = 0; i < row; i++){
//         for (int j = 0; j < col; j++)
//         {
//             if (i == cur.x && j == cur.y && isSelected[i][j])
//                 cout << "\033[37;42m"; // escape sequence
//             else if (i == cur.x && j == cur.y)
//                 cout << "\033[7m"; // white background
//             else if (isSelected[i][j])
//                 cout << "\033[1;32m"; // green text

//             cout << board[i][j] << "\033[0m ";
//         }
//         cout << endl;
//     }
//     cout << "Current Position : " << cur.x << " " << cur.y << endl;
//     cout << "current select point :" << endl;
//         for (int i = 0; i < selectedPoint.size(); i++)
//             cout << selectedPoint[i].x << " " << selectedPoint[i].y << endl;
//     for (int i = 0; i < row+2; i++){
//         for (int j = 0; j < col+2; j++)
//             cout << occupied[i][j];
//         cout << endl;
//     }
// }
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
            if (occupied[cur.x+1][cur.y+1] == true) // if the cur cell has block
            {
                if (isSelected[cur.x][cur.y] == true) // if already selected
                {
                    // Deselect point
                    isSelected[cur.x][cur.y] = false;
                    for (int i = 0; i < selectedPoint.size(); i++)
                        if (selectedPoint[i].x == cur.x && selectedPoint[i].y == cur.y)
                            selectedPoint.erase(selectedPoint.begin() + i);
                }
                else // if not, select that point
                {
                    if (selectedPoint.size() < Max_NumofSelectedPoint) // check if number of selected point exceed the limit
                    {
                        isSelected[cur.x][cur.y] = true;
                        selectedPoint.push_back({cur.x, cur.y});
                    }
                }
            }
        }
        break;
    }
}

int main()
{
    init_board();
    make_board();

    char** background;
    int bg_row = row, bg_column = col;
    getFileContent(background, bg_row, bg_column, 5);

    while (true)
    {
        checkMatching();
        //displayBoard();
        showBoard(board, row, col, 5, background, bg_row, bg_column);
//GoTo(50, 10);
        cout << cur.x << " " << cur.y << endl;
        getInput();
        
        clear();
    }
    return 0;
}