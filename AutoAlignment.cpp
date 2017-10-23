#include "Includes.h"

//------------------------------------------------------------------
void AutoAlignment::ReadActionParameters(ApplicationManager *pManager)
{
	//get the window width and height from the Application manager throw the output class
	windowWidth = pManager->getOutput()->getWidthWindow();
	windowHeight = pManager->getOutput()->getHeightWindow();

	//number of levels we have in the design
	LevelCount = pManager->getLevelCount();
}

//------------------------------------------------------------------
void AutoAlignment::Execute(ApplicationManager *pManager)
{
	pManager->evacuateLevels() ;
	pManager->fillLevels() ;

	//calling the ReadActionParameters fn
	ReadActionParameters(pManager);

	//distance between every 2 levels
	int emptyLevel_Vertical = (windowWidth - (LevelCount * 75) - 168) / (LevelCount+1);

	//calling the AutoAlign fn in the Application Manager 
	pManager->AutoAlign(emptyLevel_Vertical);
}

//------------------------------------------------------------------
void AutoAlignment::unExecute(ApplicationManager *pManager)
{}