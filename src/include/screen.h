
#ifndef  _SCREEN_H_
#define  _SCREEN_H_
#define SCREEN_HEIGHT 500 //設定遊戲視窗高度 
#define SCREEN_WIDTH 500 //設定遊戲視窗寬度
#define GRID_SIDE 40 //設定遊戲方陣每邊格子數量 
#define LEFT_MARGINE 30 //設定左邊界 
#define TOP_MARGINE 40 //設定上邊界 
#define RESOURCE_AMOUNT 1 //設定每次產生資源數量 
#define PER_RESOURCE_KILL 5 //設定多少資源數量可以殺掉一隻喪屍 
#define INIT_SPEED  80 //設定初始移動速度 
#define MAX_QUEUE_SIZE 1600 //設定柱列大小
#include <vector>
#include "player.h"
using namespace std;
class screen
{
private:
    /* data */
    int page;
public:
    screen();
    void update();
    static void drawSquare(int row, int col, int color);
    static void drawScreen(int field[][GRID_SIDE], character& Player, vector<character>& zombies);
};

class MenuBtn
{
private:
    /* data */
public:
    MenuBtn(int x, int y, int WIDTH, int HEIGHT);
    int startX, startY;
    int width, height;
    int color;
};

#endif