#include "background.h"

void deleteBg(int m, int n, char **&background){
    for (int i = 0; i < 5 * (m + 2); i++)
        delete[] background[i];
    delete[] background;
}

void getFileContent(char **&background, int &m, int &n)
{
    ifstream File("background.txt");
    string result = "";

    background = new char *[5*(m+2)];
    for (int i = 0; i < 5 * (m + 2); i++)
        background[i] = new char[7 * (n + 2)];

    int i = 0;
    int max = 0;
    if (File.is_open())
    {
        while(File.good())
        {
            string tempLine;
            getline(File, tempLine);
            strcpy(background[i], tempLine.c_str());
            if (max < strlen(background[i]))
                max = strlen(background[i]);
            //cout << background[i] << endl;
            i++;
        }
        m = i;
        n = max;
    }
    else
    {
        cout << "Error! File does not exist.";
        
    }

}

// int main()
// {
//     char** background;
//     int m = 8, n = 8;
//     int mb, nb;
//     background = new char *[5*(m+2)];
//     for (int i = 0; i < 5 * (m + 2); i++)
//         background[i] = new char[7 * (n + 2)];
    
//     getFileContent(background, mb, nb);

//     for (int i = 0; i < mb; i++)
//     {
//         for (int j = 0; j < nb; j++)
//             cout << background[i][j];
        
//         cout << endl;
//     }

//     deleteArt(m, n, background);

//     return 0;
// }