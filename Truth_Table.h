#ifndef TRUTH_TABLE_H
#define TRUTH_TABLE_H

#include "Action.h"
class Component;
class Truth_Table:public Action
{
private :
	Component * Used;
public:
	Truth_Table();
	~Truth_Table();
	void setUsedComp(ApplicationManager *pManager);

	virtual void ReadActionParameters(ApplicationManager *pManager);

	virtual void Execute(ApplicationManager *pManager);

	virtual void unExecute(ApplicationManager *pManager);//will be empty 

};
#endif 