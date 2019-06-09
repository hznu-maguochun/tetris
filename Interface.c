#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>


#include "imgui.h"
#include "Interface.h"
#include "fileop.h"
#include "game.h"



#if defined(DEMO_MENU)

extern double winwidth, winheight;
struct Tetris *lastinfo;
extern  struct Tetris *tetris; 
static int show_more_buttons = 0; // 显示更多按钮 
extern int game_running;//跳转游戏界面flag和游戏运行状态
extern int IF;
extern bool pau;



// 菜单演示程序
void drawMenu()
{ 
	static char * menuListSys[] = {"System",  
		"Setting", 
		"Exit  | Ctrl-E"}; // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾

	static char * menuListOP[] = {"Operate",
		"Start | Ctrl-S",
		"Continue",
		"Rank"};
	static char * menuListRunningOP[] = {"Operate",
		"Stop",
		"Pause | ctrl-p"};

	static char * menuListHelp[] = {"Help",
	    "Introduction",
		"About"};

	double fH = GetFontHeight();
	double x = 0; //fH/8;
	double y = winheight;
	double h = fH*1.5; // 控件高度
	double w = TextStringWidth(menuListHelp[0])*3; // 控件宽度
	double wlist = TextStringWidth(menuListOP[3])*3.2;
	double xindent = winheight/20; // 缩进
	int    selection;

	
	// menu bar
	drawMenuBar(0,y-h,winwidth,h);
	// system 菜单
	selection = menuList(GenUIID(0), x, y-h, w, wlist, h, menuListSys, sizeof(menuListSys)/sizeof(menuListSys[0]));
	if( selection==1 )
	{ 
	    IF = 1;
	    DisplayClear(); 
		drawMenu();
    	drawButtons();
    } 
	else if(selection == 2)
	    exit(-1); // choose to exit
	
	// operate 菜单
	if (game_running){
		selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListRunningOP,sizeof(menuListRunningOP)/sizeof(menuListRunningOP[0]));	
		switch(selection)
		{
			case 1:
				IF = 4;
	    		DisplayClear(); 
				drawMenu();
				drawButtons();
				break;
			case 2:
				IF = 5;
	    		DisplayClear();
				drawMenu();
			    drawButtons();
			    break; 
			default:
				break;
		}
	}else{
		selection = menuList(GenUIID(0),x+w,  y-h, w, wlist,h, menuListOP,sizeof(menuListOP)/sizeof(menuListOP[0]));	
		switch(selection)
		{
			case 1:
				IF = 2;
	    		DisplayClear();
				drawMenu();
				drawButtons();
				break;
			case 2:
				IF = 3;
	    		DisplayClear();
				drawMenu();
			    drawButtons();
			    break;
			case 3:
				IF = 8;
	    		DisplayClear();
				drawMenu();
				drawButtons();
				break;
			default:
				break;
		}
	}

	
	// Help 菜单
	selection = menuList(GenUIID(0),x+2*w,y-h, w, wlist, h, menuListHelp,sizeof(menuListHelp)/sizeof(menuListHelp[0]));
	if( selection==1 )
	{ 
	    //DisplayClear();
    	//introducewindow();
    	IF=6;
    	DisplayClear();
	    drawMenu();
    	drawButtons();
   	} 
	else  if(selection == 2){ 
 	    IF = 7;
	    DisplayClear();
	    drawMenu();
    	drawButtons();
	    //AboutWindow();
    } 
}

#endif // #if defined(DEMO_MENU)



#if defined(DEMO_BUTTON)
// 按钮演示程序
void drawButtons()
{
	double fH = GetFontHeight();
	double h = fH*3;  // 控件高度
	double x = winwidth/2.5; 
	double y = winheight/2;
	double w = winwidth/5; // 控件宽度
	
	SetPointSize(10);
	usePredefinedButtonColors(0);
	
	switch(IF){
		case 0:
			if( button(GenUIID(0), x, y+2*(h+0.2), w, h, "Start") )
			{
				IF=2; 
				DisplayClear();
				drawButtons();
				break;
			}
			if( button(GenUIID(0), x, y+(h+0.2), w, h, "Continue") )
			{
				IF=3; 
				DisplayClear();
				drawButtons();
				break;
			}		
		    if( button(GenUIID(0), x, y, w, h, "Settings") )
			{
				IF=1;
				DisplayClear();
				drawMenu();
				drawButtons();
				break;			
			}
	    	if( button(GenUIID(0), x, y-(h+0.2), w, h, "How To Play") )
			{
				IF=6;
				DisplayClear();
				drawMenu();
				drawButtons();
				break;
			}
	    	if( button(GenUIID(0), x, y-2*(h+0.2), w, h, "Rank") )
			{
				IF=8;
				DisplayClear();
				drawMenu();
				drawButtons();
				break;
			}
			if( button(GenUIID(0), x, y-3*(h+0.2), w, h, "Quit") ){ 
				exit(-1); 
			}
			break;
		case 1: 
			setting();
			break; 
		case 2: 
		    game_running=1;
			initial();
			break;
		case 3: 
			game_running=1;
			Continue();
			break;
		case 4: 
			Endwindow();
			break;
		case 5: 
			break;
		case 6:  
			introducewindow();
			break;
		case 7: 
			//Aboutwindow();
			break;
		case 8: 
			Rank();
			break;
	}
}
#endif // #if defined(DEMO_BUTTON)


