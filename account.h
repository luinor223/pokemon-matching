#include "main.h"
#include "console.cpp"
#include "draw.cpp"

void processReg(savefile &player, bool &isLogged);
void processLogin(savefile player, bool &isLogged);
void displayForm(savefile player,int choice, bool &isLogged);
void displayLoginRegisterMenu(savefile &player);