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

#include "imgui.h"
#include "game.h" 
#include "Interface.h"
#include "fileop.h"



/***************************************************************
 VisualStudio 2010 �û�ע�⣺
    ��Character Set����Ϊ Use Multibyte Character Set
	����������ʾ������
***************************************************************/

void KeyboardEventProcess(int key,int event);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);/*?p????????^?I???*/
void CharEventProcess(char ch);


// ȫ�ֱ���
double winwidth, winheight;   // ���ڳߴ�
int Flag_button=0,running=0;
int IF=0;

// ����������provided in libgraphics
//void DisplayClear(void); 
// ��ʱ������������provided in libgraphics
//void startTimer(int id,int timeinterval);

// �û�����ʾ����
//void display(void); 



// �û����������
// ����ʼ��ִ��һ��
void Main()
{
	// ��ʼ�����ں�ͼ��ϵͳ
	SetWindowTitle("Tetris Game");
	
    InitGraphics();
    //Randomize();/*��ʼ��һ���������*/


    winwidth = GetWindowWidth();     //��ȡ���ڿ�� 
	winheight = GetWindowHeight();   //��ȡ���ڸ߶� 


    
	// ע��ʱ����Ӧ����
	registerCharEvent(CharEventProcess);        // �ַ�
	registerKeyboardEvent(KeyboardEventProcess);// ����
	registerMouseEvent(MouseEventProcess);      // ���
	registerTimerEvent(TimerEventProcess);      // ��ʱ��
	//display();
	
}

// �û����ַ��¼���Ӧ����
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI�ַ�����
	display(); //ˢ����ʾ
}

// �û��ļ����¼���Ӧ����
void KeyboardEventProcess(int key, int event)
{
	if (IF==0){
	uiGetKeyboard(key,event); // ֻ��IF=0ʱ��Ӧ�������� 
	
	display(); // ˢ����Ļ�����˵��� 

	}
	
	else if(IF==1)
	{
		keyboard_game(key, event);
	}	
} 


// �û�������¼���Ӧ����
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI��ȡ���
	display(); // ˢ����ʾ
	/*while(Flag_game)
	{
		DisplayClear();
		if(event = BUTTON_DOWN)  exit(-1);
	}*/
}




