//--------------------------------------------------
#include "Includes.h"
//--------------------------------------------------

void ErrorDetector::ReadActionParameters(ApplicationManager *pManager)
{}

//--------------------------------------------------

void ErrorDetector::Execute(ApplicationManager *pManager)
{
	//activating the error detector fn in the ApplicationManager 
	pManager->errorDetector() ;

	//Point represents where to put the Cancel button on the status bar
	//p.y(i.e. the y-component of this point) is not important as it is defined in the Fn in the output class 
	Point p;
	p.x = 1036 - 150;   

	//draw the button Cancel on the status bar
	pManager->getOutput()-> drawImageStatusBar ("images//cancel.jpg" , true , p);

	//print message on the status bar
	p.x = 5;
	p.y = 610;
	pManager->getOutput()->printStringStatusBar("~~ Click Cancel button to leave Error Detection Mode. ~~", p);

	//bool to indicate end of loop (i.e. when the user clicks on the Cancel button) 
	bool end = false ;

	//loop will end only if the user clicks cancel
	//this technique is used to let the user see the highlighted elements before the update screen fn is activated
	while(!end)
	{
		//wait a click form the user
		p = pManager->getInput()->getClick();
		
		//if he clicks on the cancel button
		if ( (p.y > 608) && (p.y < 638) && (p.x > 886) && (p.x < 1006) )
			end = true ;
	}
}

//--------------------------------------------------

void ErrorDetector::unExecute(ApplicationManager *pManager)
{}