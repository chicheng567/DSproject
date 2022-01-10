#include "include/DrawField.h"

void ChangeField(int field[][GRID_SIDE]) {
    srand(time(NULL));
    int i, j;

    //畫牆壁 & 初始
    for (i = 0; i < GRID_SIDE; i++) {
		for (j = 0; j < GRID_SIDE; j++) {
			if (i == 0 || j == 0 || i == GRID_SIDE - 1 || j == GRID_SIDE - 1)
            	field[i][j] = 1;
			else 
				field[i][j] = 4;
		}
	}
    graph9(field, 1, 1);
    int cnta = 0, cntb = 0;
    for (i = 1; i < GRID_SIDE - 1; i++) {
        for (j = 1; j < GRID_SIDE - 1; j++) {
            if (field[i][j] == 4) {
                int p = rand() % 100; //數字越大地圖物件越少
                switch (p) {
                    case 1:
                        graph1(field, i, j);
                        break;
                    case 2:
                        graph2(field, i, j);
                        break;
                    case 3:
                        graph3(field, i, j);
                        break;
                    case 4:
                        graph4(field, i, j);
                        break;
                    case 5:
                        graph5(field, i, j);
                        break;
                    case 6:
                        graph6(field, i, j);
                        break;
                    case 7:
                        graph7(field, i, j);
                        break;
                    case 8:
                        graph8(field, i, j);
                        break;     
                    case 9:
                        if (cnta < 2) {
                            graph9(field, i, j);
                            cnta++;
                        }
                        break;
                    case 10:
                        if (cntb < 2) {
                            graph10(field, i, j);
                            cntb++;
                        }
                        break;                                       
                    default:
                        break;
                }
            }
        }
    }

    for (i = 0; i < GRID_SIDE; i++) {
        for (j = 0; j < GRID_SIDE; j++) {
            if (field[i][j] == 4) {
                field[i][j] = 0;
            }
        }
    }
}

// 橫長條
bool graph1(int field[][GRID_SIDE], int row, int col) {
    //3 * 9
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    printf("graph(%d, %d) \n", row, col);
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 9; j++) {
            if (i == 1 && j != 0 && j != 8) 
                field[row + i][col + j] = 1;
            else 
                field[row + i][col + j] = 0;
        }
    }
    return true;

}

// 直長條
bool graph2(int field[][GRID_SIDE], int row, int col) {
    //9 * 3
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 3; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    printf("graph(%d, %d) \n", row, col);
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 3; j++) {
            if (j == 1 && i != 0 && i != 8) 
                field[row + i][col + j] = 1;
            else 
                field[row + i][col + j] = 0;
        }
    }
    return true;

}

// 大十字
bool graph3(int field[][GRID_SIDE], int row, int col) {
    //9 * 9
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (i == 4 && j != 0 && j != 8) 
                field[row + i][col + j] = 1;
            else if (j == 4 && i != 0 && i != 8)
                field[row + i][col + j] = 1;
            else 
                field[row + i][col + j] = 0;
        }
    }
    return true;

}


// 小十字
bool graph4(int field[][GRID_SIDE], int row, int col) {
    //7 * 7
    int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 7; j++) {
            if (i == 3 && j != 0 && j != 6) 
                field[row + i][col + j] = 1;
            else if (j == 3 && i != 0 && i != 6)
                field[row + i][col + j] = 1;
            else 
                field[row + i][col + j] = 0;
        }
    }
    return true;

}

// 左C
bool graph5(int field[][GRID_SIDE], int row, int col) {
    //10 * 6
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            if ((i == 1 || i == 8) && j != 0 && j != 5)
                field[row + i][col + j] = 1;
            else if (j == 1 && i != 0 && i != 9)
                field[row + i][col + j] = 1;
            else
                field[row + i][col + j] = 0;
        }
    }
    return true;

}

// 右C
bool graph6(int field[][GRID_SIDE], int row, int col) {
    //10 * 6
    int i, j;
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    for (i = 0; i < 10; i++) {
        for (j = 0; j < 6; j++) {
            if ((i == 1 || i == 8) && j != 0 && j != 5)
                field[row + i][col + j] = 1;
            else if (j == 4 && i != 0 && i != 9)
                field[row + i][col + j] = 1;
            else
                field[row + i][col + j] = 0;
        }
    }
    return true;

}

// 閃電恩
bool graph7(int field[][GRID_SIDE], int row, int col) {
    //7 * 6
    int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (i == 3 && j != 0 && j != 5)
                field[row + i][col + j] = 1;
            else if (j == 1 && i > 0 && i < 4)
                field[row + i][col + j] = 1;
            else if (j == 4 && i > 2 && i < 6)
                field[row + i][col + j] = 1;
            else
                field[row + i][col + j] = 0;
        }
    }
    return true;
}

// 逆閃電恩
bool graph8(int field[][GRID_SIDE], int row, int col) {
    //7 * 6
    int i, j;
    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }

    for (i = 0; i < 7; i++) {
        for (j = 0; j < 6; j++) {
            if (i == 3 && j != 0 && j != 5)
                field[row + i][col + j] = 1;
            else if (j == 1 && i > 2 && i < 6)
                field[row + i][col + j] = 1;
            else if (j == 4 && i > 0 && i < 4)
                field[row + i][col + j] = 1;
            else
                field[row + i][col + j] = 0;
        }
    }
    return true;
}

// 左斜下
bool graph9(int field[][GRID_SIDE], int row, int col) {
    //5 * 5
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }
    
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (i == j) 
                field[row + i][col + j] = 1;
            else
                field[row + i][col + j] = 0;
        }
    }
    return true;
}

// 右斜下
bool graph10(int field[][GRID_SIDE], int row, int col) {
    //5 * 5
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (field[row + i][col + j] != 4 || row + i > GRID_SIDE || col + j > GRID_SIDE) return false;
        }
    }
    
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (i + j == 4) 
                field[row + i][col + j] = 1;
            else 
                field[row + i][col + j] = 0;
        }
    }
    return true;
}

