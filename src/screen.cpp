#include "include/screen.h"
#include<iostream>
#include <graphics.h>
screen::screen()
{ //constructor
    page = 0;
}

void screen::update()
{
    page = 1 - page;
    setactivepage(page);
    setvisualpage(1 - page);
    delay(10);
}
void screen::drawSquare(int row, int col, int color)
{
    //row as y
    //col as x

    int squareHeight = SCREEN_HEIGHT / GRID_SIDE;
    int SquareWidth = SCREEN_WIDTH / GRID_SIDE;
    int left = 0, right = 0, bottom = 0, top = 0;
    left = LEFT_MARGINE + col * SquareWidth + col;
    top = TOP_MARGINE + row * squareHeight + row;
    right = left + SquareWidth;
    bottom = top + squareHeight;

    setfillstyle(SOLID_FILL, color); //設定繪製物件的為實心和顏色
    bar(left, top, right, bottom);   //設定繪製方塊的位置
}

void screen::drawScreen(int field[][GRID_SIDE], character& Player, vector<character>& zombies)
{
    int row = 0, col = 0;
    cleardevice(); //清理螢幕畫面
    for (row = 0; row < GRID_SIDE; row++)
    {
        for (col = 0; col < GRID_SIDE; col++)
        {
            switch (field[row][col])
            {
            case 1: //牆在矩陣中的值是1
                drawSquare(row, col, YELLOW);
                break;
            case 2: //資源在矩陣中的值是2
                drawSquare(row, col, GREEN);
                break;
            }
        }
    }
    drawSquare((int)Player.y, (int)Player.x, BLUE);
    
    for(character i : zombies) {
        drawSquare((int)i.y, (int)i.x, RED);
    }
}