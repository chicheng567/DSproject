#include "include/Game.h"
#include "include/Clock.h"
#include "include/player.h"
#include "include/screen.h"
#include "include/DrawField.h"
//老子直接在你檔案裡宣告
int calcSteps(Location start, Location goal);
PathPointer buildPath(PathPointer goal);
Location nextStepLoc(character& node, Direction direct);


Game::Game() {
    character firstZombie(15, 15, 4);
    Player.dir = STOP;
    Player.speed = 8;
    Player.x = 4;
    Player.y = 2;
    zombies.push_back(firstZombie);
    
	openWindow();
}
Game::~Game() {
	closegraph();
}

int Game::playGame() {

	gameClock.initClock();
    killedCount = 0; 
	srand((unsigned)time(NULL)); //取目前系統時間作為亂數種子
	gameClock.initClock();
	ChangeField(field);
	createResource();
	createResource();
	bool addingZombie = 1;
    while(true){
		showInfo();
		SCREEN.update();
		cleardevice();
		gameClock.updateClock();
		//kb control
		controlPlayerDirection();
		controlZombieDirection();
		Player.movecharacter(gameClock.getDeltaTime());
		playerCollectResource();
		
		if((gameClock.getTotalTime() / CLOCKS_PER_SEC) % 15 == 0 && (gameClock.getTotalTime() / CLOCKS_PER_SEC) != 0) {
			if(addingZombie) {
				addZombie();
				
				cout << "add " << zombies.size() <<"Time: " << gameClock.getTotalTime() / CLOCKS_PER_SEC << " " << addingZombie << endl;
				addingZombie = 0;
			}
		}
		else {
			addingZombie = 1;
		}


		for(character &i : zombies) {
			i.movecharacter(gameClock.getDeltaTime());
		}
		screen::drawScreen(field, Player, zombies);
		
		if(IsGameOver()) {
			break;
		}
	}
    return 1;
}


void Game::openWindow(){
	initwindow(SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3);
}
bool Game::IsAtZombie(int row, int col){

	for(character i : zombies) {
		if (row == i.y && col == i.x)
			return true;
	}		
	return false;
}
bool Game::IsAtWall(int row, int col){
		if (field[row][col] == WALL)
			return true;
		return false;
}
bool Game::IsGameOver(){

	//檢查是否AI撞到喪屍 
	if(IsAtZombie(Player.y, Player.x))
			return true;
	
	return false;
}
void Game::controlPlayerDirection() {
	Direction playerDirect = Player.dir;
	
	//get key code by pressing keybord
	if(GetAsyncKeyState(VK_UP)){
		if (IsAtWall(Player.y-1, Player.x)){
			playerDirect = STOP;
		}
		else{
			playerDirect = UP;
		}
	
	}
	else if(GetAsyncKeyState(VK_DOWN)){
		if (IsAtWall(Player.y+1, Player.x)){
			playerDirect = STOP;
		}
		else{
			playerDirect = DOWN;
		}
	}
	else if(GetAsyncKeyState(VK_LEFT)){
		if (IsAtWall(Player.y, Player.x-1)){
			playerDirect = STOP;
		}
		else{
			playerDirect = LEFT;
		}
	}
	else if(GetAsyncKeyState(VK_RIGHT)){
		if (IsAtWall(Player.y, Player.x+1)){
			playerDirect = STOP;
		}
		else{
			playerDirect = RIGHT;
		}
	}
	else {
		playerDirect = STOP;
	}
	//decide zombie's moving direction	
	Player.dir = playerDirect;;
}
void Game::addZombie(){
	int row, col;
	do{
		row = rand() % GRID_SIDE;
		col = rand() % GRID_SIDE;	
	}while(IsAtWall(row, col) || IsAtZombie(row, col) || (Player.y == row && Player.x == col));	
	character newZombie(row, col, 4);
	zombies.push_back(newZombie);
}
void Game::showInfo(){
	char timeMsg[45] = " Time:";
	char scoreMsg[45] = "Score:";
	char killedMsg[50] = "Killed Zombie:";
	char modeMsg[20] = "";
	char optMsg1[50] = "press [q] to quit, [s] to restart or";
	char optMsg2[50] = "press [a] to change mode.";
	
	char time[10];
	char score[10];
	char killed[10];
	sprintf(time, "%5d", gameClock.getTotalTime() / CLOCKS_PER_SEC);
	strcat(timeMsg, time);
	strcat(timeMsg, " sec.");
	
	setcolor(WHITE); //設定文字顏色 
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1); //設定字型，水平或垂直和字型大小 
   	outtextxy(0, 0, timeMsg); //依據坐標輸出文字到螢幕	
	
	sprintf(score, "%5d", scoreSum);
	strcat(scoreMsg, score);
	strcat(scoreMsg, " point.");

	setcolor(WHITE);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, 19, scoreMsg);
   	
 	sprintf(killed, "%3d", killedCount);
	strcat(killedMsg, killed);  	
   	
   	setcolor(WHITE);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(250, 19, killedMsg);
   	
   	if(IFPlayAI){
   		strcat(modeMsg, "AI Mode    ");
	}else{
   		strcat(modeMsg, "Player Mode");
	}
			
   	setcolor(LIGHTMAGENTA);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(SCREEN_HEIGHT - LEFT_MARGINE * 2, 0, modeMsg);
   	
   	setcolor(LIGHTGREEN);
   	settextstyle(COMPLEX_FONT, HORIZ_DIR , 1);
   	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE, optMsg1);
	outtextxy(0, TOP_MARGINE + (GRID_SIDE + 2) * SCREEN_HEIGHT / GRID_SIDE + 20, optMsg2);	      	
}

