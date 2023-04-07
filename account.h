
void mask(char text[], char mask);
void processReg(string filename, char* name, char* password, savefile &account, bool &isLogged);
void processLogin(string filename, char* name, char* password, savefile &account, bool &isLogged);
void displayForm(string filename, savefile &account, int choice, bool &isLogged);
void displayLoginRegisterMenu(savefile &account, string filename, bool &run);
void loadBoard(GameState &game, savefile account, int index);
void saveBoard(GameState game, savefile &account, int index);
void saveGame(string filename, GameState game, savefile account);