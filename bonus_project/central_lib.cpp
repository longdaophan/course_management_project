#include "central_lib.h"
void gotoxy(int x, int y)
{
    COORD coor = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coor);
}
void drawbox(int col, int row, int width, int height)
{
    gotoxy(col, row);
    for (int i = 0; i < width; i++)
        cout << '*';
    for (int i = 0; i < height; i++)
    {
        gotoxy(col + width, row + i);
        cout << '*';
    }
    for (int i = width + col; i > col; i--)
    {
        gotoxy(i, row + height);
        cout << '*';
    }
    for (int i = row + height; i > row; i--)
    {
        gotoxy(col, i);
        cout << '*';
    }
}