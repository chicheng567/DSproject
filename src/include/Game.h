#ifndef  _GAME_H_
#define  _GAME_H_
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <math.h>
#include <vector>
#include "mingw.thread.h"
#include "player.h"
#include "Clock.h"
#include "screen.h"
#include <iostream>

using namespace std;
//定義座標結構 
	struct Location {
		int row;
		int col;
	};
	typedef struct PathNode *PathPointer;
	//定義路徑節點結構，用來建立移動路徑 
	struct PathNode {
		int cost; //距離原點的步數 
		int steps; //距離目標的步數 
		Location loc;
		PathPointer parent;
		PathPointer next;
	};
class Game {
private:
	//宣告遊戲場出現物體列舉函數 
	enum Object {
		EMPTY, //空白 
		WALL, //牆或障礙物 
		RESOURCE, //資原
		ZOMBIE,
		PLAYER
	};
	
	

	
	// attributes
	character Player;
	GameClock gameClock;
	vector<character> zombies;
	vector <Location> AllResource;
	struct PathNode pathQueue[MAX_QUEUE_SIZE]; //宣告將要拜訪的節點柱列 
	int front; //queue 第一個元素的前一個位置 
	int rear; //queue 最後一個元素的位置
	screen SCREEN;
	
	
	int scoreSum = 0; //紀錄分數 
	int killedCount = 0; //殺死喪屍數量 
	int totalTime = 0; //紀錄遊戲時間 
	int stepCount = 0; //步數計數器 
	int const scorePerResource = 1; //每一份資源可得分數
	bool IFPlayAI = false; //是否開啟AI模式 
	bool IFPause = false; //是否暫停
public:
	int field[GRID_SIDE][GRID_SIDE];
	//game proccess
	Game();
	~Game();

	void openWindow(); //開啟游戲視窗
	int playGame(); //遊戲進行邏輯 
	//inputs
	void controlPlayerDirection(); //讀取鍵盤方向輸入，或者AI輸入
	void playerCollectResource();
	//detects
	bool IsAtWall(int row, int col); //判斷是否撞到牆 
	bool IsAtZombie(int row, int col);//判斷是否撞到喪屍
	bool IsGameOver(); //(生存者死亡條件：撞牆和撞到喪屍)
	void upDateCharacter();
	void showInfo();
	int menu();
	void createResource();
	void controlZombieDirection();
	void killZombie();
	void addZombie();
	Direction zombieAI(character &zombie,Location target);
	Location findNearestResourceA(character& me);
	PathPointer zombieFindPath(Location startLoc, Location goalLoc);
	void resetPathQueue();
	void addPathQueue(PathNode pathNode);
	bool isPathQueueEmpty();
	void sortPathQueue();
	PathPointer popPathQueue();
	bool visited(Location loc);
	bool IsInPathQueue(PathNode pathNode);
	Direction getDirectionByPath(character& head, PathPointer path);
	Direction safeDirect4Zombie(character& zombie);
};


#endif