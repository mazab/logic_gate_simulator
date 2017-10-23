#include "Includes.h"

AddORgate :: AddORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);

	switch (A)
	{
	case Add_OR_2:

		m_ptrAddedComponent = new OR2 (*GfxInfo , r_ptrManager);
		break;

	case Add_OR_3:

		m_ptrAddedComponent = new OR3 (*GfxInfo , r_ptrManager);
		break;

	case Add_OR_4:

		m_ptrAddedComponent = new OR4 (*GfxInfo , r_ptrManager);
		break;

	default:
		break;
	} 

	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	r_ptrManager -> pushUndo (this);
}

void AddORgate::ReadActionParameters(ApplicationManager* pManager)
{}

void AddORgate :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp(m_ptrAddedComponent);
}

void AddORgate :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddORgate::~AddORgate()
{ }
