//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <bits/stdc++.h>
#include <cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
//Global vaiables
int m=0,n=0,option=0,rect=4,rectOpp,gap,temp[1000][1000]={0},current_key=2,opponent_key=3,score=0,level=1,lives=3,x_axis=0,y_axis=0;
//m & n used to change position of user car and x_axis & y_axis used to change direction of opponent
//temp[1000][1000] is temprary array used to define position of hurdles and food
//option used for ke options
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}
//===========================================================================================================
void lives_down()//when car hit wit opponent car this function called
{
	for(int i=50;i<400;i+=100)//making new arena
		{
			for(int j=760;j>0;j-=100)
				temp[i][j]=2;
		}
		for(int i=460;i<800;i+=100)
		{
			for(int j=60;j<900;j+=100)
				temp[i][j]=2;
		}
		if(level==1)//score will also updated after hitting opponent
		{
			score=0;
		}
		else if(level==2)
		{
			score=164;
		}
		else if(level==3)
		{
			score=328;
		}
		else if(level==4)
		{
			score=492;
		}
		lives--;
		if(lives==0)
		{
			exit(1);
		}
		m=0,n=0,x_axis=0,y_axis=0;
		opponent_key=3;
		current_key=2;

}
//===================================================================================================
//funtion used for down motion
void down()
{
	int flag=0;
	for(int i=m;i<m+60;i++)
	{
		if(temp[390+i][750+n-1]==1)	//checking hurdles
		{
				flag=1;
				current_key=3;			//if hit with hurdle change direction toward left
				break;
			}
		}
		if (flag==0)					//if no hurdle it will move
		{
			n--;
		}
		for(int i=m;i<m+60;i++)
		{
			if(temp[390+i][750+n-1]==2)		//check that there is food or not
			{
				temp[390+i][750+n-1]=3;		//removing of food
					score++;
			}
			
		}		
		for(int i=x_axis-60;i<x_axis+120;i++)
		{
			for(int j=y_axis;j<y_axis+50;j++)//checking car hitting with opponent car
			{
				if(390+m==200+i&&n==j)
				{
					lives_down();
				}
			}
		}
		glutPostRedisplay();
}
//upward motion
void up()
{
	int flag=0;
		for(int i=m;i<m+50;i++)
		{
			if(temp[390+i][750+n+60+1]==1)	//checking hurdles
			{
				flag=1;
				current_key=2;			//if hurdle is there then change direction toward right
				break;
			}
		}
		if (flag==0)
		{
			n++;						//if no hurdle is there then move on point
		}
		
		for(int i=m;i<m+60;i++)
		{
			if(temp[390+i][750+n+50+1]==2)	//checking food
			{
				temp[390+i][750+n+50+1]=3;	//removing food
					score++;
			}
		}
		for(int i=m-60;i<m+120;i++)
		{
			for(int j=n;j<n+50;j++)
			{
				if(390+i==200+x_axis&&j==y_axis)//checking car hitting with opponent car
				{
		
					lives_down();
				}
			}
		}
		glutPostRedisplay();
}
//left motion
void left()
{
	int flag=0;
		for(int i=n;i<n+60;i++)
		{
			if (temp[390+m-1][750+i]==1)	//checking hurdles
			{
				flag=1;
				current_key=4;				//change direction toward up
				break;
			}
		}
		if(flag==0)
		{
			m--;							// if no hurdle move one point 
		}
		for(int i=n;i<n+60;i++)
		{
			if (temp[390+m-1][750+i]==2)	//checking food
			{
				temp[390+m-1][750+i]=3;		//removing food
					score++;
			}	
		}
		for(int i=x_axis;i<x_axis+60;i++)
		{
			for(int j=y_axis-50;j<y_axis+100;j++)
			{
				if(390+m==200+i&&n==j)//checking car hitting with opponent car
				{
		
					lives_down();
				}
			}
		}
		glutPostRedisplay();
}
//right motion
void right()
{
	int flag=0;
		for(int i=n;i<n+60;i++)
		{
			if(temp[390+m+60+1][750+i]==1)	//checking hurdles
			{
				flag=1;
				current_key=1;			//changing direction toward down
				break;
			}
		}
		if(flag==0)
		{
			m++;						//move one point forward
		}
		for(int i=n;i<n+60;i++)
		{
			if(temp[390+m+60+1][750+i]==2)	//check food
			{
				temp[390+m+60+1][750+i]=3;	//removing food
					score++;
			}
			
		}
		for(int i=m;i<m+60;i++)
		{
			for(int j=n-50;j<n+100;j++)
			{
				if(390+i==200+x_axis&&j==y_axis)//checking car hitting with opponent car
				{
					lives_down();
				}
			}
		}
		glutPostRedisplay();
}
//===================================================================================================
void downOpp()
{
	int flag=0;
		for(int i=x_axis;i<x_axis+60;i++)
		{
			if(temp[200+i][750+y_axis-1]==1)	//checking hurdles
			{
				flag=1;
				opponent_key=2;			//if hit with hurdle change direction toward left
				break;
			}
		}
		if (flag==0)					//if no hurdle it will move
		{
			y_axis--;
		}
		
		glutPostRedisplay();
}
//upward motion
void upOpp()
{
	int flag=0;
		for(int i=x_axis;i<x_axis+50;i++)
		{
			if(temp[200+i][750+y_axis+60+1]==1)	//checking hurdles
			{
				flag=1;
				opponent_key=3;			//if hurdle is there then change direction toward right
				break;
			}
		}
		if (flag==0)
		{
			y_axis++;						//if no hurdle is there then move on point
		}
		glutPostRedisplay();
}
//left motion
void leftOpp()
{
	int flag=0;
		for(int i=y_axis;i<y_axis+60;i++)
		{
			if (temp[200+x_axis-1][750+i]==1)	//checking hurdles
			{
				flag=1;
				opponent_key=1;				//change direction toward up
				break;
			}
		}
		if(flag==0)
		{
			x_axis--;							// if no hurdle move one point 
		}
		glutPostRedisplay();
}
//right motion
void rightOpp()
{
	int flag=0;
		for(int i=y_axis;i<y_axis+60;i++)
		{
			if(temp[200+x_axis+60+1][750+i]==1)	//checking hurdles
			{
				flag=1;
				opponent_key=4;			//changing direction toward down
				break;
			}
		}
		if(flag==0)
		{
			x_axis++;						//move one point forward
		}
		glutPostRedisplay();
}
//validation for food generation if value in array is 0 it will convert it into 2
void Valid(int i,int j)
{
		if(temp[i][j]==0)
			{
				temp[i][j]=2;
			}
}

