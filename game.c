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

#include "game.h"
#include "imgui.h"
#include "interface.h"

#define blocklength  0.3333333

extern int IF;
static struct Tetris t,*tetris=&t;
int Temp,Temp1,Temp2; 	//temp,temp1,temp2���ڼ�ס��ת�����������ֵ
bool pau;



static int a[30][23];
int b[4];     				//?��O4??"?f"????G1?????????A0????L???
int i,j;
static char co[10];


// �û��ļ�ʱ��ʱ����Ӧ����
void TimerEventProcess(int timerID)
{
	switch (timerID) {
		case 1: 
		if(pau==FALSE)
		{
			CleanTetris(tetris);
			tetris->y--;
			if(ifMove(tetris)==0)
			{
				tetris->y++;
				PrintTetris(tetris);
				Del_Fullline(tetris);
				for(i=tetris->y-2;i<tetris->y+2;i++)
  				{
				  if(i>=21)   exit(0);
  				}
				tetris->flag = tetris->next;
				Flag(tetris);

	  			Temp=tetris->flag;
  				tetris->x=25;			
  				tetris->y=10;             
  				CleanTetris(tetris);
	  			tetris->flag = tetris->next;            
    			PrintTetris(tetris);          
  				tetris->x=7;  				
	  			tetris->y=21;     					
  				tetris->flag=Temp;
				Reset();
			}
			else
				PrintTetris(tetris);	
		}
		
		break;
	  	default:
		break;
	}
}