void Game::createResource(){
    int row, col, i, amount = RESOURCE_AMOUNT;

    for(i=0; i< amount; i++){
        do{
            row = rand() % GRID_SIDE;
            col = rand() % GRID_SIDE;
        }while(IsAtWall(row, col) || IsAtZombie(row, col));

            if(AllResource.size() <= 15){
                field[row][col] = RESOURCE;
				Location NewResource = {row, col};
				AllResource.push_back(NewResource);
                screen::drawSquare(row,col, GREEN);
            }

    }
}

void Game::playerCollectResource(){
	if(field[(int)Player.y][(int)Player.x] == RESOURCE){
		field[(int)Player.y][(int)Player.x] = EMPTY; 
		int i;
		for (i = 0; i < AllResource.size(); i++) {
			if (AllResource[i].row == (int)Player.y && AllResource[i].col == (int)Player.x) {
				AllResource.erase(AllResource.begin() + i);
				break;
			}
		}
		printf("The player has eaten food at row: %d, col: %d\n", (int)Player.y, (int)Player.x);
		scoreSum += scorePerResource; 
		if(scoreSum % PER_RESOURCE_KILL == 0) 
			killZombie();
	}
}

void Game::killZombie() {
	if(zombies.size() > 1) {
		zombies.pop_back();
	}
}


void Game::controlZombieDirection() {
	int count = 0;
	for(character& i : zombies) {
		Location target = {Player.y + count, Player.x + count};
		Direction zombieDirect = zombieAI(i, target);
		i.dir = zombieDirect;
		count += 2;
	}
}


