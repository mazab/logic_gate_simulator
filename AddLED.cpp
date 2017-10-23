#include "Includes.h"


AddLED::AddLED (Point Center , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);
	m_ptrAddedComponent = new Led(*GfxInfo , r_ptrManager);
	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	
	r_ptrManager -> pushUndo (this);
}

void AddLED::ReadActionParameters(ApplicationManager* pManager)
{ }

void AddLED :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp(m_ptrAddedComponent);
}

void AddLED :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddLED::~AddLED(void)
{ }
