#ifndef _OUTPUT_H
#define _OUTPUT_H

#include "CMUgraphicsLib\CMUgraphics.h"
#include "Def.h"
#include <string>
#include "CMUgraphicsLib\auxil.h"
using namespace std;

class Output
{
private:
	window* ptrWindow;  //pointer to the window

public:

	//constructors:
	//--------------
	Output();
	
	//destructor:
	//------------
	~Output();

	//setters:
	//---------
	void setWindow(window*);

	//getters:
	//--------
	window* getWindow();
	int getWidthWindow();
	int getHeightWindow();

	//others:
	//--------
	void changeBuffering(bool set);
	void drawInterface(bool);                       //this fn is to draw the interface 
	void drawLines(Point ,Point);                   //this fn is to draw lines 
	void setLineColor(bool High);                   //drawing lines in the simulation mode
	void drawComponent(char*,char*,Point);          //this fn is to draw any component and its Label
	void drawPopUpWindow(char*);                    //this fn is to draw the pop up windows in the prog.
	void drawTruthTable(int,int,int,int,STATUS**);  //this fn is to draw the truth table for any circuit
	void drawTruthTable(Point , char*);             //this fn is to draw the truth table for a specified gate
	void drawSubMenu(Point);                        //this fn is to draw gates' sub menu.
	void printStringStatusBar(char* , Point);       //this fn is to draw string on the status bar
	void drawImageStatusBar(char* , bool , Point);  //this fn is to draw picture on the status bar
	void Highlight (Point , Point);                 //this fn is to highLight any gate
	void drawStatusBar();                           //this fn is to draw the image of the status bar.  
	void ExitWindow();                              //this fn is to close the drawing window
	void MessagePause(const unsigned long seconds);
};
#endif