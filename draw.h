
#include "console.cpp"

void drawCell(string text, int x, int y, int cellSizeRow, int cellSizeColumn, int bg_color = black, int text_color = white, int mode = 0); 
// NOTE
// mode = 0, draw normally
// mode = 1, highlight the cell


void drawLine(int x1, int y1, int x2, int y2, string lineChar);
