#ifndef ERRORDETECTOR_H
#define ERRORDETECTOR_H

#include "Action.h"


//class error detector: detects the errors in the circuit and highLight them
class ErrorDetector:public Action
{
public:

	//this fn reads the action parameters from the user
	virtual void ReadActionParameters(ApplicationManager *pManager);

	//this fn executes the action (ErrorDetector) to end the program
	virtual void Execute(ApplicationManager *pManager);

	//this fn will have empty body as we will not unExectes this action
	virtual void unExecute(ApplicationManager *pManager);
};

#endif