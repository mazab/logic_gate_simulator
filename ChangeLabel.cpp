//=======================
#include "Includes.h"
//============================
ChangeLabel::ChangeLabel()
{
 First = true;
};
//================================
ChangeLabel::~ChangeLabel()
{};
//====================================
void ChangeLabel::ReadActionParameters(ApplicationManager *pManager)
{
}

void ChangeLabel::setUsedComp(ApplicationManager *pManager)
{
	Used=pManager->getselectedcomponent();
}


void ChangeLabel::Execute(ApplicationManager * pManager)
{
	Input* PtrInput = pManager->getInput();
	Output* PtrOutput = pManager->getOutput();
	
	//==========================================
	if (First)
	{
	setUsedComp(pManager);
	Used->setOldLabel(Used->getCurrentLabel()); //for unexecute
	OldLabel=Used->getOldLabel();
	PtrOutput->drawPopUpWindow("editLabel");
	Point p;
	p.x = 499;		p.y = 293;
	char* temp = PtrInput -> getString(p);
	Used->setCurrentLabel(temp);
	bool exit = false;

	while ( !exit )
						
		{
			Point mouseClick = PtrInput -> getClick();

			if ( ((mouseClick.x > 662) && (mouseClick.x < 792) && (mouseClick.y > 336) && (mouseClick.y < 366)) || (pManager->getInput()->getKey() == (char)13) )
				exit = true;

		}
	
	CurrentLabel=Used->getCurrentLabel();
	First=false;
	pManager->pushUndo(this);
	}
	//=====================================================================================
	else            //not the first time
	{
		char*tmp1=OldLabel;
		char*tmp2=CurrentLabel;
		Used->setCurrentLabel(tmp1);
		CurrentLabel=tmp1;
		Used->setOldLabel(tmp2);
		OldLabel=tmp2;
	}
}


void ChangeLabel::unExecute(ApplicationManager *pManager)
{
		char*tmp1=OldLabel;
		char*tmp2=CurrentLabel;
		Used->setCurrentLabel(tmp1);
		CurrentLabel=tmp1;
		Used->setOldLabel(tmp2);
		OldLabel=tmp2;
}