void keyboard_game(int key, int event)
{

		int t;
		switch (event) {
		case KEY_DOWN:
			switch (key) {
				case VK_LEFT:
					if(pau==FALSE)
					{
						CleanTetris(tetris);
					tetris->x--;
					if(ifMove(tetris)==0)
					{
					tetris->x++;
					PrintTetris(tetris);
					}
					else
					PrintTetris(tetris);
					}
					break;
				case VK_RIGHT:
					if(pau==FALSE)
					{
						CleanTetris(tetris);
					tetris->x++;
					if(ifMove(tetris)==0)
					{
					tetris->x--;
					PrintTetris(tetris);
					}
					else
					PrintTetris(tetris);
					}
					break;
				case VK_UP:
					{   
					if(pau==FALSE)
					{
						CleanTetris(tetris);
					t=tetris->flag;
    	 			if( tetris->flag>=2 && tetris->flag<=3 )
     				{
      					tetris->flag++; 
      					tetris->flag%=2;
      					tetris->flag+=2;
     				}
     				else if( tetris->flag>=4 && tetris->flag<=7 )
     				{
      					tetris->flag++;
      					tetris->flag%=4;
      					tetris->flag+=4;
     				}    
     				else if( tetris->flag>=8&&tetris->flag<=9)
     				{
     					tetris->flag++; 
      					tetris->flag%=2;
      					tetris->flag+=8;
     				}
     				else if( tetris->flag>=10&&tetris->flag<=11)
     				{
     					tetris->flag++; 
      					tetris->flag%=2;
      					tetris->flag+=10;
     				}
     				
     				else if( tetris->flag>=12 && tetris->flag<=15 )
     				{
      					tetris->flag++;
      					tetris->flag%=4;
      					tetris->flag+=12;
     				}    
     				else if( tetris->flag>=16 && tetris->flag<=19 )
     				{
      					tetris->flag++;
      					tetris->flag%=4;
      					tetris->flag+=16;
     				}
     				if(ifMove(tetris)==0)
     				{
     					tetris->flag=t;
     				}
     				PrintTetris(tetris);
					} 
					
     				break;
    			}
    			case VK_DOWN:
    				{
    					if(pau==FALSE)
    					{
    						CleanTetris(tetris);
						tetris->y--;
						if(ifMove(tetris)==0)
						tetris->y++;
						PrintTetris(tetris);
    					}
    					break;
    				}
    			case VK_TAB:
    				{
    					if(pau==TRUE)
						pau=FALSE;
						else
						pau=TRUE; 
    					break;
    				}
    			case VK_ESCAPE:
    				{
    					WriteLastRecordFile(tetris, a[30][23]);
    					DisplayClear();
    					cancelTimer(1);
			            IF=0;
			            display();
			            CleanTetris(tetris);
			            InitGraphics();
    					break;
    				}
    			case VK_SPACE: 
    				{
    					CleanTetris(tetris);
    					while(ifMove(tetris)==1)
    					{
    						tetris->y--;
    					}
    					tetris->y++;
    					PrintTetris(tetris);
    					break;
    				}
			}
	}
}
void MakePlayingWindow(struct Tetris *tetris)
{
	DisplayClear();
	char l[3];
	if(tetris->level<10)
	{
		l[0]=(tetris->level)+48;
		l[1]=0;
	}
	else
	{
		l[0]=(tetris->level)/10+48;
		l[1]=(tetris->level)%10+48;
		l[2]=0;
	}
	char s[5];
	if(tetris->score>=1000)
	{
		s[0]=(tetris->score)/1000+48;
		s[1]=((tetris->score)%1000)/100+48;
		s[2]=48;
		s[3]=48;
		s[4]=0;
	}
	else if(tetris->score>=100)
	{
		s[0]=48;
		s[1]=(tetris->score)/100+48;
		s[2]=((tetris->score)%100)/10+48;
		s[3]=48;
		s[4]=0;
	}
	else 
	{
		s[0]=48; s[1]=48; s[2]=48; s[3]=48;
		s[4]=0;
	}
	
	char v[4];
	if(tetris->speed>=100)
	{
		v[0]=(tetris->speed)/100+48;
		v[1]=((tetris->speed)%100)/10+48;
		v[2]=((tetris->speed)%10)+48;
		v[3]=0;
	}

	int n;
     for(n=0;n<15;n++)   /*?e???u*/ 
	{
		a[n][0]=1;
		SetPenColor("Dark Gray");
		SetPenSize(3);
		MovePen(0.16,0.16);
		DrawLine(4.68,0);
	} 
	for(n=0;n<22;n++)
	{
		a[0][n]=1;
		a[14][n]=1;
	}
	
	MovePen(4.84,0.16);
	DrawLine(0,7);
	MovePen(0.16,0.16);
	DrawLine(0,7);
	SetPenSize(1);
	
	SetPointSize(40);
	MovePen(6,6);
	SetPenColor("Magenta");
	DrawTextString("Fun Tetris !!");
	SetPointSize(20);
	MovePen(6.5,5.5);
	SetPenColor("Violet");
	DrawTextString("Level:");
	SetPenColor("Orange");

	DrawTextString(l);
	MovePen(6.5,5.0);
	SetPenColor("Violet");
	DrawTextString("Score:");
	SetPenColor("Orange");

	DrawTextString(s);
	
	MovePen(6.5,4.5);
	SetPenColor("Violet");
	DrawTextString("Speed:");
	SetPenColor("Orange");
	DrawTextString(v);
	
	MovePen(6.5,4.0);
	SetPenColor("Violet");
	DrawTextString("Next tetris:");
	
	SetPointSize(30);
	MovePen(6.5,2.5);
	SetPenColor("Magenta");
	DrawTextString("Instruction");
	SetPointSize(20);
	MovePen(6.5,2.0);
	SetPenColor("Violet");
	DrawTextString("Pause:");
	SetPenColor("Red");
	DrawTextString("  pause");
	MovePen(6.5,1.5);
	SetPenColor("Violet");
	DrawTextString("Exit Game:");
	SetPenColor("Red");
	DrawTextString("  esc");
	
	
	SetPenColor("Black");
			
	
}