void introducewindow(void)
{
	SetPointSize(40);
	MovePen(1.5,5.5);
	SetPenColor("Magenta");
	DrawTextString("How to Play");
	SetPointSize(30);
	MovePen(2,4.5);
    SetPenColor("Violet");
	DrawTextString("Up: ");
	SetPenColor("Orange");
	DrawTextString("Rotate the Tetris");
	MovePen(2,4);
	SetPenColor("Violet");
	DrawTextString("Left: ");
	SetPenColor("Orange");
	DrawTextString("Move to left");
	MovePen(2,3.5);
	SetPenColor("Violet");
	DrawTextString("Right: ");
	SetPenColor("Orange");
	DrawTextString("Move to right");
	MovePen(2,3);
	SetPenColor("Violet");
	DrawTextString("Down: ");
	SetPenColor("Orange");
	DrawTextString("Speed Up");
	MovePen(2,2.5);
	SetPenColor("Violet");
	DrawTextString("Space: ");
	SetPenColor("Orange");
	DrawTextString("To the Bottom");
	MovePen(3,2.2);
	SetPointSize(20);
	SetPenColor("Orange");
    SetPenColor("Red");
//	DrawTextString("(Input Method of English Keybord)");
	
	SetPointSize(10);
	if( button(GenUIID(0), 7, 1, 2, 0.6, "Back to Menu"))
	{
		IF=0; 
		SetPointSize(10);
		display();
	}

}

void setting(void)
{
	SetPointSize(30);
	MovePen(2,4.63);
    SetPenColor("Violet");
	DrawTextString("Speed: ");
	SetPointSize(20);
	usePredefinedButtonColors(2);
	MovePen(2,2.63);
    SetPenColor("Violet");
	DrawTextString("Current Speed: "); 
	switch (tetris->speed){
		case 500:
			DrawTextString("1/500");
			break;
		case 250:
			DrawTextString("1/250");
			break;
		case 100:
			DrawTextString("1/100");
			break;
	}
	if( button(GenUIID(5), 3.5, 4.5, 1.2, 0.5, "Slow"))
	{
		changespeed(1);
		display();
	}
	else if( button(GenUIID(5), 5, 4.5, 1.2, 0.5, "Middle"))
	{
		changespeed(2);
		display();
	}
	else if( button(GenUIID(5), 6.5, 4.5, 1.2, 0.5, "Fast"))
	{
		changespeed(3);
		display();
	}
	
	SetPointSize(10);
	setButtonColors("Orange", "Yellow", "Cyan", "Violet", 1);
	if( button(GenUIID(4), 7, 1, 2.3, 0.6, "Back to Menu"))
	{
		IF=0; 
		SetPointSize(10);
		display();
	}
}

void Endwindow(void)
{
	DisplayClear();
	MovePen(5,5);
	DrawTextString("END");
	SetPointSize(20);
	if( button(GenUIID(4), 7, 1, 2, 1, "Back to Menu"))
		{
			IF=0;
			display();
		}
	else if( button(GenUIID(4), 7, 5, 2, 1, "QUIT"))
		{
			exit(-1);
		}
}



void display()
{
	//转入游戏界面
	if(game_running)
	{
	//	MakePlayingWindow(tetris);
		return;
	}
	DisplayClear();	
	drawMenu();
	drawButtons();	
}



void Rank()
{
	UserRecordLinkList *p;
	UserRecordNode *tp;
	int i,score;
	char a[2],s[4];
	SetPointSize(30);
    SetPenColor("Violet");
    
	MovePen(2.5, winheight-1);
	DrawTextString("No");    
	MovePen(4, winheight-1);
	DrawTextString("Name");
	MovePen(6, winheight-1);
	DrawTextString("Score");
		
	SetPointSize(20);
	usePredefinedButtonColors(2);
	MovePen(2, winwidth/2.5);
	
	p = ReadRecordFile();
	tp = p->firstplayer;
	
	
	for(i = 1;i<=p->PlayerCounts && i<=10;i++)
	{
		a[0] = i+48;
		a[1] = 0;
		MovePen(2.5, winheight-1-i);
		DrawTextString(a);

		MovePen(4, winheight-1-i);
        DrawTextString(tp->playname);
      
		score = tp->score;
		if(score>=1000)
		{
			s[0]=(score)/1000+48;
			s[1]=(score%1000)/100+48;
			s[2]=48;
			s[3]=48;
			s[4]=0;
		}
		else if(score>=100)
		{
			s[0]=48;
			s[1]=(score)/100+48;
			s[2]=(score%100)/10+48;
			s[3]=48;
			s[4]=0;
		}
		else 
		{
			s[0]=48; s[1]=48; s[2]=48; s[3]=48;
			s[4]=0;
		}
		MovePen(6, winheight-1-i);
		DrawTextString(s);
		
		tp = tp->next;
    }
    
    SetPointSize(20);
	if( button(GenUIID(4), 7, 1, 2, 1, "Back to Menu"))
	{
		IF=0;
		//DisplayClear();
		SetPointSize(10);
		display();
	}
}

void AboutWindow(void)
{
    SetPointSize(30);
    SetPenColor("Violet");
    
	MovePen(2.5, winheight-1);
	DrawTextString("No");    
	MovePen(4, winheight-1);
	DrawTextString("Name");
	MovePen(6, winheight-1);
	DrawTextString("Score");
	
	SetPointSize(20);
	if( button(GenUIID(4), 7, 1, 2, 1, "Back to Menu"))
	{
		IF=0;
		//DisplayClear();
		SetPointSize(10);
		display();
	}
} 
