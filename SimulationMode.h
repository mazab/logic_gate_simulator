#ifndef SIMULATIONMODE_H
#define SIMULATIONMODE_H

#include "Action.h"


class SimulationMode:public Action
{
	bool ExitSimuMode ;
public:
	virtual void ReadActionParameters(ApplicationManager *pManager);
	virtual void Execute(ApplicationManager* pManager);
	virtual void unExecute(ApplicationManager* pManager);
	//ActionType SelectAction(ApplicationManager* pManager);
	void ExecuteAction(ApplicationManager* pManager , ActionType);
	void ExitSimulationMode(ApplicationManager* pManager);
	void CircuitOperate(ApplicationManager* pManager);
	void changeSwitchSignal(Component*);
};

#endif