void MakeTetris(struct Tetris *tetris)
{
 	a[tetris->x][tetris->y]=b[0];    //????????m???????A
 	switch(tetris->flag)      //?@7?j???A19??????
 	{
  		case 1:         /*?��r??? ????
		  			               ????  */
   		{
			
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x+1][tetris->y+1]=b[2];
    		a[tetris->x+1][tetris->y]=b[3];
   			break;
   		}
  		case 2:         /*???u??? ????????*/
   		{
		   	
    		a[tetris->x-1][tetris->y]=b[1];
    		a[tetris->x+1][tetris->y]=b[2];
    		a[tetris->x+2][tetris->y]=b[3];
    		break;
   		}
  		case 3:         /*???u??? ??
		  			               ??
								   ??
								   ??  */
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+2]=b[2];
    		a[tetris->x][tetris->y+1]=b[3];
    		break;
   		}
  		case 4:         /*T?r??? ??????
		  			                ??  */
   		{
		   	
    		a[tetris->x-1][tetris->y]=b[1];
    		a[tetris->x+1][tetris->y]=b[2];
    		a[tetris->x][tetris->y-1]=b[3];
    		break;
   		}
  		case 5:         /* ????w90?XT?r???   ??
		  			                         ????
									           ??*/
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-1][tetris->y]=b[3];
    		break;
   		}
  		case 6:         /* ????w180?XT?r???     ??
		  			                            ??????*/
   		{
		   	
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x-1][tetris->y]=b[2];
    		a[tetris->x+1][tetris->y]=b[3];
    		break;
   		}
  		case 7:         /* ????w270?XT?r???   ??
		  			                            ????
									            ??  */
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x+1][tetris->y]=b[3];
    		break;
   		}
  		case 8:         /* Z?r???   ????
		  			                   ????*/
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x-1][tetris->y]=b[2];
    		a[tetris->x+1][tetris->y-1]=b[3];
    		break;
   		}
  		case 9:         /* ????wZ?r???      ??
		  			                        ????
									        ??  */
   		{
		   	                                                                                                     
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x-1][tetris->y]=b[2];
    		a[tetris->x-1][tetris->y-1]=b[3];
    		break;
   		}
  		case 10:        /* ????Z?r???      ????
		  			                      ????  */
   		{
		   	
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x-1][tetris->y]=b[2];
    		a[tetris->x+1][tetris->y+1]=b[3];
    		break;
   		}
  		case 11:        /* ????wZ?r???    ??
		  			                        ????
									          ??  */
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x-1][tetris->y+1]=b[2];
    		a[tetris->x-1][tetris->y]=b[3];
    		break;
   		}
  		case 12:        /* 7?r???    ????
		  			                    ??
									    ??  */
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-1][tetris->y+1]=b[3];
    		break;
   		}
  		case 13:        /* ????w90?X7?r???        ??
		  			                            ??????*/
   		{
		   	
    		a[tetris->x-1][tetris->y]=b[1];
    		a[tetris->x+1][tetris->y+1]=b[2];
    		a[tetris->x+1][tetris->y]=b[3];
    		break;
   		}
  		case 14:        /* ????w180?X7?r???      ??
		  			                               ??
									               ????  */
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
   		 	a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x+1][tetris->y-1]=b[3];
    		break;
   		}
  		case 15:        /* ????w270?X7?r???    ??????
		  			                             ??    */
   		{
		   	
    		a[tetris->x-1][tetris->y]=b[1];
    		a[tetris->x-1][tetris->y-1]=b[2];
    		a[tetris->x+1][tetris->y]=b[3];
    		break;
   		}
  		case 16:        /* ????7?r???    ????
		  			                      ??
										  ??    */
   		{
		   	
    		a[tetris->x][tetris->y+1]=b[1];
    		a[tetris->x][tetris->y-1]=b[2];
    		a[tetris->x+1][tetris->y+1]=b[3];
    		break;
   		}
  		case 17:        /* ????w??90?X7?r???    ??????
		  			                                  ??*/
   		{
		   	
    		a[tetris->x-1][tetris->y]=b[1];
    		a[tetris->x+1][tetris->y-1]=b[2];
    		a[tetris->x+1][tetris->y]=b[3];
    		break;
   		}
  		case 18:        /* ????w??180?X7?r???    ??
		  			                               ??
									             ????    */
   		{
		   	
    		a[tetris->x][tetris->y-1]=b[1];
    		a[tetris->x][tetris->y+1]=b[2];
    		a[tetris->x-1][tetris->y-1]=b[3];
    		break;
   		}
  		case 19:        /* ?????w??270?X7?r???    ??
		  			                               ??????*/
  		{
		  	
    		a[tetris->x-1][tetris->y]=b[1];
    		a[tetris->x-1][tetris->y+1]=b[2];
    		a[tetris->x+1][tetris->y]=b[3];
    		break;
  	 	}
 	} 
}

