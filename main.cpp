#include "main.h"
#include "header.h"

int main()
{
    SetWindowSize(WinColumn, WinRow);

    GameState game;
    savefile player;

    char** background;
    int bg_row, bg_column;
    int board_offset_x, board_offset_y;
    //showBoard(game, background, bg_row, bg_column);

    int page = 1;
    int choice = 1;
    bool initialized = false;

    //displayLoginRegisterMenu(player);
    while (true)
    {
        while(page <= 5)
        {
            generateMenu(game, page, choice);
        }
        if (page == 6)
        {
            if ( initialized == false)
            {
                clear();
                bg_row = game.row;
                bg_column = game.col;
                
                getFileContent(background, bg_row, bg_column, game.cellSize);
                make_board(game);
                board_offset_x = (bg_row - game.row * (game.cellSize - 1) - 1) / 2;
                board_offset_y = (bg_column - game.col*(game.cellSize + 3 - 1) - 1) / 2;
                board_offset_x = (board_offset_x < 0) ? 0 : board_offset_x;
                board_offset_y = (board_offset_y < 0) ? 0 : board_offset_y;

                //drawCell(" ", 0, 0, WinRow, WinColumn);
                showBoard(game, background, bg_row, bg_column);
                
                initialized = true;
            }
            while (initialized == true)
            {
                checkMatching(game, background, bg_row, bg_column, board_offset_x, board_offset_y);
                drawSelectedPoint(game, selectedPoint, board_offset_x, board_offset_y);
                drawSelectingPoint(game, 0, 0, board_offset_x, board_offset_y);
                playerAction(game, board_offset_x, board_offset_y, page);

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