void Menu(){
 	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
 			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
 	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
 	DrawString( 330, 400, "Dodge em", colors[GREEN]);
 	DrawString( 330, 350, "1.Start a New Game", colors[RED]);
 	DrawString( 330, 320, "2.See High-Score", colors[RED]);
 	DrawString( 330, 290, "3.Help", colors[RED]);
 	DrawString( 330, 260, "4.Exit", colors[RED]);
	glutSwapBuffers();
}
void Won(){
 	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
 			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
 	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
 	for(int i=50;i<400;i+=100)
	{
		for(int j=760;j>0;j-=100)
			temp[i][j]=2;
	}
	for(int i=460;i<800;i+=100)
	{
		for(int j=60;j<900;j+=100)
			temp[i][j]=2;
	}
	score=0;//reseting values
	level=1;
	lives=3;
	m=0,n=0,x_axis=0,y_axis=0;
	opponent_key=3;
	current_key=2;
	DrawString( 330, 400, "You WON!!!", colors[GREEN]);
 	DrawString( 330, 350, "1.Start a New Game", colors[RED]);
 	DrawString( 330, 320, "2.See High-Score", colors[RED]);
 	DrawString( 330, 290, "3.Help", colors[RED]);
 	DrawString( 330, 260, "4.Exit", colors[RED]);
	glutSwapBuffers();
}
void restart()
{
	if(option==4)
	{
		for(int i=50;i<400;i+=100)//reseting arena
		{
			for(int j=760;j>0;j-=100)
				temp[i][j]=2;
		}
		for(int i=460;i<800;i+=100)
		{
			for(int j=60;j<900;j+=100)
				temp[i][j]=2;
		}
		score=0;//reseting values
		level=1;
		lives=3;
		m=0,n=0,x_axis=0,y_axis=0;
		opponent_key=3;
		current_key=2;
		Menu();
	}
}
void readhighscore()//updating highscore
{
		ifstream obj;//reading score
		obj.open("highscore.txt");//opening of file
		string x;//reading score
		obj>>x;
		obj.close();

		stringstream st(x);//conversion string to int
		int y=0;
		st>>y;
		if(score>y){
		
		
			ofstream obj;//writing score
			obj.open("highscore.txt");
			obj<<score;
			obj.close();
		}
		
		obj.close();
}

