void displayGameUI(GameState game);
void updateUI(GameState &game, int start_time);
void GameOver(GameState game);
void updateScore(GameState &game, savefile &account, PlayerInfo players[]);

bool checkNameOnLB(savefile account, PlayerInfo players[]);