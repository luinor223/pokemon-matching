#include "main.h"
#include "header.h"

int main()
{
    SetWindowSize(WinColumn, WinRow);
    SetScreenBufferSize(WinColumn, WinRow);
    

    GameState game;
    PlayerState player;
    savefile account;

    char** background;
    int bg_row = 32, bg_column = 66;
    int board_offset_x, board_offset_y;
    getFileContent("background.txt", background, bg_row, bg_column);

    char** title;
    int title_row = 12, title_col = 68;
    getFileContent("title.txt", title, title_row, title_col);

    int page = 1;
    int choice = 1;
    bool initialized = false;
    int move_count;

    bool title_display = false;
    time_t start_time;
    ShowConsoleCursor(false);

    bool run = true;

    //displayLoginRegisterMenu(player);
    while (run)
    {
        // Display main menu until player chooses to start game
        while(page <= 5 && run)
        {
            generateMenu(game, page, choice, title, title_row, title_col, run);
        }
        if (page == 6)
        {
            // If player chooses to start game, initialize game and display UI
            if (!initialized)
            {
                clear();
                start_time = time(0);
                game.total_time = player.time_left + 120;

                make_board(game, move_count);

                if (game.stage < 6)
                    game.mode = game.stage;
                else
                {
                    srand(time(NULL));
                    game.mode = rand() % 4 + 1;
                }
                
                board_offset_x = (bg_row - game.row * (game.cellSize - 1) - 1) / 2 + 1;
                board_offset_y = (bg_column - game.col*(game.cellSize + 3 - 1) - 1) / 2 + 1;
                board_offset_x = (board_offset_x < 1) ? 1 : board_offset_x;
                board_offset_y = (board_offset_y < 1) ? 1 : board_offset_y;
                while (!moveSuggestion(game, board_offset_x, board_offset_y, false))  //Check if there is any possible match on the board.
                {
                    shuffle_board(game);    //if not, shuffle the board
                }

                displayGameUI(game);
                showBoard(game, background, bg_row, bg_column, board_offset_x, board_offset_y);
                
                initialized = true;
            }
            while (initialized)
            {
                updateUI(game, player, start_time);
                if (kbhit())
                {
                    playerAction(game, player, board_offset_x, board_offset_y, page, background, bg_row, bg_column);
                    if (checkMatching(game, background, bg_row, bg_column, board_offset_x, board_offset_y))
                    {
                        updateScore(player);
                        move_count--;
                        while (!moveSuggestion(game, board_offset_x, board_offset_y, false) && move_count > 0) //After matching 2 tiles, check if there is any possible match left.
                        {
                            shuffle_board(game);    //if not, shuffle the board
                        }

                        showBoard(game, background, bg_row, bg_column, board_offset_x, board_offset_y); //show the new board
                    }

                    drawSelectedPoint(game, selectedPoint, board_offset_x, board_offset_y);
                    drawSelectingPoint(game, 0, 0, board_offset_x, board_offset_y);
                }

                if (move_count == 0) 
                {
                    game.stage++;
                    deleteMemBoard(game);
                    initialized = false;
                    break;
                }

                if (page == 1) //Go back to menu
                {
                    clear();
                    deleteMemBoard(game);
                    initialized = false;
                    break;
                }

                if (player.time_left == 0)
                {
                    displayGameOver(player);
                    page = 1;
                    deleteMemBoard(game);
                    initialized = false;
                    break;
                }
            }
        }
    }

    freeCharMatrix(background, bg_row);
    freeCharMatrix(title, title_row);
    return 0;
}