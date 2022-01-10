#ifndef  _PLAYER_H_
#define  _PLAYER_H_
enum Direction {
		STOP,
		RIGHT, 
		LEFT, 
		UP, 
		DOWN
	};
//宣告前進方向列舉函數
class character {
public:
    double x;
    double y;
    int speed;
    Direction dir;
    character(int y_in, int x_in, int speedSet);
    character();
    void movecharacter(double DeltaTime);
};
#endif