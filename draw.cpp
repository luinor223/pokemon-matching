#include "draw.h"

void drawCell(string text, int x, int y, int cellSizeRow, int cellSizeColumn, int bg_color, int text_color)
{
    // Create a separate wcout stream object
    //std::wostream& wcout = std::wcout;

    // Set the output mode to Unicode for the wcout object
    _setmode(_fileno(stdout), _O_U16TEXT);

    for (int i = 0; i < cellSizeRow; i++)
    {
        GoTo(x+i, y);
        for (int j = 0; j < cellSizeColumn; j++)
        {
            if (i == 0 && j == 0) 
                wcout << L"\u250C";
            else if (i == 0 && j == cellSizeColumn - 1)
                wcout << L"\u2510";
            else if (i == cellSizeRow - 1 && j == 0)
                wcout << L"\u2514";
            else if (i == cellSizeRow - 1 && j == cellSizeColumn - 1)
                wcout << L"\u2518";
            else if (i == 0 || i == cellSizeRow-1)
                wcout << L"\u2500";
            else if (j == 0 || j == cellSizeColumn-1) 
                wcout << L"\u2502";
            else
            {
                SetColor(bg_color, text_color);
                wcout << " ";
                SetColor(0, 7);
            }
        }
    }
    // Set the output mode back to ASCII for stdout
    _setmode(_fileno(stdout), _O_TEXT);

    GoTo(x + cellSizeRow / 2 , y + (cellSizeColumn - text.length()) / 2);
    SetColor(bg_color, text_color);
    cout << text;
    SetColor(0, 7);
}
