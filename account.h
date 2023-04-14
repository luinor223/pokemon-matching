
void mask(char text[], char mask);
void processReg(string filename, char* name, char* password, savefile &account, bool &isLogged, PlayerInfo players[]);
void processLogin(string filename, char* name, char* password, savefile &account, PlayerInfo players[], bool &isLogged);
void displayForm(string filename, savefile &account, PlayerInfo players[], int choice, bool &isLogged);
void displayLoginRegisterMenu(savefile &account, string filename, PlayerInfo players[], char** title, int title_row, int title_col, bool &run, bool &isLogged, int &choice);
void loadBoard(GameState &game, savefile account, int index, string &bg_file);
void saveBoard(GameState game, savefile &account, int index);
void getLdBoard(PlayerInfo players[], string account_file);
void updateLdBoard(PlayerInfo players[], savefile account);
void sortLB(PlayerInfo arr[]);
int checkNameOnLB(savefile account, PlayerInfo players[]);
void saveGame(string filename, savefile account);
