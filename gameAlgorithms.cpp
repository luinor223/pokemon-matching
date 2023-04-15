#include "gameAlgorithms.h"

// This function checks if a given position (x, y) is inside the game board.
bool isInMap(GameState game, int x, int y)
{
    return x >= 0 && x < game.row  && y >= 0 && y < game.col;
}

// This function finds a path between two given positions (x1, y1) and (x2, y2) on the game board.
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
		for (int i = 0; i < 4; ++i){
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
	if (trace[s.first][s.second].first != -1){
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
        int mode;
        int diff_x = res[i].first - res[i-1].first;
        int diff_y = res[i].second - res[i-1].second;
        string s;
        if (diff_x != 0) // vertical change
            mode = 0;
        else // horizontal change
            mode = 1; 
        drawLine(offset_x + res[i-1].first*(cellSize-1) + (cellSize/2), offset_y + res[i-1].second*(cellSize+3-1) + ((cellSize+2)/2), 
                 offset_x + res[i].first*(cellSize-1) + (cellSize/2) , offset_y + res[i].second*(cellSize+3-1) + ((cellSize+2)/2) , mode);
    }
}

bool checkMatching(GameState game, char** background, int bg_row, int bg_column, int offset_x, int offset_y)
{
    if (selectedPoint.size() < Max_NumofSelectedPoint) // not enough point
        return false;
    
    Point s = selectedPoint[0];
    Point f = selectedPoint[1];

    string temp;
    temp = game.board[s.x][s.y];
    drawCell(temp, offset_x + s.x*(game.cellSize - 1), offset_y + s.y*(game.cellSize + 2), game.cellSize, game.cellSize + 3); // deselecting starting cell
    
    temp = game.board[f.x][f.y];
    drawCell(temp, offset_x + f.x*(game.cellSize  - 1), offset_y + f.y*(game.cellSize + 2), game.cellSize, game.cellSize + 3); // deselecting ending cell

    if (game.board[s.x][s.y] != game.board[f.x][f.y]) // different character
    {
        selectedPoint.clear();
        return false;
    }

    vector <pair<int, int>> res;
    res = findPath(game, s.x, s.y, f.x, f.y);

    if (res.size() <= 4 && res.size() >= 2) // valid path
    {
        // show matching line
        drawMatchingLine(res, offset_x, offset_y, game.cellSize);
        this_thread::sleep_for(200ms);

        // delete both cell
        game.board[s.x][s.y] = '\0';
        game.board[f.x][f.y] = '\0';

        setBoard(game); // indent mode

        selectedPoint.clear();
        return true;
    }
    selectedPoint.clear();
    return false;
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
        drawCell(temp, offset_x + x*game.cellSize-x, offset_y + y*(game.cellSize+3)-y, game.cellSize, game.cellSize + 3, yellow, white);
    }
}

void drawSelectingPoint(GameState &game, int x, int y, int offset_x, int offset_y, char** background)
{
    // deselecting the old cell
    string temp;
    int mode;
    temp = game.board[game.cur.x][game.cur.y];
    if (game.board[game.cur.x][game.cur.y] == '\0')
    {
        int startX = offset_x + game.cur.x*game.cellSize - game.cur.x;
        int startY = offset_y + game.cur.y*(game.cellSize + 3) - game.cur.y;
        for (int i = 1; i < game.cellSize-1; i++)
        {
            GoTo(startX + i, startY + 1);
            for (int j = 1; j <  game.cellSize + 2; j++)
            {
                cout << background[startX + i - 3][startY + j - 7];
            }
        }
    }
    else 
        drawCell(temp, offset_x + game.cur.x*game.cellSize - game.cur.x, offset_y + game.cur.y*(game.cellSize + 3) - game.cur.y, game.cellSize, game.cellSize + 3, white, black, 0);
        
    // move the cursor
    if (isInMap(game, game.cur.x + x, game.cur.y + y)) 
    {
        game.cur.x += x;
        game.cur.y += y;
    } 
    else
    {
        if (game.cur.x + x >= game.row)
            game.cur.x = 0;
        else if (game.cur.x + x < 0)
            game.cur.x = game.row - 1;
        else if (game.cur.y + y >= game.col)
            game.cur.y = 0;
        else if (game.cur.y + y < 0)
            game.cur.y = game.col - 1;
    }
    // selecting the new cell
    temp = game.board[game.cur.x][game.cur.y];
    if (game.board[game.cur.x][game.cur.y] == '\0')
        mode = 1;
    else
        mode = 0;
    
    drawCell(temp, offset_x + game.cur.x*game.cellSize - game.cur.x, offset_y + game.cur.y*(game.cellSize + 3) - game.cur.y, game.cellSize, game.cellSize + 3, grey, white, mode); // select the new one
}


