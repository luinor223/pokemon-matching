#include "gameAlgorithms.h"

bool isInMap(GameState game, int x, int y)
{
    return x >= 0 && x < game.row  && y >= 0 && y < game.col;
}

vector<pair<int, int>> findPath(GameState game, int _x, int _y, int x, int y)
{
	//INIT Graph
	vector<vector<int>> e(game.row + 2, vector<int>(game.col+ 2, 0));
	for (int i = 0; i < game.row; ++i)
	{
		for (int j = 0; j < game.col; ++j)
		{
			e[i + 1][j + 1] = game.board[i][j] != '\0';
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
            s = '_'; 
    cout << "AAAAAAAA";
        drawLine(res[i-1].first + offset_x + res[i-1].first*cellSize, res[i-1].second + offset_y + res[i-1].second*(cellSize+3), 
                res[i].first + offset_x + res[i].first*cellSize, res[i].second + offset_y + res[i].second*(cellSize+3), s);
    }
}

void checkMatching(GameState game, char** background, int bg_row, int bg_column, int offset_x, int offset_y)
{
    if (selectedPoint.size() < Max_NumofSelectedPoint) // not enough point
        return;
    
    Point s = selectedPoint[0];
    Point f = selectedPoint[1];

    if (game.board[s.x][s.y] != game.board[f.x][f.y]) // different character
    {  
        clear();
        showBoard(game, background, bg_row, bg_column);
        selectedPoint.clear();
        return;
    }


    vector <pair<int, int>> res;
    res = findPath(game, s.x, s.y, f.x, f.y);

    if (res.size() <= 4 && res.size() >= 2) // valid
    {
        //drawMatchingLine(res, offset_x, offset_y, cellSize);
        //this_thread::sleep_for(chrono::seconds(2));

        game.board[s.x][s.y] = '\0';
        game.board[f.x][f.y] = '\0';
        clear();
        showBoard(game, background, bg_row, bg_column);
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

void drawSelectedPoint(GameState game, vector <Point> selectedPoint, int offset_x, int offset_y)
{
    string temp; // to convert char to string for drawCell function
    for (int i = 0; i < selectedPoint.size(); i++)
    {
        int x = selectedPoint[i].x;
        int y = selectedPoint[i].y;
        temp = game.board[x][y];
        drawCell(temp, offset_x + x*game.cellSize-x, offset_y + y*(game.cellSize+3)-y, game.cellSize, game.cellSize + 3, 11, 7);
    }
}

void drawSelectingPoint(GameState game, int x, int y, int offset_x, int offset_y)
{ 
    string temp;
    int mode;
    temp = game.board[cur.x][cur.y];
    if (game.board[cur.x][cur.y] == '\0')
        mode = 1;
    else
        mode = 0;
    drawCell(temp, offset_x + cur.x*game.cellSize - cur.x, offset_y + cur.y*(game.cellSize + 3) - cur.y, game.cellSize, game.cellSize + 3, 0, 7, mode); // deselect the old cell

    if (isInMap(game, cur.x + x, cur.y + y)) 
    {
        cur.x += x;
        cur.y += y;
    } 

    temp = game.board[cur.x][cur.y];
    if (game.board[cur.x][cur.y] == '\0')
        mode = 1;
    else
        mode = 0;
    drawCell(temp, offset_x + cur.x*game.cellSize - cur.x, offset_y + cur.y*(game.cellSize + 3) - cur.y, game.cellSize, game.cellSize + 3, 7, 0, mode); // select the new one
}

void playerAction(GameState game, int  offset_x, int offset_y, int &page) 
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
            if (game.board[cur.x][cur.y] != '\0') // if the cur cell has block
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
    case 27: //Esc = 27
        page = 1;
    }
    if (x != 0 || y != 0) // there is a movement input
        drawSelectingPoint(game, x, y, offset_x, offset_y);
}