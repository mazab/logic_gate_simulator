#include "Includes.h"

AddNOTgate::AddNOTgate (Point Center , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);
	m_ptrAddedComponent = new Not(*GfxInfo , r_ptrManager);
	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	
	r_ptrManager -> pushUndo (this);
}

void AddNOTgate::ReadActionParameters(ApplicationManager* pManager)
{ }

void AddNOTgate :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp(m_ptrAddedComponent);
}

void AddNOTgate :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddNOTgate::~AddNOTgate(void)
{ }
