#include "Includes.h"

//-----------------------------------------------------------------

void Redo::ReadActionParameters(ApplicationManager *pManager)
{}

//-----------------------------------------------------------------

void Redo::Execute(ApplicationManager *pManager)
{
	if(pManager->RedoIsEmpty())
	{
		//print a message on the status bar for the user.
		Point p;
		p.x = 25 ;    p.y = 610;
		pManager->getOutput()->printStringStatusBar("=> Sorry: Redo Stack is Empty <=" , p);
		pManager->getOutput()->MessagePause(2000);
	}
	else
	{
		//get the top action in the stack
		Action* tmp = pManager->popRedo();

		//unExecute this action(remove from lists and form screen etc .. )
		tmp->Execute(pManager);
		
		//pop the action from the undo stack and push it to redo stack
		pManager->pushUndo(tmp);
	}
	pManager->UpdateInterface();

	
}

//-----------------------------------------------------------------

void Redo::unExecute(ApplicationManager *pManager)
{}

//-----------------------------------------------------------------