#include "Includes.h"


AddBuffer::AddBuffer (Point Center , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);
	m_ptrAddedComponent = new Buffer (*GfxInfo , r_ptrManager);
	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	
	r_ptrManager -> pushUndo (this);
}


void AddBuffer::ReadActionParameters(ApplicationManager* pManager)
{ }

void AddBuffer :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp(m_ptrAddedComponent);
}

void AddBuffer :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddBuffer::~AddBuffer(void)
{ }