void PrintTetris(struct Tetris *tetris)
{
 	for(i=0;i<4;i++)
 	{
  		b[i]=checknum(tetris);         				//?}?Cb[4]???C????????????1
 	}
 	MakeTetris(tetris);      			//?s?@?C?????f
 	for( i=tetris->x-1; i<=tetris->x+2; i++ )
 	{
  		for(j=tetris->y-1;j<=tetris->y+2;j++)
  		{
   			if( a[i][j]>0 && j!=0 && i!=0 &&i!=14)
   			{
   				SetPenColor(numtocolor(a[i][j]));
    			drawblock(i*blocklength,j*blocklength);
   			}
  		}
	}
	
}

void drawblock (double x,double y)
{
	MovePen(x,y);
	StartFilledRegion(1);
	DrawLine(blocklength,0);
	DrawLine(0,blocklength);
	DrawLine(-blocklength,0);
	DrawLine(0,-blocklength);
	EndFilledRegion();
	SetPenColor("Black");
	DrawLine(blocklength,0);
	DrawLine(0,blocklength);
	DrawLine(-blocklength,0);
	DrawLine(0,-blocklength);
	SetPenColor(co);
}


int ifMove(struct Tetris *tetris)
{
 	if(a[tetris->x][tetris->y]!=0)//??????????m?W?????��A??^???0?A?Y???i????
 	{
  		return 0;
 	}
 	else
 	{
  		if( //?????��r????B??????????m?~?A??L"??"?r?????m?W?L???��A?????o???m?????U?��r????A?i?H?????o???m?A??^???1?A?Y?i????
			//??p?��r????A???????????O???U???????A?p?G?????W?A?k?A?k?W????m????A?h?o???m?N?i?H??@??��r????F?p?G???@???m?W??????A?????U?@???
   		( tetris->flag==1  && ( a[tetris->x][tetris->y+1]==0   &&
    	a[tetris->x+1][tetris->y+1]==0 && a[tetris->x+1][tetris->y]==0 ) ) ||
   		//??????u????B??????????m?~?A??L"??"?r?????m?W?L???��A??^???1?A?Y?i????
   		( tetris->flag==2  && ( a[tetris->x-1][tetris->y]==0   && 
    	a[tetris->x+1][tetris->y]==0 && a[tetris->x+2][tetris->y]==0 ) )   ||
   		( tetris->flag==3  && ( a[tetris->x][tetris->y-1]==0   &&
    	a[tetris->x][tetris->y+2]==0 && a[tetris->x][tetris->y+1]==0 ) )   ||
   		( tetris->flag==4  && ( a[tetris->x-1][tetris->y]==0   &&
    	a[tetris->x+1][tetris->y]==0 && a[tetris->x][tetris->y-1]==0 ) )   ||
   		( tetris->flag==5  && ( a[tetris->x][tetris->y-1]==0   &&
   		 a[tetris->x][tetris->y+1]==0 && a[tetris->x-1][tetris->y]==0 ) )   ||
   		( tetris->flag==6  && ( a[tetris->x][tetris->y+1]==0   &&
    	a[tetris->x-1][tetris->y]==0 && a[tetris->x+1][tetris->y]==0 ) )   ||
   		( tetris->flag==7  && ( a[tetris->x][tetris->y-1]==0   &&
    	a[tetris->x][tetris->y+1]==0 && a[tetris->x+1][tetris->y]==0 ) )   ||
   		( tetris->flag==8  && ( a[tetris->x][tetris->y-1]==0   &&
    	a[tetris->x-1][tetris->y]==0 && a[tetris->x+1][tetris->y-1]==0 ) ) ||
   		( tetris->flag==9  && ( a[tetris->x][tetris->y+1]==0   &&
    	a[tetris->x-1][tetris->y]==0 && a[tetris->x-1][tetris->y-1]==0 ) ) ||
   		( tetris->flag==10 && ( a[tetris->x][tetris->y+1]==0   &&
    	a[tetris->x-1][tetris->y]==0 && a[tetris->x+1][tetris->y+1]==0 ) ) ||
   		( tetris->flag==11 && ( a[tetris->x][tetris->y-1]==0   &&
    	a[tetris->x-1][tetris->y+1]==0 && a[tetris->x-1][tetris->y]==0 ) ) ||
   		( tetris->flag==12 && ( a[tetris->x][tetris->y+1]==0   &&
    	a[tetris->x][tetris->y-1]==0 && a[tetris->x-1][tetris->y+1]==0 ) ) ||
   		( tetris->flag==15 && ( a[tetris->x-1][tetris->y]==0   &&
    	a[tetris->x-1][tetris->y-1]==0 && a[tetris->x+1][tetris->y]==0 ) ) ||
   		( tetris->flag==14 && ( a[tetris->x][tetris->y+1]==0   &&
    	a[tetris->x][tetris->y-1]==0 && a[tetris->x+1][tetris->y-1]==0 ) ) ||
   		( tetris->flag==13 && ( a[tetris->x-1][tetris->y]==0   &&
    	a[tetris->x+1][tetris->y+1]==0 && a[tetris->x+1][tetris->y]==0 ) ) ||
   		( tetris->flag==16 && ( a[tetris->x][tetris->y-1]==0   &&
    	a[tetris->x][tetris->y+1]==0 && a[tetris->x+1][tetris->y+1]==0 ) ) ||
   		( tetris->flag==19 && ( a[tetris->x-1][tetris->y]==0   &&
    	a[tetris->x-1][tetris->y+1]==0 && a[tetris->x+1][tetris->y]==0 ) ) ||
   		( tetris->flag==18 && ( a[tetris->x][tetris->y+1]==0   &&
    	a[tetris->x][tetris->y-1]==0 && a[tetris->x-1][tetris->y-1]==0 ) ) ||
   		( tetris->flag==17 && ( a[tetris->x-1][tetris->y]==0   &&
    	a[tetris->x+1][tetris->y-1]==0 && a[tetris->x+1][tetris->y]==0 ) ) )
   		{
    		return 1;
   		}
	}
 	return 0;
}

