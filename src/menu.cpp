#include "include/Game.h"
#include "include/Clock.h"
#include "include/player.h"
#include "include/screen.h"
MenuBtn::MenuBtn(int x, int y, int WIDTH, int HEIGHT) {//constructor
    startX = x;
    startY = y;
    width = WIDTH;
    height = HEIGHT;
}
void animate_light(int d_time, int set_time, int &frame);
MenuBtn startBtn(150, 330, 280, 120), exitBtn(230, 390, 280, 120);//menu全部按鈕
vector<MenuBtn> btn = {startBtn, exitBtn};
//for title and dot animation
int duration1 = 0, duration2 = 0;
int titleColor[3] = {RED, BLUE, GREEN};
int xStep = 0, yStep = 0, xf = 0, yf = 0, zombXStep = 0, zombYStep = 0;

//turn on light animation
int animation_duration[20], frame = 0;
bool play_animation = false, light_on = false;
int title_light = 0;

//options choose
int currentButton = 1;
    
int Game::menu() {
	
	settextstyle(BOLD_FONT, HORIZ_DIR , 6);
	SCREEN.update();
	cleardevice();
	gameClock.updateClock();
	//light animation

	if(GetAsyncKeyState(VK_RIGHT)&&light_on){
		light_on = false;
		play_animation = false;
		int u = 0;
		for(u;u<10;u++){
			animation_duration[u] = 0;
		}
	}
	if(GetAsyncKeyState(VK_SPACE)){
		return currentButton + 1;
	}
	if(!play_animation&&GetAsyncKeyState(VK_LEFT)){
		play_animation = true;
		frame = 0;
	}
	if(play_animation){
		animation_duration[frame] += gameClock.getDeltaTime();
		switch (frame)
		{
		case 0:
			animate_light(animation_duration[0], 250, frame);
			break;
		case 1:
			if(animation_duration[1]>250) frame++;
			break;
		case 2:
			animate_light(animation_duration[2], 60, frame);
			break;
		case 3:
			animate_light(animation_duration[3], 60, frame);
			break;
		case 4:
			animate_light(animation_duration[4], 150, frame);
			break;
		case 5:
			animate_light(animation_duration[5], 100, frame);
			break;
		case 6:
			animate_light(animation_duration[6], 70, frame);
			break;
		case 7:
			if(animation_duration[7]>250) frame++;//要黑畫面，所以不進function，而是不做反應，直到達到設定時間，進到下一個frame
			break;
		case 8:
			animate_light(animation_duration[8], 280, frame);
			break;
		case 9:
			if(animation_duration[9]>330) frame++;
			break;
		case 10:
			// animate_light(animation_duration[9], );
			light_on = true;
		default:
			break;
		}
	}
	if(light_on){
		setfillstyle(SOLID_FILL, WHITE);
		bar(0, 0, SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3);	
	}
	
	duration1 += gameClock.getDeltaTime();
	duration2 += gameClock.getDeltaTime();
	//SET and PRINT TITLE: ZOMBIE SURVIVAL
	if(duration1 >= 800){
		duration1 = 0;//reset
		setcolor(titleColor[title_light]);
		if(title_light == 2) title_light = 0;
		else title_light++;
	}else setcolor(titleColor[title_light]);
	outtextxy(130, 130, "ZOMBIE");
	outtextxy(180, 200, "SURVIVAL");

	//option
	outtextxy(btn[1].startX, btn[1].startY, "Quit");
	outtextxy(btn[0].startX, btn[0].startY, "StartGame");
	if(GetAsyncKeyState(VK_UP)){//選項壞掉
		currentButton = 0;
	}else if(GetAsyncKeyState(VK_DOWN)){
		currentButton = 1;
	}

	settextstyle(BOLD_FONT, HORIZ_DIR , 6);
	if(currentButton == 0){//current == start
		setcolor(WHITE);
		outtextxy(btn[0].startX, btn[0].startY, "->StartGame");
		setcolor(LIGHTGRAY);
		outtextxy(btn[1].startX, btn[1].startY, "Quit");
	}else{
		setcolor(WHITE);
		outtextxy(btn[1].startX, btn[1].startY, "->Quit");
		setcolor(LIGHTGRAY);
		outtextxy(btn[0].startX, btn[0].startY, "StartGame");
	}
	

	//dot animation
	setfillstyle(SOLID_FILL, WHITE);
	int xsteps[100]{1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1
	, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, -1, -1, -1, -1, -1, 0, 0, -1, -1, -1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1};
	int ysteps[100]{0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
	, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, -1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0};
	int zombiestepsX[100]{0, 0, 1, 1, 1, 1, 1, 0, -1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, -1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0};
	int zombiestepsY[100]{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0 , 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
	if(duration2 >= 300){
		duration2 = 0;
		
		//human
		switch (xsteps[xf])
		{
		case 1:
			/* code */
			xStep++;
			break;
		case -1:
			xStep--;
			break;
		default:
			break;
		}
		switch (ysteps[yf])
		{
		case 1:
			/* code */
			yStep++;
			break;
		case -1:
			yStep--;
			break;
		default:
			break;
		}

		//zombie
		switch (zombiestepsX[xf])
		{
		case 1:
			/* code */
			zombXStep++;
			break;
		case -1:
			zombXStep--;
			break;
		default:
			break;
		}
		switch (zombiestepsY[yf])
		{
		case 1:
			/* code */
			zombYStep++;
			break;
		case -1:
			zombYStep--;
			break;
		default:
			break;
		}

		xf++;
		yf++;
	}
	screen::drawSquare(yStep, xStep, BLUE);
	screen::drawSquare(zombYStep, zombXStep, RED);


	int col = -2, row = -7;
	for(col; col < 50; col++){
		screen::drawSquare(-3, col, YELLOW);
		screen::drawSquare(43.5, col, YELLOW);
	}
	for(row; row < 50; row++){
		screen::drawSquare(row, -2, YELLOW);
		screen::drawSquare(row, 42, YELLOW);
	}
    return 0;
}

void animate_light(int d_time, int set_time, int &frame){
	setfillstyle(SOLID_FILL, WHITE);
	bar(0, 0, SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3);		
	if(d_time >= set_time){
		setfillstyle(SOLID_FILL, BLACK);
		bar(0, 0, SCREEN_WIDTH + LEFT_MARGINE * 3, SCREEN_HEIGHT + TOP_MARGINE * 3);
		frame++;
	}
}