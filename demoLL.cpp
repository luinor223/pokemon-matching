#include <iostream>
#include <string>
#include "main.h"
#include "header.h"

using namespace std;


const int MAX_SIZE = 20;

struct Node{
    char key;
    Node* p_next;
};

struct List{
    Node* p_head;
    Node* p_tail;
};

struct PointLL{
    int x, y;
    int LL_x, LL_y;
};

Node* createNode(char data)
{
    Node* p = new Node;
    p->key = data;
    p->p_next = NULL;
    return p;
}

void addHead(List &lst, char data)
{
    Node *p = createNode(data);
    if (lst.p_head == NULL)
        lst.p_head = lst.p_tail = p;
    else
    {
        p->p_next = lst.p_head;
        lst.p_head = p; 
    }
    
}

void addTail(List &lst, char data)
{
    Node* p = createNode(data);
    if (lst.p_head == NULL)
        lst.p_head = lst.p_tail = p;
    else
    {
        lst.p_tail->p_next = p;
        lst.p_tail = p;
    }
}

void removeHead(Node* &pHead)
{
    if (pHead == NULL)
        return;
    Node* temp = pHead;
    pHead = pHead->p_next;
    delete temp;
}

void removeTail(Node* &pHead)
{
    if (pHead == NULL)
        return;
    if (pHead->p_next == NULL)
    {
        pHead = NULL;
        return;
    }

// find the second last node: EX: 1 -> 3 -> 4 -> NULL  => second last node: 3
    Node* second_last = pHead;
    while (second_last->p_next->p_next != NULL)
        second_last = second_last->p_next;
    
    Node* lastNode = second_last->p_next;
    delete lastNode;
    second_last->p_next = NULL;
}

void removeAll(Node* &pHead)
{
    Node* it = pHead;
    pHead = NULL;
    it = it->p_next;
    while (it != NULL)
    {
        Node* temp = it;
        it = it->p_next;
        delete temp;
    }
}

bool addPos(Node* &pHead, int data, int pos){
    if (pos < 0)
        return false;

    int count = 0;
    Node* d = createNode(data);
    Node* it = pHead;
    while (it != NULL && count < pos)
    {
        it = it->p_next;
        count++;
    }
    Node* temp = it->p_next;
    it->p_next = d;
    d->p_next = temp;
    return true;
}

bool inMap(int x, int y, int row, int col)
{
    return x >= 0 && x < row && y >= 0 && y < col;
}

char getAt(List& lst, int index)
{
    if (lst.p_head == NULL)
        return '\0';
    int count = 0;
    Node* it = lst.p_head;
    while (count++ != index && it->p_next != NULL)
    {
        it = it->p_next;
    }
    if (count <= index)
        return '\0';
    return it->key;
}

void initList(List &lst)
{
    // Node* temp = createNode('0');
    // lst.p_head = temp;
    // int count = 0;
    // while (count++ < size)
    // {
    //     Node* newNode = createNode('0');
    //     temp->p_next = newNode;
    //     temp = temp->p_next;
    // }
    // lst.p_tail = temp;
    lst.p_head = NULL;
    lst.p_tail = NULL;
}

void deleteNodeAt(List& lst, int index)
{
    if (lst.p_head == NULL)
        return;
    if (index == 0)
    {
        removeHead(lst.p_head);
        return;
    }
    int count = 0;
    Node* it = lst.p_head;
    while (count++ != index - 1 && it->p_next != NULL)
    {
        it = it->p_next;
    }
    if (count < index - 1)
        return;
    if (it->p_next == NULL)
        return;
    
    Node* temp = it->p_next;
    it->p_next = temp->p_next;
    delete temp;
}

void make_boardLL(char** &board, int row, int col) {
    char alphabet[] = {'A', 'G', 'U', 'P', 'V', 'X', 'Z', 'M', 'L', 'K' , 'I'};
    int alphabet_size = sizeof(alphabet) / sizeof(alphabet[0]);

    board = new char *[row];
    vector<pair<int, int>> avail_pos;
    for (int i = 0; i < row; i++)
    {
        board[i] = new char[col]; 
        for (int j = 0; j < col; j++)
        {
            avail_pos.push_back(make_pair(i, j));
        } 
    }  

    const int pairs = avail_pos.size() / 2;
    for (int i = 0; i < pairs; i++) {
        char c = alphabet[rand() % alphabet_size];

        int pos1 = rand() % avail_pos.size();
        int pos2;
        do { 
            pos2 = rand() % avail_pos.size(); // select next position
        } while (pos1 == pos2); // if same position is selected

        board[avail_pos[pos1].first][avail_pos[pos1].second] = c;
        board[avail_pos[pos2].first][avail_pos[pos2].second] = c;

        avail_pos.erase(avail_pos.begin() + max(pos1, pos2));

        avail_pos.erase(avail_pos.begin() + min(pos1, pos2));
    }
}