void CleanTetris(struct Tetris *tetris)
{
 	for(i=0;i<4;i++)
 	{
  		b[i]=0;         //?}?Cb[4]???C????????????0
 	}
	MakeTetris(tetris);      //?s?@?X��?????
	SetEraseMode(TRUE);
	for( i = tetris->x - 1;i <= tetris->x + 2; i++ )       //??X ????  X????????
	{
  		for(j = tetris->y-1;j <= tetris->y + 2;j++)        /* ??
															  ??
															  X
  															  ??	*/
  		{
   			if( a[i][j] == 0)
   			{
   				drawblock(i*blocklength,j*blocklength);
   				
   			}
  		}
 	}
 	SetEraseMode(FALSE);
}


/*void Timer_game(int timerID)*/

void Flag(struct Tetris *tetris)
{
	int _rand;
 	tetris->number++;     				//��ס��������ĸ���
 	
	_rand=RandomInteger(1,7);
	if(_rand==2)
	_rand=RandomInteger(2,3);
	else if(_rand==3)
	_rand=RandomInteger(4,7);
	else if(_rand==4)
	_rand=RandomInteger(8,9);
	else if(_rand==5)
	_rand=RandomInteger(10,11);
	else if(_rand==6)
	_rand=RandomInteger(12,15);
	else if(_rand==7)
	_rand=RandomInteger(16,19);
	 if(tetris->number==1)
 	{
  		tetris->flag = _rand;  	//��ס��һ����������
 	}
 	tetris->next = _rand;   		//��ס��һ����������
}

