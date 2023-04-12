
void generateMenu(savefile &account, GameState &game, PlayerInfo players[], string filename, int &page, int &choice, char** title, int title_row, int title_col, bool &run, bool &continue_game, int &word_count, bool &isLogged, string &bg_file);
void displayGameTitle(char** title, int title_row, int title_col);
void displayMainMenu(int choice);
void displayDifficultyChoice(int choice);
void displayCustomBoardPage(GameState game, int choice);
void displayLoadGamePage(savefile account, int choice);
void displayAccountInfo(savefile account);
void displayAccOptions(int choice);
void changeNameForm(savefile &account, string filename, bool &changed);
void changePasswordForm(savefile &account, bool &changed);
void processHacking(savefile account, int choice);
bool checkCheatCode(char c, int &count, string cheatCode);
void displayCreditPage();

//Sort Record in descending order.
void sortRecord(Record record[], int n);
void displaySavePage(GameState game, savefile account, int choice);
void displayLdBoard(PlayerInfo players[]);
bool checkNameOnLB(savefile account, PlayerInfo players[]);