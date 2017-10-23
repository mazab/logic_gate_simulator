#include "Includes.h"

//-------------------------------------------------------------
void Exit::ReadActionParameters(ApplicationManager *pManager)
{
	//(x,y) Point of the upper left of the confirmation box
	windowWidth =  pManager->getOutput()->getWidthWindow()  ;
	windowHeight = pManager->getOutput()->getHeightWindow() ;
}

//-------------------------------------------------------------
void Exit::Execute(ApplicationManager *pManager)
{
	//calling the ReadActionParameters fn
	ReadActionParameters(pManager);

	int x = (windowWidth + 168 - 400) /2 ;
	int y = (windowHeight- 42  - 150) /2 ;

	//the point the user will click at
	Point p;

	//display the confirmation message for the user
	pManager->getOutput()->drawPopUpWindow("Exit");

	bool end = false;
	// the loop will break only if he pressed YES or NO if not we will wait till a valid click
	while(!end)
	{
		// reads the click from the user
		p = pManager->getInput()->getClick();

		//---------------------------------------------------------------------------------
		if (p.y > (y+110) && p.y < (y+140))
		{
			//if the user press YES
			//------------------------------------------------------
			if(p.x > (x+140) && p.x <(x+260))
			{
				pManager->getOutput()->ExitWindow();
				pManager->setExit(true);
				end = true;
			}
			//------------------------------------------------------

			//if the user press NO 
			//------------------------------------------------------
			else if(p.x >(x+260) && p.x <(x+390))
			{
				end = true ; 
			}
			//------------------------------------------------------
		}
		//---------------------------------------------------------------------------------
	}
}

//-------------------------------------------------------------
void Exit::unExecute(ApplicationManager *pManager)
{}