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
extern int buttonTheme;
extern int menuTheme;
extern UserRecordLinkList *sysinfo;
static char playername[20]; 


// 菜单演示程序
void drawMenu()
{ 
	static char * menuListSys[] = {"System",  
		"Setting", 
		"Exit  | Ctrl-E"}; // 快捷键必须采用[Ctrl-X]格式，放在字符串的结尾

	static char * menuListOP[] = {"Operate",
		"Start | Ctrl-S",
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
	double wlist = TextStringWidth(menuListOP[0])*3.2;
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
	else if(selection == 2){
		IF=4;
		drawButtons();
	}
	   
	
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
	static char playername[20]; 
	SetPointSize(10);
	float value; 
	
	
	
	switch(IF){
		case 0:
			
			textbox(GenUIID(0),x, y+2*(h+0.2),  w,  h, playername, sizeof(playername));
			
			if( button(GenUIID(0), x, y+(h+0.2), w, h, "Start") )
			{
				IF=2; 
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
				IF=4;
				drawMenu();
				drawButtons();
			}
			break;
		case 1: 
			setting();
			break; 
		case 2: 
		    game_running=1;
		    SetCurrentUser(sysinfo,playername);
		    tetris->score=sysinfo->currentplayer->score;
			initial();
			break;
		case 3: 
			game_running=1;
			initial();
			CleanTetris(tetris);
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
		case 9:
			gameover();
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
	if ( button(GenUIID(0), 3.5, 2, 1.2, 0.5, "Theme 0"))
	{
		buttonTheme=7;
		menuTheme=7;
	}
	if( button(GenUIID(0), 4.7, 2, 1.2, 0.5, "Theme 1"))
	{
		buttonTheme=1;
		menuTheme=1;
	}
	if( button(GenUIID(0), 5.9, 2, 1.2, 0.5, "Theme 2"))
	{
		buttonTheme=2;
		menuTheme=2;
	}
	SetPointSize(30);
	MovePen(2,4.63);
    SetPenColor("Violet");
	DrawTextString("Speed: ");
	SetPointSize(20);
	usePredefinedButtonColors(buttonTheme);
	MovePen(2,2.63);
    SetPenColor("Violet");
	DrawTextString("Current Speed:      "); 
	switch (tetris->speed){
		case 500:
			DrawTextString("Slow");
			break;
		case 250:
			DrawTextString("Middle");
			break;
		case 100:
			DrawTextString("Fast");
			break;
	}
	if( button(GenUIID(5), 3.5, 4.5, 1.2, 0.5, "Slow"))
	{
		changespeed(1);
		SetPointSize(10);
		display();
	}
	else if( button(GenUIID(5), 5, 4.5, 1.2, 0.5, "Middle"))
	{
		changespeed(2);
		SetPointSize(10);
		display();
	}
	else if( button(GenUIID(5), 6.5, 4.5, 1.2, 0.5, "Fast"))
	{
		changespeed(3);
		SetPointSize(10);
		display();
	}
	
	SetPointSize(10);
	if( button(GenUIID(4), 7, 1, 2.3, 0.6, "Back to Menu"))
	{
		IF=0; 
		SetPointSize(10);
		display();
	}
}

void gameover(){
	IF=9;
	game_running=0;
   //CleanTetris(tetris);
   InitGraphics();
	cancelTimer(1);
	DisplayClear();
	MovePen(4.5,4);
	SetPointSize(35);
	DrawTextString("Game Over");
	SetPointSize(10);
	if( button(GenUIID(0), 1, 1, 2, 0.6, "Back to Main Menu"))
		{
			IF=0;
			ModifyUserScore(sysinfo,tetris->score,tetris->level);
			WriteRecordFile(sysinfo);
			display();
		}
	if( button(GenUIID(0), 7, 1, 2, 0.6, "QUIT"))
		{
			ModifyUserScore(sysinfo,tetris->score,tetris->level);
			WriteRecordFile(sysinfo);
			exit(-1);
		}
}
void Endwindow(void)
{
	DisplayClear();
	MovePen(4.5,4);
	SetPointSize(35);
	DrawTextString("END");
	SetPointSize(10);
	if( button(GenUIID(4), 1, 1, 2, 0.6, "Back to Main Menu"))
		{
			IF=0;
			ModifyUserScore(sysinfo,tetris->score,tetris->level);
			WriteRecordFile(sysinfo);
			display();
		}
	if( button(GenUIID(4), 7, 1, 2, 0.6, "QUIT"))
		{
			ModifyUserScore(sysinfo,tetris->score,tetris->level);
			WriteRecordFile(sysinfo);
			exit(-1);
		}
}



void display()
{
	usePredefinedButtonColors(buttonTheme);
	usePredefinedMenuColors(menuTheme);
	//转入游戏界面
	if(game_running)
	{ 
		SetPointSize(10);
		if( button(GenUIID(0), 7.5, 0.4, 1.8, 0.5, "Exit"))
		{
			IF=4;
			game_running=0;
			CleanTetris(tetris);
			InitGraphics();
			cancelTimer(1);
			ModifyUserScore(sysinfo,tetris->score,tetris->level);
			WriteRecordFile(sysinfo);
			display();
		}
		if( button(GenUIID(0), 5.5, 0.4, 1.8, 0.5, "Back to Main Menu"))
		{
			IF=0;
			game_running=0;
			CleanTetris(tetris);
			InitGraphics();
			cancelTimer(1);
			ModifyUserScore(sysinfo,tetris->score,tetris->level);
			WriteRecordFile(sysinfo);
			display();
		}
		
		return;
	}
	DisplayClear();	
	drawMenu();
	drawButtons();	
}



void Rank()
{
	UserRecordNode *tp;
	int i=1;
	char No[5],name[20],score[10];
	double y;
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
//	usePredefinedButtonColors(2);
	MovePen(2, winwidth/2.5);
	
	sysinfo = ReadRecordFile();
	ReRank(sysinfo);
	tp=sysinfo->firstplayer;
	while(tp!=NULL&&i<10){
		
    	SetPenColor("Violet");
		sprintf(No,"%d",i);
		sprintf(name,"%s",tp->playname);
		sprintf(score,"%d",tp->score);
		MovePen(2.5,winheight-1.25-i*0.5);
		DrawTextString(No);
		MovePen(4,winheight-1.25-i*0.5);
		DrawTextString(name);
		MovePen(6,winheight-1.25-i*0.5);
		DrawTextString(score);
		usePredefinedButtonColors(buttonTheme);
		if (button(GenUIID(i), 7,winheight-1.25-i*0.5, 2, 0.3, "delete")){
			DeleteUserByRank(sysinfo,i);
			WriteRecordFile(sysinfo);
			display();
		}
		i++;
		tp=tp->next;
	}
	
    
    SetPointSize(10);
	if( button(GenUIID(4), 7, 1, 2, 0.6, "Back to Menu"))
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