void makeLLarrayFromBoard(List* &board, char** a, int row, int col, int mode)
{
    if (mode == 1) // left indent
    {
        board = new List[row];
        for (int i = 0; i < row; i++)
            initList(board[i]);
        for (int j = 0; j < col; j++)
        {
            for (int i = 0; i < row; i++)
            {
                addTail(board[i], a[i][j]);
            }
        }
    }
    else if (mode == 2) // up indent
    {
        board = new List[col];
        for (int i = 0; i < col; i++)
            initList(board[i]);
        for (int j = 0; j < col; j++)
        {
            for (int i = 0; i < row; i++)
            {
                addTail(board[j], a[i][j]);
            }
        }
    }
    else if (mode == 3) // right indent
    {
        board = new List[row];
        for (int i = 0; i < row; i++)
            initList(board[i]);
        for (int j = 0; j < col; j++)
        {
            for (int i = 0; i < row; i++)
            {
                addTail(board[i], a[i][(col-1) - j]);
            }
        }
    }
    else if (mode == 4) // down indent
    {
        board = new List[col];
        for (int i = 0; i < col; i++)
            initList(board[i]);
        for (int j = 0; j < col; j++)
        {
            for (int i = 0; i < row; i++)
            {
                addTail(board[j], a[(row-1) - i][j]);
            }
        }
    }
    
}


void printLL(List board, int x, int y, int mode)
{
    int count = 0;
    Node *it = board.p_head;
    if (mode == 1) // print left to right
    {
        while (it != NULL)
        {
            string s;
            s = it->key;
            drawCell(s, x, y + count*(5+3-1), 5, 5+3);
            count++;
            it = it->p_next;
        }
    }
    else if (mode == 2) // print downward
    {
        while (it != NULL)
        {
            string s;
            s = it->key;
            drawCell(s, x + count*(5-1), y, 5, 5+3);
            count++;
            it = it->p_next;
        }
    }
    else if (mode == 3) // print right to left
    {
        while (it != NULL)
        {
            string s;
            s = it->key;
            drawCell(s, x, y - count*(5+3-1), 5, 5+3);
            count++;
            it = it->p_next;
        }
    }
    else if (mode == 4)  // print upward
    {
        while (it != NULL)
        {
            string s;
            s = it->key;
            drawCell(s, x - count*(5-1), y, 5, 5+3);
            count++;
            it = it->p_next;
        }
    }
}
void print2dLL(List *board, int row, int col, int mode)
{
    // mode = 1 : left indent
    
    if (mode == 1) 
    {
        for (int i = 0; i < row; i++)
        {
            printLL(board[i], i*(5-1), 0, mode);
        }
    }
    else if (mode == 2) // mode = 2 : up indent
    {
        
        for (int i = 0; i < col; i++)
        {
           printLL(board[i], 0, i*(5+3-1), mode);
        }
    }
    else if (mode == 3) // right indent
    {
        for (int i = 0; i < row; i++)
        {
           printLL(board[i], i*(5-1), (col-1)*(5+3-1), mode);
        }
    }
    else if (mode == 4) // down indent
    {
        for (int i = 0; i < col; i++)
        {
           printLL(board[i], (row-1)*(5-1), i*(5+3-1), mode);
        }
    }
}



void convertPos(PointLL &cur, int row, int col, int mode)
{
    if (mode == 1) // left indent
    {
        cur.LL_x = cur.x;
        cur.LL_y = cur.y;
    }
    else if (mode == 2) // up indent
    {
        cur.LL_x = cur.y;
        cur.LL_y = cur.x;
    }
    else if (mode == 3) // right indent
    {
        cur.LL_x = cur.x;
        cur.LL_y = (col-1) - cur.y;
    }
    else if (mode == 4) // down indent
    {
        cur.LL_x = cur.y;
        cur.LL_y = cur.x;
        
        cur.LL_y = (row-1) - cur.x;
    }
}

