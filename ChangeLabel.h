#ifndef CHANGELABEL_H
#define CHANGELABEL_H

#include "Action.h"
class Component;
class ChangeLabel:public Action
{
private :
	char* OldLabel;
	char * CurrentLabel;
	Component * Used;
	bool First ;
public:
	ChangeLabel();
	void setUsedComp(ApplicationManager *pManager);

	virtual void ReadActionParameters(ApplicationManager *pManager);

	virtual void Execute(ApplicationManager *pManager);

	virtual void unExecute(ApplicationManager *pManager);
	~ChangeLabel();
	
};
#endif 