#ifndef _ADD_COMPONENT_H
#define _ADD_COMPONENT_H

#include "Action.h"

class Component;

class AddComponent :  public Action
{
protected:
	Component* m_ptrAddedComponent;
public:
	AddComponent();
	virtual void ReadActionParameters(ApplicationManager* pManager);
	GraphicsInfo computeGfxInfo(Point center);
	Component* getAddedComponent();
	virtual void Execute(ApplicationManager* pMangaer);
	virtual void unExecute(ApplicationManager* pMangaer);
};

#endif