void drawPoint(List* board, PointLL point)
{
    if (point.x == -1 && point.y == -1)
        return;
    string content;
    content = getAt(board[point.LL_x], point.LL_y);
    drawCell(content, point.x*(5-1), point.y*(5+3-1), 5, 5+3, grey, white, 1);
}



// This function finds a path between two given positions (x1, y1) and (x2, y2) on the game board.
vector<pair<int, int>> findPathLL(List* board, int row, int col, PointLL cur, PointLL selected, int mode)
{
	//INIT Graph
    vector<vector<int>> e(row + 2, vector<int>(col + 2, 0));
    if (mode == 1)
    {  
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                e[i + 1][j + 1] = getAt(board[i], j) != '\0';
            }
        }
    }
    else if (mode == 2)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                e[i + 1][j + 1] = getAt(board[j], j) != '\0';
            }
        }
    }
    else if (mode == 3)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                e[i + 1][j + 1] = getAt(board[i], (col-1)-j) != '\0';
            }
        }
    }
    else if (mode == 4)
    {
        for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                e[i + 1][j + 1] = getAt(board[j], (row-1)-i) != '\0';
            }
        }
    }
    ////////////////////////////////////////////////////////////
	pair<int, int> s = { cur.x + 1, cur.y + 1 };
	pair<int, int> t = { selected.x + 1, selected.y + 1 }; 

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

void checkMatchingLL(List* board, int row, int col, PointLL &cur, PointLL &selected, int mode)
{
    if ((selected.x == -1 && selected.y == -1) || (selected.x == cur.x && selected.y == cur.y))
        return;
    if (getAt(board[cur.LL_x], cur.LL_y) != getAt(board[selected.LL_x], selected.LL_y))
        return;
    
    vector<pair<int, int>> res = findPathLL(board, row, col, cur, selected, mode);
    if (res.size() >= 2 && res.size() <= 4)
    {
        // careful here if delete at the same row or col
        if (cur.LL_x == selected.LL_x)
        {
            deleteNodeAt(board[cur.LL_x], max(cur.LL_y, selected.LL_y));
            deleteNodeAt(board[selected.LL_x], min(cur.LL_y, selected.LL_y));
        }
        else if (cur.LL_y == selected.LL_y)
        {
            deleteNodeAt(board[max(cur.LL_x, selected.LL_x)], cur.LL_y);
            deleteNodeAt(board[min(cur.LL_x, selected.LL_x)], selected.LL_y);
        }
        else
        {
            deleteNodeAt(board[cur.LL_x], cur.LL_y);
            deleteNodeAt(board[selected.LL_x],  selected.LL_y);
        }
        selected.x = -1;
        selected.y = -1;
    }

}

void playerInput(List* board, PointLL &cur, PointLL &selected, int row, int col, int mode, bool &run)
{
    char c = getch();
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
        if (selected.x == cur.x && selected.y == cur.y)
        {
            selected.x = -1;
            selected.y = -1;
        }
        else if (selected.x != -1 && selected.y != -1)
        {
            checkMatchingLL(board, row, col, cur, selected, mode);
        }
        else
            selected = cur;
        break;
    case 27:
        run = false;
        break;
    }
    if (inMap(cur.x + x, cur.y + y, row, col))
    {
        cur.x += x;
        cur.y += y;
    }
}


int main()
{
    int row = 6, col = 4, gamemode = 4;
    char** arr;
    make_boardLL(arr, row, col);
                     
    List* board;
    PointLL cur = {0, 0, 0, 0};
    PointLL selected = {-1, -1, -1, -1};
    makeLLarrayFromBoard(board, arr, row, col, gamemode);
    
    for (int i = 0; i < row; i++)
        delete[] arr[i];
    delete[] arr;

    bool run = true;
    while (run) 
    {
        system("cls");
        convertPos(cur, row, col, gamemode);
        convertPos(selected, row, col, gamemode);
        print2dLL(board, row, col, gamemode);  

        drawPoint(board, cur);
        drawPoint(board, selected);
        
        playerInput(board, cur, selected, row, col, gamemode, run);
        
            
    }
    
    return 0;
}