#include "draw.h"

void drawCell(string text, int x, int y, int cellSizeRow, int cellSizeColumn, int bg_color, int text_color, int mode)
{
    if (mode == 0) // draw normally
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
                    SetColor(0, 7); // default setting for black background, white text
                }
            }
        }
        // Set the output mode back to ASCII for stdout
        _setmode(_fileno(stdout), _O_TEXT);
    }
    else // mode = 1 : highlight the cell
    {
        SetColor(bg_color, text_color);
        for (int i = 1; i < cellSizeRow-1; i++)
        {
            GoTo(x+i, y+1);
            for (int j = 1; j < cellSizeColumn-1; j++)
            {
                cout << " ";
            }
        }
        SetColor(0, 7); 
    }

    GoTo(x + cellSizeRow / 2 , y + (cellSizeColumn - text.length()) / 2);
    SetColor(bg_color, text_color);
    cout << text;
    SetColor(0, 7);    
}

void drawLine(int x1, int y1, int x2, int y2, string lineChar)
{
    while (x1 != x2 || y1 != y2)
    {
        if (x1 < x2)
            x1++;
        else if (x1 > x2)
            x1--;
        
        if (y1 < y2)
            y1++;
        else if (y1 > y2)
            y1--;

        GoTo(x1, y1);
         _setmode(_fileno(stdout), _O_U16TEXT);
        wcout << L"\u25A0";
         _setmode(_fileno(stdout), _O_TEXT);
    }
}
