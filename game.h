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

struct Tetris		//��������˹����Ľṹ��
{
 	int x;     		//���ķ����x������
 	int y;     		//���ķ����y������
 	int flag;    	//��Ƿ������͵����
 	int next;    	//��һ������˹�������͵����
 	int speed;    	//����˹�����ƶ����ٶ�
 	int number;    	//��������˹����ĸ���
 	int score;    	//��Ϸ�ķ���
 	int level;    	//��Ϸ�ĵȼ�
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
void CleanTetris(struct Tetris *tetris);	//?M???X��???????????
void Flag(struct Tetris *tetris);			//?H?????????????????
void Del_Fullline(struct Tetris *tetris);	//?P?_?O?_????A??R?????��?X��?????

void initial(void);
void Continue();

void changespeed(int v);
#endif



