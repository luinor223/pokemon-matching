

bool isInMap(GameState game, int x, int y);

/**
 * This function finds a path from the starting position (_x, _y) to the 
 * ending position (x, y) on a game board represented by the GameState object.
 *
 * The function creates a graph where each cell on the game board is a node, 
 * and there is an edge between two adjacent cells. The edge weight is 1 if 
 * the cell is not empty, and 0 if it is empty. Then it uses the breadth-first 
 * search (BFS) algorithm to find the shortest path from the ending position 
 * to the starting position.
 *
 * @param game The GameState object representing the game board
 * @param _x The row index of the starting position
 * @param _y The column index of the starting position
 * @param x The row index of the ending position
 * @param y The column index of the ending position
 *
 * @return A vector of pairs representing the path from the starting position 
 *         to the ending position. Each pair represents a (row, col) coordinate 
 *         on the game board.
 */
vector<pair<int, int>> findPath(GameState game, int _x, int _y, int x, int y);

void drawMatchingLine(vector <pair <int, int> > res, int offset_x, int offset_y, int cellSize);

/**
* @brief Checks if the two selected points on the game board form a valid matching pair, draws a line between them if so, and removes the matching pair from the game board
* @param game: Current game state
* @param background: Background of the game board
* @param bg_row: Number of rows in the background
* @param bg_column: Number of columns in the background
* @param offset_x: Horizontal offset of the game board
* @param offset_y: Vertical offset of the game board
* @return true if the selected points form a valid matching pair and the matching pair has been removed from the board, false otherwise
*/
bool checkMatching(GameState game, char** background, int bg_row, int bg_column, int offset_x, int offset_y);

bool findPoint(vector <Point> v, Point a);
void drawSelectedPoint(GameState game, vector <Point> selectedPoint, int offset_x, int offset_y);
void drawSelectingPoint(GameState game, int x, int y, int offset_x, int offset_y);
void playerAction(GameState game, PlayerState &player, int  offset_x, int offset_y, int &page, char** background, char bg_row, char bg_column); 