Direction Game::zombieAI(character &zombie, Location target) {
    Direction zombieDirect = zombie.dir;
    Location start = {zombie.y, zombie.x};

    Location nearestResource = findNearestResourceA(Player);
    Location player_position = {Player.y, Player.x};
	character playerfood(nearestResource.row, nearestResource.col, 0);
    Location secondResource = findNearestResourceA(playerfood);

    //��������a���Z��
    int zombie_player = 0;
    zombie_player = calcSteps(start, player_position);
    //�����nearestResource���Z��
    int zombie_nearest = 0;
    zombie_nearest = calcSteps(start, nearestResource); 

    //secondResource
    int secondResourcestep = 0;
    secondResourcestep = calcSteps(start, secondResource);

    PathPointer path = zombieFindPath(start, target);
	
	int player_nearest = calcSteps(player_position, nearestResource);

	if (zombie_player <= player_nearest) {	
    	PathPointer zombie_player_path = zombieFindPath(start, player_position);
		if(zombie_player_path){
            zombieDirect = getDirectionByPath(zombie, zombie_player_path);
        }else{
            zombieDirect = safeDirect4Zombie(zombie);
        }
	}
	else if(secondResourcestep > int(60)){
		PathPointer zombie_second_path = zombieFindPath(start, secondResource);
		if (zombie_second_path) {
			zombieDirect = getDirectionByPath(zombie, zombie_second_path);
		}
		else {
			zombieDirect = safeDirect4Zombie(zombie);
		}
    }
	else{
		PathPointer zombie_nearest_path = zombieFindPath(start, nearestResource);
        if(zombie_nearest_path){
            zombieDirect = getDirectionByPath(zombie, zombie_nearest_path);
        }else{
            zombieDirect = safeDirect4Zombie(zombie);
        }
    }
    return zombieDirect;
}

Direction Game::safeDirect4Zombie(character& zombie){
	int i;
	int dirSize = 4;
	Location loc;
	
	loc = nextStepLoc(zombie, UP);
	if(!IsAtWall(loc.row, loc.col))
		return UP;
	loc = nextStepLoc(zombie, DOWN);
	if(!IsAtWall(loc.row, loc.col))
		return DOWN;
	loc = nextStepLoc(zombie, RIGHT);
	if(!IsAtWall(loc.row, loc.col))
		return RIGHT;
	loc = nextStepLoc(zombie, LEFT);
	if(!IsAtWall(loc.row, loc.col))
		return LEFT;						
	return zombie.dir;
}
Location nextStepLoc(character& node, Direction direct){
	int currRow =  node.y;
	int currCol = node.x;
	int nextRow, nextCol;
	Location loc;
	switch(direct){
		case RIGHT:
			nextRow = currRow;
			nextCol = currCol + 1;
			break;	
		case LEFT:
			nextRow = currRow;
			nextCol = currCol - 1;
			break;
		case UP:
			nextRow = currRow - 1;
			nextCol = currCol;
			break;				
		case DOWN:
			nextRow = currRow + 1;
			nextCol = currCol;		
			break;	
	}
	loc.row = nextRow;
	loc.col = nextCol;
	return loc;
}

Direction Game::getDirectionByPath(character& head, PathPointer path){
	PathPointer nextPath = path->next;
	int horizontal = nextPath->loc.col - head.x;
	int vertical = nextPath->loc.row - head.y;
	if(horizontal == 1)
		return RIGHT;
	else if(horizontal == -1)
		return LEFT;
	
	if(vertical == 1)
		return DOWN;
	else if(vertical == -1)
		return UP;
	return 	head.dir;	
}
Location Game::findNearestResourceA(character& me){
    int rowDis, colDis, row, col, nearest = 100000;
    Location nearestFood = {-1, -1};
    for(row = 0; row < GRID_SIDE; row++){
        for(col = 0; col < GRID_SIDE; col++){
            if(field[row][col] == RESOURCE){
                rowDis = abs(row - me.y);//abs()��^��ƪ������
                colDis = abs(col - me.x);
                if(nearest > (rowDis + colDis)){
                    nearest = (rowDis + colDis);
                    nearestFood.row = row;
                    nearestFood.col = col;
                }
            }
        }
    }
    return nearestFood;
}

int calcSteps(Location start, Location goal){
	int steps = abs(start.row - goal.row) + abs(start.col - goal.col);
	return steps;
}

