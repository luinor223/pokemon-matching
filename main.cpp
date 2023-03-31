#include "main.h"
#include "header.h"

int main()
{
    SetWindowSize(WinColumn, WinRow);
    SetScreenBufferSize(WinColumn, WinRow);
    

    GameState game;
    savefile player;

    char** background;
    int bg_row = 32, bg_column = 66;
    int board_offset_x, board_offset_y;
    //showBoard(game, background, bg_row, bg_column);

    char** title;
    int title_row = 12, title_col = 68;
    getFileContent("title.txt", title, title_row, title_col);

    int page = 1;
    int choice = 1;
    bool initialized = false;

    bool title_display = false;
    int time_left = 10;
    time_t start_time;
    ShowConsoleCursor(false);

    //displayLoginRegisterMenu(player);
    while (true)
    {
        while(page <= 5)
        {
            generateMenu(game, page, choice, title, title_row, title_col);
        }
        if (page == 6)
        {
            if ( initialized == false)
            {
                clear();
                time_left = 10;
                start_time = time(0);
                getFileContent("background.txt", background, bg_row, bg_column);
                make_board(game);
                board_offset_x = (bg_row - game.row * (game.cellSize - 1) - 1) / 2 + 1;
                board_offset_y = (bg_column - game.col*(game.cellSize + 3 - 1) - 1) / 2 + 1;
                board_offset_x = (board_offset_x < 1) ? 1 : board_offset_x;
                board_offset_y = (board_offset_y < 1) ? 1 : board_offset_y;

                displayGameUI(game);
                showBoard(game, background, bg_row, bg_column, board_offset_x, board_offset_y);
                
                initialized = true;
            }
            while (initialized == true && time_left > 0)
            {
                updateTime(game, time_left, start_time);
                
                if (kbhit())
                {
                    playerAction(game, board_offset_x, board_offset_y, page);
                    checkMatching(game, background, bg_row, bg_column, board_offset_x, board_offset_y);
                    drawSelectedPoint(game, selectedPoint, board_offset_x, board_offset_y);
                    drawSelectingPoint(game, 0, 0, board_offset_x, board_offset_y);
                }

                if (page == 1) //Player go back to menu
                {
                    deleteBg(background, bg_row);
                    deleteMemBoard(game);
                    initialized = false;
                }
            }
        }
    }

    deleteBg(bg_row, bg_column, background);
    deleteMemBoard(game);
    return 0;
}