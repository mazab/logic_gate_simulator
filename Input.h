#ifndef _INPUT_H
#define _INPUT_H

#include "CMUgraphicsLib\CMUgraphics.h"
#include "Def.h"

class Output;

class Input
{
private:
	Point m_Point;
	char m_Key;
	char* m_String;
	window * m_Window;
	Output * m_Out;

public:
	//constructors:
	//-----------------------------
	Input( window*, Output*);
	
	//destructor:
	//-----------
	~Input();

	//setters:
	//---------
	void setPoint(int r_X,int r_Y);
	void setKey(char r_Key);
	void setWindow(window* r_Window);

	//getters:
	//---------
	Point getPoint();
	char getKey();
	window* getWindow();

	//others:
	//--------
	Point getClick();
	char getKeyStroke();
	char* getString(Point r_P);
	////////////////////////////////////
	buttonstate ButtonStatus(const button btmouse , Point &click);

};

#endif