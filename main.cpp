//#include "main.h"
#include "header.h"

bool isInMap(int x, int y)
{
    return x >= 0 && x < row  && y >= 0 && y < col;
}


vector<pair<int, int>> findPath(char** board, int _x, int _y, int x, int y)
{
	//INIT Graph
	vector<vector<int>> e(row + 2, vector<int>(col+ 2, 0));
	for (int i = 0; i < row; ++i)
	{
		for (int j = 0; j < col; ++j)
		{
			e[i + 1][j + 1] = board[i][j] != '\0';
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

void drawMatchingLine(vector <pair <int, int> > res, int offset_x, int offset_y, int cellSize)
{
    for (int i = 1; i < res.size(); i++)
    {
        int diff_x = res[i].first - res[i-1].first;
        int diff_y = res[i].second - res[i-1].second;
        string s;
        if (diff_x != 0) // vertical change
            s = "|";
        else // horizontal change
            s = '-'; 

        drawCell(s, offset_x + res[i].first*cellSize - res[i].first, offset_y + res[i].second*(cellSize+2) - res[i].second, diff_y, diff_x);
    }
}

void checkMatching(char** board, char** background, int bg_row, int bg_column, int offset_x, int offset_y, int cellSize)
{
    if (selectedPoint.size() < Max_NumofSelectedPoint) // not enough point
        return;
    
    Point s = selectedPoint[0];
    Point f = selectedPoint[1];

    if (board[s.x][s.y] != board[f.x][f.y]) // different character
    {  
        clear();
        showBoard(board, row, col, 5, background, bg_row, bg_column);
        selectedPoint.clear();
        return;
    }


    vector <pair<int, int>> res;
    res = findPath(board, s.x, s.y, f.x, f.y);
    // for (int i = 0; i < res.size(); i++)
    //     cout << res[i].first << " " << res[i].second << endl;
    

    if (res.size() <= 4 && res.size() >= 2) // valid
    {
        //drawMatchingLine(res, offset_x, offset_y, cellSize);
        this_thread::sleep_for(chrono::seconds(0));
        board[s.x][s.y] = '\0';
        board[f.x][f.y] = '\0';
        clear();
        showBoard(board, row, col, 5, background, bg_row, bg_column);
        while (board[cur.x][cur.y] == '\0') // random until the cur pos is not empty cell
        {
            cur.x = rand() % row;
            cur.y = rand() % col;
        }
    }
    selectedPoint.clear();
}



bool findPoint(vector <Point> v, Point a)
{
    for (int i = 0; i < v.size(); i++)
        if (v[i].x == a.x && v[i].y == a.y)
            return true;
    return false; 
}

void drawSelectedPoint(char** board, vector <Point> selectedPoint, int offset_x, int offset_y, int cellSize)
{
    string temp; // to convert char to string for drawCell function
    for (int i = 0; i < selectedPoint.size(); i++)
    {
        int x = selectedPoint[i].x;
        int y = selectedPoint[i].y;
        temp = board[x][y];
        drawCell(temp, offset_x + x*cellSize-x, offset_y + y*(cellSize+2)-y, cellSize, cellSize + 3, 11, 7);
    }
}

void drawNewCurrentSelectedPoint(char** board, int x, int y, int offset_x, int offset_y, int cellSize)
{ 
    Point original = cur;
    do 
    {
        cur.x += x;
        cur.y += y;
    } while (isInMap(cur.x, cur.y) && board[cur.x][cur.y] == '\0');

    if (isInMap(cur.x, cur.y) == true) 
    {
        string temp;
        temp = board[original.x][original.y];
        drawCell(temp, offset_x + original.x*cellSize - original.x, offset_y + original.y*(cellSize + 3) - original.y, cellSize, cellSize + 3); // deselect the old cell

        temp = board[cur.x][cur.y];
        drawCell(temp, offset_x + cur.x*cellSize - cur.x, offset_y + cur.y*(cellSize + 3) - cur.y, cellSize, cellSize + 3, 7, 0); // select the new one
    }
    else // no more cell avaliable, return to the orginal position
        cur = original;
    

}

void playerAction(char** board, int  offset_x, int offset_y, int cellSize) 
{
    char c = getch(); // get direct input
    int x = 0, y = 0;
    switch (c){ 
    case 's':
        x = 1;
        break;
    case 'd':
        y = 1;
        break;
    case 'a':
        y = -1;
        break;
    case 'w':
        x = -1;
        break;
    case ' ':
        {
            if (board[cur.x][cur.y] != '\0') // if the cur cell has block
            {
                if (findPoint(selectedPoint, cur) == true) // if already selected
                {
                    // Deselect point
                    for (int i = 0; i < selectedPoint.size(); i++)
                        if (selectedPoint[i].x == cur.x && selectedPoint[i].y == cur.y)
                            selectedPoint.erase(selectedPoint.begin() + i);
                }
                else // if not, select that point
                {
                    if (selectedPoint.size() < Max_NumofSelectedPoint) // check if number of selected point exceed the limit
                    {
                        selectedPoint.push_back({cur.x, cur.y});
                    }
                }
            }
        }
        break;
    }
    if (x != 0 || y != 0) // there is a movement input
        drawNewCurrentSelectedPoint(board, x, y, offset_x, offset_y, cellSize);
}

int main()
{
    char** board;
    init_board(board);
    make_board(board, row, col);
    SetWindowSize(400, 400);

    char** background;
    int bg_row = row, bg_column = col;
    getFileContent(background, bg_row, bg_column, 5);

    int cellSize = 5;
    int board_offset_x = (bg_row - row * cellSize) / 2;
    int board_offset_y = (bg_column - col*(cellSize + 3)) / 2;
    showBoard(board, row, col, 5, background, bg_row, bg_column);
    while (true)
    {
        checkMatching(board, background, bg_row, bg_column, board_offset_x, board_offset_y, cellSize);
        drawSelectedPoint(board, selectedPoint, board_offset_x, board_offset_y, cellSize);
        drawNewCurrentSelectedPoint(board, 0, 0, board_offset_x, board_offset_y, cellSize);
        //showBoard(board, row, col, 5, background, bg_row, bg_column);
        playerAction(board, board_offset_x, board_offset_y, cellSize);
    }

    deleteBg(bg_row, bg_column, background);
    deleteMemBoard(board, row, col);
    return 0;
}