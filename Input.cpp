
//----------------------------------
#define ENTER 13
#define BACKSPACE 8
//----------------------------------
#include "Includes.h"
//----------------------------------
Input::Input(window* rWindow, Output* r_Out)
{
	m_Point.x = 0;
	m_Point.y = 0;
	m_Key = ' ';
	m_Window = rWindow;
	m_Out = r_Out;
}


Input::~Input()
{}

void Input::setPoint(int rX, int rY)
{
	m_Point.x = rX;
	m_Point.y = rY;
}

void Input::setKey(char rKey)
{
	m_Key = rKey;
}

void Input::setWindow(window *rWindow)
{
	m_Window = rWindow;
}

Point Input::getPoint()
{
	return m_Point;
}

char Input::getKey()
{
	return m_Key;
}

window* Input::getWindow()
{
	return m_Window;
}

Point Input::getClick()
{
	m_Window->WaitMouseClick(m_Point.x , m_Point.y);
	return m_Point;
}

char Input::getKeyStroke()
{
	m_Window->WaitKeyPress(m_Key);
	return m_Key;
}


//This function gets string from the screen character by character, starts from a geven point r_P:
char* Input::getString(Point r_P)
{
	char k =' ';
	char* tmp = new char[100]; //the string
	int i = 0; // Walker
	int hight(0), width(0); // the string's dimantions
	
	while( (k != ENTER) && (k != '$') && i<100 ) //If the user didn't finish:
	{
		m_Window->WaitKeyPress(k);
		
		if(k != BACKSPACE)
			tmp[i++]=k; //push the last key at the end of the string
			
		else
			if(i != 0) //If the backSpace didn't presed at the begining of the string: 
				tmp[--i]=' ';

		//====
		// This part of code is drawing, it is the only case the input class
		// draw somthing in the screen!

		m_Window->GetStringSize(width, hight, tmp); //get the size of the string

		tmp[i] = '\0'; //Define the string's end point

		//Drawing a wight- rectangle with the same size of the string:
		m_Window->SetPen(WHITE , 3);
		m_Window->DrawRectangle(r_P.x,r_P.y,r_P.x+290, r_P.y+26, FILLED);
		m_Window->UpdateBuffer();

		//draw the updated string:
		m_Window->SetPen(BLACK , 3);
		m_Window->SetFont(25 , PLAIN , BY_NAME , "Arial");
		m_Window->DrawString(r_P.x, r_P.y, tmp);
		m_Window->UpdateBuffer();
		//===========================================================
		
	}
		tmp[i-1] = '\0';
		return tmp;
}

//-----------------------------------------------------
buttonstate Input ::ButtonStatus(const button btMouse , Point  &click)
{
	buttonstate St = m_Window->GetButtonState(btMouse, click.x, click.y);
		return St;
}
//===================================================================================