void Del_Fullline(struct Tetris *tetris)
{
	int cc=0;
	int k,del_rows=0;  //�ֱ����ڼ�¼ĳ�з���ĸ�����ɾ������������ı���
 	for(j=1;j<20;j++)
 	{
  		k=0;
  		for(i=1;i<=13;i++)
  		{  
   			if(a[i][j]>0) //���������δ������ϣ��������������������ж��Ƿ�����
   			{
    			k++;  //��¼���з���ĸ���
    			if(k==13)  //������� 
    			{
     				for(k=1;k<14;k++)//ɾ�����еķ���
     				{  
      					a[k][j]=0;
      					SetEraseMode(TRUE);
      					drawblock(i*blocklength,j*blocklength);
      					SetEraseMode(FALSE);
//      					Sleep(1);
     				}
    	 			for(k=j+1;k<20;k++) //���ɾ�������ϵ�λ���з��飬����������ٽ���������һ��λ��
     				{ 
      					for(i=1;i<14;i++)
      					{
       						if(a[i][k]>0)
       						{
       							cc=a[i][k];
        						a[i][k]=0;
        						SetEraseMode(TRUE);
      							drawblock(i*blocklength,k*blocklength);
      							SetEraseMode(FALSE);
        						a[i][k-1]=cc;
        						SetPenColor(numtocolor(a[i][k-1]));
        						drawblock(i*blocklength,(k-1)*blocklength);
       						}
      					}
     				}			
     				j--;   //�������ƺ������ж�ɾ�����Ƿ�����
     				del_rows++; //��¼ɾ�����������
    			}
   			}
  		}
 	}
 	tetris->score+=100*del_rows; //ÿɾ��һ�У���100��
 	if( del_rows>0 && ( tetris->score%1000==0 || tetris->score/1000>tetris->level-1 ) )
 	{        //�����1000�ּ��ۼ�ɾ��10�У��ٶȼӿ�20ms����һ��
  		tetris->speed-=50;
  		tetris->level++;
  		cancelTimer(1);
		startTimer(1,tetris->speed); 
 	}
 	MakePlayingWindow(tetris);
}

void Reset(void)
{
	int x,y;
	for(x=1;x<=13;x++)
	{
		for(y=1;y<=20;y++)
		{
			SetEraseMode(TRUE);
			drawblock(x*blocklength,y*blocklength);
      		
      		SetEraseMode(FALSE);
		}
	}
	for(x=1;x<=13;x++)
	{
		for(y=1;y<=20;y++)
		{
			if(a[x][y]>0)
			{
				SetPenColor(numtocolor(a[x][y]));
				drawblock(x*blocklength,y*blocklength);
			}
			
		}
	} 
}


int checknum(struct Tetris *tetris)
{
	if(tetris->flag==1)
	return 1;
	else if(tetris->flag>=2 && tetris->flag<=3)
	return 2;
	else if(tetris->flag>=4 && tetris->flag<=7)
	return 3;
	else if(tetris->flag>=8&&tetris->flag<=9)
	return 4;
	else if(tetris->flag>=12&&tetris->flag<=15)
	return 5;
	else if(tetris->flag>=10&&tetris->flag<=11)
	return 6;
	else if(tetris->flag>=16&&tetris->flag<=19)
	return 7;
}

