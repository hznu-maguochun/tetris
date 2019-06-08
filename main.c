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
 VisualStudio 2010 用户注意：
    将Character Set设置为 Use Multibyte Character Set
	否则中文显示不正常
***************************************************************/

void KeyboardEventProcess(int key,int event);
void MouseEventProcess(int x, int y, int button, int event);
void TimerEventProcess(int timerID);/*?p????????^?I???*/
void CharEventProcess(char ch);


// 全局变量
double winwidth, winheight;   // 窗口尺寸
int Flag_button=0,running=0;
int IF=0;

// 清屏函数，provided in libgraphics
//void DisplayClear(void); 
// 计时器启动函数，provided in libgraphics
//void startTimer(int id,int timeinterval);

// 用户的显示函数
//void display(void); 



// 用户主程序入口
// 仅初始化执行一次
void Main()
{
	// 初始化窗口和图形系统
	SetWindowTitle("Tetris Game");
	
    InitGraphics();
    //Randomize();/*初始化一个随机种子*/


    winwidth = GetWindowWidth();     //获取窗口宽度 
	winheight = GetWindowHeight();   //获取窗口高度 


    
	// 注册时间响应函数
	registerCharEvent(CharEventProcess);        // 字符
	registerKeyboardEvent(KeyboardEventProcess);// 键盘
	registerMouseEvent(MouseEventProcess);      // 鼠标
	registerTimerEvent(TimerEventProcess);      // 定时器
	//display();
	
}

// 用户的字符事件响应函数
void CharEventProcess(char ch)
{
	uiGetChar(ch); // GUI字符输入
	display(); //刷新显示
}

// 用户的键盘事件响应函数
void KeyboardEventProcess(int key, int event)
{
	if (IF==0){
	uiGetKeyboard(key,event); // 只在IF=0时响应击键输入 
	
	display(); // 刷新屏幕（主菜单） 

	}
	
	else if(IF==1)
	{
		keyboard_game(key, event);
	}	
} 


// 用户的鼠标事件响应函数
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x,y,button,event); //GUI获取鼠标
	display(); // 刷新显示
	/*while(Flag_game)
	{
		DisplayClear();
		if(event = BUTTON_DOWN)  exit(-1);
	}*/
}




