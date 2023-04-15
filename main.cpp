#include "resources.h"
#include "header.h"

int main()
{
    //Set Window size and Screen Buffer size to WinColum = 130, WinRow = 45
    SetWindowSize(WinColumn, WinRow);
    SetScreenBufferSize(WinColumn, WinRow);

    //Hide the cursor
    ShowConsoleCursor(false);

    //Random
    srand(time(NULL));

    //Set Game Color to white background, black text.
    SetColor();
    //Clear screen (or fill screen with ' ')
    clear();

    //This struct represents in-game board
    GameState game;

    //This struct represents account
    savefile account;

    //This array represents players on the leaderboard
    PlayerInfo players[MAXPLAYERS];

    //Save file
    string file_account = "save\\account.bin";

    //Background
    char** background;
    int bg_row = 40, bg_column = 70;
    string bg_file = "";

    //Game title
    char** title;
    int title_row = 10, title_col = 87;
    loadArtFromFile("asciiart\\title.txt", title, title_row, title_col);


    //Offset to align the board to middle
    int board_offset_x, board_offset_y;

    //Count cheat words
    int word_count = 0;
    int cheatWordsCount[4] = {0};

    //Menu page
    int page = 1;
    //Menu choice
    int choice = 1;

    //Check if the board is initialized
    bool initialized = false;

    time_t start_time;

    //State of the game
    bool run = true;

    //Check if the player logged in or not
    bool isLogged = false;

    //Check if player continue a saved game.
    bool continue_game = false;

    while (run)
    {
        //Display login/register menu until player logs in successfully
        while (!isLogged && run)
            displayLoginRegisterMenu(account, file_account, players, title, title_row, title_col, run, isLogged, page);

        // Display main menu until player chooses to start game
        while(isLogged && run && (page < gameplay_page || page == save_page))
            generateMenu(account, game, players, file_account, page, choice, title, title_row, title_col, run, continue_game, word_count, isLogged, bg_file);

        //Gameplay Page
        if (page == gameplay_page)
        {
            // If player chooses to start game, initialize game and display UI
            if (!initialized)
            {
                clear();
                start_time = time(0);
                game.total_time = game.time_left;

                //If player start a new game, make a new board.
                if (!continue_game)
                    make_board(game);

                /*Load background*/
                if (bg_file.length() <= 1)
                {
                    switch(game.difficulty)
                    {
                        case 1:
                            bg_file = "asciiart\\background1.txt";
                            break;
                        case 2:
                            bg_file = "asciiart\\background2.txt";
                            break;
                        case 3:
                            bg_file = "asciiart\\background3.txt";
                            break;
                        default:
                            bg_file = "asciiart\\background4.txt";
                            break;
                    }
                }

                loadArtFromFile(bg_file, background, bg_row, bg_column);
                bg_file = "";
                ////////////////////////////////////////////////////////////

                /*Modify the board offset to align the board to middle of the "Game Box"*/
                board_offset_x = (gameboxrow - game.row * (game.cellSize - 1) - 1) / 2 ;
                board_offset_y = (gameboxcol - game.col*(game.cellSize + 2) - 1) / 2;
                board_offset_x = (board_offset_x < 1) ? 1 : board_offset_x;
                board_offset_y = (board_offset_y < 1) ? 1 : board_offset_y;

                while (!moveSuggestion(game, board_offset_x, board_offset_y, false))  //Check if there is any possible match on the board.
                    shuffle_board(game);    //if not, shuffle the board
                
                //Display the game UI
                displayGameUI(game);

                //Show the board
                showBoard(game, background, bg_row, bg_column, board_offset_x, board_offset_y);
                drawSelectingPoint(game, 0, 0, board_offset_x, board_offset_y, background);
                
                //Set initialized to true
                initialized = true;

                //Set continue_game to false
                continue_game = false;
            }

            /*In-game*/
            while (initialized)
            {
                //Update UI (time, score, shuffle count, help count)
                updateUI(game, start_time);

                //This function is used to determine if a key has been pressed or not 
                if (kbhit())    //This function is used to prevent the getch() function from pausing the game
                {
                    //Handle player's input
                    playerAction(game, account, board_offset_x, board_offset_y, page, background, bg_row, bg_column, cheatWordsCount);

                    //If 2 cells are selected, the game check the valid path between them
                    if (checkMatching(game, background, bg_row, bg_column, board_offset_x, board_offset_y))
                    {
                        //Play matching sound
                        PlaySound(TEXT("SoundSFX/match.wav"), NULL, SND_FILENAME | SND_ASYNC);

                        //Update score
                        updateScore(game, account, players);

                        //Decrease the number of available moves left by 1
                        game.move_count--;

                        //After matching 2 tiles, check if there is any possible match left.
                        while (!moveSuggestion(game, board_offset_x, board_offset_y, false) && game.move_count > 0)
                            shuffle_board(game);    //if not, shuffle the board

                        //Show the new board after 2 cells are deleted
                        showBoard(game, background, bg_row, bg_column, board_offset_x, board_offset_y);
                        drawSelectingPoint(game, 0, 0, board_offset_x, board_offset_y, background);
                    }
                    
                    //Draw the all the current selected cells in selectedPoint vector
                    drawSelectedPoint(game, selectedPoint, board_offset_x, board_offset_y);
                }

                //If there is no move left
                if (game.move_count == 0) 
                {
                    //Play complete stage sound effect
                    PlaySound(TEXT("SoundSFX/stagecomplete.wav"), NULL, SND_FILENAME | SND_ASYNC);

                    //If the game is not custom mode
                    if (game.difficulty != 0)
                        game.stage++;   //Increase stage
                    else
                    {
                        //Go back to main menu
                        clear();
                        page = main_page;
                    }

                    freeCharMatrix(background, bg_row);
                    deleteMemBoard(game);
                    initialized = false;
                    break;
                }

                if (page == main_page) //Go back to menu
                {
                    clear();
                    freeCharMatrix(background, bg_row);
                    deleteMemBoard(game);
                    initialized = false;
                    break;
                }

                if (page == save_page)  //Go to save page
                {
                    drawCell(" ", 3, (WinColumn - 80) / 2, 30, 80);
                    initialized = false;
                    break;
                }
                    
                if (game.time_left <= 0)    //If there is no time left
                {
                    GameOver(game);
                    page = main_page;
                    freeCharMatrix(background, bg_row);
                    deleteMemBoard(game);
                    initialized = false;
                    break;
                }
            }
        }
    }

    freeCharMatrix(title, title_row);
    return 0;
}