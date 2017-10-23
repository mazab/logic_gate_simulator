#include "Includes.h"


AddSWITCH::AddSWITCH (Point Center , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);
	m_ptrAddedComponent = new Switch(*GfxInfo , r_ptrManager);
	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	
	r_ptrManager -> pushUndo (this);
}

void AddSWITCH::ReadActionParameters(ApplicationManager* pManager)
{ }

void AddSWITCH :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp(m_ptrAddedComponent);
}

void AddSWITCH :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddSWITCH::~AddSWITCH(void)
{ }
