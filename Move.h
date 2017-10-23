#ifndef MOVE_H
#define MOVE_H

#include "Action.h"
class Component;
class Move :public Action
{
private :
	Component * Used;
	GraphicsInfo Current ;
	GraphicsInfo Old;
	bool First;
	Point p2;
public:
	Move(Component* Used);
	~Move();
	void setUsedComp(ApplicationManager *pManager);

	virtual void ReadActionParameters(ApplicationManager *pManager);

	virtual void Execute(ApplicationManager *pManager);

	virtual void unExecute(ApplicationManager *pManager);

	
};
#endif 