void highscores()
{
		glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
 			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
 		glClear (GL_COLOR_BUFFER_BIT); //Update the colors
 		ifstream obj;//reading score
		obj.open("highscore.txt");
		string x;
		DrawString( 330, 400, "High-Score", colors[RED]);
		obj>>x;
		obj.close();

		stringstream st(x);//conversion string to int
		int y=0;
		st>>y;
		if(score>y){
		
		
			ofstream obj;//writing score
			obj.open("highscore.txt");
			obj<<score;
			obj.close();
		}
		
		obj.close();
 		DrawString( 330, 300, x, colors[GREEN]);
 		
 		glutSwapBuffers();
	
}
void help()
{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
 		0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
 	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
 	DrawString( 150, 550, "Help:", colors[GREEN]);
 	DrawString( 170, 500, "The player controls one car and has to drive counter-clockwise,", colors[RED]);
 	DrawString( 170, 470, "avoiding computer-controlled cars whose sole aim is to produce ", colors[RED]);
 	DrawString( 170, 440, "a head-on collision. Each roadway of the maze has four gaps in ", colors[RED]);
 	DrawString( 170, 410, "it — at the top, bottom, left, and right of the screen — the ", colors[RED]);
 	DrawString( 170, 380, "player can use the gaps to change lanes in order to pick up", colors[RED]);	
 	DrawString( 170, 350, "other dots or to avoid the computer-controlled cars", colors[RED]);
 	DrawString( 170, 300, "1. Start a New Game", colors[GREEN]);
 			
 	glutSwapBuffers();
	
}
void stop(){//when game is paused

 
 	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
 			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
 	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
 	DrawString( 330, 400, "Pause", colors[GREEN]);
 	DrawString( 330, 350, "1.Continue", colors[RED]);
 	DrawString( 330, 320, "2.See High-Score", colors[RED]);
 	DrawString( 330, 290, "3.Help", colors[RED]);
 	DrawString( 330, 260, "4.Exit", colors[RED]);
 	DrawString( 330, 230, "5.Start a New Game", colors[RED]);
 	glutSwapBuffers();
	
}
//food generation
void Food(int sx,int sy)//making gift boxes
{
	DrawRectangle(sx, sy, 20, 10, colors[RED]);	
}
//drawing car
void Car(float x,float y,float* color)//car function given by instructor
	{	
	float width = 15; 
	float height = 10; 
	float radius = 5.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect
	}
