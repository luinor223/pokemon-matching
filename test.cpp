// formatBoard(board[SIZE][SIZE], int cellSize, int backGroundSize, char cellOutLineChar)
// {
// 	NOTE : cellSize*SIZE < backGroundSize  
// 	  EX : 
// 	board = {A, B}
// 			{A, B}
// 	cellSize = 5
// 	backGroundSize = 15
// 	cellOutLineChar = *
// 	###############
// 	###############
// 	###############
// 	###**********##
// 	###*   **   *##
// 	###* A ** B *##
// 	###*   **   *##
// 	###**********##
// 	###**********##
// 	###*   **   *##
// 	###* A ** B *##
// 	###*   **   *##
// 	###**********##
// 	###############
// 	###############

// }
// void draw_board(char a[][MAX], int m, int n)
// {
//     char backGroundChar = '#';
//     int box_row = cellSize + 2;
//     int box_column = cellSize;
//     int backGroundSize_row = max(m, n) * cellSize + 10;
//     int backGroundSize_column = max(m, n) * cellSize + 8;

//     for (int i = 0; i <= (backGroundSize_row -  max(m, n) * cellSize) / 2 ; i++)
//         for (int i = 0; i < backGroundSize_column; i++)
//             cout << backGroundChar;

    
//     for (int i = 0; i < m; i++) {
//         for (int j = 0 ; j < n; j++) {
//             cout << a[i][j] << " ";
//         }
//         cout << endl;
//     }
// }

// bool is_valid_path(char board[][MAX], int m, int n, int r1, int c1, int r2, int c2, int max_turns, int num_turns) {
//     if (r1 < 0 || r1 >= m || c1 < 0 || c1 >= n || r2 < 0 || r2 >= m || c2 < 0 || c2 >= n) {
//         // Out of bounds
//         return false;
//     }

//     if (num_turns > max_turns) {
//         // Too many turns
//         return false;
//     }

//     if (board[r1][c1] != board[r2][c2]) {
//         // Different letters
//         return false;
//     }

//     if (r1 == r2 && c1 == c2) {
//         // Same cell
//         return true;
//     }

//     // Check L path
//     if ((r1 == r2 && abs(c1 - c2) == 1) || (c1 == c2 && abs(r1 - r2) == 1)) {
//         return true;
//     }

//     // Check U path using DFS
//     bool visited[MAX][MAX] = {false};
//     stack<pair<int, int>> s;

//     s.push(make_pair(r1, c1));

//     while (!s.empty()) {
//         pair<int, int> p = s.top();
//         s.pop();

//         int r = p.first;
//         int c = p.second;

//         if (r == r2 && c == c2) {
//             return true;
//         }

//         // Visit adjacent cells
//         if (r > 0 && !visited[r-1][c] && board[r-1][c] == ' ') {
//             visited[r-1][c] = true;
//             s.push(make_pair(r-1, c));
//         }
//         if (r < m-1 && !visited[r+1][c] && board[r+1][c] == ' ') {
//             visited[r+1][c] = true;
//             s.push(make_pair(r+1, c));
//         }
//         if (c > 0 && !visited[r][c-1] && board[r][c-1] == ' ') {
//             visited[r][c-1] = true;
//             s.push(make_pair(r, c-1));
//         }
//         if (c < n-1 && !visited[r][c+1] && board[r][c+1] == ' ') {
//             visited[r][c+1] = true;
//             s.push(make_pair(r, c+1));
//         }
//     }

//     return false;
// }


// void play_game(char board[][MAX], int m, int n)
// {
//     int num_turns = 0;
//     int max_turns = 3;
//     while (num_turns < max_turns) {
//         // Draw the updated board
//         showBoard(board, m, n, 5, '|', '-');

//         // Get the user's input for the first tile
//         pair<int, int> tile1_pos;
//         cout << "Enter the row and column of the first tile: ";
//         cin >> tile1_pos.first >> tile1_pos.second;

//         // Get the user's input for the second tile
//         pair<int, int> tile2_pos;
//         cout << "Enter the row and column of the second tile: ";
//         cin >> tile2_pos.first >> tile2_pos.second;

//         // Check if the tiles match and remove them if they do
//         if (is_valid_path(board, m, n, tile1_pos.first, tile1_pos.second, tile2_pos.first, tile2_pos.second, max_turns, num_turns )) {
//             cout << "Tiles match!" << endl;
//             board[tile1_pos.first][tile1_pos.second] = ' ';
//             board[tile2_pos.first][tile2_pos.second] = ' ';
//         }
//         else {
//             cout << "Tiles do not match." << endl;
//         }

//         // Increment the number of turns
//         num_turns++;
//     }
// }

