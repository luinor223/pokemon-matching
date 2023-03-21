#include "background.h"

void deleteBg(int m, int n, char **&background){
    for (int i = 0; i < 5 * (m + 2); i++)
        delete[] background[i];
    delete[] background;
}

void getFileContent(char **&background, int &m, int &n)
{
    ifstream File("art.txt");
    string result = "";

    background = new char *[5*(m+2)];

    int i = 0;
    int max = 0;
    if (File.is_open())
    {
        while(File.good() && i < 5*(m+2) - 1)
        {
            string tempLine;
            getline(File, tempLine);
            background[i] = new char[tempLine.length() + 1];
            strcpy(background[i], tempLine.c_str());
            if (max < tempLine.length())
                max = tempLine.length();
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
//     int mb = m, nb = n;
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

//     deleteBg(m, n, background);

//     return 0;
// }