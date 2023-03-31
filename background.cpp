#include "background.h"

void getFileContent(string filename, char **&background, int &row, int &col)
{
    ifstream File(filename);
    string result = "";

    
    background = new char *[row];

    int i = 0;
    int maxx = 0;
    if (File.is_open())
    {
        while(File.good() && i < row - 1)
        {
            string tempLine;
            getline(File, tempLine);
            background[i] = new char[max((int)tempLine.length() + 1, col)];
            strcpy(background[i], tempLine.c_str());
            if (maxx < tempLine.length())
                maxx = tempLine.length();
            //cout << background[i] << endl;
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
        GoTo(i + 1, 1);
        for (int j = 0; j < bg_column; j++)
            cout << background[i][j];
        
    }
}

void deleteBg(char **&background, int bg_row){
    for (int i = 0; i < bg_row; i++)
        delete[] background[i];
    delete[] background;
}

