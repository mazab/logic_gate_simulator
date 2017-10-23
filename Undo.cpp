#include "Includes.h"

//-----------------------------------------------------------------

void Undo::ReadActionParameters(ApplicationManager *pManager)
{}

//-----------------------------------------------------------------

void Undo::Execute(ApplicationManager *pManager)
{
	if(pManager->UndoIsEmpty())
	{
		//print message for the user on the status bar
		Point p;
		p.x = 25 ;    p.y = 610;
		pManager->getOutput()->printStringStatusBar("=> Sorry: Undo Stack is Empty <=" , p);
		pManager->getOutput()->MessagePause(2000);
	}
	else
	{
		//get the top action in the stack
		Action* tmp = pManager->popUndo();

		//unExecute this action(remove from lists and form screen etc .. )
		tmp->unExecute(pManager);
		
		//pop the action from the undo stack and push it to redo stack
		pManager->pushRedo(tmp);
	}

	pManager->UpdateInterface();

}

//-----------------------------------------------------------------

void Undo::unExecute(ApplicationManager *pManager)
{}

//-----------------------------------------------------------------