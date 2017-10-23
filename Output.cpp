//----------------------------------------------------------

#include "Includes.h"

//--------------------------------------------------------

Output::Output()
{
	ptrWindow = new window(1036 , 644 , 10 , 10);
	//ptrWindow->SetBuffering(true);
}

//---------------------------------------------------------
void Output::setWindow(window * rWindow)
{
	ptrWindow = rWindow;
}

//---------------------------------------------------------

window* Output::getWindow()
{
	return ptrWindow;
}

//----------------------------------------------------------

int Output::getWidthWindow()
{
	return ptrWindow->GetWidth();
}

//----------------------------------------------------------

int Output::getHeightWindow()
{
	return ptrWindow->GetHeight();
}

//----------------------------------------------------------
void Output::changeBuffering(bool set)
{
	if(set)
		ptrWindow->SetBuffering(true);
	else
	{
		ptrWindow->UpdateBuffer();
		ptrWindow->SetBuffering(false);
	}
}
//----------------------------------------------------------
void Output::drawInterface(bool simuMode)
{
	// this fn draw the interface as a picture with height and width of the window
	int w = ptrWindow->GetWidth();
	int h = ptrWindow->GetHeight();

	if(simuMode == false)
		ptrWindow->DrawImage("images//designMode.jpg" , 0 ,0 , w ,h);
	else
		ptrWindow->DrawImage("images//simuMode.jpg" , 0 ,0 , w ,h);

	ptrWindow->SetPen(LIGHTGRAY);
	for(int x= 168 ; x<= 1036 ; x+=14)
		ptrWindow->DrawLine(x,0,x,602);
	for(int y=0 ; y<=602 ; y+=14)
		ptrWindow->DrawLine(168,y,1036,y);

	//ptrWindow->UpdateBuffer();
}

//----------------------------------------------------------

void Output::drawLines(Point start, Point end)
{
	ptrWindow->DrawLine(start.x , start.y , end.x , end.y);
	//ptrWindow->UpdateBuffer();
}
//----------------------------------------------------------
void Output::setLineColor(bool High)
{
	if(!High)
		ptrWindow->SetPen(BLUE , 3) ;
	else
		ptrWindow->SetPen(RED , 3) ;
}
//----------------------------------------------------------

void Output::drawComponent(char* path , char* label , Point p)
{
	//the point p is the center of the gate and the drawImage fn draws from the upperLeft
	//ptrWindow->SetBuffering(true);
	int upLeft_x_comp = p.x - ((int) 0.5*75);
	int upLeft_y_comp = p.y - ((int) 0.5*50);

	//we want to put the label under the gate in the center
	//we get the width of the string to put it under the gate in the center
	int LabelWidth;
	int LabelHeight;
	ptrWindow->GetStringSize(LabelWidth , LabelHeight , label);

	int upLeft_x_label = upLeft_x_comp + ( 75 - LabelWidth )/2 ;
	int upLeft_y_label = upLeft_y_comp + 52 ;

	//draws the component according to the new coordinates
	ptrWindow->DrawImage(path , upLeft_x_comp , upLeft_y_comp , 75 , 50);
	//ptrWindow->UpdateBuffer();


	//draw the label according to the new coordinates
	ptrWindow->SetPen(BLUE , 3);
	ptrWindow->SetFont(14 , BOLD , BY_NAME , "Arial" );
	ptrWindow->DrawString(upLeft_x_label , upLeft_y_label , label);
	//ptrWindow->UpdateBuffer();
}

//----------------------------------------------------------

void Output::drawPopUpWindow(char* message)
{
	int x,y;
	string path;
	x = (ptrWindow->GetWidth() + 168 - 400) /2;
	y = (ptrWindow->GetHeight() - 42 - 150) /2;

	//draws the Exit confirmation box
	if (message == "Exit")
		path = "images//exitConfirm.jpg";

	//draws the error message
	else if (message == "Error")
		path = "images//Error.jpg";

	//draws the save box 
	else if (message == "Save")
		path = "images//Save.jpg";

	//draws the load box
	else if (message == "Load")
		path = "images//Load.jpg";

	//draws the edit label box
	else if (message == "editLabel")
		path = "images//editLabel.jpg";

	//execute the drawing of the message
	ptrWindow->DrawImage(path , x , y );
	//ptrWindow->UpdateBuffer();
}

//----------------------------------------------------------

void Output::printStringStatusBar(char* text,Point p)
{
	int string_width ;
	int string_height ;

	int x;
	int y;

	ptrWindow->GetStringSize(string_width , string_height , text );

	//the upper left of the string 
	x = p.x ; 
	//the y-coordinates is fixed to put the string in the center of the height of status bar
	y = 602 + (42 - string_height)/2 ;

	//executes the drawing string issue
	ptrWindow->SetPen(BLACK , 3);
	ptrWindow->SetFont(16 , BOLD , BY_NAME , "Arial" );
	ptrWindow->DrawString( x , y , text);
	//ptrWindow->UpdateBuffer();
}

//----------------------------------------------------------

void Output::drawImageStatusBar(char* path , bool isButton , Point p)
{
	//2 types of images can be drawn on the status bar

	//type 1: buttons on the status bar (like remove gate , edit label)
	//--------
	//note: the y-component is const to make it aligned
	if(isButton)
	{
		ptrWindow->DrawImage(path , p.x , 608);
		//ptrWindow->UpdateBuffer();
	}

	//type 2: the picture of the component resized to scale about -27%
	//--------
	//note: the y-component of the point is const to put the pic in the center of the statusBar
	else 
	{
		ptrWindow->DrawImage(path , p.x , 607 , 48 , 32);
		//ptrWindow->UpdateBuffer();
	}
}

