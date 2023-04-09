
void generateMenu(savefile &account, GameState &game, PlayerInfo players[], string filename, int &page, int &choice, char** title, int title_row, int title_col, bool &run, bool &continue_game, int &word_count);
void displayGameTitle(char** title, int title_row, int title_col);
void displayMainMenu(int choice);
void displayDifficultyChoice(int choice);
void displayCustomBoardPage(GameState game, int choice);
void displayLoadGamePage(savefile account, int choice);
void displayAccountInfo(savefile account, int choice, int page);
void changeNameForm(savefile &account, string filename, bool &changed);
void changePasswordForm(savefile &account, bool &changed);
void processHacking(savefile account, int choice);
bool checkCheatCode(char c, int &count, string cheatCode);
void displayCreditPage();

//Sort Record in descending order.
void sortRecord(Record record[], int n);
void displaySavePage(GameState game, savefile account, int choice);

void getLdBoard(PlayerInfo players[], string account_file);
void sortLB(PlayerInfo arr[]);
void displayLdBoard(PlayerInfo players[]);