void Change_Rect1()//when player car is outer round and opponent is inner
{
		if(gap==1)//left gaps
		{
			opponent_key=3;//left turn
			if(rect==rectOpp)
			{
				opponent_key=1;//down turn
			}
		}
		else if(gap==2)//right gaps
		{
			opponent_key=2;//right turn
			if(rect==rectOpp)
			{
				opponent_key=4;//up turn
			}
		}
		else if(gap==3)//down gaps
		{
			opponent_key=3;//down turn
			if(rect==rectOpp)
			{
				opponent_key=2;//right turn
			}
		}
		else if(gap==4)//up gaps
		{
			opponent_key=4;//up turn
			if(rect==rectOpp)
			{
				opponent_key=3;//left turn
			}
		}
}
void Change_Rect2()//when player car is inner round and opponent is outer 
{
	if(gap==1)//left gaps
		{
			opponent_key=2;//right turn
			if(rect==rectOpp)
			{
				opponent_key=4;//down turn
			}
		}
		else if(gap==2)//right gaps
		{
			opponent_key=3;//left turn
			if(rect==rectOpp)
			{
				opponent_key=1;//up turn
			}
		}
		else if(gap==3)//down gaps
		{
			opponent_key=4;//up turn
			if(rect==rectOpp)
			{
				opponent_key=3;//right turn
			}
		}
		else if(gap==4)//up gaps
		{
			opponent_key=1;//down turn
			if(rect==rectOpp)
			{
				opponent_key=2;//left turn
			}
		}
}
//drawing arena
void Arena(int sx, int sy,int l,int k, int s)
{
	int gap_turn=80;
	int swidth = l/2 - gap_turn/2; // half width
	int sheight = 10;
	float *scolor = colors[BROWN];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	//changing the values of array to 1 where arena is made
	for (int i=sy;i<=sy+sheight;i++)//on mazes the values in array is 1
	{
		for (int j=sx+1;j<=sx + swidth ;j++)
			temp[j][i]=1;
	}
	//left boundary
	for (int i = 20; i < 760; ++i)
	{
		temp[20][i]=1;
	}
	//top boundary
	for (int i = 20; i < 770; ++i)
	{
		temp[i][812]=1;
	}
	//right boundary
	for (int i = 20; i < 770; ++i)
	{
		temp[815][i]=1;
	}
	//down boundary
	for (int i = 20; i < 770; ++i)
	{
		temp[i][20]=1;
	}
	DrawRectangle(sx + swidth + gap_turn, sy/**/, swidth, sheight, scolor); // bottom right
	//changing the values of array to 1 where arena is made
	for (int i=sy;i<=sy+sheight;i++)
	{
		for (int j=sx+1 + swidth + gap_turn;j<=sx + swidth + gap_turn+ swidth;j++)
			temp[j][i]=1;
	}
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	//changing the values of array to 1 where arena is made
	for (int i=sy+sheight;i<=sy+sheight+swidth;i++)
	{
		for (int j=sx + swidth*2 + gap_turn;j<=sx + swidth*2 + gap_turn + sheight*2;j++)
			temp[j][i]=1;
	}
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	//changing the values of array to 1 where arena is made
	for (int i=sy+sheight+swidth+gap_turn;i<=sy+sheight+swidth+gap_turn+swidth;i++)
	{
		for (int j=sx + swidth*2 + gap_turn;j<=sx + swidth*2 + gap_turn + sheight*2;j++)
			temp[j][i]=1;
	}
	DrawRectangle(sx + swidth + gap_turn, sy+k, swidth, sheight, scolor); // top left
	//changing the values of array to 1 where arena is made
	for (int i=sy+k;i<=sy+k+sheight;i++)
	{
		for (int j=sx + swidth + gap_turn;j<=sx + swidth + gap_turn + swidth;j++)
			temp[j][i]=1;
	}
	DrawRectangle(sx, sy+s, swidth, sheight, scolor); // top right
	//changing the values of array to 1 where arena is made
	for (int i=sy+s;i<=sy+s+sheight;i++)
	{
		for (int j=sx;j<=sx + swidth;j++)
			temp[j][i]=1;
	}
	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	//changing the values of array to 1 where arena is made
	for (int i=sy+sheight+swidth+gap_turn;i<=sy+sheight+swidth+gap_turn+swidth;i++)
	{
		for (int j=sx-sheight*2;j<=sx-sheight*2 + sheight*2;j++)
			temp[j][i]=1;
	}
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down
	//changing the values of array to 1 where arena is made
	for (int i=sy+sheight;i<=sy+sheight+swidth;i++)
	{
		for (int j=sx-sheight*2;j<=sx-sheight*2 + sheight*2;j++)
			temp[j][i]=1;
	}
}
/*
 * Main Canvas drawing function.
 * */