//----------------------------------------------------------

void Output::drawSubMenu(Point p)
{
	// draws the subMenu (contains the types of gates i.e. 2,3,4 inputs)
	string path = "images//subMenu.jpg";
	ptrWindow->DrawImage( path , p.x , p.y );
	//ptrWindow->UpdateBuffer();
}

//----------------------------------------------------------

Output::~Output()
{
	delete ptrWindow;
}

//----------------------------------------------------------

void Output::ExitWindow()
{
	ptrWindow->SetWaitClose(false);
}

//----------------------------------------------------------

void Output::Highlight (Point UpLeft , Point LowerRight )
{
	int n = 2;  //thikness of the line

	// this fn is to highLight a gate 
	 ptrWindow -> SetPen(BLUE , n);

	// this fn draws 4 borders , color red , thickness 2 , at the 4 borders of the gates
     ptrWindow -> DrawLine (UpLeft.x - n, UpLeft.y , UpLeft.x - n , LowerRight.y);		//the north side !!
     ptrWindow -> DrawLine (LowerRight.x + n , UpLeft.y , LowerRight.x + n , LowerRight.y);  //the east side !!
     ptrWindow -> DrawLine (UpLeft.x , UpLeft.y - n , LowerRight.x , UpLeft.y - n);	//the west side !!
     ptrWindow -> DrawLine (UpLeft.x , LowerRight.y + n , LowerRight.x , LowerRight.y + n);  //the south side !!
	 //ptrWindow->UpdateBuffer();
}

//----------------------------------------------------------

void Output::drawTruthTable(int rowsCount , int columnsCount , int SwitchCount ,int  LedCount ,STATUS** ptrGrid)
{
	//the width and the height of the window in which the truth table will appear
	int win_width , win_height ;

	//dimensions of a cell in the truthtable
	int cell_width = 50 ;
	int cell_height = 20 ;

	//calculating the dimensions of the window
	win_width = (columnsCount*cell_width) +20; 
	win_height = (rowsCount*cell_height) + 20 ;

	//creating the window with the required data
	window* truthTable = new window(win_width , win_height , 10 , 10 ) ;
	truthTable->ChangeTitle("Truth Table");

	//drawing the truth table it self
	//setting the pen to light gray and the thickness to 1px
	truthTable->SetPen(LIGHTGRAY , 1) ;

	for(int i=1 ; i<SwitchCount ; i++)
	{
		truthTable->DrawLine(10+(i*cell_width) ,10 , 10+(i*cell_width),win_height-10 );
	}

	for(int j=1 ; j<LedCount ; j++)
	{
		truthTable->DrawLine(10+((j+SwitchCount)*cell_width) , 10 , 10+((j+SwitchCount)*cell_width) , win_height-10 );
	}

	for(int k=1 ;k<rowsCount-1 ;k++)
	{
		truthTable->DrawLine(10 ,10+((k+1)*cell_height) , win_width-10 ,10+((k+1)*cell_height) );
	}

	//drawing the boders of the truth table
	//setting the pen to balck and the thickness to 2px
	truthTable->SetPen(BLACK , 2) ;

	truthTable->DrawLine(10 , 10 , win_width-10 , 10);
	truthTable->DrawLine(10 , win_height-10 , win_width-10 , win_height-10 );
	truthTable->DrawLine(10 , 10 , 10 , win_height-10);
	truthTable->DrawLine(win_width-10 , 10 , win_width-10 , win_height-10);

	truthTable->DrawLine(10 ,10+cell_height , win_width-10 ,10+cell_height );
	truthTable->DrawLine( 10+(SwitchCount*cell_width) , 10 , 10+(SwitchCount*cell_width) , win_height-10  );


	//writing to the truth table
	truthTable->SetFont(16 , PLAIN , BY_NAME , "Times New Roman" );

	//writing the header of the truth table(the input part)
	for(int t=0 ; t<SwitchCount ; t++)
	{
		truthTable->DrawString(30+(t*cell_width),12,"I");
		truthTable->DrawInteger(37+(t*cell_width),12, t);
	}

	//writing the header of the truth table(the output part)
	for(int r=0 ; r<LedCount ; r++)
	{
		truthTable->DrawString(30+((r+SwitchCount)*cell_width),12,"O");
		truthTable->DrawInteger(41+((r+SwitchCount)*cell_width),12, r);
	}

	//printing the 0's and 1's inside the table
	for(int i=0 ; i<rowsCount-1 ; i++)
	{
		for(int j= 0 ; j<columnsCount ; j++)
		{
			//if the signal is LOW .. then print 0
			if(ptrGrid[i][j] == LOW)
				truthTable->DrawInteger(30+(j*cell_width) , 12+((i+1)*cell_height) , 0);

			//if the signal is HIGH .. then print 1
			else 
				truthTable->DrawInteger(30+(j*cell_width) , 12+((i+1)*cell_height) , 1);
		}
	}

	//make the window waits till a click is clikcked to let the user see the truth tablr
	int x,y;

	truthTable->WaitMouseClick(x,y);
	truthTable->SetWaitClose(false) ;
	//deleting the pointer to the window
	delete truthTable ;
}

//----------------------------------------------------------

void Output::drawStatusBar()
{
	ptrWindow->DrawImage("images//StatusBar.jpg", 0 , 602);
	//ptrWindow->UpdateBuffer();
}
//===========================================================
void Output::MessagePause(const unsigned long seconds)
{
	Pause(seconds);
}

//===========================================================
void Output::drawTruthTable(Point p , char* path)
{
	ptrWindow->DrawImage(path , p.x , p.y );
	//ptrWindow->UpdateBuffer();
	ptrWindow->WaitMouseClick(p.x, p.y);
}
