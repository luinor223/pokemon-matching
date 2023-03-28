

bool isInMap(GameState game, int x, int y);
vector<pair<int, int>> findPath(GameState game, int _x, int _y, int x, int y);
void drawMatchingLine(vector <pair <int, int> > res, int offset_x, int offset_y, int cellSize);
void checkMatching(GameState game, char** background, int bg_row, int bg_column, int offset_x, int offset_y);
bool findPoint(vector <Point> v, Point a);
void drawSelectedPoint(GameState game, vector <Point> selectedPoint, int offset_x, int offset_y);
void drawSelectingPoint(GameState game, int x, int y, int offset_x, int offset_y);
void playerAction(GameState game, int  offset_x, int offset_y, int &page) ;