PathPointer Game::zombieFindPath(Location startLoc, Location goalLoc){
	resetPathQueue();
	int steps = calcSteps(startLoc, goalLoc);
	PathNode start = {0, steps, startLoc, NULL, NULL};
	addPathQueue(start);
	while(!isPathQueueEmpty()){
		sortPathQueue();
		PathPointer current = popPathQueue();
		if(current->loc.row == goalLoc.row && current->loc.col == goalLoc.col)
			return buildPath(current);
		int dirSize = 4;
					//�k �U �� �W
		int iDir[] = {1, 0, -1, 0};
		int jDir[] = {0, 1, 0, -1};
		int i,j;
		for(i=0, j=0; i<dirSize; i++, j++){
			//�P�_�{�b�I���W�U���k��m
			Location neighborLoc = {current->loc.row + iDir[i], current->loc.col + jDir[j]};
			if(!visited(neighborLoc) && !IsAtWall(neighborLoc.row, neighborLoc.col) && !IsAtZombie(neighborLoc.row, neighborLoc.col)){
				int steps = calcSteps(neighborLoc, goalLoc);
				int cost = 	current->cost + 1;
				PathNode neighbor = {cost, steps, neighborLoc, current, NULL};
				if(!IsInPathQueue(neighbor)){
					addPathQueue(neighbor);
				}				
			}
		}
	}
	return NULL;
}
void Game::resetPathQueue(){
	front = -1;
	rear = -1;	
}
void Game::addPathQueue(PathNode pathNode){
	if(rear == MAX_QUEUE_SIZE - 1){
		printf("the queue is full");
		return;
	}
	rear += 1;
	pathQueue[rear]	= pathNode;
}
bool Game::isPathQueueEmpty(){
	return front == rear;
}
void Game::sortPathQueue(){
	if(front == rear)
		return;
	int i, j;
	int nowTotal, nextTotal;
	//bubble sort	
	for(i=front + 1; i<rear; i++){
		for(j=i+1; j<=rear; j++){

			nowTotal = pathQueue[i].cost + pathQueue[i].steps;
			nextTotal = pathQueue[j].cost + pathQueue[j].steps;

			if(nowTotal > nextTotal){
				PathNode temp = pathQueue[i];
				pathQueue[i] = pathQueue[j];
				pathQueue[j] = temp;
			}
		}
	}		
}

PathPointer Game::popPathQueue(){
	if(front == rear){
		printf("the queue is empty");
		return NULL;
	}
	front ++;
	PathPointer node = (PathPointer)malloc(sizeof(PathNode));
	node->cost = pathQueue[front].cost;
	node->steps = pathQueue[front].steps;
	node->loc = pathQueue[front].loc;
	node->parent = pathQueue[front].parent;
	node->next = pathQueue[front].next;
	return node;
}

PathPointer buildPath(PathPointer goal){
	printf("buildPath ");
	printf("(%d, %d)\n", goal->loc.row, goal->loc.col);
	if(goal == NULL || goal->parent == NULL)
		return NULL;
	PathPointer head = goal;
	head->next = NULL;
	PathPointer temp = head;
	
	while(head->parent){
		if(head == NULL)
			return NULL;
		printf("node (%d, %d)->", head->loc.row, head->loc.col);	
		head = head->parent; 
		head->next = temp;
		temp = head;
	}
	printf("NULL\n");
	return head;
}
bool Game::visited(Location loc){
	int i;
	for(i=0;i<=front;i++){
		if(pathQueue[i].loc.row == loc.row && pathQueue[i].loc.col == loc.col)
			return true;
	}
	return false;
}
bool Game::IsInPathQueue(PathNode pathNode){
	int i;
	if(front == rear)
		return false;
	for(i=front;i<=rear;i++){
		if(pathQueue[i].loc.row == pathNode.loc.row && pathQueue[i].loc.col == pathNode.loc.col)
			return true;
	}
	return false;
}

int main() {
    Game game;
	int key = 0;
	while(1) {
		key = game.menu();
		if(key)	break;
	}
	if(key == 1) {
		game.playGame();
	}
    return 0;
}