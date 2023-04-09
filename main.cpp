#include "main.h"
#include "header.h"

int main()
{
    SetWindowSize(WinColumn, WinRow);
    SetScreenBufferSize(WinColumn, WinRow);
    srand(time(NULL));
    setConsoleColors();

    GameState game;
    savefile account;
    PlayerInfo players[10];
    string file_account = "save\\account.bin";

    char** background;
    int bg_row = 34, bg_column = 68;
    int board_offset_x, board_offset_y;
    getFileContent("asciiart\\background.txt", background, bg_row, bg_column);

    char** title;
    int title_row = 10, title_col = 87;
    getFileContent("asciiart\\title.txt", title, title_row, title_col);

    int word_count = 0;
    int cheatWordsCount[4] = {0};
    int page = 1;
    int choice = 1;
    bool initialized = false;
    int move_count;

    bool title_display = false;
    time_t start_time;
    ShowConsoleCursor(false);

    bool run = true;
    bool continue_game = false;

    displayLoginRegisterMenu(account, file_account, title, title_row, title_col, run);
    getLdBoard(players, file_account);
    while (run)
    {
        // Display main menu until player chooses to start game
        while((page < gameplay_page || page == save_page)  && run )
        {
            generateMenu(account, game, players, file_account, page, choice, title, title_row, title_col, run, continue_game, word_count);
        }
        if (page == gameplay_page)
        {
            // If player chooses to start game, initialize game and display UI
            if (!initialized)
            {
                clear();
                start_time = time(0);
                game.total_time = game.time_left;

                if (!continue_game)
                {
                    game.total_time = game.time_left + bouns_time;
                    make_board(game);
                    
                    if (game.difficulty != 0)
                    {
                        if (game.stage < 6)
                            game.mode = game.stage;
                        else
                            game.mode = rand() % 4 + 1;
                    }
                }
                
                board_offset_x = (gameboxrow - game.row * (game.cellSize - 1) - 1) / 2 ;
                board_offset_y = (gameboxcol - game.col*(game.cellSize + 3 - 1) - 1) / 2;
                board_offset_x = (board_offset_x < 1) ? 1 : board_offset_x;
                board_offset_y = (board_offset_y < 1) ? 1 : board_offset_y;
                while (!moveSuggestion(game, board_offset_x, board_offset_y, false))  //Check if there is any possible match on the board.
                {
                    shuffle_board(game);    //if not, shuffle the board
                }
                
                displayGameUI(game);
                showBoard(game, background, bg_row, bg_column, board_offset_x, board_offset_y);
                
                initialized = true;
                continue_game = false;
            }
            while (initialized)
            {
                updateUI(game, start_time);
                if (kbhit())
                {
                    playerAction(game, board_offset_x, board_offset_y, page, background, bg_row, bg_column, cheatWordsCount);
                    if (checkMatching(game, background, bg_row, bg_column, board_offset_x, board_offset_y))
                    {
                        updateScore(game, account, players);
                        game.move_count--;
                        while (!moveSuggestion(game, board_offset_x, board_offset_y, false) && move_count > 0) //After matching 2 tiles, check if there is any possible match left.
                        {
                            shuffle_board(game);    //if not, shuffle the board
                        }

                        showBoard(game, background, bg_row, bg_column, board_offset_x, board_offset_y); //show the new board
                    }

                    drawSelectedPoint(game, selectedPoint, board_offset_x, board_offset_y);
                    drawSelectingPoint(game, 0, 0, board_offset_x, board_offset_y);
                }

                if (game.move_count == 0) 
                {
                    if (game.difficulty != 0)
                        game.stage++;
                    else 
                    {
                        clear();
                        page = main_page;
                    }
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

                if (page == save_page)
                {
                    drawCell(" ", 3, (WinColumn - 80) / 2, 30, 80);
                    initialized = false;
                    break;
                }
                    
                if (game.time_left <= 0)
                {
                    GameOver(game);
                    page = main_page;
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