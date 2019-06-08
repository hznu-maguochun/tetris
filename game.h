#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#define blocklength  0.3333333



#ifndef GAME_H_
#define GAME_H_

struct Tetris		//声明俄罗斯方块的结构体
{
 	int x;     		//中心方块的x轴坐标
 	int y;     		//中心方块的y轴坐标
 	int flag;    	//标记方块类型的序号
 	int next;    	//下一个俄罗斯方块类型的序号
 	int speed;    	//俄罗斯方块移动的速度
 	int number;    	//产生俄罗斯方块的个数
 	int score;    	//游戏的分数
 	int level;    	//游戏的等级
};



void keyboard_game(int key, int event);
void MakePlayingWindow(struct Tetris *tetris);

void drawblock (double x,double y);

void MakeTetris(struct Tetris *tetris);

void PrintTetris(struct Tetris *tetris);

int checknum(struct Tetris *tetris);
char *checkcolor(struct Tetris *tetris);
char *numtocolor(int num); 
void Reset(void);


int ifMove(struct Tetris *tetris);		//?P?_?O?_????A??^???1?A????A?_?h?A??????
void CleanTetris(struct Tetris *tetris);	//?M???Xù???????????
void Flag(struct Tetris *tetris);			//?H?????????????????
void Del_Fullline(struct Tetris *tetris);	//?P?_?O?_????A??R?????檺?Xù?????

void initial(void);
void Continue();

void changespeed(int v);
#endif



