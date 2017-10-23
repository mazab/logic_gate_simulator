//----------------------------------------------------
#include "Includes.h"
#include <fstream>

//----------------------------------------------------

void Load::ReadActionParameters(ApplicationManager *pManager)
{
	windowWidth = pManager->getOutput()->getWidthWindow() ;
	windowHeight = pManager->getOutput()->getHeightWindow() ;
}

//----------------------------------------------------

void Load::Execute(ApplicationManager *pManager)
{
	int x,y;
	int endConnections;

	ReadActionParameters(pManager) ;

	//(x,y) Point of the upper left of the confirmation box
	x = (windowWidth + 168 - 400) /2 ;
	y = (windowHeight- 42  - 150) /2 ;


	//display the load window to let the user write the name of the file he want to load
	pManager->getOutput()->drawPopUpWindow("Load");

	Point p;
	p.x = 500;
	p.y = 292;

	string fileName ;

	fileName = pManager->getInput()->getString(p);

	ifstream in;

	bool end = false;
	// the loop will break only if he pressed YES or NO if not we will wait till a valid click
	while(!end)
	{
		// reads the click from the user
		p = pManager->getInput()->getClick();

		if (p.y > (y+110) && p.y < (y+140))
		{
			//--------------------------------------------------------------------
			//if the user press YES
			if(p.x > (x+140) && p.x <(x+260))
			{
				//open the file with the name that user wrote
				in.open(fileName);

				//calling the Load fn in the ApplicationManager
				pManager->load(in) ;

				//closing the file
				in.close() ;

				//set end to true to end the loop
				end = true;
			}
			//--------------------------------------------------------------------
			//if the user press NO 
			else if(p.x >(x+260) && p.x <(x+390))
			{
				end = true ; 
			}
			//--------------------------------------------------------------------
		}
	}
}

//----------------------------------------------------

void Load::unExecute(ApplicationManager *pManager)
{}
