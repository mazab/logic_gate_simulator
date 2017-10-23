#include "Includes.h"

AddXORgate :: AddXORgate (Point Center , ActionType A , ApplicationManager* r_ptrManager)
{
	GraphicsInfo* GfxInfo = new GraphicsInfo;
	*GfxInfo = computeGfxInfo(Center);

	switch (A)
	{
	case Add_XOR_2:

		m_ptrAddedComponent = new XOR2 (*GfxInfo , r_ptrManager);
		break;

	case Add_XOR_3:

		m_ptrAddedComponent = new XOR3 (*GfxInfo , r_ptrManager);
		break;

	case Add_XOR_4:

		m_ptrAddedComponent = new XOR4 (*GfxInfo , r_ptrManager);
		break;

	default:
		break;
	} 

	//r_ptrManager -> AddComp (m_ptrAddedComponent);
	r_ptrManager -> pushUndo (this);
}

void AddXORgate::ReadActionParameters(ApplicationManager* pManager)
{ }

void AddXORgate :: Execute (ApplicationManager* pManager)
{
	//Executes the action in case of Redo
	pManager -> AddComp (m_ptrAddedComponent);
}

void AddXORgate :: unExecute (ApplicationManager* pManager)
{
	//unExecutes the action in case of Undo
	pManager -> RemoveComp ( m_ptrAddedComponent -> getID() ); 
}

AddXORgate::~AddXORgate()
{ }