//Board *b;
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	if(option==1)
	{
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
	//glutDisplayFunc(Menu);

	// calling some functions from util.cpp file to help students
	//cout<<score<<endl;
	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Square at 250,250 position
	//DrawSquare( 250 , 250 ,20,colors[GREEN]); 
	//Display Score
	stringstream ss;//conversion string to int
	ss<<score;
	string scr;
	ss>>scr;
	DrawString( 50, 790, "score="+scr, colors[MISTY_ROSE]);
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(50,670,10,colors[RED]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	stringstream sss;//conversion string to int
	sss<<level;
	string life;
	sss>>life;
	DrawString( 400, 790, "level="+life, colors[MISTY_ROSE]);
	
	stringstream s;//conversion string to int
	s<<lives;
	string sc;
	s>>sc;
	DrawString( 700, 790, "lives="+sc, colors[MISTY_ROSE]);
	// Drawing Player car
	Car(390+m,750+n,colors[GREEN]);
	//drawing opponent car
	Car(200+x_axis,750+y_axis,colors[RED]);
	
	//rounds of player car
	if((390+m>=20&&390+m<=765&&750+n>=20&&750+n<=55)||(390+m>=20&&390+m<=35&&750+n>=20&&750+n<=775)||(390+m>=745&&390+m<=760&&750+n>=20&&750+n<=775)||(390+m>=20&&390+m<=765&&750+n>=735&&750+n<=775))
	{
		rect=4;//outer round
	}
	else if((390+m>=120&&390+m<=650&&750+n>=120&&750+n<=160)||(390+m>=120&&390+m<=140&&750+n>=120&&750+n<=660)||(390+m>=640&&390+m<=660&&750+n>=120&&750+n<=660)||(390+m>=120&&390+m<=650&&750+n>=630&&750+n<=665))
	{
		rect=3;
	}
	else if((390+m>=220&&390+m<=560&&750+n>=530&&750+n<=565)||(390+m>=540&&390+m<=560&&750+n>=220&&750+n<=575)||(390+m>=220&&390+m<=240&&750+n>=220&&750+n<=575)||(390+m>=220&&390+m<=565&&750+n>=220&&750+n<=260))
	{
		rect=2;
	}
	else if(390+m>=320&&390+m<=465&&750+n>=320&&750+n<=475)
	{
		rect=1;//inner round
	}
	else
	{
		rect=5;
	}
	
	//rounds of opponent car
	if((205+x_axis>=20&&200+x_axis<=765&&750+y_axis>=20&&750+y_axis<=55)||(200+x_axis>=25&&200+x_axis<=35&&750+y_axis>=25&&750+y_axis<=775)||(200+x_axis>=750&&200+x_axis<=760&&750+y_axis>=25&&750+y_axis<=775)||(200+x_axis>=25&&200+x_axis<=765&&750+y_axis>=740&&750+y_axis<=775))
	{
		rectOpp=4;//most outer round
	}
	else if((200+x_axis>=125&&200+x_axis<=650&&750+y_axis>=125&&750+y_axis<=160)||(200+x_axis>=125&&200+x_axis<=140&&750+y_axis>=125&&750+y_axis<=660)||(200+x_axis>=645&&200+x_axis<=660&&750+y_axis>=125&&750+y_axis<=660)||(200+x_axis>=125&&200+x_axis<=650&&750+y_axis>=635&&750+y_axis<=665))
	{
		rectOpp=3;
	}
	else if((200+x_axis>=225&&200+x_axis<=560&&750+y_axis>=535&&750+y_axis<=565)||(200+x_axis>=545&&200+x_axis<=560&&750+y_axis>=225&&750+y_axis<=575)||(200+x_axis>=225&&200+x_axis<=240&&750+y_axis>=225&&750+y_axis<=575)||(200+x_axis>=225&&200+x_axis<=565&&750+y_axis>=225&&750+y_axis<=260))
	{
		rectOpp=2;
	}
	else if(200+x_axis>=325&&200+x_axis<=465&&750+y_axis>=325&&750+y_axis<=475)
	{
		rectOpp=1;//most inner round
	}
	else
	{
		rectOpp=0;
	}
	

	if((750+y_axis)>=385&&(750+y_axis)<=400&&(200+x_axis)<=330&&level>1)//left gaps
	{
		gap=1;
	}
	else if((750+y_axis)>=385&&(750+y_axis)<=400&&(200+x_axis)>=450&&level>1)//right gaps
	{
		gap=2;
	}
	else if((200+x_axis)>=385&&(200+x_axis)<=400&&(750+y_axis)<=340)//down gaps
	{
		gap=3;
	}
	else if((200+x_axis)>=385&&(200+x_axis)<=400&&(750+y_axis)>=450)//up gaps
	{
		gap=4;
	}
	else
	{
		gap=0;
	}

	int count=0;
	if(rect>=rectOpp&&rectOpp!=0)//when player car in outer and oppoenent is inner round
	{
		count=1;
		Change_Rect1();
	}
	else if(rect<=rectOpp && rectOpp!=0)//when player car in inner and oppoenent is outer round
	{
		count=2;
		Change_Rect2();
	}
	if(rectOpp==0&&count==2)//will continue its motion
	{
		Change_Rect2();
	}
	if (rectOpp==0&&count==1)//will continue its motion
	{
		Change_Rect1();
	}

	//drawing arena
	Arena(20,10,800,810,810);	
	Arena(120,110,600,610,610);
	Arena(220,210,400,410,410);
	Arena(320,310,200,210,210);
	
	//changing  value 0 to 2 
	for(int i=50;i<400;i+=100)
	{
		for(int j=760;j>0;j-=100)
			Valid(i,j);
	}
	for(int i=50;i<400;i+=100)
	{
		for(int j=760;j>0;j-=100)
		{
					if(temp[i][j]==2)
						Food(i,j);		//drawing food		
		}
	}
	//repeat the same procedure for 2nd half
	for(int i=460;i<800;i+=100)
	{
		for(int j=60;j<900;j+=100)
			Valid(i,j);
	}
	for(int i=460;i<800;i+=100)
	{
		for(int j=60;j<900;j+=100)
		{
			if(temp[i][j]==2)
				Food(i,j);		//drawing food
			
		}
	}
	//draw square at centre of maze
	DrawSquare( 390 , 390 ,60,colors[BROWN]);
	//validating square
	for (int i = 390; i < 390+60; ++i)
	{
		for (int j = 390; j < 390+60; ++j)
		{
			temp[j][i]=1;
		}
	}



	if (current_key==1/*DOWN KEY*/)
	{
		down();
	}
	else if(current_key==2/*RIGHT KEY*/)
	{
		right();
	}
	else if(current_key==3/*LEFT KEY*/)
	{
		left();
	}
	else if(current_key==4/*UP KEY*/)
	{
		up();
	}


	if(level<=2||level==4)
	{
		if (opponent_key==1/*DOWN KEY*/)
		{
			downOpp();
		}
		else if(opponent_key==2/*RIGHT KEY*/)
		{
			rightOpp();
		}
		else if(opponent_key==3/*LEFT KEY*/)
		{
			leftOpp();
		}
		else if(opponent_key==4/*UP KEY*/)
		{
			upOpp();
		}
	}
	//in level 3 car will move with double speed
	if(level==3)
	{
		if (opponent_key==1/*DOWN KEY*/)
		{
			downOpp();
			downOpp();
		}
		else if(opponent_key==2/*RIGHT KEY*/)
		{
			rightOpp();
			rightOpp();
		}
		else if(opponent_key==3/*LEFT KEY*/)
		{
			leftOpp();
			leftOpp();
		}
		else if(opponent_key==4/*UP KEY*/)
		{
			upOpp();
			upOpp();
		}
	}
	if(score==64)//when score is 64 level updated
	{
		level=2;
		for(int i=50;i<400;i+=100)//updating arena
		{
			for(int j=760;j>0;j-=100)
				temp[i][j]=2;
		}
		for(int i=460;i<800;i+=100)
		{
			for(int j=60;j<900;j+=100)
				temp[i][j]=2;
		}
		score=164;//bonus score
	}
	if(score==228)//when score is 228 level updated
	{
		level=3;
		for(int i=50;i<400;i+=100)//updating arena
		{
			for(int j=760;j>0;j-=100)
				temp[i][j]=2;
		}
		for(int i=460;i<800;i+=100)
		{
			for(int j=60;j<900;j+=100)
				temp[i][j]=2;
		}
		score=328;//bonus score
	}
	if(score==392)//when score is 392 level updated
	{
		level=4;
		for(int i=50;i<400;i+=100)//updating arena
		{
			for(int j=760;j>0;j-=100)
				temp[i][j]=2;
		}
		for(int i=460;i<800;i+=100)
		{
			for(int j=60;j<900;j+=100)
				temp[i][j]=2;
		}
		score=492;//bonus score
	}
	if(score==556)//if scpre is 556 player won 
	{
		Won();
	}
	readhighscore();//updating highscore
		
	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
	
}

}
//==========================================================================================================
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {

	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		current_key=3;
	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		current_key=2;
	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		current_key=4;
	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
		current_key=1;
		
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();
}




/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		//file ma current valuescore ki save krni
		exit(1); // exit the program when escape key is pressed.
	}
	else if(key==49){//used in menu
		// glutDisplayFunc(GameDisplay);
		option=1;
	}
	else if(key==50){//used in menu
		option=2;
		highscores();

	}
	else if(key==51)//used in menu
	{
		option=3;
		help();
	}
	else if(key==52)//used in menu & stop
	{
		exit(1);
	}
	else if(key==53)//used in stop
	{
		option=4;
		restart();
	}
	else if(key=='p'||key=='P')//game pause when p is pressed
	{
		option=6;
		stop();
	}
	else if(key==32)//when space is pressed car will move with double speed
	{
		if (current_key==2)
		{
			right();
			right();
		}
		else if(current_key==1)
		{
			down();
			down();
		}
		else if(current_key==3)
		{
			left();
			left();
		}
		else if(current_key==4)
		{
			up();
			up();
		}

	}
	glutPostRedisplay();
}


/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(1000.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	}else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[]) {

	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	srand(time(NULL));
	int width = 840, height = 840;
	

 // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("Rizwan Habib i190603"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	Menu();//menu will display before game display
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	
	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();

	return 1;

}
#endif /* AsteroidS_CPP_ */