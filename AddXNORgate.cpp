#include "Includes.h"

AddXNORgate :: AddXNORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);

	switch (A)
	{
	case Add_XNOR_2:

		m_ptrAddedComponent = new XNOR2 (*GfxInfo , r_ptrManager);
		break;

	case Add_XNOR_3:

		m_ptrAddedComponent = new XNOR3 (*GfxInfo , r_ptrManager);
		break;

	case Add_XNOR_4:

		m_ptrAddedComponent = new XNOR4 (*GfxInfo , r_ptrManager);
		break;

	default:
		break;
	} 

	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	r_ptrManager -> pushUndo (this);
}

void AddXNORgate::ReadActionParameters(ApplicationManager* pManager)
{}

void AddXNORgate :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp (m_ptrAddedComponent);
}

void AddXNORgate :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddXNORgate::~AddXNORgate()
{ }
