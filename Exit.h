#ifndef EXIT_H
#define EXIT_H


#include "Action.h"


//Exit class : this class' job is to exit the application
class Exit:public Action
{
private:
	int windowWidth ;
	int windowHeight ;

public:

	//this fn reads the action parameters from the user
	virtual void ReadActionParameters(ApplicationManager *pManager);

	//this fn executes the action (EXIT) to end the program
	virtual void Execute(ApplicationManager *pManager);

	//this fn will have empty body as we will not unExectes this action
	virtual void unExecute(ApplicationManager *pManager);
};

#endif