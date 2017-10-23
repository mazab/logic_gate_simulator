//----------------------------------------------------
#include "Includes.h"
#include <fstream>

//----------------------------------------------------

void Save::ReadActionParameters(ApplicationManager *pManager)
{
	windowWidth = pManager->getOutput()->getWidthWindow();
	windowHeight = pManager->getOutput()->getHeightWindow();
}

//----------------------------------------------------

void Save::Execute(ApplicationManager *pManager)
{
	int x,y;

	//make the levels
	pManager->evacuateLevels() ;
	pManager->fillLevels() ; 

	//calling the read action parameters fn
	ReadActionParameters(pManager);

	//(x,y) Point of the upper left of the confirmation box
	x = (windowWidth + 168 - 400) /2 ;
	y = (windowHeight- 42  - 150) /2 ;

	//char* represents the name of the file to save in
	string fileName ;

	ofstream out;

	//the point of the upper left of the string box to write at in the PopUpWindow "Save"
	Point p;
	p.x = 500;     
	p.y = 292;

	//show the save window to let the user write the name of the file
	pManager->getOutput()->drawPopUpWindow("Save");
	fileName = pManager->getInput()->getString(p);


	//bool to determine when to end the loop (the loop will end in 2 cases:=> 1.press YES , 2.press NO)
	bool end = false;

	// the loop will break only if he pressed YES or NO if not we will wait till a valid click
	while(!end)
	{
		// reads the click from the user
		p = pManager->getInput()->getClick();

		//-------------------------------------------------------------------------------------
		if (p.y > (y+110) && p.y < (y+140))
		{
			
			//if the user press YES
			//---------------------------------------------------------------------------------
			if(p.x > (x+140) && p.x <(x+260))
			{
				//make a file with the name the user specified a couple of lines ago
				out.open(fileName) ;

				//calling the save fn in the Application Manager 
				pManager->save(out);

				//print -1 to indicate end of the file
				out<<"-1"<<endl;

				//close the file
				out.close();

				//set end to true to end the loop
				end = true;
			}
			//---------------------------------------------------------------------------------

			//if the user press NO 
			//---------------------------------------------------------------------------------
			else if(p.x >(x+260) && p.x <(x+390))
			{
				//set end to true to end the loop
				end = true ; 
			}
			//---------------------------------------------------------------------------------
		}
		//-------------------------------------------------------------------------------------
	}
}

//----------------------------------------------------

void Save::unExecute(ApplicationManager *pManager)
{}
