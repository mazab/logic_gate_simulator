//======================================================
#include "Includes.h"
//======================================================

void SimulationMode::ReadActionParameters(ApplicationManager* pManager)
{}

//======================================================

void SimulationMode::Execute(ApplicationManager* pManager)
{
	pManager->setSimulationMode(true) ;
	pManager->UpdateInterface() ;

	ActionType Act = SIMULATION_MODE;

	ExitSimuMode = false ;

	do
	{
		pManager->UpdateInterface() ;

		Act =pManager->SelectSimulationAction();

		ExecuteAction(pManager , Act) ;

		CircuitOperate(pManager) ;		


	}while(! ExitSimuMode && ! pManager->getExit());
}


//======================================================

void SimulationMode::unExecute(ApplicationManager* pManager)
{}

//======================================================

//ActionType SimulationMode::SelectAction(ApplicationManager* pManager)
//{
//	Point p = pManager->getInput()->getClick() ;
//
//	if(p.x >10 && p.x <158)
//	{
//		if(p.y > 50 && p.y < 85)
//		{
//			return EXIT ;
//		}
//		else if(p.y >90 && p.y < 125)
//		{
//			return SAVE ;
//		}
//		else if(p.y>130 && p.y <165)
//		{
//			return DESIGN_MODE ;
//		}
//		else if(p.y >170 && p.y < 205)
//		{
//			return TRUTH_TABLE ;
//		}
//		else
//		{
//			return CANCEL ;
//		}
//	}
//	else
//	{
//		Component* pComp = pManager->getComponentByPoint(p) ;
//		if(pComp == NULL)
//		{
//			return CANCEL ;
//		}
//		else
//		{
//			if(pComp->getName() == SWITCH)
//			{
//				changeSwitchSignal(pComp) ;
//				return CANCEL ;
//			}
//			else
//				return SELECT_COMPONENT ;
//		}
//	}
//}

//======================================================

void SimulationMode::ExecuteAction(ApplicationManager* pManager , ActionType Act)
{
	Action* pAct = NULL;
	switch(Act)
	{
	case(EXIT):
		pAct= new Exit ;
		pAct->Execute(pManager);
		break;

	case(SAVE):
		pAct = new Save ;
		pAct->Execute(pManager);
		break;

	case(DESIGN_MODE):
		ExitSimulationMode(pManager);
		break;

	case(SELECT_COMPONENT):
		pManager->DoCompAction();
		break;

	case(TRUTH_TABLE):
		pAct = new CreateTruthTable;
		pAct->Execute(pManager);
		break;

	case(CANCEL):
		break;
	}
}

//======================================================

void SimulationMode::ExitSimulationMode(ApplicationManager* pManager)
{
	pManager->setSimulationMode(false);
	pManager->getOutput()->drawInterface(pManager->getSimulationMode()) ;
	ExitSimuMode = true ; 
}

//======================================================

void SimulationMode::CircuitOperate(ApplicationManager* pManager)
{
	pManager->simulate() ;
}

//======================================================

void SimulationMode::changeSwitchSignal(Component* pComp)
{
	pComp->Operate() ;
}