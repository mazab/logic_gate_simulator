#include "Includes.h"
//==================================
void Move::ReadActionParameters(ApplicationManager *pManager)
{
}
//=============================================
Move::Move(Component* r_Used)
{
	Used = r_Used;
	First=true;
}
//========================================
Move::~Move()
{}
//=============================================

void Move::setUsedComp(ApplicationManager *pManager)
{
	Used=pManager->getselectedcomponent();
}

void Move::Execute(ApplicationManager *pManager)

{
	if(First)
	{
		Point p_status;
		p_status.x = 35;
		p_status.y = 600;
		Used->changeMovingStatus();
		Point p;
		p.x ;
		p.y ;
		Used->setOldGfxInfo(Used->getCurrentGfxInfo());
		do
		{
			pManager->getOutput()->getWindow()->GetMouseCoord(p.x, p.y);
			// (1)--->Update the GfxInfo:
			GraphicsInfo Current_Gfx;
			Current_Gfx.Center.x=p.x;
			Current_Gfx.Center.y=p.y;
			Current_Gfx.UpLeft.x=p.x-  0.5*75;
			Current_Gfx.UpLeft.y=p.y-  0.5*50;
			Current_Gfx.DownRight.x=p.x+  0.5*75;
			Current_Gfx.DownRight.y=p.y+  0.5*50;
			Used->setCurrentGfxInfo(Current_Gfx);
			Used->UpdatePinsGfxInfo();
			
			// (2)--->UpdateInterface:
			pManager->UpdateInterface();

		}while(pManager->getInput()->ButtonStatus(LEFT_BUTTON,p) != BUTTON_DOWN);
		pManager->getOutput()->MessagePause(1000);

		if (!pManager->CheckValidity(p,pManager->getselectedcomponent()))
		{
			pManager->getOutput()->printStringStatusBar("This place you dropped the component to is invalid ",p_status);
			pManager->getOutput()->MessagePause(2000);
			Used->setCurrentGfxInfo(Used->getOldGfxInfo());
			Used->UpdatePinsGfxInfo();
			pManager->UpdateInterface();
		}
		else
		{
			Current=Used->getCurrentGfxInfo();
			Old=Used->getOldGfxInfo();
			pManager->pushUndo(this);
		}
		Used->changeMovingStatus();
		First=false;
		
	}

	else
	{
		GraphicsInfo tmp1 =Old;
		GraphicsInfo tmp2 =Current;
		Used->setCurrentGfxInfo(tmp1);
		Current=tmp1;
		Used->setOldGfxInfo(tmp2);
		Old=tmp2;
		Used->UpdatePinsGfxInfo();
		pManager->UpdateInterface();
		pManager->pushUndo(this);
	}
}
//=======================================================================================================

void Move::unExecute(ApplicationManager *pManager)
{
		GraphicsInfo tmp1 =Old;
		GraphicsInfo tmp2 =Current;
		Used->setCurrentGfxInfo(tmp1);
		Current=tmp1;
		Used->setOldGfxInfo(tmp2);
		Old=tmp2;
		Used->UpdatePinsGfxInfo();
		pManager->UpdateInterface();
}
//=========================================================================================================
