#include "asciiart.h"

void loadArtFromFile(string filename, char **&background, int &row, int &col)
{
    ifstream File(filename);
    string result = "";
 
    background = new char *[row];

    int i = 0;
    int maxx = 0;
    if (File.is_open())
    {
        while(!File.eof() && i < row - 1)
        {
            string tempLine;
            getline(File, tempLine);
            background[i] = new char[max((int)tempLine.length() + 1, col)];
            strcpy(background[i], tempLine.c_str());
            if (maxx < tempLine.length())
                maxx = tempLine.length();
            i++;
        }
        row = i;
        col = maxx;
    }
    else
    {
        cout << "Error! File does not exist.";
    }
}

void printBg(char** background, int bg_row, int bg_column)
{
    for(int i = 0; i < bg_row; i++)
    {
        GoTo(i + (gameboxrow - bg_row) / 2, (gameboxcol - bg_column) / 2);
        for (int j = 0; j < bg_column; j++)
            cout << background[i][j];
    }
}

void displayGameTitle(char** title, int title_row, int title_col)
{
    SetColor();
    for (int i = 0; i < title_row; i++)
    {
        GoTo(i, (WinColumn - title_col) / 2);
        for (int j = 0; j < title_col; j++)
        {
            cout << title[i][j];
        }
    }
}

void freeCharMatrix(char **&background, int bg_row){
    for (int i = 0; i < bg_row; i++)
        delete[] background[i];
    delete[] background;
}

