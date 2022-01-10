#include"include/player.h"
#include "include/Game.h"
#include <iostream>

character::character(int y_in, int x_in, int speedSet): dir(STOP), x(x_in), y(y_in), speed(speedSet) {}
character::character(): dir(STOP), x(0), y(0), speed(0) {}
void character::movecharacter(double DeltaTime) {
    if(dir != STOP) {
       double DeltaMove = DeltaTime * speed / 1000;
       if(dir == RIGHT) x += DeltaMove;
       else if(dir == LEFT)  x -= DeltaMove;
       else if(dir == UP)    y -= DeltaMove;
       else if(dir == DOWN)  y += DeltaMove;
    }
}