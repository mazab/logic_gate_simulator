#include "Includes.h"

AddNORgate :: AddNORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);

	switch (A)
	{
	case Add_NOR_2:

		m_ptrAddedComponent = new NOR2 (*GfxInfo , r_ptrManager);
		break;

	case Add_NOR_3:

		m_ptrAddedComponent = new NOR3 (*GfxInfo , r_ptrManager);
		break;

	case Add_NOR_4:

		m_ptrAddedComponent = new NOR4 (*GfxInfo , r_ptrManager);
		break;

	default:
		break;
	} 

	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	r_ptrManager -> pushUndo (this);
}

void AddNORgate::ReadActionParameters(ApplicationManager* pManager)
{}

void AddNORgate :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp (m_ptrAddedComponent);
}

void AddNORgate :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddNORgate::~AddNORgate()
{ }
