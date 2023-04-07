
void generateMenu(savefile &account, GameState &game, string filename, int &page, int &choice, char** title, int title_row, int title_col, bool &run, bool &hackMode, bool &continue_game);
void displayGameTitle(char** title, int title_row, int title_col);
void displayMainMenu(int choice);
void displayDifficultyChoice(int choice);
void displayCustomBoardPage(GameState game, int choice);
void displayLoadGamePage(savefile account, int choice);
void displayAccountInfo(savefile account, int choice, bool hackMode);
void changeNameForm(savefile &account, string filename, bool &changed);
void changePasswordForm(savefile &account, bool &changed);
void processHacking(savefile account, int choice);
void displayCreditPage();

//Sort Record in descending order.
void sortRecord(Record record[], int n);
void displaySavePage(GameState game, savefile account, int choice);