char *checkcolor(struct Tetris *tetris)
{

	if(tetris->flag==1)
	strcpy(co,"Green");
	else if(tetris->flag>=2&&tetris->flag<=3)
	strcpy(co,"Red");
	else if(tetris->flag>=4&&tetris->flag<=7)
	strcpy(co,"Blue");
	else if(tetris->flag>=8&&tetris->flag<=9)
	strcpy(co,"Yellow");
	else if(tetris->flag>=10&&tetris->flag<=11)
	strcpy(co,"Orange");
	else if(tetris->flag>=12&&tetris->flag<=15)
	strcpy(co,"Cyan");
	else if(tetris->flag>=16&&tetris->flag<=19)
	strcpy(co,"Magenta");
	return co;
}

char *numtocolor(int num)
{
	switch (num) 
	{
		case 1:
			{
			strcpy(co,"Green");
			break;
			}
		case 2:
			{
			strcpy(co,"Red");
			break;
			}
		case 3:
			{
			strcpy(co,"Blue");
			break;
			}
		case 4:
			{
			strcpy(co,"Yellow");
			break;
			}
		case 5:
			{
			strcpy(co,"Cyan");
			break;
			}
		case 6:
			{
				strcpy(co,"Orange");
				break;
			}
		case 7:
			{
				strcpy(co,"Magenta");
				break;
			}
	}
	return co;
}


void initial()
{
	int m,n;
	for(m = 0; m<30 ;m++)
	{
		for(n = 0; n<23; n++)
		a[m][n] = 0;
	}
	memset(b,0,4*sizeof(int));
	memset(co,0,10*sizeof(char));
	tetris->number=0;      								//��ʼ������˹������Ϊ0��
 	if(tetris->speed!=150 && tetris->speed!=500)tetris->speed=250; //��ʼ�ƶ��ٶ�Ϊ300ms
	tetris->score=0;      								//��ʼ��Ϸ�ķ���Ϊ0��
 	tetris->level=1;
	MakePlayingWindow(tetris);
	startTimer(1, tetris->speed);  		
					
 	Flag(tetris);
	if(tetris->number == 1)
	Flag(tetris);
  	Temp=tetris->flag;     							//��ס��ǰ����˹�������
  	tetris->x=22;				//���Ԥ�����淽���x����
  	tetris->y=10;                            //���Ԥ�����淽���y����
  	tetris->flag = tetris->next;                    //�����һ������˹��������
    PrintTetris(tetris);                 //���ô�ӡ����˹���鷽��
  	tetris->x=7;  					//�����Ϸ�Ӵ����ķ���x����
  	tetris->y=21;     						//�����Ϸ�Ӵ����ķ���y����
  	tetris->flag=Temp; 
}


void Continue()
{
	ReadLastRecordFlietoMemory(tetris, a[30][23]);
	memset(b,0,4*sizeof(int));
	memset(co,0,10*sizeof(char));
	MakePlayingWindow(tetris);
	startTimer(1, tetris->speed);  		
							
 	Flag(tetris);
	if(tetris->number == 1)
	Flag(tetris);
  	Temp=tetris->flag;     							//��ס��ǰ����˹�������
  	tetris->x=22;				//���Ԥ�����淽���x����
  	tetris->y=10;                            //���Ԥ�����淽���y����
  	tetris->flag = tetris->next;                    //�����һ������˹��������
    PrintTetris(tetris);                 //���ô�ӡ����˹���鷽��
  	tetris->x=7;  					//�����Ϸ�Ӵ����ķ���x����
  	tetris->y=21;     						//�����Ϸ�Ӵ����ķ���y����
  	tetris->flag=Temp; 
}

void changespeed(int v)
{
	switch(v)
	{
		case 1: tetris->speed = 500;break;
		case 2: tetris->speed = 250;break;
		case 3: tetris->speed = 100;break;
	}
	
		
}
