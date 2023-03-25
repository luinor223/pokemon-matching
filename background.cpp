#include "background.h"

void getFileContent(char **&background, int &m, int &n, int cellSize)
{
    ifstream File("background.txt");
    string result = "";

    
    background = new char *[cellSize*(m+2)];

    int i = 0;
    int maxx = 0;
    if (File.is_open())
    {
        while(File.good() && i < 5*(m+2) - 1)
        {
            string tempLine;
            getline(File, tempLine);
            background[i] = new char[max((int)tempLine.length() + 1, n)];
            strcpy(background[i], tempLine.c_str());
            if (maxx < tempLine.length())
                maxx = tempLine.length();
            //cout << background[i] << endl;
            i++;
        }
        m = i;
        n = maxx;
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
        for (int j = 0; j < bg_column; j++)
            cout << background[i][j];
        
        cout << endl;
    }
}

void deleteBg(int m, int n, char **&background){
    for (int i = 0; i < 5 * (m + 2); i++)
        delete[] background[i];
    delete[] background;
}