bool moveSuggestion(GameState game, int offset_x, int offset_y, bool draw) // draw == true: hint the player for a possible match
{                 
    // Idea: for each element in the board, find cells similar to its character to check for a valid path                                                         // draw == false: only check the possible match
    for (int startX = 0; startX < game.row; startX++)
    {
        for (int startY = 0; startY < game.col; startY++)
        {
            // now compare game.board[startX][startY] to all the rest of the board
            for (int i = 0; i < game.row; i++)
            {
                for (int j = 0; j < game.col; j++)
                {
                    if (i == startX && j == startY) // currently checking the same cell
                        continue;
                    if (game.board[startX][startY] != game.board[i][j]) // 2 cells have different character
                        continue;
                    if (game.board[i][j] == '\0') // empty cell
                        continue;

                    // if not all of the above, check the path between 2 cell
                    vector <pair <int, int> > res;
                    res = findPath(game, startX, startY, i, j);

                    if (res.size() <= 4 && res.size() >= 2) // valid path
                    {
                        string temp1, temp2;
                        temp1 = game.board[startX][startY];
                        temp2 = game.board[i][j];

                        if (draw == true) 
                        {
                            // highlight the cells with green color
                            drawCell(temp1, offset_x + startX*game.cellSize - startX, offset_y + startY*(game.cellSize + 3) - startY, game.cellSize, game.cellSize + 3, 10, 0);
                            drawCell(temp2, offset_x + i*game.cellSize - i, offset_y + j*(game.cellSize + 3) - j, game.cellSize, game.cellSize + 3, 10, 0);
                        }
                        return true;
                    }

                }
            }
        }
    }
    return false;
}

void playerAction(GameState &game,savefile &account, int  offset_x, int offset_y, int &page, char** background, char bg_row, char bg_column, int cheatWordsCount[]) 
{
    char c = getch(); // get direct input

    /*Check if player enter the right cheat code*/
    if (checkCheatCode(c, cheatWordsCount[0], Cheat_shuffle))
        game.shuffle_count += 3;
    if (checkCheatCode(c, cheatWordsCount[1], Cheat_help))
        game.help_count += 3;
    if (checkCheatCode(c, cheatWordsCount[2], Cheat_score))
        game.score += 1000;
    if (checkCheatCode(c, cheatWordsCount[3], Cheat_time))
        game.total_time += bouns_time;

    /*Handle player's input*/
    int x = 0, y = 0;
    switch (c){ 
    case 's':
        PlaySound(TEXT("SoundSFX/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        x = 1;
        break;
    case 'd':
        PlaySound(TEXT("SoundSFX/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        y = 1;
        break;
    case 'a':
        PlaySound(TEXT("SoundSFX/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        y = -1;
        break;
    case 'w':
        PlaySound(TEXT("SoundSFX/move.wav"), NULL, SND_FILENAME | SND_ASYNC);
        x = -1;
        break;
    case ' ':   //Select/Unselect the cell
        {
            if (game.board[game.cur.x][game.cur.y] != '\0') // if the cur cell has block
            {
                if (findPoint(selectedPoint, game.cur) == true) // if already selected
                {
                    // Deselect point
                    for (int i = 0; i < selectedPoint.size(); i++)
                        if (selectedPoint[i].x == game.cur.x && selectedPoint[i].y == game.cur.y)
                            selectedPoint.erase(selectedPoint.begin() + i);
                }
                else // if not, select that point
                {
                    if (selectedPoint.size() < Max_NumofSelectedPoint) // check if number of selected point exceed the limit
                    {
                        selectedPoint.push_back({game.cur.x, game.cur.y});
                    }
                }
            }
        }
        break;
    case 'h':   //Move suggestion
        if (game.help_count > 0)
        {
            game.help_count--;
            moveSuggestion(game, offset_x, offset_y, true);
        }
        break;
    case 'r':   //Shuffle the board
        if (game.shuffle_count > 0)
        {
            game.shuffle_count--;
            shuffle_board(game);
            showBoard(game, background, bg_row, bg_column, offset_x, offset_y); //show the new board
        }
        break;
    case 'p':   //Save game
        page = save_page;
        break;
    case 27: //Esc = 27
        game.score = 0;
        game.mode = 1;
        game.stage = 1;
        game.help_count = 3;
        game.shuffle_count = 3;
        page = main_page;
        sortRecord(account.record, 5);
        break;
    }
    if (x != 0 || y != 0) // there is a movement input
        drawSelectingPoint(game, x, y, offset_x, offset_y, background);
}